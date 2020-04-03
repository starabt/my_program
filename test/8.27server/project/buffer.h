/* Buffer.h */
#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

struct Buffer{
	/* 缓冲区容量，用于 malloc 申请内存空间 */
    size_t capacity;
    /* 累计所有写入操作实际写入的字节总数，其对 capacity 取余即为‘下一个写入位置’ */
    size_t byte_writed_count;
    /* 累计所有读取操作实际读取的字节总数，其对 capacity 取余即为‘下一个读取位置’ */
    size_t byte_readed_count;
    /* 指向实际缓冲区 */
    char *data;
};
/* 初始化缓冲区 buf，使用指定容量 capacity 申请内存空间 */
void buffer_init(struct Buffer *buf, size_t capacity);
/* 版本一：读写函数，内部每次读写一个字节，
   将指针 chars 指向的长度为 len 的数据写入缓冲区 buf，
   返回值：实际写入的字节数，可能小于 len，当缓冲区可写空间不足时。 */
size_t buffer_write(struct Buffer *buf, char *chars, size_t len);
/* 从缓冲区 buf 中读取长度为 len 的数据到指针 chars 指向的空间，
   返回值：实际读取的字节数，可能小于 len，当缓冲区没有足够的数据时。 */
size_t buffer_read(struct Buffer *buf, char *chars, size_t len);
/* 版本二：读/写函数，内部使用 memcpy 函数进行内存复制，效率高 */
size_t buffer_write_by_memcpy(struct Buffer *buf, char *chars, size_t len);
size_t buffer_read_by_memcpy(struct Buffer *buf, char *chars, size_t len);
size_t buffer_only_read_by_memcpy(struct Buffer *buf, char *chars, size_t len);//只读不取

/* （待实现）版本三：线程安全版本
   （待实现）线程安全写，应与线程安全读 Buffer_pread 配合使用 */
// size_t buffer_pwrite(struct Buffer *buf, char *chars, size_t len);
/* （待实现）线程安全读，应与线程安全写 Buffer_pwrite 配合使用 */
// size_t buffer_pread(struct Buffer *buf, char *chars, size_t len);

/* 返回值：缓冲区中已缓存的（可读取）字节数 */
size_t buffer_available_read(struct Buffer *buf);
/* 返回值：缓冲区可写入的字节数 */
size_t buffer_available_write(struct Buffer *buf);
/* 返回值：缓冲区容量 capacity */
size_t buffer_capacity(struct Buffer *buf);
/* 清空缓冲区，实际上仅仅重置读/写指针，缓冲区容量不变 */
void buffer_clear(struct Buffer *buf);
/* 销毁/释放缓冲区，free 内存资源 */
void buffer_destroy(struct Buffer *buf);
/* 简单错误日志输出至 stderr */
void errlog(const char *msg);
/* 简单日志输出至 stdout */
void infolog(const char *msg);

#endif