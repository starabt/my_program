/***********************************************************
    Copyright (C), 2016,Guang Zhou Tongda auto electric Co., Ltd.
    File name:      ptypes.h
    Author:         Tony gao
    Version:        1.0
    Date:           2017/02/18
    Description:    param参数类型定义头文件
    History:
        Date            Author          Version       Modification
*************************************************************/
#ifndef __PTYPES_H__
#define __PTYPES_H__
#include <string>
#include "const.h"

#define PARAM_CONFIG_MAX_MEMBERS	200
#define MAX_CONFIG_MONITOR_CENTER   5   //监控中心最大数
#define MAX_CONFIG_CAN_NUM          4  //最多支持几路CAN

#define APP_RUN_FILE_ROOTDIR "/APP"   //程序运行文件根目录
#define APP_CONFIG_FILE_ROOTDIR "/APP/paramFile"   //程序运行相关文件所在目录

#define PACK_ALIGN	__attribute__((packed))

//此结构体的大小固定为512bytes
typedef struct _ParamConfigStoreHead_
{
	uint	size;            // SYS_CONFIG 配置结构体的大小
	uint 	totalMembers;    // SYS_CONFIG 有多少个成员
	ushort 	memberSize[PARAM_CONFIG_MAX_MEMBERS];    //每个结构体的大小
	char	mark[16];         //  标识
	char	reserved[80];
} PACK_ALIGN PARAM_CONFIG_STORE_HEAD;

//
// 公共结构体
//

// 配置结构体头
typedef struct _ParamConfigHead_
{
	char	signature[8];        // 配置文件标识
	char	reserved[16];
} PACK_ALIGN PARAM_CONFIG_HEAD;

//
// 设备基本信息
//
typedef struct _ParamConfigBaseInfo_
{
	char	devModel[24];               // 设备型号
	char	hardwareVersion[32];        // 硬件版本号
	char	softwareVersion[32];        // 软件版本号
	char	configureVersion[8];        // 配置版本号
	char	devName[32];                // 设备名称
	uchar	c_spot_check_statue;		//是否处于抽样检测中,“0x01"表示处于抽样，“0x02”表示否，“0XFE”表示异常，“0XFF”表示无效
	char	reserved[6];        //
}PACK_ALIGN PARAM_CONFIG_BASE_INFO;

//
// 网络参数
//

// 1.服务器IP+端口号
typedef struct _ConfigNetworkIPPort_
{
	uchar	centerTotalNum;        // 一共有几路监控中心
	char    centerip[16];		//监控中心服务器IP1
	char	connectPort[10];         // 连接端口
	char	uploadprotocoltype;      // 上传数据协议类型
	char    link_status;
	uchar	 centerNum;        // 标识是哪一路监控中心
	uchar	url_len;		//url name len
	char	url_name[256];		//url name
	ushort	url_port;
	char	reserved[16];
	bool 	client_on;			//链路是否开启
} PACK_ALIGN PARAM_CONFIG_NETWORK;


//服务器管理
/*
typedef struct _ParamConfigNetwork_
{
	CONFIG_NETWORk_IP_PORT    	monitor[MAX_CONFIG_MONITOR_CENTER];   // 管理所有监控中心IP和端口
	
} PACK_ALIGN PARAM_CONFIG_NETWORK;
*/


//
// 车辆信息
//
typedef struct _ParamConfigCarInfo_
{
	char    userinfo[32];      // 终端用户信息（车厂信息）
	char	devserialNo[21];   // 产品序列号20位	
	char 	vin[18];           // 车辆VIN号17位
	char	reserved[8];
} PACK_ALIGN PARAM_CONFIG_CAR_INFO;


//
// CAN波特率配置
//
//
typedef struct _CanSt_
{
	uchar   cantotalnum;
	uint	baudRate;    // 波特率
	char    cancollectprotocoltype[32];      // CAN采集协议类型版本信息
	uchar	canPort;        // 标识哪一路can
	char    candevname[5];  //can0
	char 	reserved[4];
} PACK_ALIGN PARAM_CONFIG_CAN;

/*
typedef struct _ParamConfigCan_
{
	CAN_ST	can[MAX_CONFIG_CAN_NUM];        //管理所有的CAN波特率配置
} PACK_ALIGN PARAM_CONFIG_CAN;
*/

//
// ftp 参数
//
typedef struct _ParamConfigFtp_
{
	string trans;
	ushort 	port;        // 服务器端口
	string	ip;                // 服务器ip
	string 	user;        // 用户名
	string  psw;        // 密码
	string	work_dir;
} PARAM_CONFIG_FTP;

//
// cycle time
//
typedef struct _ParamCycletime_
{
	ushort  local_save_time_cycle;	//ms 0~60 000
	ushort  rtmsg_upload_cycle;		//s 1~600
	ushort	alarmmsg_upload_cycle;	//ms 0~60 000
	uchar	heartbeat_upload_cycle;	//s  1~240
	ushort	c_reply_overtime;		//s 1~600
	ushort	s_reply_overtime;		//s 1~600
	uchar	login_interval_after3times;	//min 1~240
	char 	reserved[4];
} PACK_ALIGN PARAM_CONFIG_CYCLE_TIME;

// wifi搜索结果
typedef struct _ParamWifiScanResult_
{
	char	essid[32];        // 最多支持32个字节
	char	encType;        // 0-无加密;1-wep;2-wpa/wpa2(802.1x);3-wpa-psk/wpa2-psk.目前终端支持0、1、3这三种连接
	char	signalLevel;    // 信号强度(单位 格)1-5
	char	reserved[2];            
} PACK_ALIGN PARAM_WIFI_SCAN_RESULT;

// 
// wifi连接配置
//
typedef struct _ParamConfigWifiConnect_
{
	char	essid[32];        // 最多支持32个字节,支持手动输入和从搜索中获取
	char	key[64];        // 密码
	unsigned char connectFlag;    // 只读, 0-没有连接到无线路由;1-已经连接到无线路由
	unsigned char signalLevel;    // 只读, 信号强度, 1~5格
	char	reserved[14];
} PACK_ALIGN PARAM_CONFIG_WIFI_CONNECT;

#undef PACK_ALIGN
#endif