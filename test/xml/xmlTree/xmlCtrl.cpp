
#include "xmlCtrl.h"
#include <type_traits>
#include <iostream>
#include <assert.h>
using std::is_same;
static SYS_CONF s_sysconf;
SYS_CONF::SYS_CONF()
{
	pXmlCtrlDev = new XML_CTRL(XML_MSG_DEV_NODE);
	assert(pXmlCtrlDev);
	pXmlCtrlFtp = new XML_CTRL(XML_MSG_FTP_NODE);
	assert(pXmlCtrlFtp);
	pXmlCtrlNet = new XML_CTRL(XML_MSG_NET_NODE);
	assert(pXmlCtrlNet);
}
SYS_CONF::~SYS_CONF()
{
	if(pXmlCtrlDev)
		delete pXmlCtrlDev;
	if(pXmlCtrlFtp)
		delete pXmlCtrlFtp;
	if(pXmlCtrlNet)
		delete pXmlCtrlNet;
}

XML_CTRL::XML_CTRL(string element)
{
	xmlTree.init_tree(element);
}
XML_CTRL::~XML_CTRL()
{
	xmlTree.deinit_tree();
}
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
void default_init_ftp(CONF_FTP& conf_ftp,XML_CTRL::XML_TREE& xml_tree_ftp)
{
	XML_CTRL::XML_NODE tmpNode;
	conf_ftp.ftp_ip.element = XML_MSG_FTP_UP_IP;
	conf_ftp.ftp_ip.content = PARAM_CONFIG_DEFAULT_FTP_UP_IP;
	tmpNode.init_node(conf_ftp.ftp_ip.element,&conf_ftp.ftp_ip);
	xml_tree_ftp.insert(&tmpNode,xml_tree_ftp.pRoot);
	

	conf_ftp.ftp_port.element = XML_MSG_FTP_UP_PORT;
	conf_ftp.ftp_port.content = PARAM_CONFIG_DEFAULT_FTP_UP_PORT;
	tmpNode.init_node(conf_ftp.ftp_port.element,&conf_ftp.ftp_port);
	xml_tree_ftp.insert(&tmpNode,xml_tree_ftp.pRoot);

	conf_ftp.ftp_user.element = XML_MSG_FTP_UP_USER;
	conf_ftp.ftp_user.content = PARAM_CONFIG_DEFAULT_FTP_UP_USER;
	tmpNode.init_node(conf_ftp.ftp_user.element,&conf_ftp.ftp_user);
	xml_tree_ftp.insert(&tmpNode,xml_tree_ftp.pRoot);

	conf_ftp.ftp_pwd.element = XML_MSG_FTP_UP_PASSWD;
	conf_ftp.ftp_pwd.content = PARAM_CONFIG_DEFAULT_FTP_UP_PASSWD;
	tmpNode.init_node(conf_ftp.ftp_pwd.element,&conf_ftp.ftp_pwd);
	xml_tree_ftp.insert(&tmpNode,xml_tree_ftp.pRoot);

	conf_ftp.ftp_servdir.element = XML_MSG_FTP_UP_SERVDIR;
	conf_ftp.ftp_servdir.content = PARAM_CONFIG_DEFAULT_FTP_UP_SERVDIR;
	tmpNode.init_node(conf_ftp.ftp_servdir.element,&conf_ftp.ftp_servdir);
	xml_tree_ftp.insert(&tmpNode,xml_tree_ftp.pRoot);
	return;
}
void default_init_net(CONF_NET& conf_net,XML_CTRL::XML_TREE& xml_tree_net)
{
	conf_net.maxLinkNum =  PARAM_CONFIG_DEFAULT_NET_TOTAL_NUM;
	string tmpStr;
	int plate_clientNum = 0;
	if(plate_clientNum+1 > PARAM_CONFIG_DEFAULT_NET_TOTAL_NUM)
		goto EXIT_INIT_NET;
	conf_net.plates[plate_clientNum].plate_clientNo = plate_clientNum;	//标识那一路链路
	
	// tmpStr = straddx("XML_MSG_PLATE_STATUS",plate_clientNum);
	// cout << "tmpStr:" << tmpStr << endl;

	conf_net.plates[plate_clientNum].plate_status.element 		= 		straddx(XML_MSG_PLATE_STATUS,plate_clientNum);
	conf_net.plates[plate_clientNum].plate_status.content 		= 		PARAM_CONFIG_DEFAULT_PLATE_STATUS1;
	conf_net.plates[plate_clientNum].plate_type.element 		= 		straddx(XML_MSG_PLATE_TYPE,plate_clientNum);
	conf_net.plates[plate_clientNum].plate_type.content 		= 		PARAM_CONFIG_DEFAULT_PLATE_TYPE1;
	conf_net.plates[plate_clientNum].plate_ptl.element 			= 		straddx(XML_MSG_PLATE_PTL,plate_clientNum);
	conf_net.plates[plate_clientNum].plate_ptl.content 			= 		PARAM_CONFIG_DEFAULT_PLATE_PTL1;
	conf_net.plates[plate_clientNum].plate_ip.element 			= 		straddx(XML_MSG_PLATE_IP,plate_clientNum);
	conf_net.plates[plate_clientNum].plate_ip.content 			= 		PARAM_CONFIG_DEFAULT_PLATE_IP1;
	conf_net.plates[plate_clientNum].plate_port.element 		= 		straddx(XML_MSG_PLATE_PORT,plate_clientNum);
	conf_net.plates[plate_clientNum].plate_port.content 		= 		PARAM_CONFIG_DEFAULT_PLATE_PORT1;
	conf_net.plates[plate_clientNum].plate_url.element 			= 		straddx(XML_MSG_PLATE_URL,plate_clientNum);
	conf_net.plates[plate_clientNum].plate_url.content 			= 		PARAM_CONFIG_DEFAULT_PLATE_DOMAIN_1;
	conf_net.plates[plate_clientNum].plate_urlport.element 		= 		straddx(XML_MSG_PLATE_URLPORT,plate_clientNum);
	conf_net.plates[plate_clientNum].plate_urlport.content 		= 		PARAM_CONFIG_DEFAULT_PLATE_DOMAIN_PORT_1;
	plate_clientNum ++;

	if(plate_clientNum+1 > PARAM_CONFIG_DEFAULT_NET_TOTAL_NUM)
		goto EXIT_INIT_NET;
	conf_net.plates[plate_clientNum].plate_clientNo = plate_clientNum;	//标识那一路链路
	conf_net.plates[plate_clientNum].plate_status.element 		= 		straddx(XML_MSG_PLATE_STATUS,plate_clientNum);
	conf_net.plates[plate_clientNum].plate_status.content 		= 		PARAM_CONFIG_DEFAULT_PLATE_STATUS2;
	conf_net.plates[plate_clientNum].plate_type.element 		= 		straddx(XML_MSG_PLATE_TYPE,plate_clientNum);
	conf_net.plates[plate_clientNum].plate_type.content 		= 		PARAM_CONFIG_DEFAULT_PLATE_TYPE2;
	conf_net.plates[plate_clientNum].plate_ptl.element 			= 		straddx(XML_MSG_PLATE_PTL,plate_clientNum);
	conf_net.plates[plate_clientNum].plate_ptl.content 			= 		PARAM_CONFIG_DEFAULT_PLATE_PTL2;
	conf_net.plates[plate_clientNum].plate_ip.element 			= 		straddx(XML_MSG_PLATE_IP,plate_clientNum);
	conf_net.plates[plate_clientNum].plate_ip.content 			= 		PARAM_CONFIG_DEFAULT_PLATE_IP2;
	conf_net.plates[plate_clientNum].plate_port.element 		= 		straddx(XML_MSG_PLATE_PORT,plate_clientNum);
	conf_net.plates[plate_clientNum].plate_port.content 		= 		PARAM_CONFIG_DEFAULT_PLATE_PORT2;
	conf_net.plates[plate_clientNum].plate_url.element 			= 		straddx(XML_MSG_PLATE_URL,plate_clientNum);
	conf_net.plates[plate_clientNum].plate_url.content 			= 		PARAM_CONFIG_DEFAULT_PLATE_DOMAIN_2;
	conf_net.plates[plate_clientNum].plate_urlport.element 		= 		straddx(XML_MSG_PLATE_URLPORT,plate_clientNum);
	conf_net.plates[plate_clientNum].plate_urlport.content 		= 		PARAM_CONFIG_DEFAULT_PLATE_DOMAIN_PORT_2;
	plate_clientNum ++;

	if(plate_clientNum+1 > PARAM_CONFIG_DEFAULT_NET_TOTAL_NUM)
		goto EXIT_INIT_NET;
	conf_net.plates[plate_clientNum].plate_clientNo = plate_clientNum;	//标识那一路链路
	conf_net.plates[plate_clientNum].plate_status.element 		= 		straddx(XML_MSG_PLATE_STATUS,plate_clientNum);
	conf_net.plates[plate_clientNum].plate_status.content 		= 		PARAM_CONFIG_DEFAULT_PLATE_STATUS3;
	conf_net.plates[plate_clientNum].plate_type.element 		= 		straddx(XML_MSG_PLATE_TYPE,plate_clientNum);
	conf_net.plates[plate_clientNum].plate_type.content 		= 		PARAM_CONFIG_DEFAULT_PLATE_TYPE3;
	conf_net.plates[plate_clientNum].plate_ptl.element 			= 		straddx(XML_MSG_PLATE_PTL,plate_clientNum);
	conf_net.plates[plate_clientNum].plate_ptl.content 			= 		PARAM_CONFIG_DEFAULT_PLATE_PTL3;
	conf_net.plates[plate_clientNum].plate_ip.element 			= 		straddx(XML_MSG_PLATE_IP,plate_clientNum);
	conf_net.plates[plate_clientNum].plate_ip.content 			= 		PARAM_CONFIG_DEFAULT_PLATE_IP3;
	conf_net.plates[plate_clientNum].plate_port.element 		= 		straddx(XML_MSG_PLATE_PORT,plate_clientNum);
	conf_net.plates[plate_clientNum].plate_port.content 		= 		PARAM_CONFIG_DEFAULT_PLATE_PORT3;
	conf_net.plates[plate_clientNum].plate_url.element 			= 		straddx(XML_MSG_PLATE_URL,plate_clientNum);
	conf_net.plates[plate_clientNum].plate_url.content 			= 		PARAM_CONFIG_DEFAULT_PLATE_DOMAIN_3;
	conf_net.plates[plate_clientNum].plate_urlport.element 		= 		straddx(XML_MSG_PLATE_URLPORT,plate_clientNum);
	conf_net.plates[plate_clientNum].plate_urlport.content 		= 		PARAM_CONFIG_DEFAULT_PLATE_DOMAIN_PORT_3;
	plate_clientNum ++;

EXIT_INIT_NET:
	XML_CTRL::XML_NODE tmpNode;
	

	for(int i = 0; i < plate_clientNum; i++)
	{
		XML_CTRL::XML_NODE tmpPlateNode;
		conf_net.plates[i].name.element = straddx(XML_MSG_PLATE_NODE,i);
		tmpPlateNode.init_node(conf_net.plates[i].name.element,&conf_net.plates[i].name);
		xml_tree_net.insert(&tmpPlateNode,xml_tree_net.pRoot);
		
		tmpNode.init_node(conf_net.plates[i].plate_status.element,&conf_net.plates[i].plate_status);
		xml_tree_net.insert(&tmpNode,&tmpPlateNode);
		tmpNode.init_node(conf_net.plates[i].plate_type.element,&conf_net.plates[i].plate_type);
		xml_tree_net.insert(&tmpNode,&tmpPlateNode);
		tmpNode.init_node(conf_net.plates[i].plate_ptl.element,&conf_net.plates[i].plate_ptl);
		xml_tree_net.insert(&tmpNode,&tmpPlateNode);
		tmpNode.init_node(conf_net.plates[i].plate_ip.element,&conf_net.plates[i].plate_ip);
		xml_tree_net.insert(&tmpNode,&tmpPlateNode);
		tmpNode.init_node(conf_net.plates[i].plate_port.element,&conf_net.plates[i].plate_port);
		xml_tree_net.insert(&tmpNode,&tmpPlateNode);
		tmpNode.init_node(conf_net.plates[i].plate_url.element,&conf_net.plates[i].plate_url);
		xml_tree_net.insert(&tmpNode,&tmpPlateNode);
		tmpNode.init_node(conf_net.plates[i].plate_urlport.element,&conf_net.plates[i].plate_urlport);
		xml_tree_net.insert(&tmpNode,&tmpPlateNode);
	}	
	return;
}
void default_init_dev_info(CONF_DEVICE_INFO & conf_dev,XML_CTRL::XML_TREE& xml_tree_dev)
{
	XML_CTRL::XML_NODE tmpNode;
	conf_dev.devID.element = XML_MSG_DEV_DEVID;
	conf_dev.devID.content = PARAM_CONFIG_DEFAULT_DEV_DEVID;
	tmpNode.init_node(conf_dev.devID.element,&conf_dev.devID);
	xml_tree_dev.insert(&tmpNode,xml_tree_dev.pRoot);

	conf_dev.userInfo.element = XML_MSG_DEV_USERINFO;
	conf_dev.userInfo.content = PARAM_CONFIG_DEFAULT_DEV_USERINFO ;
	tmpNode.init_node(conf_dev.userInfo.element,&conf_dev.userInfo);
	xml_tree_dev.insert(&tmpNode,xml_tree_dev.pRoot);

	conf_dev.vin.element = XML_MSG_DEV_VIN ;
	conf_dev.vin.content = PARAM_CONFIG_DEFAULT_DEV_VIN  ;
	tmpNode.init_node(conf_dev.vin.element,&conf_dev.vin);
	xml_tree_dev.insert(&tmpNode,xml_tree_dev.pRoot);
	return ;
}
void param_default_init()
{
	default_init_dev_info(s_sysconf.confDev,s_sysconf.pXmlCtrlDev->GetXmlTree());
	default_init_ftp(s_sysconf.confFtp,s_sysconf.pXmlCtrlFtp->GetXmlTree());
	default_init_net(s_sysconf.confNet,s_sysconf.pXmlCtrlNet->GetXmlTree());

	return ;
}
bool RefreshConfWithFile()
{
	bool bRet = true;
	if(!s_sysconf.pXmlCtrlDev->xml_ctrl_parse(XML_MSG_DEV_FILENAME))
		if(!s_sysconf.pXmlCtrlDev->xml_ctrl_save(XML_MSG_DEV_FILENAME))
			bRet = false;
	if(!s_sysconf.pXmlCtrlFtp->xml_ctrl_parse(XML_MSG_FTP_FILENAME))
		if(!s_sysconf.pXmlCtrlFtp->xml_ctrl_save(XML_MSG_FTP_FILENAME))
			bRet = false;
	if(!s_sysconf.pXmlCtrlNet->xml_ctrl_parse(XML_MSG_NET_FILENAME))
		if(!s_sysconf.pXmlCtrlNet->xml_ctrl_save(XML_MSG_NET_FILENAME))
			bRet = false;	
	return bRet;
}
bool InitParamConfig()
{
	bool bRet = true;
	param_default_init();
	if(!RefreshConfWithFile())
		bRet = false ;
	return bRet;
}

