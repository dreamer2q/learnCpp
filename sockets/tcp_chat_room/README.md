# TCP 聊天室

TCP 可靠传输协议, 有状态, 长连接。
基于 TCP 的聊天室要考虑:

1. 服务端要同时处理多个客户端的数据请求, 使用多线程还是单线程? 
2. 如果使用多线程如何处理数据同步/竞争(做到线程安全)? 
3. 如果使用单线程如何处理多个用户的连接?

数据的传输, 序列化与反序列化的问题:
1. TCP 数据流没有分段/分帧的概念, 如何确定数据传输的分界点?
2. 不定长数据的传输

使用序列化库, 完成结构体的序列化与反序列化的工作, 用于支持数据的流式传输。

 - [tpl](https://github.com/troydhanson/tpl)

## 需求

- 用户进入与离开聊天室(加入退出提醒)
- 进入聊天室可以看到最近 10 条公开记录
- 用户发起一条公开消息
- [可选] 用户发起一个私有消息

## 数据结构体

```cpp
struct pkg_t {
    uint16 proto;
    uint8 type;
    uint16 size;
}
```
消息数据包前缀, 指示接下来的数据类型。这里依赖数据的发送前后顺序。

```cpp
struct login {
    char username[32];
    char password[32];
}
```
用户登录请求。

```cpp
struct login_response {
    uint8 result;
}
```
用户登录请求结果(失败, 成功创建, 恢复登录)。

```cpp
struct chat {
    char* text;
}
```
用户发送聊天内容。


```cpp
struct show_chat {
    char username[32];
    char* text;
}
```
系统下发聊天记录, 这里其实缺少了时间信息。


```cpp
struct welcome {
    char* message;
    uint8 count;
    struct show_chat* chats;
}
```
系统欢迎信息, 同时携带最多 10 条历史聊天记录。

## 服务端

### 用户数据维护

使用`双向链表`维护用户数据

```cpp
struct clnt_node {
  pthread_t thread;
  int clnt_fd;
  struct sockaddr_in clnt_addr;
  socklen_t clnt_len;
  struct list_head list;
  struct login lg;
};
```

以上保存了客户端最基础的一些信息, 其中最常用的就是 `clnt_fd`(套接字描述符) 和 `lg`(用户信息)。
有一点不太好的就是: 一个用户可以建立多个连接, 对应地这里就有多个链表节点, 有点浪费。可以将 `clnt_fd` 改成数组的形式, 同时限制同一个用户最大连接数量。

既然已经保存了 `thread` 信息, 服务端自然而然使用的就是多线程了, 每一个客户端对应一个 `thread` 用于处理用户发送的消息(其实主要原因是我对 `select` 等机制不熟悉)。

当服务端收到客户端的消息后, 广播给所有用户(也包括发消息的用户), 这样基本上就完成了简单的聊天室了。

更进一步, 可以根据用户 `uid` 实现私聊功能。

同样使用 `双向链表` 维护聊天聊天列表。(思路和 `UDP` 聊天室一样)。

## send/recv 的操作是否线程安全?

这里有一个点需要注意一下, 设想有多个线程同时向控制台输出内容, 比如说：
- 线程一: 输出 `11111....`
- 线程二: 输出 `22222....`

当这两个线程并发执行的时候, 由于调度时机无法预知因此可能会出现很多种可能的输出。
在 `Linux` 中 `everything is a file` 因此 `socket` 也可以看成一种“远程文件”的读写。
所以我就比较担心, 多线程情况下是不是会出现类似的情况, 导致发送的数据出现“错位”的情况。

- [are-parallel-calls-to-send-recv-on-the-same-socket-valid](https://stackoverflow.com/questions/1981372/are-parallel-calls-to-send-recv-on-the-same-socket-valid)

高赞的回答是: 
> 在 `POSIX` 标准下 `send/recv` 都是原子操作因此不需要担心多线程并非的问题。

虽然不用担心并发的问题, 但是每条消息都携带了`pkt_t`一个数据包前缀, 因此这里需要注意时序问题, 为了稳妥起见还是需要加一个同步机制。

## 客户端

相比于之前的 `UDP` 聊天室, 这里的客户端直接被动接受聊天内容, 因此主要的复杂逻辑都在服务端上面了。

所以, 客户端的重点还是在于 `ncurses` 的 UI 上面, 这里我发现一个问题, 由于客户端也是多线程的, 因此出现了并发刷新控制台导致的乱码问题。

解决方案是, 对 `ncurse` 的刷新使用 `mutex` 锁进行同步。

## 数据的序列化

`TCP` 流式传输需要我们做好数据的分割操作, 这里我使用 `tpl` 进行数据的序列化。`tpl` 保证每次读取数据(包括流数据)不会超过最后一位, 换句话说它知道自己要读取多少长度的数据, 然后会准确的读取这些数据。非常适合当前消息处理场景。

其它方面, `tpl` 允许数据可变长的, 会为 `char*` 不定长的数据分配内存, 不需要手动处理这些数据了（最后还是需要手动释放）。

使用 `tpl` 序列化结构体数据, 有其缺陷, 结构体里面不能包含不定长度的数组, 因此针对 `struct welcome_t` 结构的序列化其实比较麻烦:

```cpp
char msg_buf[BUFSIZ] = {0};
sprintf(msg_buf, "welcome to tcp-chat room, you have logged as %s",
        lg.username);
uint8_t msg_cnt = chat_list_count > 10 ? 10 : chat_list_count;
struct show_chat chat_item;
char* msg_ptr = msg_buf;
tpl_node* tn = tpl_map("sA(S(c#s))", &msg_ptr, &chat_item, 32);
tpl_pack(tn, 0);
list_for_each(iter, &chat_list_head) {
    struct chat_node* n = container_of(iter, struct chat_node, list);
    chat_item = n->chat;
    tpl_pack(tn, 1);
    debug_log("tpl_pack: %d: %s\n", msg_cnt, chat_item.text);
    if (--msg_cnt == 0) break;
}
write_pkg(fd, TYPE_WELCOME);
tpl_dump(tn, TPL_FD, fd);
tpl_free(tn);
```

这里将最外层的 `S(..)` 给拆掉了, 因为结构体的本质就是一堆按照循序排列的不同类型的变量罢了。

```cpp
char* msg_ptr;
struct show_chat chat_item;
tpl_node* tn = tpl_map("sA(S(c#s))", &msg_ptr, &chat_item, 32);
tpl_load(tn, TPL_FD, serv_fd);
tpl_unpack(tn, 0);
int item_len = tpl_Alen(tn, 1);
for (int i = 0; i < item_len; i++) {
    tpl_unpack(tn, 1);
    struct chat_node* chat_node =
        (struct chat_node*)malloc(sizeof(struct chat_node));
    chat_node->chat = chat_item;
    list_add_tail(&chat_node->list, &chat_list_head);
    printf("\n%s:\n> %s\n", chat_item.username, chat_item.text);
}
tpl_free(tn);
free(msg_ptr);
```

客户端进行拆包的时候, 直接使用 `tpl_Alen` 获取数组的长度, 然后根据长度创建聊天数据。

# 总结

相比于 UDP 天生的数据分段传输, TCP 屏蔽了许多底层的细节, 以 `socket` 模型抽象给上层用户, 非常符合 `Linux everything is a file` 的理念。
可以直接使用 `read/write` 接口读写 `socket` 网络数据。(也就是说学会了操作文件, 自然而然就会写网络数据流了)。

TCP 数据传输的特点是数据流, 面对不定长度的数据需要提前获知其大小, 用于数据的分段(或者使用特定的分段标志进行分段)。
TCP 数据流运行读写同时进行, 因此往往伴随多线程模式, 分别处理读写情况。
