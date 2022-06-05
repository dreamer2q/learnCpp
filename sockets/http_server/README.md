
# C 简陋的 HTTP Server

使用 Linux C 完成的一个建立的 HTTP/1.0 服务器, 支持 GET 方法。

> The Hypertext Transfer Protocol (HTTP) is an application-level
   protocol with the lightness and speed necessary for distributed,
   collaborative, hypermedia information systems. HTTP has been in use
   by the World-Wide Web global information initiative since 1990.


## 实现思路

HTTP 服务属于典型的问答服务：即一个请求对应一个回复。(request --> response)。而 HTTP 协议的格式都是明文类型的，因此分为以下几步:

1. 创建 socket 监听指定 TCP 端口
2. 解析 HTTP Request 数据
3. 根据 Request 进行相关路由(例如路由到文件系统, 或者重定向到可执行文件 CGI)
4. 根据路由结果，构造 HTTP Response 数据
5. 数据发给客户端, 关闭 socket 链接

以上就是一个 HTTP Server 要做的工作了, 当然现实中的服务器肯定比这个复杂很多，而且随着 HTTP 协议的升级，需要处理的东西非常多，例如最基础的缓存功能等等。

这里只是简单的实现其最基本的 GET 方法，托管静态文件功能。

## Socket 端口监听与复用

```cpp
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
```

以上通过 `setsocket` 设置复用模式, 可以让这个端口的`bind`能立刻得到使用, 否则可能需要等得端口完全空闲状态才能`bind`。

其中 `listen` 中的 `5` 代表, 建立连接队列最多有 5 个等待连接的客户端, 如果超出会返回一个 `ECONNREFUSED` 错误。

## HTTP Request 的解析

```cpp
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
```

观察 HTTP Request 格式可以讲请求头分成三个部分：
1. METHOD + PATH 的命令行
2. Header 头信息
3. `optional` body 数据

这里最重要的就是第一个部分, 代表了 HTTP 的请求方法和请求路径, 知道这两个信息就能构造出 `HTTP Response` 数据了。

```cpp
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
```

这里的解析过程很简单, 首先读取一行数据, 然后根据空格作为风格, 分别保存对应的信息到结构体里面；
接下来解析 `header` 数据, 这里使用到了链表结构进行存储(因为头部长度不固定)。

如果 `Request` 携带 `Body` 数据还需要进一步处理它, 当然这里是没有做的。

## HTTP Response 构造

```cpp
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
  int body_fd;  // sending body bytes from readig fd
  off_t body_length;
} response_t;
```

构造 `Response` 的工作量是大头, 也是最复杂的部分。
`Response` 的结构和 `Request` 的结构差不多：
1. 第一行表示状态信息, 最常见的就是 `200 OK` 表示成功。
2. 第二行开始都是 `header` 的内容。
3. 由 `\r\n` 进行风格后面的是 `body` 内容。

`header` 里面的内容其实和 `body` 密切关联的, 比如说一个很重要的一点是 `Content-Type` 这个字段, 指明了返回的数据内容格式。
因此需要探测 `body` 里面代表的内容是什么格式的, 比较复杂。然后还有其它就是 `Content-Length` 属性, 如果 `body` 的长度无法提前获知还可能需要分段传输即编码形式变成 `chunked`。

如果服务器准备支持 `cgi` 脚本的话, 还需要为 `cgi` 脚本建立双向的 `pipe` 管道, 将脚本的输出作为 `body` 将 `request body` 作为脚步的输入。

当然这里简单起见, 只实现了文件的推送, 也没有 `Content-Type` 字段, 复杂的任务交给浏览器吧。

## 发送客户端数据

```cpp
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
```

这里将数据的发送分成了三个部分，正好对应 `Reponse` 的三个结构。其实 `status` 实现最简单, 只需要返回当前请求的状态吗和状态信息即可。
第二点便是 `header` 的发送, 由于采用了链表这里实现起来也是非常简单。最后一个就是 `body` 数据的发送了，这里将 `body` 分成两种情况:
1. 文件数据, 通过 `body_fd` 直接读取文件数据, 然后下发给 `client`。
2. 文字数据, 给内部自定义的错误码使用的, 例如 `not found` 的默认行为。

## 其它

HTTP Server 的模式是一对多的, 因此多线程是必不可少的, 否则一个 HTTP Server 只能给一个 `client` 提供服务，实在对不起服务的多核 CPU。
这里使用了 `pthread` 针对每一个连接建立一个线程。但是不好的一点就是，如果这个连接只是单纯的建立连接确不发送请求，就会导致线程在 `recv` 这里干等待, 效率比较低下, 如果有恶意客户端的故意建立许多连接可以很容易拖垮服务器。

> 线程也称为轻量级的进程（lightweight process, LWP），在支持线程的系统中，线程是CPU调度和分派的基本单元；传统操作系统中CPU高度和分派的基本单位是进程，传统上的进程（相当于只含有一个线程的进程）也被称为重量级进程（heavyweight process, HWP）。当一个进程包含多个线程时，相当于将进程的任务划分成多个子任务，由线程同时执行多个任何。
进程中引入线程后，线程即作为CPU调度和分派的基本单位，而进程则作为资源拥有的基本单位，同一进程中的线程切换不会引起进程切换，可以避免昂贵的系统调用。
因为进程之间可以并发执行，而同一进程中的线程之间也可以并发执行，所以线程提高了操作系统的并发性，能更有效的使用系统资源和提高系统的吞吐量。
线程拥有自己独立的栈、调度优先级和策略、信号屏蔽字（创建时继承）、errno变量以及线程私有数据，这些资源相对于进程占用的资源来说很少。进程的其他地址空间（包含进程的代码段、数据段以及其他系统资源，如已打开的文件、IO设备等）均被所有线程所共享，因此线程可以访问进程的全局变量和堆中分配的数据，并通过同步机制保证对数据访问的一致性。这样多线程相对于进程可以降低系统开销。

以上就是一个简陋的 `HTTP Server` 的实现过程了, 算是对 `HTTP` 协议了解跟进一步了吧。当然要学习的东西还是很多的。

# 参考

- [RFC1945](https://datatracker.ietf.org/doc/html/rfc1945)
- [tinyhttp](https://github.com/mendsley/tinyhttp)
- [linux-fork](http://notes.maxwi.com/2016/08/17/linux-fork/)
