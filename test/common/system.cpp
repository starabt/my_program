/*
 * system.cpp
 *
 *  Created on: Dec 16, 2016
 *      Author: xMusk
 */
#include <stdio.h>
#include <string.h>
#include "system.h"

// 执行shell命令，并返回执行结果
// input: (cmd) need to be executed
// output: (result) execute result,char string
// return: -1: failed  0: successful
int ExeSysShellCmd(const char *cmd, char *result)
{
	if(cmd == NULL || result == NULL)
		return -1;
	int nRet = -1;
	char buf_ps[1024];
	char ps[1024]={0};
	FILE *ptr;
	strcpy(ps, cmd);

	memset(buf_ps,'\0',sizeof(buf_ps));

//	setbuf(stdin, NULL);

	if(cmd == NULL)
		return -1;

	if(result == NULL)
		return -1;

	if((ptr=popen(ps, "r"))!=NULL)
	{
		while(fgets(buf_ps, 1024, ptr)!=NULL)
		{
		   strcat(result, buf_ps);
		   if(strlen(result)>1024)
			   break;
		}
		pclose(ptr);
		ptr = NULL;
		nRet = 0;
	}
	else
	{
		printf("%s: popen %s error\n", __FUNCTION__, ps);
		nRet = -1;
	}

	return nRet;
}

// use mkfs.vfat format disk
int FormatDisk(const char *dev)
{
	char buffer[256] = {0};
	char result[1024] = {0};

	if(dev == NULL)
		return -1;
	sprintf(buffer,"mkfs.vfat %s",dev);
	if(0 == ExeSysShellCmd(buffer, result))
	{
		printf("%s: FormatDisk %s successfully\n", __FUNCTION__, dev);
		return 0;
	}
	else
	{
		printf("%s: FormatDisk %s failed!\n", __FUNCTION__, dev);
		return -1;
	}
}

//
// use fuser cmd to umount dir
int ForceUmmout(const char *dir)
{
	char buffer[256] = {0};
	char result[1024] = {0};

	if(dir == NULL)
		return -1;
	sprintf(buffer,"fuser -k %s",dir);
	if(0 == ExeSysShellCmd(buffer, result))
	{
		printf("%s: ForceUmmout %s successfully\n", __FUNCTION__, dir);
		return 0;
	}
	else
	{
		printf("%s: ForceUmmout %s failed!\n", __FUNCTION__, dir);
		return -1;
	}
}

