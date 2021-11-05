#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * 进程调度模拟
 *
 * 假设进程的状态分为执行和就绪两种。
 * 每个进程以其PCB为代表，以链表的方式组织.
 * 分为三个队列：
 * - freeQueue：一个空白PCB队列
 * - readyQueue：一个就绪队列
 * - runningQueue：一个执行队列
 * 开始时用户输入进程数量n，每个进程需要运行的时间 t0,t1,t2...tn。
 * 程序从空白PCB队列中取出PCB创建进程，插入到 readyQueue。
 * 进程的调度采用随机的方式，即从就绪队列中随机选择一个进程投入运行（就是将该PCB中的状态变量赋值为“运行”）。
 * 相应的修改其所在队列，并且原来处于运行态的进程需要转变为“就绪”态，插入readyQueue。
 * 假设时间片是2，进程每次调度运行后，其还需运行的时间应该减少2，直至为0，即表示该进程执行完毕。
 * 执行完毕后需要回收PCB到freeQueue。每次发生调度的时候，需要打印信息示例：
 * Sched: P0(Running -> Ready), P3(Ready -> Running)
 * Running: P3
 * Ready: P1->P2->P0
 * 上述信息表示调度时P0处于运行态，选择P3运行，P0进程的PCB进入就绪队列，并且在队尾。
 * 就绪队列是按照队列节点次序输出进程名称。
 */

#define assert(cond, msg)                                                    \
  do {                                                                       \
    if (!(cond)) {                                                           \
      fprintf(stderr, "%s: %s %d: " msg "\n", __DATE__, __FILE__, __LINE__); \
      exit(-1);                                                              \
    }                                                                        \
  } while (0)

#define swap(a, b)        \
  do {                    \
    typeof(a) _tmp = (a); \
    (a) = (b);            \
    (b) = _tmp;           \
  } while (0)

#define free 0
#define ready 1
#define running 2
#define ts 2 /* time slice */

const char *status_running = "Running";
const char *status_ready = "Ready";
const char *status_free = "Free";

struct pcb {
  int pid;           /* 进程ID  */
  int pstate;        /* 进程状态 */
  const char *pname; /* 映象名称 */
  int ptime;         /* 剩余运行时间 */
  struct pcb *next;  /* 下一个PCB */
};

struct pcb freequeue, readyqueue, runqueue;

#define list_each(list, node) \
  for (struct pcb *node = (list)->next; node != NULL; node = node->next)

void init_list(struct pcb *p) { p->pname = NULL; }

size_t list_len(struct pcb *head) {
  size_t len = 0;
  struct pcb *p = head->next;
  while (p != NULL) {
    len++;
    p = p->next;
  }
  return len;
}

struct pcb *list_get_random(struct pcb *head) {
  size_t len = list_len(head);
  if (len == 0) return NULL;
  if (len == 1) return head->next;
  size_t r = rand() % len;
  struct pcb *p = head->next;
  for (size_t t = 0; p != NULL; p = p->next, t++) {
    if (t == len - 1) return p;
  }
  return NULL;
}

void list_add(struct pcb *head, struct pcb *node) {
  struct pcb *tm = head->next;
  head->next = node;
  node->next = tm;
}

void list_del(struct pcb *head, struct pcb *node) {
  if (node == NULL) return;
  struct pcb *p = head;
  while (p != NULL) {
    if (p->next == node) {
      // remove node, no free it
      p->next = node->next;
      node->next = NULL;
      break;
    }
    p = p->next;
  }
}

uint8_t list_is_empty(struct pcb *head) { return head->next == NULL; }

void print_queue(const char *msg, struct pcb *queuq) {
  printf("%s: ", msg);
  if (list_is_empty(queuq)) {
    printf("empty queue\n");
  } else {
    list_each(queuq, item) {
      printf("%s", item->pname);
      if (item->next) {
        printf(" -> ");
      }
    }
    printf("\n");
  }
}

void init_ready_queue() {
  size_t freesize = 0;
  scanf("%ld", &freesize);
  for (size_t pid = 0; pid < freesize; pid++) {
    int ptime = 0;
    scanf("%d", &ptime);

    char *pname = malloc(20 * sizeof(char));
    assert(pname != NULL, "malloc pname");
    sprintf(pname, "P%ld", pid);

    struct pcb pcb = {
        .pid = pid,
        .pname = pname,
        .ptime = ptime,
        .next = NULL,
        .pstate = ready,  // assume initial ready
    };

    struct pcb *p = malloc(sizeof(struct pcb));
    assert(p != NULL, "malloc free pcb struct");
    *p = pcb;  // copy initial pcb struct
    list_add(&readyqueue, p);
  }
}

void print_sched(struct pcb *p, const char *from, const char *to) {
  printf("%s(%s -> %s) ", p->pname, from, to);
}

/**
 * Sched: P0(Running -> Ready), P3(Ready -> Running)
 */
void sched(struct pcb *readytorun) {
  printf("Sched: ");
  if (!list_is_empty(&runqueue)) {
    // if not empty, there must only be one running
    // then it should be scheduled out with a time slice
    struct pcb *run = list_get_random(&runqueue);
    list_del(&runqueue, run);
    run->ptime -= ts;
    run->pstate = ready;
    print_sched(run, status_running, status_ready);
    if (run->ptime > 0) {
      // pcb is yet not over, put it back to ready queue for next schedule
      list_add(&readyqueue, run);
    } else {
      // pcb is over, sched it out free quque
      run->pstate = free;
      print_sched(run, status_ready, status_free);
      list_add(&freequeue, run);
    }
  }
  if (readytorun != NULL) {
    readytorun->pstate = running;
    list_del(&readyqueue, readytorun);
    list_add(&runqueue, readytorun);
    print_sched(readytorun, status_ready, status_running);
  }
  printf("\n");
  print_queue("Running", &runqueue);
  print_queue("Ready", &readyqueue);
  print_queue("Free", &freequeue);
}

void init() {
  srand(time(NULL));
  init_list(&freequeue);
  init_list(&readyqueue);
  init_list(&runqueue);
  init_ready_queue();
}

int main() {
  init();

  do {
    struct pcb *current = list_get_random(&readyqueue);
    sched(current);
  } while (!list_is_empty(&runqueue) || !list_is_empty(&readyqueue));

  printf("schedule simulation over\n");
  return 0;
}
