  #ifndef __SYSCONFDEFAULT_H__
#define __SYSCONFDEFAULT_H__

#include <iostream>

//for head
#define PARAM_CONFIG_SIGNATURE	"Tonygao"   //Tonygao ,该宏固定不变(长度为7)

//for baseinfo
#define DEV_MODEL	            "TD-D-62-V01"         //产品型号
#define DEV_HARDWARE_VERSION    "C1.7D"             //硬件版本

#define DEV_SOFTWARE_VERSION	"TAH01"             //软件版本
#define DEV_CONFIG_VERSION	    "v1.00"             //配置版本
#define DEV_NAME               "TD_CAN_MONITOR"     //产品名字

#define APP_WORK_DIR "/APP/"


#define PARAM_CONFIG_DEFAULT_DEV_VIN             ""   //100台测试终端默认VIN 2017/12/07  Java和net平台(域名解析)
// #define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM         "TD4G11C070001" //100台测试终端默认VIN 2017/12/07  Java和net平台(域名解析) 
#define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM         "" //100台测试终端默认VIN 2017/12/07  Java和net平台(域名解析) 



//for userinfo
#define  USER_INFO              "广州通达"     //用户信息

#define	XML_MSG_DEV_FILENAME	    "dev.xml"
#define	XML_MSG_DEV_NODE	    "dev"

#define XML_MSG_DEV_DEVID 		"devID"
#define XML_MSG_DEV_VIN 		"vin"
#define XML_MSG_DEV_USERINFO 		"userInfo"

#define	PARAM_CONFIG_DEFAULT_DEV_DEVID ""
#define	PARAM_CONFIG_DEFAULT_DEV_VIN  "GZTDT0191201STD01"
#define	PARAM_CONFIG_DEFAULT_DEV_USERINFO ""


#define PARAM_CONFIG_DEFAULT_NET_TOTAL_NUM  1
//server plate use ip port
#define	PARAM_CONFIG_DEFAULT_PLATE_STATUS1 "on"		// on or off
#define	PARAM_CONFIG_DEFAULT_PLATE_TYPE1 "ip"		//ip or domain
#define	PARAM_CONFIG_DEFAULT_PLATE_PTL1 "gb32960"			//协议
#define PARAM_CONFIG_DEFAULT_PLATE_IP1 "120.76.154.240" 
#define PARAM_CONFIG_DEFAULT_PLATE_PORT1 "7789" 
#define PARAM_CONFIG_DEFAULT_PLATE_DOMAIN_1 "td013.e-bus.cc" //通达升级服务器
#define PARAM_CONFIG_DEFAULT_PLATE_DOMAIN_PORT_1 "7781" //通达升级服务器

#define	PARAM_CONFIG_DEFAULT_PLATE_STATUS2 "off"		// on or off
#define	PARAM_CONFIG_DEFAULT_PLATE_TYPE2 "ip"		//ip or domain
#define	PARAM_CONFIG_DEFAULT_PLATE_PTL2 "gb32960"			//协议
#define PARAM_CONFIG_DEFAULT_PLATE_IP2 "120.76.154.240" 
#define PARAM_CONFIG_DEFAULT_PLATE_PORT2 "7789" 
#define PARAM_CONFIG_DEFAULT_PLATE_DOMAIN_2 "td014.e-bus.cc" //通达升级服务器 186
#define PARAM_CONFIG_DEFAULT_PLATE_DOMAIN_PORT_2 "7781" //通达升级服务器

#define	PARAM_CONFIG_DEFAULT_PLATE_STATUS3 "off"		// on or off
#define	PARAM_CONFIG_DEFAULT_PLATE_TYPE3 "ip"		//ip or domain
#define	PARAM_CONFIG_DEFAULT_PLATE_PTL3 "gb32960"			//协议
#define PARAM_CONFIG_DEFAULT_PLATE_IP3 "120.76.154.240" 
#define PARAM_CONFIG_DEFAULT_PLATE_PORT3 "7789" 
#define PARAM_CONFIG_DEFAULT_PLATE_DOMAIN_3 "td000.e-bus.cc" //通达升级服务器
#define PARAM_CONFIG_DEFAULT_PLATE_DOMAIN_PORT_3 "7781" //通达升级服务器


#define	XML_MSG_NET_FILENAME	    "net.xml"
#define	XML_MSG_NET_NODE	    "net"
#define	XML_MSG_PLATE_NODE	    "plate"
#define	XML_MSG_PLATE_STATUS "status"		//是否开启
#define	XML_MSG_PLATE_TYPE "type"		//ip 还是域名
#define	XML_MSG_PLATE_PTL "ptl"			//协议
#define	XML_MSG_PLATE_IP "ip"
#define	XML_MSG_PLATE_PORT "port"
#define	XML_MSG_PLATE_URL "url"
#define	XML_MSG_PLATE_URLPORT "urlport"




// for ftp

#define	PARAM_CONFIG_DEFAULT_FTP_UP_PORT		"10095"
#define	PARAM_CONFIG_DEFAULT_FTP_UP_IP	        "200.200.4.193"
#define	PARAM_CONFIG_DEFAULT_FTP_UP_USER	    "lxc"
#define	PARAM_CONFIG_DEFAULT_FTP_UP_PASSWD	    "123456"
#define	PARAM_CONFIG_DEFAULT_FTP_UP_SERVDIR	    "snapphoto"
#define	XML_MSG_FTP_FILENAME	    "ftp.xml"
#define	XML_MSG_FTP_NODE	    "ftp"

#define	XML_MSG_FTP_UP_PORT		"port"
#define	XML_MSG_FTP_UP_IP	        "servIP"
#define	XML_MSG_FTP_UP_USER	    "user"
#define	XML_MSG_FTP_UP_PASSWD	    "psw"
#define	XML_MSG_FTP_UP_SERVDIR	    "servDir"





#endif

