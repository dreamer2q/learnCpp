
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "include/list.h"

struct message {
  struct list_head list;

  int id;
  int uid;
  char* body;
};

int main() {
  printf("hello\n");

  struct list_head head_msg = LIST_HEAD_INIT(head_msg);

  for (int i = 0; i < 100; i++) {
    time_t now = time(NULL);
    struct tm* ptm = localtime(&now);
    char* tbuf = (char*)malloc(128);
    strftime(tbuf, 128, "Time: %F", ptm);
    struct message* msg = (struct message*)malloc(sizeof(struct message));
    msg->body = tbuf;
    msg->id = i;
    msg->uid = 1;
    list_add_tail(&msg->list, &head_msg);
  }

  struct list_head* iter;
  list_for_each(iter, &head_msg) {
    struct message* msg = container_of(iter, struct message, list);
    printf("%02d: %d %s\n", msg->id, msg->uid, msg->body);
  }

  return 0;
}
