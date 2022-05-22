#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/signal.h>

#define MSGSIZ 256
#define MSGTYP 1

#define P(s) sem_wait(s)
#define V(s) sem_post(s)

sem_t send_psx, recv_psx, final_recv;
pthread_t send_pid, recv_pid;

// 消息结构体
struct msgbuf {
  long mtype;         /* message type, must be > 0 */
  char mtext[MSGSIZ]; /* message data */
};

int msgid;

void *send_thread(void *arg) {
  int count = 0;
  char msgline[BUFSIZ];
  struct msgbuf s_msg = {
      .mtype = MSGTYP,
  };
  while (1) {
    P(&send_psx);

    printf("send_thread: ");
    scanf("%s", msgline);
    // memset(info, '*', sizeof(info));
    if (strcmp(msgline, "exit") == 0) {
      strcpy(s_msg.mtext, "end");
      msgsnd(msgid, &s_msg, sizeof(struct msgbuf), 0);
      V(&recv_psx);
      break;
    }
    strcpy(s_msg.mtext, msgline);
    count++;
    printf("%d\n", count);
    msgsnd(msgid, &s_msg, sizeof(struct msgbuf), 0);

    V(&send_psx);
    V(&recv_psx);
  }
  P(&final_recv);
  msgrcv(msgid, &s_msg, sizeof(struct msgbuf), 2, 0);
  printf("send_thread recv: %s\ndone.\n", s_msg.mtext);
  // remove msg queue
  msgctl(msgid, IPC_RMID, 0);
  pthread_exit(NULL);
}

void *recv_thread(void *arg) {
  // sleep(10);
  struct msgbuf r_msg;
  r_msg.mtype = 1;
  while (1) {
    P(&recv_psx);
    sleep(2);
    msgrcv(msgid, &r_msg, sizeof(struct msgbuf), MSGTYP, 0);
    if (strcmp(r_msg.mtext, "end") == 0) {
      strcpy(r_msg.mtext, "over");
      r_msg.mtype = 2;
      msgsnd(msgid, &r_msg, sizeof(struct msgbuf), 0);
      printf("recv_thread recv 'end', return 'over'\n");
      V(&final_recv);
      break;
    }
    printf("recv_thrend: %s\n", r_msg.mtext);
  }
  pthread_exit(NULL);
}

void catch_INT(int sig) {
  printf("catch SIGINT\n");
  msgctl(msgid, IPC_RMID, 0);
  exit(0);
}

int main(void) {
  signal(SIGINT, catch_INT);

  sem_init(&send_psx, 0, 1);
  sem_init(&recv_psx, 0, 0);
  sem_init(&final_recv, 0, 0);
  msgid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);
  if (msgid < 0) {
    printf("msgget error\n");
    exit(1);
  }
  pthread_create(&send_pid, NULL, send_thread, NULL);
  pthread_create(&recv_pid, NULL, recv_thread, NULL);

  pthread_join(send_pid, NULL);
  pthread_join(recv_pid, NULL);

  return 0;
}
