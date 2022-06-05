#include "http.h"
#include "include/list.h"

#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <ctype.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdarg.h>

#define ROOT_DIR "/home/jack/www"
#define SERV_PORT 8080
#define SERV_ADDR 0

const char* METHOD_GET = "GET";
const char* METHOD_POST = "POST";

struct header_node {
  const char* key;
  const char* value;
  struct list_head list;
};

struct header_node* header_get(struct list_head* head, const char* key) {
  struct list_head* iter;
  list_for_each(iter, head) {
    struct header_node* node = container_of(iter, struct header_node, list);
    if (strcasecmp(node->key, key) == 0) {
      return node;
    }
  }
  return NULL;
}

void header_add(struct list_head* head, const char* key, const char* val) {
  struct header_node* node =
      (struct header_node*)malloc(sizeof(struct header_node));
  node->key = new_str(key);
  node->value = new_str(val);
  list_add_tail(&node->list, head);
}

/**
GET /wireshark-labs/HTTP-wireshark-file1.html HTTP/1.1\r\n
Host: gaia.cs.umass.edu\r\n
Connection: keep-alive\r\n
User-Agent: Mozilla/5.0\r\n
Accept: text/html\r\n
Accept-Encoding: gzip, deflate\r\n
Accept-Language: zh-CN,zh;q=0.9\r\n
\r\n
*/
typedef struct request {
  int clnt_fd;
  struct sockaddr_in clnt_addr;
  utime_t request_at;
  pthread_t thread;
  const char* method;
  const char* version;
  const char* path;
  const char* query;
  const char* host;
  const char* user_agent;
  struct list_head header_list;
} request_t;

/**
< HTTP/1.1 200 OK
< Date: Sun, 05 Jun 2022 05:19:56 GMT
< Server: Apache
< Last-Modified: Tue, 12 Jan 2010 13:48:00 GMT
< ETag: "51-47cf7e6ee8400"
< Accept-Ranges: bytes
< Content-Length: 81
< Cache-Control: max-age=86400
< Expires: Mon, 06 Jun 2022 05:19:56 GMT
< Connection: Keep-Alive
< Content-Type: text/html
 */
typedef struct response {
  request_t* request;
  struct http_status status;
  struct list_head header_list;
  int body_fd;  // sending body bytes from reading fd
  off_t body_length;
} response_t;

int serv_fd;
struct sockaddr_in serv_addr;

void free_header_list(struct list_head* head) {
  struct list_head *iter, *next;
  list_for_each_safe(iter, next, head) {
    struct header_node* node = container_of(iter, struct header_node, list);
    free((void*)node->key);
    free(node);
  }
}

void free_request(request_t* req) {
  free((void*)req->version);
  free((void*)req->path);
  free((void*)req->query);
  free_header_list(&req->header_list);
}

void free_response(response_t* res) { free_header_list(&res->header_list); }

void setup_socket() {
  serv_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (serv_fd < 0) die("socket");

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(8080);
  serv_addr.sin_addr.s_addr = INADDR_ANY;

  int on = 1;
  if (setsockopt(serv_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on) < 0) {
    die("setsocket");
  }

  if (bind(serv_fd, (struct sockaddr*)&serv_addr, sizeof serv_addr) < 0)
    die("bind");

  if (listen(serv_fd, 5) < 0) die("listen");
}

int read_line(int fd, char* buf, int size) {
  int i = 0;
  char c = '\0';
  int n;

  while ((i < size - 1) && (c != '\n')) {
    n = recv(fd, &c, 1, 0);
    if (n <= 0) break;
    if (c == '\r') {
      n = recv(fd, &c, 1, MSG_PEEK);
      if (n > 0 && c == '\n') {
        recv(fd, &c, 1, 0);
      } else {
        c = '\n';
      }
    }
    buf[i++] = c;
  }
  buf[i] = '\0';
  return i;
}

void write_seperator(int fd) { send(fd, "\r\n", 2, 0); }

void write_line(int fd, const char* fmt, ...) {
  char buf[BUFSIZ];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buf, BUFSIZ, fmt, args);
  va_end(args);
  int len = strlen(buf);
  send(fd, buf, len, 0);
}

void write_status(int fd, struct http_status status) {
  write_line(fd, "HTTP/1.0 %u %s\r\n", status.code, status.msg);
}

void write_header(int fd, struct list_head* head) {
  struct list_head* iter;
  list_for_each(iter, head) {
    struct header_node* node = container_of(iter, struct header_node, list);
    write_line(fd, "%s: %s\r\n", node->key, node->value);
  }
  write_seperator(fd);
}

void write_file_body(int fd, int body) {
  char buf[1024];
  ssize_t sz = read(body, buf, sizeof buf);
  while (sz > 0) {
    send(fd, buf, sz, 0);
    sz = read(body, buf, sizeof buf);
  }
  close(body);
}

void write_string_body(int fd, const char* str) {
  send(fd, str, strlen(str), 0);
}

