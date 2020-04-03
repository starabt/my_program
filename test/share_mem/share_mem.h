/***********************************************************
    Copyright (C), 2016,Guang Zhou Tongda auto electric Co., Ltd.
    File name:      share_mem.h
    Author:         Tony gao
    Version:        1.0
    Date:           2018/03/27
    Description:    share memery
    History:
        Date            Author          Version       Modification
*************************************************************/
#ifndef _SHARE_MEM_H_
#define _SHARE_MEM_H_
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

// #define DELIVER 1 //是否出货版本
#define SHARE_STRING 1  //
#define SHARE_SINGLE 0

#define PACK_ALIGN  __attribute__((packed))


typedef struct sys_infos_t
{
	int age;
	
}PACK_ALIGN sys_infos;
#undef PACK_ALIGN

int get_infos_address(struct sys_infos_t **infos_addr);
int creat_shemp(struct sys_infos_t **infos_addr) ;
template  <typename SHARETYPE> 
static void share_write(char type,SHARETYPE* monitor_msg,SHARETYPE* msg,void *struct_p=NULL,int monitor_msglen=0,int msglen=0)
{
#ifdef DELIVER
    printf("deliver version ,return...\n");
    return;
#endif
    if(struct_p == NULL)
    {
        printf("the struct put in is NULL.........\n");
        return;
    }
    switch(type)
    {
        case SHARE_SINGLE:
            *monitor_msg = *msg;
            printf("monitor_msg:%d\n", *monitor_msg);
            break;
        case SHARE_STRING:
            memset(monitor_msg,0,monitor_msglen);
            memcpy(monitor_msg,msg,msglen);
            printf("monitor_msg:%s\n", monitor_msg);
            break;
        default:
            break;
    }
    return;
}

#endif //_SHARE_MEM_H_