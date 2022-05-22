#include <stdio.h>
#include <stdlib.h>

#define ALEN(a) (sizeof(a) / sizeof(a[0]))
#define PAGE_MASK ((unsigned int)-1)
#define ADDR_SIZE 31
#define PAGE_SIZE 12

/*
某分页系统中，程序空间与物理空间都是2GB，页面大小为4KB。
请编写程序模拟分页系统的地址变换过程。
要求分为公式法和硬拼法两种方式实现，并对比体会两种方法的差别。
*/

// 2GB = 2^31
// 4k  = 2^12

// 已知某进程的页表如下
int page_tables[] = {
    32102, 443217, 6723, 8985, 11238, 29065, 234205, 45812, 240561, 300451,
};

int table_size = ALEN(page_tables);

void missing_page_error(int page) {
  fprintf(stderr, "exception: missing page %d\n", page);
  exit(-1);
}

int get_physical_address_hardware(int logic) {
  int page_num = logic >> PAGE_SIZE;
  if (page_num >= table_size)
    missing_page_error(page_num);
  return (page_tables[page_num] << PAGE_SIZE) |
         (logic & ~(PAGE_MASK << PAGE_SIZE));
}

int get_physical_address_softmath(int logic) {
  int page_size = 1 << PAGE_SIZE;
  int page_num = logic / page_size;
  if (page_num >= table_size)
    missing_page_error(page_num);
  int inner_addr = logic % page_size;
  return page_tables[page_num] * page_size + inner_addr;
}

int main() {
  printf("--- PAGE TABLE ---\n");
  for (int i = 0; i < table_size; i++) {
    printf("%d: 0x%05X\n", i, page_tables[i]);
  }
  printf("--- END TABLE ---\n");
  for (;;) {
    int logic_addr;
    printf("logic address: ");
    scanf("%x", &logic_addr);
    printf("physical address hardware: %08X\n",
           get_physical_address_hardware(logic_addr));
    printf("physical address softmath: %08X\n",
           get_physical_address_softmath(logic_addr));
  }
  return 0;
}