int parse_request(request_t* req) {
  char buf[BUFSIZ];
  char* del = buf;
  int fd = req->clnt_fd;
  int len = read_line(fd, buf, sizeof buf);
  if (len == 0) return -1;

  const char* method = del;
  del = strchr(del, ' ');
  *del++ = '\0';
  if (strcasecmp(method, "GET") == 0) {
    req->method = METHOD_GET;
  } else if (strcasecmp(method, "POST") == 0) {
    req->method = METHOD_POST;
  } else {
    req->method = new_str(method);
  }

  const char* url = del;
  del = strchr(del, ' ');
  *del++ = '\0';

  char* query_str = strchr(url, '?');
  if (query_str != NULL) {
    req->query = new_str(query_str + 1);
    *query_str = '\0';
  }
  req->path = new_str(url);

  const char* http_ver = del;
  req->version = new_str(http_ver);

  len = read_line(fd, buf, sizeof buf);
  while (len > 0 && strcmp("\n", buf)) {
    char* header_line = new_str(buf);
    del = strchr(header_line, ':');
    if (del == NULL || del[1] != ' ') continue;
    del[0] = del[1] = '\0';
    const char* key = header_line;
    const char* val = del + 2;
    struct header_node* node =
        (struct header_node*)malloc(sizeof(struct header_node));
    node->key = key;
    node->value = val;
    list_add(&node->list, &req->header_list);

    if (cmpcase(key, ==, "user-agent")) {
      req->user_agent = val;
    } else if (cmpcase(key, ==, "host")) {
      req->host = val;
    }

    len = read_line(fd, buf, sizeof buf);
  }
  return 0;
}

struct http_status handle_response(request_t* req, response_t* res) {
  if (req->method == METHOD_GET) {
    struct stat st;
    char uri[BUFSIZ];
    snprintf(uri, sizeof uri, ROOT_DIR "%s", req->path);
    if (uri[strlen(uri) - 1] == '/') {
      strcat(uri, "index.html");
    }
    if (stat(uri, &st)) {
      return StatusNotFound;
    }
    if ((st.st_mode & __S_IFMT) == __S_IFDIR) {
      strcat(uri, "/index.html");
    }
    // serve html
    res->body_length = st.st_size;
    res->body_fd = open(uri, O_RDONLY, S_IRUSR | S_IRGRP);
    return StatusOK;
  } else if (req->method == METHOD_POST) {
    // cgi
  } else {
    //
  }
  return StatusInternalServerError;
}

void make_response(response_t* res) {
  header_add(&res->header_list, "Server", "MyHttpd 0.1");
  // header_add(&res->header_list, "Date", fmt_now());
  // header_add(&res->header_list, "Content-Type", "text/html");

  char buf[BUFSIZ];
  int fd = res->request->clnt_fd;
  if (res->status.code == StatusOK.code) {
    if (res->body_length == 0) {
      res->status = StatusNoContent;
    } else {
      snprintf(buf, sizeof buf, "%ld", res->body_length);
      header_add(&res->header_list, "Content-Length", buf);
    }
  }

  write_status(fd, res->status);
  write_header(fd, &res->header_list);
  if (res->status.code == StatusOK.code) {
    write_file_body(fd, res->body_fd);
  } else if (res->status.code == StatusNotFound.code) {
    write_string_body(fd, BODY_NOT_FOUND);
  } else if (res->status.code == StatusNoContent.code) {
    write_string_body(fd, "");
  } else {
  }
}

void* accept_request(void* args) {
  request_t* req = (request_t*)args;
  if (parse_request(req)) {
    return NULL;
  }

  int fd = req->clnt_fd;
  response_t res = {
      .request = req,
      .header_list = LIST_HEAD_INIT(res.header_list),
  };
  res.status = handle_response(req, &res);
  make_response(&res);
  int span_ms = get_time() - req->request_at;
  printf("%s %s %s [%d ms] %d\n", inet_ntoa(req->clnt_addr.sin_addr),
         req->method, req->path, span_ms, res.status.code);

  free_request(req);
  free_response(&res);
  free(req);
  close(fd);
  return NULL;
}

int main(void) {
  setup_socket();
  printf("listening at :%d\n", ntohs(serv_addr.sin_port));

  struct sockaddr_in clnt_addr;
  socklen_t clnt_len = sizeof(clnt_addr);
  for (;;) {
    int clnt_fd = accept(serv_fd, (struct sockaddr*)&clnt_addr, &clnt_len);
    if (clnt_fd == -1) {
      die("accept");
    }

    // printf("client connected: %s:%d\n", inet_ntoa(clnt_addr.sin_addr),
    //        ntohs(clnt_addr.sin_port));

    request_t* req = (request_t*)malloc(sizeof(request_t));
    memset(req, 0x0, sizeof(request_t));
    req->clnt_fd = clnt_fd;
    req->clnt_addr = clnt_addr;
    req->request_at = get_time();
    INIT_LIST_HEAD(&req->header_list);
    if (pthread_create(&req->thread, NULL, accept_request, req) != 0) {
      perror("pthread_create");
      free(req);
    }
  }

  close(serv_fd);
  return 0;
}
