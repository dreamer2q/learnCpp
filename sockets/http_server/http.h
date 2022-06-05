#ifndef __HTTP_H
#define __HTTP_H

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

typedef long long utime_t;

#define cmpcase(a, eq, b) (strcasecmp((a), (b)) eq 0)

void die(const char* err) {
  perror(err);
  exit(-1);
}

const char* fmt_now() {
  time_t t = time(NULL);
  return ctime(&t);
}

utime_t get_time() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000 + tv.tv_usec / 1e3;
}

char* new_str(const char* str) {
  size_t len = strlen(str);
  char* n = (char*)malloc(len + 1);
  if (n == NULL) die("malloc");
  memcpy(n, str, len);
  n[len] = '\0';
  return n;
}

const struct http_status {
  uint16_t code;
  const char* msg;
} StatusOK =
    {
        .code = 200,
        .msg = "OK",
},
  StatusNoContent =
      {
          .code = 201,
          .msg = "No Content",

},
  StatusBadRequest =
      {
          .code = 400,
          .msg = "Bad Request",
},
  StatusNotFound =
      {
          .code = 404,
          .msg = "Not Found",
},
  StatusUnauthorized =
      {
          .code = 401,
          .msg = "Unauthorized",
},
  StatusInternalServerError = {
      .code = 500,
      .msg = "Internal Server Error",
};

const char* BODY_NOT_FOUND =
    "<html><body>"
    "<h1>404</h1>"
    "<h2>Not Found</h2>"
    "</body></html>";

const char* BODY_BAD_REQUEST =
    "<html><body>"
    "<h1>400</h1>"
    "<h2>Bad Request</h2>"
    "</body></html>";

#endif
