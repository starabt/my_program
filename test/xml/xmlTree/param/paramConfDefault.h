  #ifndef __SYSCONFDEFAULT_H__
#define __SYSCONFDEFAULT_H__

#include "const.h"

//for head
#define PARAM_CONFIG_SIGNATURE	"Tonygao"   //Tonygao ,该宏固定不变(长度为7)

//for baseinfo
#define DEV_MODEL	            "TD-D-62-V01"         //产品型号
#define DEV_HARDWARE_VERSION    "S2.0"             //硬件版本

#define DEV_SOFTWARE_VERSION	"TAH01"             //软件版本
#define DEV_CONFIG_VERSION	    "v1.00"             //配置版本
#define DEV_NAME               "TD_CAN_MONITOR"     //产品名字

#define APP_WORK_DIR "/APP/"

//for DevSerialno
// #define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM	        "TD4G11A0E0005"      //产品序列号(长度为13)TD 2位+2位年16进制（17年）+1位月+2位日16进制+4位编号16进制

// #define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM            "T117083000002"
// #define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM         "HSLTEST0000000001"
// #define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM         "HSLTEST0000000113"

//for vin

// #define PARAM_CONFIG_DEFAULT_DEV_VIN             "11111111111111111"   //车辆VIN号17位
 // #define PARAM_CONFIG_DEFAULT_DEV_VIN                "TDgzgtest17080401"   //车辆VIN号17位

// #define PARAM_CONFIG_DEFAULT_DEV_VIN             "ZJJTEST0000000113"   //车辆VIN号17位

// #define PARAM_CONFIG_DEFAULT_DEV_VIN             "AKTEST00000000011"   //车辆VIN号17位
 // #define PARAM_CONFIG_DEFAULT_DEV_VIN                "LNE4CC3LXG0000121"   //车辆VIN号17位

 // #define PARAM_CONFIG_DEFAULT_DEV_VIN                "L9GCBF6G7H2000035"   //车辆VIN号17位


//#define PARAM_CONFIG_DEFAULT_DEV_VIN             "L9GHBF8G7G2005530"   //车辆VIN号17位
//#define PARAM_CONFIG_DEFAULT_DEV_VIN               "TDTEST17093000005"   //车辆VIN号17位



// #define PARAM_CONFIG_DEFAULT_DEV_VIN             "ZHYLTEST201711181"   //实验室测试2017/11/18  
// #define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM         "TD4G11B120001" //实验室测试2017/11/18



// #define PARAM_CONFIG_DEFAULT_DEV_VIN             "ZHYLTEST201710143"   //珠海银隆三路can测试2017/11/1  
// #define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM         "TD4G11A0E0003" //珠海银隆三路can测试2017/11/1  

// #define PARAM_CONFIG_DEFAULT_DEV_VIN             "ZHYLTEST201710144"   //珠海银隆三路can测试2017/11/1  
// #define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM         "TD4G11A0E0004" //珠海银隆三路can测试2017/11/1 

// #define PARAM_CONFIG_DEFAULT_DEV_VIN             "LCF5DDRC0G0ZS0103"   //珠海银隆三路can测试2017/11/1  guobiao
// #define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM         "TD4G11A0E0003" //珠海银隆三路can测试2017/11/1  



// #define PARAM_CONFIG_DEFAULT_DEV_VIN             "LCFH1FYA4G0Z03760"   //珠海银隆三路can测试2017/11/28  楚风CE023 guobiao
// #define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM         "" //珠海银隆三路can测试2017/11/28  huayi test

// #define PARAM_CONFIG_DEFAULT_DEV_VIN             "171116GQ07CZH0001"
// #define PARAM_CONFIG_DEFAULT_DEV_VIN             "LCFH1FYA2G0ZS2212"   //珠海银隆三路can测试2017/11/28  楚风CE020 guobiao
// #define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM         "" //珠海银隆三路can测试2017/11/28  huayi test


// #define PARAM_CONFIG_DEFAULT_DEV_VIN             "LCFG6CPB7G0ZS2311"   //珠海银隆三路can测试2017/11/1  guobiao
// #define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM         "TD4G11A0E0003" //珠海银隆三路can测试2017/11/1  


// #define PARAM_CONFIG_DEFAULT_DEV_VIN             "ZHYLTW20171109001"   //寄给台湾2017/11/9  
// #define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM         "TD4G11B090001" //寄给台湾2017/11/9  


