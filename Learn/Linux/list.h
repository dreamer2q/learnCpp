#ifndef _HEAD_LIST_H
#define _HEAD_LIST_H

#define offsetof(TYPE, MEMBER) ((size_t) & ((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) \
  ((type *)((char *)(ptr)-offsetof(type, member)))

struct list_head {
  struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(name) \
  { &(name), &(name) }

#define LIST_HEAD(name) struct list_head name = LIST_HEAD_INIT(name)

static inline void INIT_LIST_HEAD(struct list_head *list) {
  list->next = list;
  list->prev = list;
}

/**
 * 添加节点
 */
static inline void __list_add(struct list_head *n, struct list_head *prev,
                              struct list_head *next) {
  prev->next = n;
  n->prev = prev;
  n->next = next;
  next->prev = n;
}

static inline void list_add(struct list_head *n, struct list_head *head) {
  __list_add(n, head, head->next);
}

static inline void list_add_tail(struct list_head *n, struct list_head *head) {
  __list_add(n, head->prev, head);
}

/**
 * 删除节点
 */
static inline void __list_del(struct list_head *prev, struct list_head *next) {
  next->prev = prev;
  prev->next = next;
}

static inline void list_del(struct list_head *entry) {
  __list_del(entry->prev, entry->next);
}

static inline void __list_del_entry(struct list_head *entry) {
  __list_del(entry->prev, entry->next);
}

static inline void list_del_init(struct list_head *entry) {
  __list_del_entry(entry);
  INIT_LIST_HEAD(entry);
}

/**
 * 替换节点
 */
static inline void list_replace(struct list_head *old, struct list_head *n) {
  n->next = old->next;
  n->next->prev = n;
  n->prev = old->prev;
  n->prev->next = n;
}

/**
 * 判断链表是否为空
 */
static inline int list_empty(const struct list_head *head) {
  return head->next == head;
}

/**
 * 获取节点
 */
#define list_entry(ptr, type, member) container_of(ptr, type, member)

/**
 * 遍历节点
 */
#define list_for_each(pos, head) \
  for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_safe(pos, n, head) \
  for (pos = (head)->next, n = pos->next; pos != (head); pos = n, n = pos->next)

#endif
