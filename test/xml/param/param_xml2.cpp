#include "param_xml2.h"
#include "ptypes.h"
#include "paramDefault.h"
#ifdef __cplusplus
extern "C"{
#endif

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <libxml/xmlmemory.h>
#include <libxml/xpointer.h>
	
#ifdef __cplusplus
}
#endif
xmlXPathObjectPtr getNodeset(xmlDocPtr pdoc, const xmlChar *xpath) {
	xmlXPathContextPtr context = NULL;// XPath上下文指针
	xmlXPathObjectPtr result = NULL;  // XPath结果指针
	context = xmlXPathNewContext(pdoc);
	
	if (pdoc == NULL) {
		printf("pdoc is NULL\n");
		return NULL;
	}
	
	if (xpath) {
		if (context == NULL) {
			printf("context is NULL\n");
			return NULL;
		}
		
		result = xmlXPathEvalExpression(xpath, context);
		xmlXPathFreeContext(context); //释放上下文指针
		if (result == NULL) {
			printf("xmlXPathEvalExpression return NULL\n");
			return NULL;
		}
		
		if (xmlXPathNodeSetIsEmpty(result->nodesetval)) {
			xmlXPathFreeObject(result);
			printf("nodeset is empty\n");
			return NULL;
		}
	}
	
	return result;
}
int paramXml2_create_ftp()
{
	//建立XML文档和根结点
	xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
	xmlNodePtr root = xmlNewNode(NULL, BAD_CAST "root");
	//将根节点绑定到XML文档
    xmlDocSetRootElement(doc, root);
    //建立子结点，为其安装属性
    xmlNodePtr newNode = NULL;
    newNode = xmlNewNode(NULL, BAD_CAST PARAM_CONFIG_DEFAULT_FTP_NODE);
    xmlNewProp(newNode, BAD_CAST DEFAULT_FTP_UP_ATTR.first.c_str(), BAD_CAST DEFAULT_FTP_UP_ATTR.second.c_str());//u:upload,d:download
    xmlAddChild(root, newNode);
    //在结点下安放子结点，并为子节点添加内容
    xmlNewTextChild(newNode, NULL, BAD_CAST"servIP", BAD_CAST ftp_ip);
    xmlNewTextChild(newNode, NULL, BAD_CAST"port", BAD_CAST ftp_port);
    xmlNewTextChild(newNode, NULL, BAD_CAST"user", BAD_CAST ftp_user);
    xmlNewTextChild(newNode, NULL, BAD_CAST"psw", BAD_CAST ftp_psw);

    int ret = xmlSaveFormatFileEnc(ftp_file,doc,"UTF-8",1);
    printf("ret:%d\n",ret );
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return ret;
}
int paramXml2_parse_ftp(PARAM_CONFIG_FTP &conf_ftp)
{
	xmlDocPtr pdoc = NULL;
	xmlNodePtr proot = NULL;
	
	/*****************打开xml文档********************/
	xmlKeepBlanksDefault(0);//必须加上，防止程序把元素前后的空白文本符号当作一个node
	pdoc = xmlReadFile (ftp_file, "UTF-8", XML_PARSE_RECOVER);//libxml只能解析UTF-8格式数据
	
	if (pdoc == NULL) {
		printf ("error:can't open file!\n");
		return (-1);
	}
	
	/*****************获取xml文档对象的根节对象********************/
	proot = xmlDocGetRootElement (pdoc);
	
	if (proot == NULL) {
		printf("error: file is empty!\n");
		return (-1);
	}
	char xpath[256]={0};
	xmlNodePtr cur = NULL;
	xmlChar *content;
	memset(xpath,0,sizeof(xpath));
	sprintf(xpath,"/root/ftp/%s",XML_MSG_FTP_UP_ATTR);
	xmlXPathObjectPtr result = getNodeset(pdoc, BAD_CAST xpath); //查询XPath表达式，得到一个查询结果
	if (result != NULL)
	{
		cur = result->nodesetval->nodeTab[0];
		if(cur)
		{
			content = xmlGetProp(cur,BAD_CAST XML_MSG_FTP_UP_ATTR);
			if(content)
			{
				conf_ftp.trans = string(content);
				xmlFree(content);
			}
			
		}
		
	}
	memset(xpath,0,sizeof(xpath));
	sprintf(xpath,"/root/ftp/%s",XML_MSG_FTP_UP_PORT);
	xmlXPathObjectPtr result = getNodeset(pdoc, BAD_CAST xpath); //查询XPath表达式，得到一个查询结果
	if (result != NULL)
	{
		cur = result->nodesetval->nodeTab[0];
		if(cur)
		{
			content = xmlNodeGetContent(cur,BAD_CAST);
			if(content)
			{
				conf_ftp.port = atoi((char*)content);
				xmlFree(content);
			}
		}
	}
	memset(xpath,0,sizeof(xpath));
	sprintf(xpath,"/root/ftp/%s",XML_MSG_FTP_UP_IP);
	xmlXPathObjectPtr result = getNodeset(pdoc, BAD_CAST xpath); //查询XPath表达式，得到一个查询结果
	if (result != NULL)
	{
		cur = result->nodesetval->nodeTab[0];
		if(cur)
		{
			content = xmlNodeGetContent(cur,BAD_CAST);
			if(content)
			{
				conf_ftp.ip = string(content);
				xmlFree(content);
			}
		}
	}
	memset(xpath,0,sizeof(xpath));
	sprintf(xpath,"/root/ftp/%s",XML_MSG_FTP_UP_USER);
	xmlXPathObjectPtr result = getNodeset(pdoc, BAD_CAST xpath); //查询XPath表达式，得到一个查询结果
	if (result != NULL)
	{
		cur = result->nodesetval->nodeTab[0];
		if(cur)
		{
			content = xmlNodeGetContent(cur,BAD_CAST);
			if(content)
			{
				conf_ftp.user = string(content);
				xmlFree(content);
			}
		}
	}
	memset(xpath,0,sizeof(xpath));
	sprintf(xpath,"/root/ftp/%s",XML_MSG_FTP_UP_PASSWD);
	xmlXPathObjectPtr result = getNodeset(pdoc, BAD_CAST xpath); //查询XPath表达式，得到一个查询结果
	if (result != NULL)
	{
		cur = result->nodesetval->nodeTab[0];
		if(cur)
		{
			content = xmlNodeGetContent(cur,BAD_CAST);
			if(content)
			{
				conf_ftp.psw = string(content);
				xmlFree(content);
			}
		}
	}
	memset(xpath,0,sizeof(xpath));
	sprintf(xpath,"/root/ftp/%s",XML_MSG_FTP_UP_SERVDIR);
	xmlXPathObjectPtr result = getNodeset(pdoc, BAD_CAST xpath); //查询XPath表达式，得到一个查询结果
	if (result != NULL)
	{
		cur = result->nodesetval->nodeTab[0];
		if(cur)
		{
			content = xmlNodeGetContent(cur,BAD_CAST);
			if(content)
			{
				conf_ftp.work_dir = string(content);
				xmlFree(content);
			}
		}
	}

	xmlSaveFormatFileEnc(ftp_file,pdoc,"UTF-8",1);
	xmlFreeDoc(pdoc);
    xmlCleanupParser();
	return 0;
}
