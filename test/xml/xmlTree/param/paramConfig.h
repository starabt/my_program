//说明: 对于网络等特别重要的参数实行双备份的方式。

#ifndef __SYSCONFIG_H__
#define __SYSCONFIG_H__

//#define PACK_ALIGN	__attribute__((packed))

#include "const.h"
#include "paramConfDefault.h"
#include "ptypes.h"

#define MD5_KEY_SIZE		16

#define MAX_PARAM_CONFIG_SIZE	    (12*1024) 
#define PARAM_CONFIG_MAX_MEMBERS	200
#define PARAM_CONFIG_MARK	        "Tonygao20160217"  //标识15位



#define PACK_ALIGN	__attribute__((packed))

//
// 系统配置结构,本结构体成员的顺序一旦定下来就不能做任何修改。
// 但是可以对某个成员结构体进行扩展
//
typedef struct _ParamConfig_
{
#define		INDEX_PARAM_CONFIG_HEAD	            	0
           	PARAM_CONFIG_HEAD	                	head;
#define		INDEX_PARAM_CONFIG_BASE_INFO	    	1
        	PARAM_CONFIG_BASE_INFO                 	baseInfo;
#define		INDEX_PARAM_CONFIG_NETWORK             	2
        	PARAM_CONFIG_NETWORK                 	network[MAX_CONFIG_MONITOR_CENTER];
#define		INDEX_PARAM_CONFIG_CAR_INFO	    	    3
        	PARAM_CONFIG_CAR_INFO             	    carinfo;
#define		INDEX_PARAM_CONFIG_CAN                  4
        	PARAM_CONFIG_CAN		                can[MAX_CONFIG_CAN_NUM];
        	
#define		INDEX_PARAM_CONFIG_FTP	    	        5   
        	PARAM_CONFIG_FTP             	        ftp;
#define     INDEX_PARAM_CYCLE_TIME                  6  
            PARAM_CONFIG_CYCLE_TIME                 cycletime;
        	
#define		INDEX_PARAM_CONFIG_TOTAL	        	7 //SYS_CONFIG 总共有多少个成员

} PACK_ALIGN SYS_CONFIG;

#undef  PACK_ALIGN

//初始化系统配置
void InitParamConfig();

//其他模块调用该函数保存配置
int SaveParamConfig();

//获取指定系统参数
int GetParamConfig( int index, void *pBuf, int len, int n);
//设置指定的系统参数
int SetParamConfig( int index, void *pBuf, int len, int n);

//恢复出厂配置，恢复包含网络的参数为出厂配置
void SysConfigRestoreFactoryConf();

//初始化参数成员的地址
void SysConfigInitMemberAddr();

//恢复出厂配置，恢复除网络参数以外的参数为出厂配置
void SysConfigSetDefaultParam();


bool GetHostByName(char *hostIP,char *hostPort,int tcp_num);


//1 attention please:
/* !!! 注意, 为了实现参数配置的兼容: 要往 SYS_CONFIG 结构体里面添加成员,
	一定要修改下面成员:
0. #define		INDEX_PARAM_CONFIG_TOTAL ***
1. static void SysConfigInitMemberAddr()
2. SysConfigpRestoreDefaultParam();
3. static void SysConfigInitStoreHead( PARAM_CONFIG_STORE_HEAD *pStoreHead )
4. int GetParamConfig( int index, char *pBuf, int len, int n)
5. int SetParamConfig( int index, char *pBuf, int len, int n)
6. paramManage.cpp 和 paramManage.h
*/

#endif

