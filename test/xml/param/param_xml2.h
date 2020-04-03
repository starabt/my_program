#ifndef _PARAM_XML2_H
#define _PARAM_XML2_H
#include "ptypes.h"
typedef struct XML_NODE_ATTR_
{
	char attrName[20];
	char attrContent[20];
}XML_NODE_ATTR; 
typedef struct XML_NODE_TEXT_
{
	char nodeName[20];
	char nodeContent[20];
}XML_NODE_TEXT; 
int paramXml2_create_ftp();
int paramXml2_parse_ftp(PARAM_CONFIG_FTP &conf_ftp);
#endif