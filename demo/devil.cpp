
//输入字符串B(adasdas)B#
//输出tsaedsaeasaaadasaaadatsaedsae
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
//定义节点
typedef struct node {
  char word;
  struct node *pnode;
} Snode, Qnode;

//定义栈
typedef struct linkStack {
  Snode *top;
} LinkStack;

//定义队列
typedef struct linkQueue {
  Qnode *rear, *front;
} LinkQueue;

void initStack(LinkStack *s) {  //初始化栈
  s->top = NULL;
}

int push(char w, LinkStack *s) {
  Snode *p = (Snode *)malloc(sizeof(Snode));
  if (!p) {
    return 0;  //内存申请失败返回0
  }
  p->word = w;
  p->pnode = s->top;
  s->top = p;
  return 1;  //内存申请成功返回1
}

//出栈
int pop(LinkStack *s, char *w) {
  if (s == NULL || s->top == NULL) return 0;
  Snode *p = s->top;
  *w = p->word;
  s->top = p->pnode;
  //    free(p);
  return 1;
}

void InitQueue(LinkQueue *q) {  //初始化队列
  q->rear = q->front = NULL;
}

int EnQueue(LinkQueue *q, char w) {
  Qnode *p = (Qnode *)malloc(sizeof(Qnode));
  if (!p) {
    return 0;  //内存申请失败返回0
  }
  p->word = w;
  if (q->front == NULL)  //队列为空，创建第一个结点
    q->front = q->rear = p;
  else
    q->rear->pnode = p;
  q->rear = p;
  return 1;  //内存申请成功返回1
}

//出队
int DeQueue(LinkQueue *q, char *w) {
  if (q->front == NULL) return 0;
  Qnode *p = q->front;
  *w = p->word;
  q->front = q->front->pnode;
  free(p);
  return 1;
}

//主函数
int main() {
  char input;
  char w;
  char sentence[MAX_SIZE];
  LinkStack S;
  LinkQueue Q;
  initStack(&S);
  InitQueue(&Q);
  int i = 0;
  printf("请输入要翻译的语言，并以‘#’结尾:\n");
  while ((input = getchar()) != '#')  //输入#结束
  {
    sentence[i] = input;
    i++;
  }
  for (int j = i - 1; j >= 0; j--)  //倒叙入栈
  {
    push(sentence[j], &S);
  }
  while (pop(&S, &w)) {  //核心代码
    if (w == 'A') {
      printf("sae");
    } else if (w == 'B') {
      printf("tsaedsae");
    } else if (w == '(') {
      char firts_word;
      while (w != ')') {
        pop(&S, &w);
        EnQueue(&Q, w);
      }
      DeQueue(&Q, &w);
      firts_word = w;  //将首元素赋值给first_word
      while (DeQueue(&Q, &w)) {
        push(firts_word, &S);
        push(w, &S);
      }
    } else if (w == ')') {
      //右括号不打印东西
    } else {
      printf("%c", w);
    }
  }
  return 0;
}
