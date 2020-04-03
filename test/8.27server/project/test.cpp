/* test.c */
#include "buffer.h"

/* 简单测试 */
int main()
{
    char buffer[10];
    bzero(buffer, 10);
    struct Buffer buf;
    char str[1024];
    long int res;
    buffer_init(&buf, 10);
    buffer_write(&buf, (char*)"1234567890", 10);
    printf("1 - buffer_available_read is %d bytes\n", buffer_available_read(&buf));
    printf("1 - buffer_available_write is %d bytes\n", buffer_available_write(&buf));
    buffer_only_read_by_memcpy(&buf, (char*)(buffer + 2), 5);
    for (int i = 0; i < 10; ++i)
    {
        printf("buffer[%d]:%d\n", i, buffer[i]);
    }
   /* 
    printf("buffer capacity is %d bytes\n", buf.capacity);
    printf("writed %d\n", buffer_write(&buf, (char*)"abc", 3));
    printf("1 - buffer_available_read is %d bytes\n", buffer_available_read(&buf));
    printf("1 - buffer_available_write is %d bytes\n", buffer_available_write(&buf));

    res = buffer_read(&buf, str, res = buffer_available_read(&buf));
    str[res] = '\0';
    printf("readed str: %s\n", str);

    printf("2 - buffer_available_read is %d bytes\n", buffer_available_read(&buf));
    printf("2 - buffer_available_write is %d bytes\n", buffer_available_write(&buf));
    
    printf("writed %d\n", buffer_write(&buf, (char*)"abc123456789xyz", 10));
    printf("3 - buffer_available_read is %d bytes\n", buffer_available_read(&buf));
    printf("3 - buffer_available_write is %d bytes\n", buffer_available_write(&buf));
    res = buffer_only_read_by_memcpy(&buf, str, 8);
    str[res] = '\0';
    printf("readed str: %s\n", str);
    printf("4 - buffer_available_read is %d bytes\n", buffer_available_read(&buf));
    printf("4 - buffer_available_write is %d bytes\n", buffer_available_write(&buf));
    buffer_clear(&buf);
    buffer_destroy(&buf);*/
}