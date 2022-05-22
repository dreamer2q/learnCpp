#ifndef __FAT_FILESYS
#define __FAT_FILESYS

#include "common.h"

#define __DEBUG_FLAG
#ifdef __DEBUG_FLAG
#define DEBUG(block) \
  do block while (0)
#else
#define DEBUG(block)
#endif

#define debug_log(log, args...) DEBUG({ fprintf(stderr, log, ##args); })

#define FAT_MAGIC 0x1234   // MAGIC NUMBER
#define KiB 1024           // kilobytes
#define BLOCK_SIZE 1024    // 磁盘块大小 bytes
#define BLOCK_FREE 0x0000  // 磁盘块未占用标志
#define BLOCK_END 0xFFFF   // 磁盘块结束标志
#define BLOCK_MAXCNT 1000  // 磁盘块最大数量
// 虚拟磁盘大小 1M
#define DISK_SIZE (BLOCK_SIZE * BLOCK_MAXCNT)
#define ERR_DISK_FULL -2
#define MAX_OPENCNT 32
#define BUFSIZ_FCB ((sizeof(struct fcb_t) * BLOCK_SIZE))
#define MAX_PATHCNT 80

// FAT 日期时间
struct fat_datetime {
  u16 date;
  u16 time;
};

// 5 6 5 bits
#define fat_time(hour, minute, second) \
  ((hour) << 11 | (minute) << 5 | (second) >> 1)

// 7 4 5 bits
#define fat_date(year, month, day) (((year)-80) << 9 | (month) << 5 | (day))

// fat time/date utils
#define fat_get_hour(time) (time >> 11)
#define fat_get_minute(time) (((time)&0x07E0) >> 5)
#define fat_get_second(time) (((time)&0x001F) << 1)
#define fat_get_year(date) (((date) >> 9) + 1980)
#define fat_get_month(date) (((date)&0x01E0) >> 5)
#define fat_get_day(date) ((date)&0x001F)

// FAT 文件分配表
// 用于记录磁盘块分配情况
struct fat_t {
  u16 id;  // 用于指示下一个磁盘块ID
};

struct block0 {
  u32 magic;       // FAT16 魔法数
  char info[200];  // 描述信息，例如磁盘块大小、磁盘块数量等
  u16 root;        // 根目录其实磁盘块ID
  u8 *data_block;  // 数据区开始位置
};

// 思考
// 为了加快索引，可以将FAT表装入内存

// FCB 文件控制块
struct fcb_t {
  /**
   * 魔改：增加文件名长度，不再区分扩展名
   */
  char filename[20];  // 文件名(目录是一种特殊的文件)
  // char extname[3];   // 文件扩展名
  u8 attr;       // 文件属性字段
  u16 time;      // 最近修改时间
  u16 date;      // 最近修改日期
  u16 first_id;  // 起始磁盘块号
  u32 length;    // 文件长度 bytes
  /**
   * 这里不知道为何要用一个 use_state 来标记 FCB 是否被使用
   */
  u8 use_state;  // 目录项目是否为空(0,表示空)
};               // 32bytes

#define FAT_ATTR_DIR 0x01
#define FAT_ATTR_FILE 0x00

// FILE 用户打开文件表
struct file_t {
  char dirname[MAX_PATHCNT];  // 目录路径

  u16 dir_block;   // 目录磁盘块号
  u16 dir_offset;  // 目录磁盘块号的偏移量

  u8 open_state;  // 表示该用户打开表项是否为空，若值为0，表示为空，否则表示已被某打开文件占据

  // 思考: 读和写为什么是同一个指针指示的?
  int count;         // 读写指针在文件中的位置
  struct fcb_t fcb;  // FCB 文件控制块
  u8 fcb_state;      // 是否修改了文件的FCB内容，如果修改为1
};

/*
 * 全局变量定义
 */
extern int fat_errno;  // FAT 操作错误

/**
 * 函数声明
 */
void startsys();
void exitsys();
struct block0 *fat_blkinfo();
struct fcb_t *fat_list(int *count);
char *fat_getcwd(char *buf, size_t len);
int fat_chdir(const char *dirname);
int fat_mkdir(const char *dirname);
int fat_rmdir(const char *dirname);
int fat_open(const char *filename);
int fat_close(int fd);
int fat_delete(const char *filename);
int fat_create(const char *filename);
int fat_read(int fd, void *buf, u32 len);
int fat_write(int fd, void *buf, u32 len);
int fat_getline(char **buf, size_t *bufcap, int fd);
int fat_trunc(int fd, int len);

#endif