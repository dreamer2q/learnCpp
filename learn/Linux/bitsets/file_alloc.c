#include <stdio.h>

#define BITS_SIZE(bits) (sizeof(bits) * 8)
#define ARR_LEN(arr) (sizeof(arr) / sizeof(arr[0]))

/**
 * 初始化分配情况
 */
char file_alloc[8] = {
    0xC7, 0x26, 0x1F, 0x87, 0xE3, 0xF0, 0x0D, 0xE8,
};

// 统计二进制1的数量
int popcount_4(char x) {
  int count;
  for (count = 0; x; count++) x &= x - 1;
  return count;
}

int get_alloc_stat(int* free, int* busy) {
  int total = BITS_SIZE(file_alloc);
  *busy = 0;
  for (int i = 0; i < ARR_LEN(file_alloc); i++) {
    *busy += popcount_4(file_alloc[i]);
  }
  *free = total - *busy;
  return total;
}

int alloc_file_block() {
  for (int i = 0; i < BITS_SIZE(file_alloc); i++) {
    int row = i / 8;
    int col = 1 << (7 - (i % 8));
    if (!(file_alloc[row] & col)) {
      file_alloc[row] |= col;
      return i + 1;
    }
  }
}

void alloc_free_block(int id) {
  id -= 1;
  file_alloc[id / 8] &= ~(1 << (7 - (id % 8)));
}

void print_alloc_table(void) {
  printf("\nalloc_table\n");
  printf("   1 2 3 4 5 6 7 8\n");
  for (int i = 0; i < ARR_LEN(file_alloc); i++) {
    printf("%d:", i + 1);
    for (int j = 0; j < BITS_SIZE(char); j++) {
      printf(" %d", file_alloc[i] & (1 << (7 - j)) ? 1 : 0);
    }
    printf("\n");
  }
  printf("\n");
}

int main() {
  int free, busy;
  int total = get_alloc_stat(&free, &busy);
  printf("Free/Busy/Total: %d/%d/%d\n", free, busy, total);

  print_alloc_table();

  for (int i = 0; i < 5; i++) {
    int alloc_id = alloc_file_block();
    printf("alloc: %d\n", alloc_id);
  }

  print_alloc_table();

  int frees[] = {6, 11, 20, 24, 35};
  for (int i = 0; i < ARR_LEN(frees); i++) {
    alloc_free_block(frees[i]);
    printf("free: %d\n", frees[i]);
  }

  print_alloc_table();

  return 0;
}
