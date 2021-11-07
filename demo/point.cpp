#include <stdio.h>

void exchange1(int a, int b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void exchange2(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int getLength(char* p) {
    int len = 0;
    while (p[len] != '\0') len++;
    return len;
}

int main() {
    int a = 1;
    int b = 2;
    exchange1(a, b);
    printf("%d %d\n", a, b);
    exchange2(&a, &b);
    printf("%d %d\n", a, b);

    char str[] = "hello, Anna; dreamer2q loves you";

    printf("%d", getLength(str));
    return 0;
}
