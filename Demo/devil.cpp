
//�����ַ���B(adasdas)B#
//���tsaedsaeasaaadasaaadatsaedsae
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
//����ڵ�
typedef struct node {
    char word;
    struct node *pnode;
} Snode, Qnode;

//����ջ
typedef struct linkStack {
    Snode *top;
} LinkStack;

//�������
typedef struct linkQueue {
    Qnode *rear, *front;
} LinkQueue;

void initStack(LinkStack *s) {  //��ʼ��ջ
    s->top = NULL;
}

int push(char w, LinkStack *s) {
    Snode *p = (Snode *)malloc(sizeof(Snode));
    if (!p) {
        return 0;  //�ڴ�����ʧ�ܷ���0
    }
    p->word = w;
    p->pnode = s->top;
    s->top = p;
    return 1;  //�ڴ�����ɹ�����1
}

//��ջ
int pop(LinkStack *s, char *w) {
    if (s == NULL || s->top == NULL) return 0;
    Snode *p = s->top;
    *w = p->word;
    s->top = p->pnode;
    //    free(p);
    return 1;
}

void InitQueue(LinkQueue *q) {//��ʼ������
    q->rear = q->front = NULL;
}

int EnQueue(LinkQueue *q, char w) {
    Qnode *p = (Qnode *)malloc(sizeof(Qnode));
    if (!p) {
        return 0;  //�ڴ�����ʧ�ܷ���0
    }
    p->word = w;
    if (q->front == NULL)  //����Ϊ�գ�������һ�����
        q->front = q->rear = p;
    else
        q->rear->pnode = p;
    q->rear = p;
    return 1;  //�ڴ�����ɹ�����1
}

//����
int DeQueue(LinkQueue *q, char *w) {
    if (q->front == NULL) return 0;
    Qnode *p = q->front;
    *w = p->word;
    q->front = q->front->pnode;
    free(p);
    return 1;
}

//������
int main() {
    char input;
    char w;
    char sentence[MAX_SIZE];
    LinkStack S;
    LinkQueue Q;
    initStack(&S);
    InitQueue(&Q);
    int i = 0;
    printf("������Ҫ��������ԣ����ԡ�#����β:\n");
    while ((input = getchar()) != '#')  //����#����
    {
        sentence[i] = input;
        i++;
    }
    for (int j = i - 1; j >= 0; j--)  //������ջ
    {
        push(sentence[j], &S);
    }
    while (pop(&S, &w)) {  //���Ĵ���
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
            firts_word = w;  //����Ԫ�ظ�ֵ��first_word
            while (DeQueue(&Q, &w)) {
                push(firts_word, &S);
                push(w, &S);
            }
        } else if (w == ')') {
            //�����Ų���ӡ����
        } else {
            printf("%c", w);
        }
    }
    return 0;
}
