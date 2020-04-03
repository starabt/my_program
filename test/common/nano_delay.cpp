#include <stdio.h>
#include <time.h>
#include <sys/select.h>
#include <string.h>

#include "nano_delay.h"


//函数原型 int nanosleep(struct timespec *req, struct timespec *rem)
//参数列表：
//  req:要求的睡眠时间
//  rem:剩余的睡眠时间
//返回值：
//  0：成功；-1，失败，errno保存错误代码

//目的：纳秒级别的延迟
int nano_delay(unsigned long milisec)
{
    struct timespec req , rem ;
    memset(&req,0,sizeof(req));
    memset(&rem,0,sizeof(rem));
    time_t sec = (int)(milisec / 1000);
    milisec = milisec - (sec * 1000);

    unsigned long nano_delay = milisec *1000000;
    int ret = 0;
    while(nano_delay > 0)
    {
        rem.tv_sec = 0;
        rem.tv_nsec = 0;
        req.tv_sec = sec;
        req.tv_nsec = nano_delay;
        ret = (nanosleep(&req, &rem));
        if( ret== -1)
        {
            printf("nanosleep failed.\n");                
        }
        nano_delay = rem.tv_nsec;
    };
    return ret;

    // struct timeval tv;
    // tv.tv_sec = 0;
    // tv.tv_usec = milisec;
    // return select(0, NULL, NULL, NULL, &tv);
}