/*******************************************************************************
    Copyright (C), 2016,Guang Zhou Tongda auto electric Co., Ltd.
    File name:      monitor_process.h
    Author:         Tony gao
    Version:        1.0
    Date:           2018/03/28
    Description:    用来监测运行程序的内存内容
    History:
        Date            Author          Version       Modification
*******************************************************************************/
#ifndef _MONITOR_PROCESS_H_
#define _MONITOR_PROCESS_H_
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <pthread.h>

#define PACK_ALIGN  __attribute__((packed))

typedef struct 
{
    pthread_mutex_t cond_lock;
    pthread_cond_t cond;

}COND_MUTEX;
enum
{
    ALOW_SHARE_CMD = '0',
    BASE_INFO_CMD,
    NET_INFO_CMD,
    SPI_INFO_CMD,
    QUIT_CMD = 'q'
};
//基本信息
typedef struct  
{
    bool Is_writing_baseinfo;
    int clientnum;
    unsigned char system_time[6];
    bool connet_status;
    bool login_status;
    float online_time;
    float outline_time;
    bool SIM_status;
    char ICCID[21];
    int DCEsignal;
    unsigned char gps_num;
    char serverIP[16];
    char serverPort[6];
    char software_version[20];
    char hardware_version[20];
    char terminalID[14];
    char vin[18];
    unsigned char acc_on;
    unsigned char charge_on;
    float voltage;
}PACK_ALIGN BASE_INFO;
//网络收发 数据
typedef struct 
{
    int net_recvlen;
    char net_recvdata[3][2048];
    int net_sendlen;
    char net_senddata[3][2048];
}PACK_ALIGN NET_INFO;
//spi收发数据
typedef struct 
{
    int spi_recvlen;
    char spi_recvdata[1024];
    int spi_sendlen;
    char spi_senddata[1024];
}PACK_ALIGN SPI_INFO;
typedef struct sys_infos_t
{
    bool ALOW_SHARE_MEM;
    BASE_INFO base_info;
    NET_INFO net_info;
    SPI_INFO spi_info;
}PACK_ALIGN sys_infos;
sys_infos *l_system_infos;
#undef PACK_ALIGN

#endif //_MONITOR_PROCESS_H_