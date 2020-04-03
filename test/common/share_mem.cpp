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
char share_mem_name[] ="/tmp/tmpshare";

int get_infos_address(struct sys_infos_t **infos_addr)
{
	key_t conf_key;
	int conf_id;

	// if(NULL == infos_addr)
	// 	return -1;
	/*creat share memory of configure*/
	conf_key = ftok(share_mem_name, 'X');
	conf_id = shmget(conf_key, 0, 0);
	if(-1 == conf_id)
	{
		printf("<APP/CHECK>Get share memory fail!(%s)\n", strerror(errno));
		return -1;
	}

	*infos_addr = (struct sys_infos_t *)shmat(conf_id, NULL, 0);
	if((struct sys_infos_t *)(-1) == (*infos_addr))
	{
		printf("<APP/CHECK>can not get memory address!(%s)\n", strerror(errno));
		return -1;	
	}
	return 0;
}