// #define PARAM_CONFIG_DEFAULT_DEV_VIN                "TEST2017112000001"   //书广测试2017/11/20  
// #define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM         "TD4G11B140001" //书广测试2017/11/20 
	

// #define PARAM_CONFIG_DEFAULT_DEV_VIN             "BJHT0001710300001"   //时空巴士GPS测试2017/11/9  
// #define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM         "TD4G11A1E0001" //时空巴士GPS测试2017/11/9 
// #define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM         "" //时空巴士GPS测试2017/11/9  

 
// #define PARAM_CONFIG_DEFAULT_DEV_VIN             "GZTDTEST171128001"   //时空巴士GPS测试2017/11/28 
// #define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM         "TD4G11B100001" //时空巴士GPS测试2017/11/9  



// #define PARAM_CONFIG_DEFAULT_DEV_VIN             "BJHT0001711220002"   //时空巴士GPS测试2017/11/22  
// #define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM         "TD4G11B160002" //时空巴士GPS测试2017/11/22 

	
// #define PARAM_CONFIG_DEFAULT_DEV_VIN             "ZHYLTEST201710141"   //珠海银隆三路can测试2017/11/1  
// #define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM         "TD4G11A0E0001" //珠海银隆三路can测试2017/11/1


// #define PARAM_CONFIG_DEFAULT_DEV_VIN             "ZHYLTEST201710142"   //珠海银隆三路can测试2017/11/1 已已寄台湾
// #define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM         "TD4G11A0E0002" //珠海银隆三路can测试2017/11/1 已寄台湾

// #define PARAM_CONFIG_DEFAULT_DEV_VIN                "ZHYLTEST201711211"   //测试2017/11/21  
// #define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM         "TD4G11B150001" //测试2017/11/21


#define PARAM_CONFIG_DEFAULT_DEV_VIN             ""   //100台测试终端默认VIN 2017/12/07  Java和net平台(域名解析)
// #define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM         "TD4G11C070001" //100台测试终端默认VIN 2017/12/07  Java和net平台(域名解析) 
#define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM         "" //100台测试终端默认VIN 2017/12/07  Java和net平台(域名解析) 

// #define PARAM_CONFIG_DEFAULT_DEV_VIN             "ZHYLTW20171209003"   //书光-台湾 2017/12/09  
// #define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM         "TD4G11C070001" //100台测试终端默认VIN 2017/12/09   
// #define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM         "TD4G11C090003" //书光-台湾  

// #define PARAM_CONFIG_DEFAULT_DEV_VIN             "L9GCBF7D4J2003334"   //台湾2017/12/14 
// #define PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM         "TD4G11C090004" //台湾2017/12/14 


//for userinfo
#define  USER_INFO              "广州通达"     //用户信息

//for monitor center
// //AT300
//#define PARAM_CONFIG_DEFAULT_MONITOR_IP1 "120.77.89.60"
//#define PARAM_CONFIG_DEFAULT_MONITOR_PORT1 "28022"
// #define PARAM_CONFIG_DEFAULT_MONITOR_IP1 "211.147.239.138"
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT1 "28021"
//test server 
// #define PARAM_CONFIG_DEFAULT_MONITOR_IP1 "192.168.199.160"
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT1 "8888"
#define PARAM_CONFIG_DEFAULT_MONITOR_IP5 "192.168.199.160"
#define PARAM_CONFIG_DEFAULT_MONITOR_PORT5 "8888"
#define PARAM_CONFIG_DEFAULT_MONITOR_IP3 "192.168.199.160"
#define PARAM_CONFIG_DEFAULT_MONITOR_PORT3 "8889"
// //中车
// #define PARAM_CONFIG_DEFAULT_MONITOR_IP1 "112.35.23.52"
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT1 "7780"
// #define PARAM_CONFIG_DEFAULT_MONITOR_IP2 "112.126.90.186"
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT2 "7780"
//台湾储能平台
// #define PARAM_CONFIG_DEFAULT_MONITOR_IP1 "14.21.33.230" 
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT1 "8886"

// #define PARAM_CONFIG_DEFAULT_MONITOR_IP2 "200.200.1.208"
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT2 "10094"


// #define PARAM_CONFIG_DEFAULT_MONITOR_IP1 "112.126.90.186"
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT1 "7780"


