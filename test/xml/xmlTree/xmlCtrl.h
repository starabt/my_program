#ifndef XML_TREE_H_
#define XML_TREE_H_

#include "paramDefault.h"
#include "tinyxml.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "const.h"
using std::stringstream;
using std::string;
using std::cout;
using std::endl;
using std::vector;
#include "Ntree.hpp"

typedef struct XML_NODE_ATTR_
{
	string attrName;
	string content;
}XML_NODE_ATTR;
typedef struct XML_NODE_MSG_
{
	string element;
	string content;
}XML_NODE_MSG;

typedef vector<XML_NODE_MSG*> XML_NODE_VEC;

typedef struct CONF_FTP_
{
	XML_NODE_MSG name;//if more than one obj, will be needed
	XML_NODE_MSG ftp_ip;
	XML_NODE_MSG ftp_port;
	XML_NODE_MSG ftp_user;
	XML_NODE_MSG ftp_pwd;
	XML_NODE_MSG ftp_servdir;
}CONF_FTP;

typedef enum CONNECT_STATUS_
{
	CONNECTING,
	CONNECTED,
	NOCONNECT,
	CONNECT_UNKNOWN,
}CONNECT_STATUS;
typedef enum LOGIN_STATUS_
{
	LOGING,
	LOGGED,
	NOLOGIN,
	LOGIN_UNKNOWN,
}LOGIN_STATUS;
typedef struct CONF_PLATE_
{
	CONNECT_STATUS connect_status;	//noneed to add in xml conf file
	LOGIN_STATUS login_status;		//noneed to add in xml conf file
	UINT8 plate_clientNo;	//标识那一路链路
	XML_NODE_MSG name;		//if more than one obj, will be needed
	XML_NODE_MSG plate_status;		//是否开启
	XML_NODE_MSG plate_type;		//ip 还是域名
	XML_NODE_MSG plate_ptl;			//协议
	XML_NODE_MSG plate_ip;
	XML_NODE_MSG plate_port;
	XML_NODE_MSG plate_url;
	XML_NODE_MSG plate_urlport;
}CONF_PLATE;
typedef struct CONF_NET_
{
	UINT8 maxLinkNum;
	std::vector<unsigned char> onLinkNo;
	CONF_PLATE plates[PARAM_CONFIG_DEFAULT_NET_TOTAL_NUM];
}CONF_NET;

typedef struct CONF_DEVICE_INFO_
{
	XML_NODE_MSG	devID;        // 产品序列号
	XML_NODE_MSG    userInfo;      // 终端用户信息（车厂信息）
	XML_NODE_MSG 	vin;           // 车辆VIN号
}CONF_DEVICE_INFO;

class XML_CTRL
{
public:
	XML_CTRL(string element);
	~XML_CTRL();

	typedef TREE_NODE<XML_NODE_MSG*> XML_NODE;
	typedef NTREE<XML_NODE> XML_TREE;
	bool xml_ctrl_parse(const string& xmlFile);
	bool xml_ctrl_save(const string& xmlFile);
	XML_TREE& GetXmlTree();
private:
	XML_TREE xmlTree;
	bool xml_ctrl_save_inside(TiXmlElement* fatherElem,XML_NODE* helpNode=NULL);
	bool xml_ctrl_parse_inside(TiXmlElement* fatherElem);
};

class SYS_CONF
{
public:
	SYS_CONF();
	~SYS_CONF();
#define INDEX_PARAM_CONFIG_DEV 0
	CONF_DEVICE_INFO confDev;
	XML_CTRL* pXmlCtrlDev;
#define	INDEX_PARAM_CONFIG_FTP	1
	CONF_FTP confFtp;
	XML_CTRL* pXmlCtrlFtp;
#define	INDEX_PARAM_CONFIG_NET	2
	CONF_NET confNet;
	XML_CTRL* pXmlCtrlNet;
};
#endif