#include "txml2.h"
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
static const char* ftp_ip = "200.200.4.193";
static const char* ftp_port = "10095";
static const char* ftp_user = "lxc";
static const char* ftp_psw = "123456";
static const char* ftp_file = "ftp.xml";
int xmlParam_create_ftp();
int xmlParam_read_ftp();



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





int xmlParam_create_ftp()
{
	//建立XML文档和根结点
	xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
	xmlNodePtr root = xmlNewNode(NULL, BAD_CAST "root");
	//将根节点绑定到XML文档
    xmlDocSetRootElement(doc, root);
    //建立子结点，为其安装属性
    xmlNodePtr newNode = NULL;
    newNode = xmlNewNode(NULL, BAD_CAST "ftp");
    xmlNewProp(newNode, BAD_CAST "trans", BAD_CAST "u");//u:upload,d:download
    xmlAddChild(root, newNode);
    //在结点下安放子结点，并为子节点添加内容
    xmlNewTextChild(newNode, NULL, BAD_CAST"servIP", BAD_CAST ftp_ip);
    xmlNewTextChild(newNode, NULL, BAD_CAST"port", BAD_CAST ftp_port);
    xmlNewTextChild(newNode, NULL, BAD_CAST"user", BAD_CAST ftp_user);
    xmlNewTextChild(newNode, NULL, BAD_CAST"psw", BAD_CAST ftp_psw);

    newNode = xmlNewNode(NULL, BAD_CAST "palte");
    xmlNewProp(newNode, BAD_CAST "client_N", BAD_CAST "0");//u:upload,d:download
    xmlAddChild(root, newNode);
    //在结点下安放子结点，并为子节点添加内容
    xmlNewTextChild(newNode, NULL, BAD_CAST"servIP", BAD_CAST "200.200.4.194");
    xmlNewTextChild(newNode, NULL, BAD_CAST"port", BAD_CAST "10094");

    int ret = xmlSaveFormatFileEnc(ftp_file,doc,"UTF-8",1);
    printf("ret:%d\n",ret );
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return ret;

}
int xmlParam_read_ftp()
{
	xmlDocPtr doc = xmlParseFile(ftp_file);
	if(doc == NULL)
	{
		fprintf(stderr, "open xml file %s failed :%s\n",ftp_file,strerror(errno) );
		return -1;
	}
	//找到首结点
    xmlNodePtr root = xmlDocGetRootElement(doc);
    if(root == NULL)
    {

        perror("Error: Can not find the root!\n");
    	return -1;
    }
    xmlNodePtr cur=NULL;
    
    
    for(cur = root->xmlChildrenNode;cur;cur=cur->next)
    {
    	printf("Node: %s\t", cur -> name);
        printf("Content: %s\t", (char*)xmlNodeGetContent(cur));
        printf("End\n");
    }
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return 0;
}
int change_node_content(char* xpath,char *content)
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
	// xmlChar *xpath = BAD_CAST xpath; //xpath语句
	xmlXPathObjectPtr result = getNodeset(pdoc, BAD_CAST xpath); //查询XPath表达式，得到一个查询结果
	if (result == NULL) {
		printf("result is NULL\n");
		return (-1);
	}
	else
	{
		xmlNodePtr cur=result->nodesetval->nodeTab[0];
		xmlNodeSetContent(cur,BAD_CAST content);
	}
	xmlSaveFormatFileEnc(ftp_file,pdoc,"UTF-8",1);
	xmlFreeDoc(pdoc);
    xmlCleanupParser();
	return 0;
}
int change_node_attr(char* xpath,char *attrName,char* attr)
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
	// xmlChar *xpath = BAD_CAST xpath; //xpath语句
	xmlXPathObjectPtr result = getNodeset(pdoc, BAD_CAST xpath); //查询XPath表达式，得到一个查询结果
	if (result == NULL) {
		printf("result is NULL\n");
		return (-1);
	}
	else
	{
		xmlNodePtr cur=result->nodesetval->nodeTab[0];
		xmlSetProp(cur,BAD_CAST attrName,BAD_CAST attr);
	}
	xmlSaveFormatFileEnc(ftp_file,pdoc,"UTF-8",1);
	xmlFreeDoc(pdoc);
    xmlCleanupParser();
	return 0;
}
int main()
{
	// xmlParam_create_ftp();
	xmlParam_read_ftp();
	change_node_content("/root/ftp/port","10001");
	change_node_attr("/root/ftp","trans","d");
	xmlParam_read_ftp();
	return 0;
}
