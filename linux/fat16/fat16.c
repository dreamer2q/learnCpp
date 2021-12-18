#include "filesys.h"
#include <errno.h>
#include <memory.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int do_fat_write(int fd, void *buf, u32 len);
int do_fat_read(int fd, void *buf, u32 len);

#define _get_fat_ptr(i) ((struct fat_t *)(virtual_disk + i * BLOCK_SIZE))
#define get_fat1 _get_fat_ptr(1)
#define get_fat2 _get_fat_ptr(3)
#define current_dir current_useropens[current_dirfd]

struct fat_datetime fat_now() {
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  struct fat_datetime datetime = {
      .date = fat_date(t->tm_year, t->tm_mon, t->tm_mday),
      .time = fat_time(t->tm_hour, t->tm_min, t->tm_sec),
  };
  return datetime;
}

/*
 * 全局变量定义
 */
u8 *virtual_disk;  // 虚拟磁盘的起始地址
u8 *start_vdata;   // 虚拟磁盘数据区开始位置
u8 current_dirfd;  // 当前目录的文件描述号 fd
struct file_t current_useropens[MAX_OPENCNT];
const char *local_disk_file = "fat16.disk";

void sync_fat2() { memcpy(get_fat2, get_fat1, 2 * BLOCK_SIZE); }

struct block0 *fat_blkinfo() {
  return (struct block0 *)virtual_disk;
}

int get_free_openfd() {
  for (int i = 0; i < MAX_OPENCNT; i++) {
    struct file_t *f = current_useropens + i;
    if (f->open_state == 0) {
      f->open_state = 1;
      return i;
    }
  }
  return -1;
}

#define for_each_current_fcb(fcb) \
  for (struct fcb_t **_fcb = get_current_fcb(); (fcb = *_fcb) != NULL; _fcb++)

struct fcb_t **get_current_fcb() {
  static struct fcb_t fcb_buf[BLOCK_SIZE];
  static struct fcb_t *fcb_list[BLOCK_SIZE];
  current_dir.count = 0;
  int len = do_fat_read(current_dirfd, fcb_buf, current_dir.fcb.length);
  int count = len / sizeof(struct fcb_t);
  for (int i = 0; i < count; i++) {
    fcb_list[i] = fcb_buf + i;
  }
  fcb_list[count] = NULL;
  return fcb_list;
}

#define for_each_tmpdir(tmpdir, fcb)                             \
  for (tmpdir.i = 0, fcb = tmpdir.fcb; tmpdir.i < tmpdir.fcblen; \
       tmpdir.i++, fcb++)

struct tmp_dir_t {
  int i;              // tmp_dir index
  int fd;             // file descriptor
  int fcblen;         // fcb array length
  struct fcb_t *fcb;  // fcb array
};

struct tmp_dir_t tmp_open_dir(struct fcb_t *fcb) {
  int fd = get_free_openfd();
  assert(fd != -1, "no free openid");

  struct file_t tmpfile = {
      .fcb = *fcb,
      .count = 0,
      .open_state = 1,
  };
  current_useropens[fd] = tmpfile;

  static char buf[BUFSIZ_FCB];
  int len = do_fat_read(fd, buf, fcb->length);

  struct tmp_dir_t res = {
      .i = 0,
      .fd = fd,
      .fcblen = len / sizeof(struct fcb_t),
      .fcb = (struct fcb_t *)buf,
  };
  return res;
}

int tmp_close_dir(struct tmp_dir_t *tmpdir, char writeback) {
  struct file_t *of = current_useropens + tmpdir->fd;
  if (writeback) {
    of->count = 0;
    do_fat_write(tmpdir->fd, tmpdir->fcb,
                 tmpdir->fcblen * sizeof(struct fcb_t));
  }
  of->open_state = 0;
  return 0;
}

u16 get_smallest_free_block() {
  struct fat_t *fat = get_fat1;
  for (int i = 6; i < BLOCK_MAXCNT; i++) {
    if (fat[i].id == BLOCK_FREE) {
      return i;
    }
  }
  debug_log("no free block, disk is full\n");
  return BLOCK_END;
}

void init_filesize(int fd) {
  struct stat filestat;
  fstat(fd, &filestat);
  if (filestat.st_size < DISK_SIZE) {
    // 手动增加文件大小
    for (int i = 0; i < DISK_SIZE; i++) {
      write(fd, "\0", 1);
    }
    debug_log("init filesize from %ld to %d\n", filestat.st_size, DISK_SIZE);
  }
}

