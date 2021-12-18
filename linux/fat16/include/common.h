#ifndef __COMMON_H
#define __COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include "color.h"

// 数据结构定义
#define bool char
#define u32 unsigned int
#define u16 unsigned short
#define u8 unsigned char
#define true 1
#define false (!true)

#define offsetof(type, member) ((size_t) & (((type *)0)->member))

typedef unsigned long size_t;

#define assert(boolean, err)                                      \
  do {                                                            \
    if (!(boolean)) {                                             \
      fprintf(stderr, "assert error at %d: %s\n", __LINE__, err); \
      exit(-1);                                                   \
    }                                                             \
  } while (0)

#define min(a, b) ((a) < (b) ? (a) : (b))
#define compare(s1, cmp, s2) (strcmp(s1, s2) cmp 0)

#endif