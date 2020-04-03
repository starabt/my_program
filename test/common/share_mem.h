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

#define PACK_ALIGN  __attribute__((packed))

//can info 
typedef struct _CAN_INFO_STRUCT_
{
    int flag;
    int canport;  //  标识是哪个CAN口发出的数据    
	unsigned int    CanId; 	
	unsigned char   packdata_len;
	char    CanVal[8];  //CANID对应的数据
	bool    need_deal; 
    int run_location; 
    int run_location_pop;
}PACK_ALIGN CAN_INFO;


//cansplit info 
typedef struct _CAN_SPLIT_INFO_STRUCT_
{
    int can_0_split_run_location; 
    int can_1_split_run_location;
    int can_2_split_run_location;

}PACK_ALIGN CAN_SPLIT_INFO;
//tcp info

//hard info
typedef struct _HARD_INFO_STRUCT_
{
    int run_location; 
    int gps_run_location;
    int G4_run_location;
    int IO_run_location;
    
}PACK_ALIGN HARD_INFO;

typedef struct sys_infos_t
{
	CAN_INFO can_info_0;
	CAN_INFO can_info_1;
	CAN_INFO can_info_2;
    CAN_SPLIT_INFO cansplit_info;
    HARD_INFO hard_info;
	
}PACK_ALIGN sys_infos;
#undef PACK_ALIGN

int get_infos_address(struct sys_infos_t **infos_addr);


#endif //_SHARE_MEM_H_