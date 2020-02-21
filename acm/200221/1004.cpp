#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *key;
    int value;
} MAP;

#define N 1001

MAP map[N];

void add(char *key) {
    for (int i = 0; i < N; i++) {
        char *t = map[i].key;
        if (t && (strcmp(key, t) == 0)) {
            map[i].value++;
            return;
        } else if(t == NULL) {
            char *k = (char *)malloc(strlen(key) * sizeof(char));
            if (k == NULL) {
                //printf("error\n");
                while (true)
                    ;
            }
            strcpy(k, key);
            map[i].key = k;
            map[i].value++;
            return;
        }
    }
}

void reset() {
    for (int i = 0; i < N; i++) {
        if (map[i].key != NULL) {
            free(map[i].key);
            map[i].key = NULL;
            map[i].value = 0;
        }
    }
}

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        if (n == 0) break;
        reset();
        char tmp[16];
        for (int i = 0; i < n; i++) {
            scanf("%s", tmp);
            add(tmp);
        }
        char *popular;
        int m = 0;
        for (int i = 0; i < N; i++) {
            if (map[i].value > m) {
                m = map[i].value;
                popular = map[i].key;
            }
        }
        if (popular != NULL) {
            printf("%s\n", popular);
        }
    }

    return 0;
}