void* GetParamConfig(int paramIdx)
{
	bool bRet = true;
	switch(paramIdx)
	{
		case INDEX_PARAM_CONFIG_DEV:
			return (void*)&s_sysconf.confDev;
			break;
		case INDEX_PARAM_CONFIG_FTP:
			return (void*)&s_sysconf.confFtp;
			break;
		case INDEX_PARAM_CONFIG_NET:
			return (void*)&s_sysconf.confNet;
			break;
		default:
			bRet = false;
			break;
	}
	return NULL;
	// return bRet;
	
}
bool SetParamConfig(int paramIdx)
{
	bool bRet = true;
	switch(paramIdx)
	{
		case INDEX_PARAM_CONFIG_DEV:
			if(!s_sysconf.pXmlCtrlDev->xml_ctrl_save(XML_MSG_DEV_FILENAME))
				bRet = false;
		case INDEX_PARAM_CONFIG_FTP:
			if(!s_sysconf.pXmlCtrlFtp->xml_ctrl_save(XML_MSG_FTP_FILENAME))
				bRet = false;
		case INDEX_PARAM_CONFIG_NET:
			if(!s_sysconf.pXmlCtrlNet->xml_ctrl_save(XML_MSG_NET_FILENAME))
				bRet = false;
		default:
			bRet = false;
			break;
	}
	return bRet;
}
XML_CTRL::XML_TREE& XML_CTRL::GetXmlTree()
{
	return xmlTree;
}
bool XML_CTRL::xml_ctrl_parse(const string& xmlFile)
{
	bool bRet;
	TiXmlDocument xmlDoc(xmlFile.c_str());
	
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
	return xml_ctrl_parse_inside(pRootElement);
}
bool XML_CTRL::xml_ctrl_parse_inside(TiXmlElement* fatherElem)
{
	bool bRet = true;
	for(TiXmlElement* elem = fatherElem->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		string valueTmp,textTmp ;
		valueTmp = elem->Value();
		if(elem->GetText())
			textTmp = elem->GetText();
        XML_NODE *pXmlNodeTmp =  xmlTree.search(valueTmp);
        if(pXmlNodeTmp)
        {
        	pXmlNodeTmp->data->element = valueTmp;
        	pXmlNodeTmp->data->content = textTmp;
        }
        else
        	bRet = false;
        xml_ctrl_parse_inside(elem);

	}
	return bRet;
}
bool XML_CTRL::xml_ctrl_save(const string& xmlFile)
{
	bool bRet = false;
	if(xmlTree.pRoot == NULL)
	{
		printf("xmlTree no init \n");
		return false;
	}
	TiXmlDocument xmlDoc; //xml文档指针
	xmlDoc.InsertEndChild(TiXmlDeclaration("1.0", "UTF-8", "yes"));
	TiXmlNode* pRootNode = xmlDoc.InsertEndChild(TiXmlElement(xmlTree.pRoot->symbol.c_str()));
	if(pRootNode== NULL)
	{
		cout << "create root node failed:" << xmlTree.pRoot->symbol << endl;
		return false;
	}
	if(xml_ctrl_save_inside(pRootNode->ToElement(),xmlTree.pRoot))
		bRet = xmlDoc.SaveFile(xmlFile.c_str());
	return bRet;
}
bool XML_CTRL::xml_ctrl_save_inside(TiXmlElement* fatherElem,XML_NODE* helpNode)
{
	if(helpNode==NULL)
    {
        if(xmlTree.pRoot)
            helpNode=xmlTree.pRoot;
        else
            return false;
    }
    for(auto it = helpNode->childrenNode.begin();it != helpNode->childrenNode.end(); it++)
    {
    	if((*it) -> data == NULL)
    		printf("%s -> data == NULL\n",(*it) ->symbol.c_str());
    	TiXmlElement *tmpElem = new TiXmlElement( (*it) -> data->element.c_str() );
    	if(!(*it) -> data->content.empty())
    		tmpElem -> InsertEndChild(     TiXmlText( (*it) -> data->content.c_str() ) );
    	// fatherElem -> InsertEndChild( *tmpElem ) ;
    	/*用new出来的节点，使用LinkEndChild接口，最后会自行回收，不用也不能自己delete*/
    	fatherElem -> LinkEndChild(tmpElem);
		xml_ctrl_save_inside(tmpElem,(*it));
		// delete tmpElem; 
    }
    return true;
}
#ifdef CHECK
int main(int argc, char const *argv[])
{
	// XML_CTRL xmlCtrl("root");
	// printf("1111111111111111\n");
	// xmlCtrl.xml_ctrl_parse("test.xml");
	// printf("32222222222222222\n");
	// vector<XML_CTRL::XML_NODE*> xmlNodes;
	// xmlCtrl.xmlTree.get_allNodes("root",xmlNodes);
	// printf("333333333333333\n");
	// for(auto it = xmlNodes.begin();it != xmlNodes.end();it++)
	// {
	// 	cout << (*it)->data->element << ":" << (*it)->data->content << endl;
	// }
	// xmlCtrl.xml_ctrl_save("test2.xml");
	/*CONF_FTP confFtp;
	default_init_ftp(confFtp,xmlCtrl.xmlTree);
	xmlCtrl.xml_ctrl_save("ftp2.xml");*/
	/*CONF_NET confNet;
	
	default_init_net(confNet,xmlCtrl.GetXmlTree());
	cout << "init port0:" << confNet.plates[0].plate_port.content << endl;
	xmlCtrl.xml_ctrl_parse("net.xml");
	cout << "parse port0:" << confNet.plates[0].plate_port.content << endl;
	XML_CTRL::XML_NODE *tmpXmlNode= NULL;
	tmpXmlNode = xmlCtrl.GetXmlTree().search("port0");
	// if(tmpXmlNode)
	// 	tmpXmlNode->data->content = "1111";
		
	confNet.plates[0].plate_port.content = "3333";
	xmlCtrl.xml_ctrl_save("net.xml");*/
	InitParamConfig();
	CONF_FTP* ftp_idx = NULL;
	
	void *tmp =  NULL;

	CONF_FTP *confFtpTmp =(CONF_FTP*) GetParamConfig(INDEX_PARAM_CONFIG_FTP);
	// CONF_FTP *confFtpTmp = static_cast<CONF_FTP*> (tmp);
	printf("confFtpTmp is %s\n",confFtpTmp==NULL?"NULL":"not NULL" );
	cout << confFtpTmp->ftp_ip.element <<":" << confFtpTmp->ftp_ip.content << endl;
	confFtpTmp->ftp_ip.content = "10.200.4.38";
	SetParamConfig(INDEX_PARAM_CONFIG_FTP);
	cout << s_sysconf.confFtp.ftp_ip.element <<":" << s_sysconf.confFtp.ftp_ip.content << endl;


	CONF_NET *confNetTmp =(CONF_NET*) GetParamConfig(INDEX_PARAM_CONFIG_NET);
	// CONF_NET *confNetTmp = static_cast<CONF_NET*> (tmp);
	printf("confNetTmp is %s\n",confNetTmp==NULL?"NULL":"not NULL" );
	cout << confNetTmp->plates[0].plate_ip.element <<":" << confNetTmp->plates[0].plate_ip.content << endl;
	confNetTmp->plates[0].plate_ip.content = "10.200.4.38";
	SetParamConfig(INDEX_PARAM_CONFIG_NET);
	cout << s_sysconf.confNet.plates[0].plate_ip.element <<":" << s_sysconf.confNet.plates[0].plate_ip.content << endl;
	
	CONF_DEVICE_INFO *confDevTmp =(CONF_DEVICE_INFO*) GetParamConfig(INDEX_PARAM_CONFIG_DEV);
	printf("confDevTmp is %s\n",confDevTmp==NULL?"NULL":"not NULL" );
	cout << confDevTmp->devID.element <<":" << confDevTmp->devID.content << endl;
	cout << confDevTmp->vin.element <<":" << confDevTmp->vin.content << endl;
	cout << confDevTmp->userInfo.element <<":" << confDevTmp->userInfo.content << endl;
	if(confDevTmp->vin.content.size()>4)
		confDevTmp->devID.content = confDevTmp->vin.content.substr(4);

	SetParamConfig(INDEX_PARAM_CONFIG_DEV);
	cout << confDevTmp->devID.element <<":" << confDevTmp->devID.content << endl;

	return 0;
}
#endif