void fat_format() {
  struct block0 *blk = (struct block0 *)virtual_disk;
  if (blk->magic == FAT_MAGIC) return;
  debug_log("disk not format, formatting...");

  // clear BLOCK0, FAT1, FAT2
  memset(virtual_disk, 0x00, BLOCK_SIZE * 5);

  // format BLOCK0
  blk->magic = FAT_MAGIC;
  blk->root = 5;
  sprintf(blk->info,
          "VFAT16 File System Ver 0.1\n"
          "BlockSize=%dKiB TotalSize=%dKiB\n"
          "BlockCount=%d RootBlock=%d",
          BLOCK_SIZE / KiB, DISK_SIZE / KiB, BLOCK_MAXCNT, blk->root);

  // 初始化FAT表
  // 一个FAT表占用两个BLOCK_SIZE大小
  for (int i = 0; i <= blk->root; i++) {
    get_fat1[i].id = BLOCK_END;
  }
  sync_fat2();

  // 初始化根目录
  struct fcb_t *root = (struct fcb_t *)(virtual_disk + blk->root * BLOCK_SIZE);

  struct fat_datetime now = fat_now();
  struct fcb_t fcb = {
      .filename = ".",  // 本级目录
      // .extname = "",
      .attr = FAT_ATTR_DIR,
      .use_state = 1,
      .length = 2 * sizeof(struct fcb_t),
      .first_id = blk->root,
      .time = now.time,
      .date = now.date,
  };

  root[0] = fcb;
  strcpy(fcb.filename, "..");
  root[1] = fcb;

  debug_log("formate done: %s\n", blk->info);
}

