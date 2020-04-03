/***********************************************************
    Copyright (C), 2016,Guang Zhou Tongda auto electric Co., Ltd.
    File name:      share_mem.cpp
    Author:         Tony gao
    Version:        1.0
    Date:           2018/03/27
    Description:    share memery
    History:
        Date            Author          Version       Modification
*************************************************************/
#include "share_mem.h"
static const char share_mem_name[] ="/tmp/tmpshare";
int get_infos_address(struct sys_infos_t **infos_addr)
{
	int conf_id;
	key_t conf_key = IPC_PRIVATE;
	// if(NULL == infos_addr)
	// 	return -1;
	/*creat share memory of configure*/
	if(access(share_mem_name,F_OK) == 0)
	{
		conf_key = ftok(share_mem_name, 'X');
	}
	conf_id = shmget(conf_key, 0, 0);
	if(-1 == conf_id)
	{
		printf("<get_infos_address>Get share memory fail!(%s)\n", strerror(errno));
		return -1;
	}

	*infos_addr = (struct sys_infos_t *)shmat(conf_id, NULL, 0);
	if((struct sys_infos_t *)(-1) == (*infos_addr))
	{
		printf("<get_infos_address>can not get memory address!(%s)\n", strerror(errno));
		return -1;	
	}
	return 0;
}
int creat_shemp(struct sys_infos_t **infos_addr) 
{
	int info_id;
	key_t info_key = IPC_PRIVATE;
	/*creat share memory of configure*/
	/*只为创建该临时文件*/
	int fd = open(share_mem_name,O_CREAT,0777);
	if( fd > 0 )
	{
		info_key = ftok(share_mem_name, 'X');
		close(fd);
	}
	info_id = shmget(info_key, sizeof(struct sys_infos_t), IPC_CREAT|IPC_EXCL|0660);
	if(-1 == info_id)
	{
		fprintf(stderr, "<creat_shemp>shmget:errno:%d,%s\n", errno,strerror(errno) );
		if(17 == errno)
		{
			info_id = shmget(info_key, 0, IPC_EXCL|0660);
			shmctl(info_id, IPC_RMID, NULL);
		}
		info_id = shmget(info_key, sizeof(struct sys_infos_t), IPC_CREAT|IPC_EXCL|0660);
		if(-1 == info_id)
		{
			printf("<creat_shemp>Create share memory fail!(%d)\n", errno);
			return -1;;
		}
	}
	*infos_addr = (struct sys_infos_t *)shmat(info_id, NULL, 0);
	if((struct sys_infos_t *)(-1) == (*infos_addr))
	{
		printf("<creat_shemp> can not get memory address!(%s)\n", strerror(errno));
		return -1;	
	}
	printf("create success\n");
	
	return 0;
}
/**
 * [rm_share_mem 删除共享内存]
 * @return [-1：失败 0：成功]
 */
int rm_share_mem()
{
	int rm_id;
	key_t rm_key = IPC_PRIVATE;

	if(access(share_mem_name,F_OK) == 0)
	{
		rm_key = ftok(share_mem_name, 'X');
	}
	rm_id = shmget(rm_key, 0, 0);
	if(-1 == rm_id)
	{
		printf("<rm_share_mem>Get share memory fail!(%s)\n", strerror(errno));
		return -1;
	}
	shmctl(rm_id, IPC_RMID, NULL);
	printf("<rm_share_mem>rm share memory success!\n" );
	return 0;
}