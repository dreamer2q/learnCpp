#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int q_cmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }

int main() {
  int n, arr[1000] = {0};
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", arr + i);
  }

  qsort(arr + 1, n, sizeof(int), q_cmp);
  int total = 0;
  for (int i = 1; i <= n; i++) {
    arr[i] += arr[i - 1];
    total += arr[i];
  }

  printf("%d\n%.1lf", total, (double)total / n);

  return 0;
}