void startsys() {
  // 载入文件
  int fd = open(local_disk_file, O_CREAT | O_RDWR);
  if (fd == -1) {
    perror("open file");
    exit(-1);
  }
  // 初始化文件
  init_filesize(fd);
  virtual_disk =
      mmap(NULL, DISK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (MAP_FAILED == virtual_disk) {
    perror("map error");
    exit(-1);
  }
  start_vdata = virtual_disk + 5 * BLOCK_SIZE;
  // 格式化虚拟磁盘
  fat_format();
  close(fd);  // 关闭文件不会影响到mmap的映射

  // 打开根目录
  struct fcb_t *root = (struct fcb_t *)(start_vdata);
  struct file_t init_dir = {
      .count = 0,
      .fcb = root[0],
      .dirname = "(root)",
      .dir_block = 5,
      .dir_offset = 0,
      .fcb_state = 0,
      .open_state = 1,
  };
  current_dirfd = 0;
  current_dir = init_dir;
}

void exitsys() {
  while (current_dirfd != 0) {
    fat_close(current_dirfd);
  }
  fat_close(0);
  msync(virtual_disk, DISK_SIZE, MS_SYNC);
  if (munmap(virtual_disk, DISK_SIZE)) {
    perror("unmap file");
    exit(-1);
  }
}

int do_fat_read(int fd, void *buf, u32 len) {
  assert(buf != NULL, "buf is empty");
  assert(fd >= 0 && fd <= MAX_OPENCNT, "invalid fd");

  struct file_t *of = &current_useropens[fd];
  int first_id = of->fcb.first_id;

  // 移动 FAT 位置，匹配 OFFSET
  if (of->count >= of->fcb.length) {
    return EOF;
  }
  int offset = of->count;
  if (offset + len > of->fcb.length) {
    len = of->fcb.length - offset;
  }

  while (offset >= BLOCK_SIZE) {
    offset -= BLOCK_SIZE;
    first_id = get_fat1[first_id].id;  // 下一个 block
    if (first_id == BLOCK_END) {
      // offset 错误
      debug_log("do_fat_read: invalid offset\n");
      return EOF;
    }
  }

  // 如果 BLOCK_SIZE 比较大,可以使用 malloc
  char blockbuf[BLOCK_SIZE];
  u8 *blockptr = virtual_disk + BLOCK_SIZE * first_id;
  // 这一步仅仅是模拟从磁盘中读取数据这个过程
  memcpy(blockbuf, blockptr, BLOCK_SIZE);

  if (BLOCK_SIZE - offset >= len) {
    // 一次读取完成
    memcpy(buf, blockbuf + offset, len);
    of->count += len;
    return len;
  }

  // 超出一次,需要迭代
  int readcnt = BLOCK_SIZE - offset;
  memcpy(buf, blockbuf + offset, readcnt);
  buf += readcnt;

  while (readcnt < len) {
    int left = len - readcnt;

    // 模拟从磁盘读取下一个 block
    first_id = get_fat1[first_id].id;
    if (first_id == BLOCK_END) {
      debug_log("do_fat_read: end of file\n");
      return EOF;
    }
    blockptr = virtual_disk + first_id * BLOCK_SIZE;
    memcpy(blockbuf, blockptr, BLOCK_SIZE);

    // 复制给用户
    int len = min(left, BLOCK_SIZE);
    memcpy(buf, blockbuf, len);
    buf += len;
    readcnt += len;
  }

  of->count += readcnt;
  return readcnt;
}

int do_fat_write(int fd, void *buf, u32 len) {
  assert(buf != NULL, "buf is empty");
  assert(fd >= 0 && fd <= MAX_OPENCNT, "invalid fd");

  if (len == 0) return 0;

  struct file_t *of = current_useropens + fd;
  int first_id = of->fcb.first_id;

  if (of->count > of->fcb.length) {
    debug_log("do_fat_write: invalid offset\n");
    return EOF;
  }

  // 保证至少有一个 BLOCK 可用
  if (first_id == BLOCK_END) {
    // 如果还没有分配BLOCK, 再这里给它分配空间
    first_id = get_smallest_free_block();
    if (first_id == BLOCK_END) {
      // 空间分配失败
      debug_log("do_fat_write: next_block: disk is full\n");
      return ERR_DISK_FULL;
    }
    // 这里分配的是初始块，不需要 connect
    get_fat1[first_id].id = BLOCK_END;  // mark END

    // 分配成功后我们要更新它的 first_id
    of->fcb.first_id = first_id;
    of->fcb_state = 1;
  }

  // 移动 FAT 位置，匹配 OFFSET
  int offset = of->count;
  while (offset >= BLOCK_SIZE) {
    offset -= BLOCK_SIZE;
    int next_id = get_fat1[first_id].id;
    if (next_id == BLOCK_END) {
      if (offset > 0) {  // offset 错误
        debug_log("do_fat_write: invalid offset\n");
        return EOF;
      }
      // 边界情况, 当offset是block整数倍时候, 确保后续有块可写
      next_id = get_smallest_free_block();
      if (next_id == BLOCK_END) {
        // 空间分配失败
        debug_log("do_fat_write: next_block: disk is full\n");
        return ERR_DISK_FULL;
      }
      get_fat1[first_id].id = next_id;   // connect BLOCK
      get_fat1[next_id].id = BLOCK_END;  // mark END
    }
    first_id = next_id;  // 下一个 block
  }

  // 如果 BLOCK_SIZE 比较大,可以使用 malloc
  char blockbuf[BLOCK_SIZE];
  u8 *blockptr = virtual_disk + first_id * BLOCK_SIZE;
  // 这一步仅仅是模拟从磁盘中读取数据这个过程
  memcpy(blockbuf, blockptr, BLOCK_SIZE);

  int written = 0;
  if (BLOCK_SIZE - offset >= len) {
    written = len;
    // 剩余的 BLOCK 可以存放下
    memcpy(blockbuf + offset, buf, len);
    // 这一步模拟写入磁盘的过程
    memcpy(blockptr, blockbuf, BLOCK_SIZE);
  } else {
    written = BLOCK_SIZE - offset;
    // 迭代写入
    memcpy(blockbuf + offset, buf, written);
    memcpy(blockptr, blockbuf, BLOCK_SIZE);
    buf += written;

    while (written < len) {
      int left = len - written;

      int next_id = get_fat1[first_id].id;
      if (next_id == BLOCK_END) {
        next_id = get_smallest_free_block();
        if (next_id == BLOCK_END) {
          debug_log("do_fat_write: next_block: disk is full\n");
          return ERR_DISK_FULL;
        }
        get_fat1[first_id].id = next_id;   // connect BLOCK
        get_fat1[next_id].id = BLOCK_END;  // mark END
      }
      first_id = next_id;  // move NEXT
      blockptr = virtual_disk + first_id * BLOCK_SIZE;

      int len = min(BLOCK_SIZE, left);
      memcpy(blockbuf, buf, len);       // 写入缓存
      memcpy(blockptr, blockbuf, len);  // 写入文件
      written += len;
      buf += len;
    }
  }
  of->count += written;

  // 判断是否增量写入
  if (of->count > of->fcb.length) {
    of->fcb.length = of->count;
    of->fcb_state = 1;  // FCB 需要更新
  }

  return written;
}

char *fat_getcwd(char *buf, size_t len) {
  int cpylen = min(strlen(current_dir.dirname), len);
  strncpy(buf, current_dir.dirname, cpylen);
  buf[cpylen] = '\0';
  return buf;
}

int fat_mkdir(const char *dirname) {
  /**
   * 当前目录：当前打开目录项表示的目录
   * 该目录：以下指创建的目录
   * 父目录：指该目录的父目录
   */
  assert(strlen(dirname) < 8, "dirname is too long");
  assert(strchr(dirname, '.') == NULL, "invalid character .");

  // 读取当前目录信息
  struct fcb_t *fcb;
  int free_fcbid = -1, i = 0;
  for_each_current_fcb(fcb) {
    // 不允许目录和文件重名
    if (compare(dirname, ==, fcb->filename)) {
      debug_log("fat_mkdir: dirname already exist\n");
      return -1;
    }
    if (!fcb->use_state) {
      free_fcbid = i;
      break;
    }
    i++;
  }

  if (free_fcbid == -1) {  // 没有空闲的FCB使用
    free_fcbid = i;
  }
  u16 first_block = get_smallest_free_block();
  if (first_block == BLOCK_END) {
    return ERR_DISK_FULL;
  }
  get_fat1[first_block].id = BLOCK_END;

  // 创建一条目录 FCB 记录
  struct fat_datetime now = fat_now();
  struct fcb_t newfcb = {
      .attr = FAT_ATTR_DIR,
      .date = now.date,
      .time = now.time,
      // .extname = "",
      .first_id = first_block,
      .use_state = 1,
      // 初始化只有 "." 和 ".." 两个子目录
      .length = 2 * sizeof(struct fcb_t),
  };
  strcpy(newfcb.filename, dirname);

  // 写入当前目录下，新的fcb item
  current_dir.count = free_fcbid * sizeof(struct fcb_t);
  do_fat_write(current_dirfd, &newfcb, sizeof(struct fcb_t));

  // 初始化新目录
  struct tmp_dir_t newdir = tmp_open_dir(&newfcb);
  newdir.fcb[0] = newfcb;
  newdir.fcb[1] = current_dir.fcb;
  strcpy(newdir.fcb[0].filename, ".");
  strcpy(newdir.fcb[1].filename, "..");
  tmp_close_dir(&newdir, true);

  return 0;
}

int fat_rmdir(const char *dirname) {
  assert(strlen(dirname) < 8, "dirname is too long");

  if (!strcmp(dirname, ".") || !strcmp(dirname, "..")) {
    debug_log("fat_rmdir: cannot perform on . or ..");
    return -1;
  }

  int rmindex = 0;
  struct fcb_t *fcb, *rmfcb = NULL;
  for_each_current_fcb(fcb) {
    if (fcb->use_state) {
      if (!strcmp(fcb->filename, dirname) && fcb->attr & FAT_ATTR_DIR) {
        rmfcb = fcb;
        break;
      }
    }
    rmindex++;
  }
  if (!rmfcb) {
    debug_log("dirname: %s not found\n", dirname);
    return -1;
  }

  struct tmp_dir_t tmpdir = tmp_open_dir(rmfcb);
  for_each_tmpdir(tmpdir, fcb) {
    if (fcb->use_state) {
      if (compare(fcb->filename, !=, ".") && compare(fcb->filename, !=, "..")) {
        debug_log("fat_rmdir: cannot remove nonempty dir\n");
        return -1;
      }
    }
  }
  tmp_close_dir(&tmpdir, false);

  // 释放目录空间
  int first_id = rmfcb->first_id;
  while (first_id != BLOCK_END) {
    int next_id = get_fat1[first_id].id;
    get_fat1[first_id].id = BLOCK_FREE;
    first_id = next_id;
  }
  sync_fat2();

  // 清除目录的FCB记录
  rmfcb->use_state = 0;
  current_dir.count = rmindex * sizeof(struct fcb_t);
  do_fat_write(current_dirfd, rmfcb, sizeof(struct fcb_t));

  // 如果删除的FCB是最后一块,说明此目录的大小有变化,需要更新它的长度
  if (rmindex + 1 == current_dir.fcb.length / sizeof(struct fcb_t)) {
    for (fcb = rmfcb; rmindex >= 0 && fcb->use_state == 0; rmindex--, fcb--) {
      current_dir.fcb.length -= sizeof(struct fcb_t);
    }
    current_dir.fcb_state = 1;  // 需要更新 FCB
  }
  return 0;
}

struct fcb_t *fat_list(int *count) {
  if (count) {
    *count = current_dir.fcb.length / sizeof(struct fcb_t);
  }
  return *get_current_fcb();
}

int fat_create(const char *filename) {
  assert(filename != NULL, "invalid filename");
  assert(strlen(filename) > 0, "filename is empty");
  assert(strlen(filename) < 8, "filename is too long");

  int i = 0, file_id = -1;
  struct fcb_t *fcb;
  for_each_current_fcb(fcb) {
    if (fcb->use_state) {
      // TODO 比较 extname
      if (compare(filename, ==, fcb->filename)) {
        debug_log("fat_create: file already exists");
        return -1;
      }
    } else if (file_id == -1) {
      file_id = i;
    }
    i++;
  }

  // 申请空 FCB
  if (file_id == -1) {
    file_id = current_dir.fcb.length / sizeof(struct fcb_t);
  }

  struct fat_datetime now = fat_now();
  struct fcb_t file = {
      .first_id = BLOCK_END,  // 等待写入数据时再分配block
      .attr = FAT_ATTR_FILE,
      .date = now.date,
      .time = now.time,
      // .extname = "",
      .use_state = true,
      .length = 0,
  };
  strcpy(file.filename, filename);

  // 保存文件 FCB
  current_dir.count = file_id * sizeof(struct fcb_t);
  do_fat_write(current_dirfd, &file, sizeof(file));

  return 0;
}

int fat_delete(const char *filename) {
  assert(filename != NULL, "invalid filename");
  assert(strlen(filename) > 0, "filename is empty");
  assert(strlen(filename) < 8, "filename is too long");

  int i = 0, rm_id = -1;
  struct fcb_t *fcb, *rmfcb;
  for_each_current_fcb(fcb) {
    if (fcb->use_state && !(fcb->attr & FAT_ATTR_DIR)) {
      if (compare(filename, ==, fcb->filename)) {
        rmfcb = fcb;
        rm_id = i;
        break;
      }
    }
    i++;
  }
  if (rm_id == -1) {
    debug_log("fat_delete: file not exists");
    return -1;
  }

  // 释放文件占用的 BLOCK
  for (int i = rmfcb->first_id; i && i != BLOCK_END; i = get_fat1[i].id) {
    get_fat1[i].id = BLOCK_FREE;
  }

  // 释放文件占用的 FCB
  rmfcb->use_state = false;
  current_dir.count = rm_id * sizeof(struct fcb_t);
  do_fat_write(current_dirfd, rmfcb, sizeof(struct fcb_t));

  // 如果文件 FCB 位于末尾，释放多余空间
  if (rm_id + 1 == current_dir.fcb.length / sizeof(struct fcb_t)) {
    for (i = rm_id, fcb = rmfcb; i >= 0 && !fcb->use_state; i--, fcb--) {
      current_dir.fcb.length -= sizeof(struct fcb_t);
    }
    current_dir.fcb_state = true;  // 需要更新
  }

  return 0;
}

int fat_open(const char *filename) {
  assert(strlen(filename) < 8, "filename is too long");

  int i = 0, file_id = -1;
  struct fcb_t *fcb, *filefcb;
  for_each_current_fcb(fcb) {
    if (fcb->use_state && !(fcb->attr & FAT_ATTR_DIR)) {
      if (compare(filename, ==, fcb->filename)) {
        filefcb = fcb;
        file_id = i;
        break;
      }
    }
    i++;
  }
  if (file_id == -1) {
    debug_log("fat_open: no such file\n");
    return -1;
  }

  int fd = get_free_openfd();
  if (fd == -1) {
    debug_log("fat_open: reach max openfiles\n");
    return -1;
  }

  struct file_t file = {
      .fcb = *filefcb,
      .count = 0,
      .fcb_state = 0,
      .open_state = 1,
      .dir_block = current_dir.fcb.first_id,
      .dir_offset = file_id * sizeof(struct fcb_t),
  };

  sprintf(file.dirname, "%s/%s", current_dir.dirname, filename);
  current_useropens[fd] = file;
  current_dirfd = fd;
  return fd;
}

int fat_close(int fd) {
  assert(fd >= 0 || fd < MAX_OPENCNT, "invalid file descriptor");

  int parent_fd = -1;
  struct file_t *file = current_useropens + fd, *parent = NULL;

  if (fd == 0) {
    if (file->fcb_state) {
      file->count = 0;
      do_fat_write(fd, &file->fcb, sizeof(file->fcb));
    }
    return 0;
  }

  for (int i = 0; i < MAX_OPENCNT; i++) {
    struct file_t *f = current_useropens + i;
    if (i != fd && f->open_state) {
      if (file->dir_block == f->fcb.first_id) {
        parent_fd = i;
        parent = f;
        break;
      }
    }
  }
  if (!parent) {
    debug_log("fat_close: no parent directory");
    return -1;
  }

  if (file->fcb_state) {
    // 更新文件FCB
    parent->count = file->dir_offset;
    do_fat_write(parent_fd, &file->fcb, sizeof(file->fcb));
    if (file->fcb.attr & FAT_ATTR_DIR) {
      // 更新父目录FCB
      strcpy(file->fcb.filename, ".");
      file->count = 0;
      do_fat_write(fd, &file->fcb, sizeof(file->fcb));
    }
    file->fcb_state = 0;
  }

  file->open_state = 0;
  current_dirfd = parent_fd;
  return 0;
}

int fat_chdir(const char *dirname) {
  assert(strlen(dirname) < 8, "dirname is too long");

  if (!strcmp(dirname, ".")) {
    return 0;
  }

  // 回到上一级目录
  if (compare(dirname, ==, "..")) {
    if (current_dirfd != 0) {
      fat_close(current_dirfd);
    }
    return 0;
  }

  int i = 0, cd_id = -1;
  struct fcb_t *fcb, *cdfcb;
  for_each_current_fcb(fcb) {
    if (fcb->use_state) {
      if (fcb->attr & FAT_ATTR_DIR && compare(dirname, ==, fcb->filename)) {
        cd_id = i;
        cdfcb = fcb;
      }
    }
    i++;
  }
  if (cd_id == -1) {
    debug_log("fat_cd: target directory not found\n");
    return -1;
  }

  int dirfd = get_free_openfd();
  if (dirfd == -1) {
    debug_log("fat_cd: reach max openfiles\n");
    return -1;
  }

  struct file_t cddir = {
      .count = 0,
      .fcb_state = 0,
      .open_state = 1,
      .fcb = *cdfcb,
      .dir_block = current_dir.fcb.first_id,
      .dir_offset = cd_id * sizeof(struct fcb_t),
  };
  sprintf(cddir.dirname, "%s/%s", current_dir.dirname, cddir.fcb.filename);
  current_useropens[dirfd] = cddir;
  current_dirfd = dirfd;

  return 0;
}

int fat_read(int fd, void *buf, u32 len) { return do_fat_read(fd, buf, len); }
int fat_write(int fd, void *buf, u32 len) { return do_fat_write(fd, buf, len); }

int fat_eof(int fd) {
  assert(fd >= 0 && fd <= MAX_OPENCNT, "invalid fd");
  struct file_t *op = current_useropens + fd;
  return op->count >= op->fcb.length;
}

int fat_getline(char **buf, size_t *bufcap, int fd) {
  assert(buf != NULL, "buf is empty");
  assert(fd >= 0 && fd <= MAX_OPENCNT, "invalid fd");

  static char bufline[BUFSIZ];
  *bufcap = BUFSIZ;
  *buf = bufline;

  if (fat_eof(fd)) return -1;

  char ch;
  int len = 0;
  while (do_fat_read(fd, &ch, 1) == 1 && len < sizeof bufline) {
    bufline[len++] = ch;
    if (ch == '\n') {
      bufline[len] = '\0';
      return len;
    }
  }
  bufline[len] = '\0';
  return len;
}

int fat_trunc(int fd, int len) {
  assert(fd >= 0 && fd <= MAX_OPENCNT, "invalid fd");

  struct file_t *of = current_useropens + fd;
  if (len == of->fcb.length) return 0;

  of->fcb_state = 1;
  if (len < of->fcb.length) {
    of->count = 0;
    of->fcb.length = len;
    // TODO release fat space
    return 0;
  }

  of->count = of->fcb.length;
  int siz = len - of->fcb.length;
  void *buf = malloc(siz);
  assert(buf != NULL, "malloc");
  memset(buf, 0, siz);
  int ex = do_fat_write(fd, buf, siz);
  free(buf);
  return ex;
}