// //台湾平台
// #define PARAM_CONFIG_DEFAULT_MONITOR_IP1 "14.21.33.230" 
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT1 "7790"
//银隆平台.net
// #define PARAM_CONFIG_DEFAULT_MONITOR_IP1 "14.21.33.230" 
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT1 "7780"
//银隆平台java
#define PARAM_CONFIG_DEFAULT_MONITOR_IP2 "14.21.33.230" 
#define PARAM_CONFIG_DEFAULT_MONITOR_PORT2 "5188"
//时空巴士平台
// #define PARAM_CONFIG_DEFAULT_MONITOR_IP2 "120.76.154.240" 
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT2 "7781"


// #define PARAM_CONFIG_DEFAULT_MONITOR_IP1 "120.76.154.240"
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT1 "7781"

// #define PARAM_CONFIG_DEFAULT_MONITOR_IP1 "218.205.176.44"
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT1 "19006"
// local server
// #define PARAM_CONFIG_DEFAULT_MONITOR_IP1 "200.200.4.194"
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT1 "10094"
//通达测试平台
// #define PARAM_CONFIG_DEFAULT_MONITOR_IP1 "58.248.27.228"
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT1 "7117"
//通达专用平台
// #define PARAM_CONFIG_DEFAULT_MONITOR_IP5 "121.33.233.34"
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT5 "7117"

//台湾新平台
// #define PARAM_CONFIG_DEFAULT_MONITOR_IP2 "14.21.33.230" 
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT2 "7790"  //台湾新平台


//Java新能源繁体和英文版
// #define PARAM_CONFIG_DEFAULT_MONITOR_IP1 "14.21.33.230" 
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT1 "8888"  


//java平台
// #define PARAM_CONFIG_DEFAULT_MONITOR_IP3 "58.248.27.228"
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT3 "7117"

// #define PARAM_CONFIG_DEFAULT_MONITOR_IP3 "120.76.154.240" 
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT3 "7781"

//java平台
// #define PARAM_CONFIG_DEFAULT_MONITOR_IP1 "58.248.27.228"
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT1 "7117"


//扬子江平台
#define PARAM_CONFIG_DEFAULT_MONITOR_IP1 "120.79.57.113"
#define PARAM_CONFIG_DEFAULT_MONITOR_PORT1 "8888"
// #define PARAM_CONFIG_DEFAULT_MONITOR_IP5 "120.79.57.113"
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT5 "8888"
#define PARAM_CONFIG_DEFAULT_MONITOR_IP4 "120.79.57.113"
#define PARAM_CONFIG_DEFAULT_MONITOR_PORT4 "8888"

//扬子江平台
// #define PARAM_CONFIG_DEFAULT_MONITOR_IP3 "120.79.57.113"
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT3 "8888"


//通达东风升级平台
// #define PARAM_CONFIG_DEFAULT_MONITOR_IP2 "120.76.154.240"
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT2 "7781"


// #define PARAM_CONFIG_DEFAULT_MONITOR_IP1 "112.126.90.186"
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT1 "7780"


//东风平台
// #define PARAM_CONFIG_DEFAULT_MONITOR_IP1 "58.49.84.92"
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT1 "9090"


//维保平台-TEST
// #define PARAM_CONFIG_DEFAULT_MONITOR_IP4 "120.76.194.12" 
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT4 "7781" 

//维保平台-车间
// #define PARAM_CONFIG_DEFAULT_MONITOR_IP3 
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT4 "7781" "120.76.154.240" 
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT3 "7789" 


//国家平台
// #define PARAM_CONFIG_DEFAULT_MONITOR_IP1 "218.205.176.44" 
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT1 "19006" 

// #define PARAM_CONFIG_DEFAULT_MONITOR_IP2 "218.205.176.44" 
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT2 "19006"

// #define PARAM_CONFIG_DEFAULT_MONITOR_IP3 "218.205.176.44" 
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT3 "19006"

// #define PARAM_CONFIG_DEFAULT_MONITOR_IP4 "218.205.176.44" 
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT4 "19006"

//台湾新平台
// #define PARAM_CONFIG_DEFAULT_MONITOR_IP1 "14.21.33.230" 
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT1 "7790"  //台湾新平台


// #define PARAM_CONFIG_DEFAULT_MONITOR_IP1 "14.21.33.230" //yinlong server
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT1 "8888" 


// #define PARAM_CONFIG_DEFAULT_MONITOR_IP3 "58.248.27.228"
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT3 "60008"


//#define PARAM_CONFIG_DEFAULT_MONITOR_PORT1 "7780"
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT2 "7781"
//#define PARAM_CONFIG_DEFAULT_MONITOR_PORT3 "19006"
// #define PARAM_CONFIG_DEFAULT_MONITOR_PORT1 "7780"







// for http

