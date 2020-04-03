#ifdef CHECK
#include "paramDefault.h"
#include "tinyxml.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using std::stringstream;
using std::string;
using std::cout;
using std::endl;
using std::vector;

typedef unsigned char UINT8;
template<class T>
T strtoi(const std::string& istr)
{
	T iResult;
	std::stringstream ss;
	ss << istr;
	ss >> iResult;
	return iResult;
}
template<class T>
std::string itostr(T iobj)
{
	std::string istr;
	std::stringstream ss;
	ss << iobj;
	ss >> istr;
	return istr;
}
template<class T>
std::string straddx(const std::string& strsrc,T addx)
{
	std::string istr;
	std::stringstream ss;
	ss << strsrc << addx;
	ss >> istr;
	return istr;
}
typedef struct XML_NODE_MSG_
{
	string element;
	string content;
}XML_NODE_MSG;
typedef vector<XML_NODE_MSG*> XML_NODE_VEC;

typedef struct CONF_FTP_
{
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
	UINT8 onNum;
	CONF_PLATE plates[PARAM_CONFIG_DEFAULT_NET_TOTAL_NUM];
}CONF_NET;

void default_init_net(CONF_NET& conf_net,XML_NODE_VEC& xml_net_v)
{
	string tmpStr;
	int plate_clientNo;
	plate_clientNo = 0;
	if(plate_clientNo+1 > PARAM_CONFIG_DEFAULT_NET_TOTAL_NUM)
		goto EXIT_INIT_NET;
	conf_net.plates[plate_clientNo].plate_clientNo = plate_clientNo;	//标识那一路链路
	
	tmpStr = straddx("XML_MSG_PLATE_STATUS",plate_clientNo);
	cout << "tmpStr:" << tmpStr << endl;
	conf_net.plates[plate_clientNo].plate_status.element 		= 		straddx(XML_MSG_PLATE_STATUS,plate_clientNo);
	conf_net.plates[plate_clientNo].plate_status.content 		= 		PARAM_CONFIG_DEFAULT_PLATE_STATUS1;
	conf_net.plates[plate_clientNo].plate_type.element 		= 		straddx(XML_MSG_PLATE_TYPE,plate_clientNo);
	conf_net.plates[plate_clientNo].plate_type.content 		= 		PARAM_CONFIG_DEFAULT_PLATE_TYPE1;
	conf_net.plates[plate_clientNo].plate_ptl.element 			= 		straddx(XML_MSG_PLATE_PTL,plate_clientNo);
	conf_net.plates[plate_clientNo].plate_ptl.content 			= 		PARAM_CONFIG_DEFAULT_PLATE_PTL1;
	conf_net.plates[plate_clientNo].plate_ip.element 			= 		straddx(XML_MSG_PLATE_IP,plate_clientNo);
	conf_net.plates[plate_clientNo].plate_ip.content 			= 		PARAM_CONFIG_DEFAULT_PLATE_IP1;
	conf_net.plates[plate_clientNo].plate_port.element 		= 		straddx(XML_MSG_PLATE_PORT,plate_clientNo);
	conf_net.plates[plate_clientNo].plate_port.content 		= 		PARAM_CONFIG_DEFAULT_PLATE_PORT1;
	conf_net.plates[plate_clientNo].plate_url.element 			= 		straddx(XML_MSG_PLATE_URL,plate_clientNo);
	conf_net.plates[plate_clientNo].plate_url.content 			= 		PARAM_CONFIG_DEFAULT_PLATE_DOMAIN_1;
	conf_net.plates[plate_clientNo].plate_urlport.element 		= 		straddx(XML_MSG_PLATE_URLPORT,plate_clientNo);
	conf_net.plates[plate_clientNo].plate_urlport.content 		= 		PARAM_CONFIG_DEFAULT_PLATE_DOMAIN_PORT_1;

	plate_clientNo = 1;
	if(plate_clientNo+1 > PARAM_CONFIG_DEFAULT_NET_TOTAL_NUM)
		goto EXIT_INIT_NET;
	conf_net.plates[plate_clientNo].plate_clientNo = plate_clientNo;	//标识那一路链路
	conf_net.plates[plate_clientNo].plate_status.element 		= 		straddx(XML_MSG_PLATE_STATUS,plate_clientNo);
	conf_net.plates[plate_clientNo].plate_status.content 		= 		PARAM_CONFIG_DEFAULT_PLATE_STATUS2;
	conf_net.plates[plate_clientNo].plate_type.element 		= 		straddx(XML_MSG_PLATE_TYPE,plate_clientNo);
	conf_net.plates[plate_clientNo].plate_type.content 		= 		PARAM_CONFIG_DEFAULT_PLATE_TYPE2;
	conf_net.plates[plate_clientNo].plate_ptl.element 			= 		straddx(XML_MSG_PLATE_PTL,plate_clientNo);
	conf_net.plates[plate_clientNo].plate_ptl.content 			= 		PARAM_CONFIG_DEFAULT_PLATE_PTL2;
	conf_net.plates[plate_clientNo].plate_ip.element 			= 		straddx(XML_MSG_PLATE_IP,plate_clientNo);
	conf_net.plates[plate_clientNo].plate_ip.content 			= 		PARAM_CONFIG_DEFAULT_PLATE_IP2;
	conf_net.plates[plate_clientNo].plate_port.element 		= 		straddx(XML_MSG_PLATE_PORT,plate_clientNo);
	conf_net.plates[plate_clientNo].plate_port.content 		= 		PARAM_CONFIG_DEFAULT_PLATE_PORT2;
	conf_net.plates[plate_clientNo].plate_url.element 			= 		straddx(XML_MSG_PLATE_URL,plate_clientNo);
	conf_net.plates[plate_clientNo].plate_url.content 			= 		PARAM_CONFIG_DEFAULT_PLATE_DOMAIN_2;
	conf_net.plates[plate_clientNo].plate_urlport.element 		= 		straddx(XML_MSG_PLATE_URLPORT,plate_clientNo);
	conf_net.plates[plate_clientNo].plate_urlport.content 		= 		PARAM_CONFIG_DEFAULT_PLATE_DOMAIN_PORT_2;


	plate_clientNo = 2;
	if(plate_clientNo+1 > PARAM_CONFIG_DEFAULT_NET_TOTAL_NUM)
		goto EXIT_INIT_NET;
	conf_net.plates[plate_clientNo].plate_clientNo = plate_clientNo;	//标识那一路链路
	conf_net.plates[plate_clientNo].plate_status.element 		= 		straddx(XML_MSG_PLATE_STATUS,plate_clientNo);
	conf_net.plates[plate_clientNo].plate_status.content 		= 		PARAM_CONFIG_DEFAULT_PLATE_STATUS3;
	conf_net.plates[plate_clientNo].plate_type.element 		= 		straddx(XML_MSG_PLATE_TYPE,plate_clientNo);
	conf_net.plates[plate_clientNo].plate_type.content 		= 		PARAM_CONFIG_DEFAULT_PLATE_TYPE3;
	conf_net.plates[plate_clientNo].plate_ptl.element 			= 		straddx(XML_MSG_PLATE_PTL,plate_clientNo);
	conf_net.plates[plate_clientNo].plate_ptl.content 			= 		PARAM_CONFIG_DEFAULT_PLATE_PTL3;
	conf_net.plates[plate_clientNo].plate_ip.element 			= 		straddx(XML_MSG_PLATE_IP,plate_clientNo);
	conf_net.plates[plate_clientNo].plate_ip.content 			= 		PARAM_CONFIG_DEFAULT_PLATE_IP3;
	conf_net.plates[plate_clientNo].plate_port.element 		= 		straddx(XML_MSG_PLATE_PORT,plate_clientNo);
	conf_net.plates[plate_clientNo].plate_port.content 		= 		PARAM_CONFIG_DEFAULT_PLATE_PORT3;
	conf_net.plates[plate_clientNo].plate_url.element 			= 		straddx(XML_MSG_PLATE_URL,plate_clientNo);
	conf_net.plates[plate_clientNo].plate_url.content 			= 		PARAM_CONFIG_DEFAULT_PLATE_DOMAIN_3;
	conf_net.plates[plate_clientNo].plate_urlport.element 		= 		straddx(XML_MSG_PLATE_URLPORT,plate_clientNo);
	conf_net.plates[plate_clientNo].plate_urlport.content 		= 		PARAM_CONFIG_DEFAULT_PLATE_DOMAIN_PORT_3;

EXIT_INIT_NET:
	for(int i = 0; i < plate_clientNo +1; i++)
	{
		xml_net_v.push_back(&conf_net.plates[i].plate_status);
		xml_net_v.push_back(&conf_net.plates[i].plate_type);
		xml_net_v.push_back(&conf_net.plates[i].plate_ptl);
		xml_net_v.push_back(&conf_net.plates[i].plate_ip);
		xml_net_v.push_back(&conf_net.plates[i].plate_port);
		xml_net_v.push_back(&conf_net.plates[i].plate_url);
		xml_net_v.push_back(&conf_net.plates[i].plate_urlport);
	}	
	return;
}
void default_init_ftp(CONF_FTP& conf_ftp,XML_NODE_VEC& xml_ftp_v)
{
	conf_ftp.ftp_ip.element = XML_MSG_FTP_UP_IP;
	conf_ftp.ftp_ip.content = PARAM_CONFIG_DEFAULT_FTP_UP_IP;
	xml_ftp_v.push_back(&conf_ftp.ftp_ip);

	conf_ftp.ftp_port.element = XML_MSG_FTP_UP_PORT;
	conf_ftp.ftp_port.content = PARAM_CONFIG_DEFAULT_FTP_UP_PORT;
	xml_ftp_v.push_back(&conf_ftp.ftp_port);

	conf_ftp.ftp_user.element = XML_MSG_FTP_UP_USER;
	conf_ftp.ftp_user.content = PARAM_CONFIG_DEFAULT_FTP_UP_USER;
	xml_ftp_v.push_back(&conf_ftp.ftp_user);

	conf_ftp.ftp_pwd.element = XML_MSG_FTP_UP_PASSWD;
	conf_ftp.ftp_pwd.content = PARAM_CONFIG_DEFAULT_FTP_UP_PASSWD;
	xml_ftp_v.push_back(&conf_ftp.ftp_pwd);

	conf_ftp.ftp_servdir.element = XML_MSG_FTP_UP_SERVDIR;
	conf_ftp.ftp_servdir.content = PARAM_CONFIG_DEFAULT_FTP_UP_SERVDIR;
	xml_ftp_v.push_back(&conf_ftp.ftp_servdir);
	return;
}
bool save_xml_file(const string& filePath,const XML_NODE_VEC& xml_in_v,const string& rootElement)
{
	TiXmlDocument xmlDoc; //xml文档指针
	xmlDoc.InsertEndChild(TiXmlDeclaration("1.0", "UTF-8", "yes"));
	TiXmlNode* pRoot = xmlDoc.InsertEndChild(TiXmlElement(rootElement.c_str()));
	if(pRoot== NULL)
	{
		cout << "create root node failed:" << rootElement << endl;
		return false;
	}
	for(auto it = xml_in_v.begin();it != xml_in_v.end();it++)
	{
		pRoot -> InsertEndChild( TiXmlElement( (*it) -> element.c_str() ) ) \
			  -> InsertEndChild(    TiXmlText( (*it) -> content.c_str() ) );
	}
	return xmlDoc.SaveFile(filePath.c_str());
}
bool read_xml_file(const string& filePath,XML_NODE_VEC& xml_out_v)
{
	bool bRet;
	TiXmlDocument xmlDoc(filePath.c_str());
	
	bRet = xmlDoc.LoadFile();
	if (!bRet)
	{
		cout << "could not load the xml file.Error:" << xmlDoc.ErrorDesc() << endl;
		return false;
	}
	TiXmlElement* pRootElement = xmlDoc.RootElement();
	if(!pRootElement)
	{
		cout << "could not get rootNode of the xml file.Error:" << xmlDoc.ErrorDesc() << endl;
		return false;
	}
	TiXmlElement* pNode = NULL;
	for(auto it = xml_out_v.begin();it != xml_out_v.end();it++)
	{
		pNode = pRootElement->FirstChildElement( (*it) -> element.c_str() );
		if(pNode)
		{
			(*it) -> content = pNode->GetText();
			cout << (*it) -> element << ":" << (*it) -> content << endl;
		}
		/*只要有一个解析错误，就返回错误*/
		else
			return false;
	}
	return true;

}
int main(int argc, char const *argv[])
{
	CONF_FTP confFtp;
	XML_NODE_VEC xmlFtp;
	default_init_ftp(confFtp,xmlFtp);
	CONF_NET confNet;
	XML_NODE_VEC xmlNet;
	default_init_net(confNet,xmlNet);
	// cout << "ip:" << confFtp.ftp_ip.content << endl;
	// cout << "port:" << confFtp.ftp_port.content << endl;
	// cout << "user:" << confFtp.ftp_user.content << endl;
	// cout << "pwd:" << confFtp.ftp_pwd.content << endl;
	// cout << "servdir:" << confFtp.ftp_servdir.content << endl;
	bool bRet ;
	bRet = save_xml_file(XML_MSG_NET_FILENAME,xmlNet,XML_MSG_NET_NODE);
	cout << "save bRet:" << bRet << endl;
	bRet = read_xml_file(XML_MSG_NET_FILENAME,xmlNet);
	cout << "read bRet:" << bRet << endl;
	return 0;
}
#endif