// #define PARAM_CONFIG_DEFAULT_DOMAIN_1 "telematics.dfmc.com.cn" //东风平台
// #define PARAM_CONFIG_DEFAULT_DOMAIN_PORT_1 "15005" //东风平台

#define PARAM_CONFIG_DEFAULT_DOMAIN_1 "td013.e-bus.cc" //通达升级服务器
#define PARAM_CONFIG_DEFAULT_DOMAIN_PORT_1 "7781" //通达升级服务器


// #define PARAM_CONFIG_DEFAULT_DOMAIN_1 "td000.e-bus.cc" //通达升级服务器
// #define PARAM_CONFIG_DEFAULT_DOMAIN_PORT_1 "7781" //通达升级服务器

// #define PARAM_CONFIG_DEFAULT_DOMAIN_1 "td006.e-bus.cc" //通达升级服务器
// #define PARAM_CONFIG_DEFAULT_DOMAIN_PORT_1 "7780" //通达升级服务器

#define PARAM_CONFIG_DEFAULT_DOMAIN_2 "td014.e-bus.cc" //通达升级服务器 186
#define PARAM_CONFIG_DEFAULT_DOMAIN_PORT_2 "7781" //通达升级服务器


// #define PARAM_CONFIG_DEFAULT_DOMAIN_2 "td000.e-bus.cc" //通达升级服务器
// #define PARAM_CONFIG_DEFAULT_DOMAIN_PORT_2 "7781" //通达升级服务器

#define PARAM_CONFIG_DEFAULT_DOMAIN_3 "td000.e-bus.cc" //通达升级服务器
#define PARAM_CONFIG_DEFAULT_DOMAIN_PORT_3 "7781" //通达升级服务器




#define UPLOAD_PROTOCOL_TYPE1               0x01     //上传数据协议类型
#define UPLOAD_PROTOCOL_TYPE2               0x02     //上传数据协议类型
#define UPLOAD_PROTOCOL_TYPE3               0x03     //上传数据协议类型
#define UPLOAD_PROTOCOL_TYPE4               0x04     //上传数据协议类型
#define UPLOAD_PROTOCOL_TYPE5               0x05     //上传数据协议类型

#define PARAM_CONFIG_DEFAULT_CENTER_TOTAL_NUM  3

//for can
#define PARAM_CONFIG_DEFAULT_CAN_TOTAL_NUM  3
#define DEV_DEFAULT_CAN_BAUDRATE1		250
#define DEV_DEFAULT_CAN_BAUDRATE2       250
#define DEV_DEFAULT_CAN_BAUDRATE3       250
#define CAN_COLLECT_PROTOCOL_TYPE0      "BMS_otm_v1.0"
#define CAN_COLLECT_PROTOCOL_TYPE1       "VCU_tongda_v1.0"
#define CAN_COLLECT_PROTOCOL_TYPE2       "VCU_tongda_v1.0"
#define CAN_DEFAULT_CAN_PORT0           0
#define CAN_DEFAULT_CAN_PORT1           1
#define CAN_DEFAULT_CAN_PORT2           2
#define CAN_DEFAULT_CAN_DEVNAME0         "can0"
#define CAN_DEFAULT_CAN_DEVNAME1         "can1"
#define CAN_DEFAULT_CAN_DEVNAME2         "can2"


// for ftp
#define	PARAM_CONFIG_DEFAULT_FTP_ENABLE		1
#define	PARAM_CONFIG_DEFAULT_FTP_PORT		21
#define	PARAM_CONFIG_DEFAULT_FTP_IP	        "58.248.27.228"
#define	PARAM_CONFIG_DEFAULT_FTP_USER	    "Tony"
#define	PARAM_CONFIG_DEFAULT_FTP_PASSWD	    "123456789"
#define	PARAM_CONFIG_DEFAULT_FTP_UP	    	1

//for cycle time
#define PARAM_CONFIG_DEFAULT_LOCAL_SAVE_TIME    1000   
#define PARAM_CONFIG_DEFAULT_RTMSG_UPLOAD_TIME  10      
#define PARAM_CONFIG_DEFAULT_ALARM_UPLOAD_TIME  1   
#define PARAM_CONFIG_DEFAULT_HEARTBEAT_TIME     60      
#define PARAM_CONFIG_DEFAULT_C_REPLY_OVERTIME   60      
#define PARAM_CONFIG_DEFAULT_S_REPLY_OVERTIME   60*3      
#define PARAM_CONFIG_DEFAULT_LOGIN_INTERVAL_TIME    30 

#endif
