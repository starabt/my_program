#ifndef T_XML2_H_
#define T_XML2_H_

int change_node_content(char* xpath,char *content);
int change_node_attr(char* xpath,char *attrName,char* attr);
typedef struct XML_NODE_ATTR_
{
	char attrName[20];
	char attrContent[20];
}XML_NODE_ATTR; 
typedef struct XML_NODE_MSG_
{
	XML_NODE_ATTR nodeAttr;
	char nodeName[20];
	char nodeContent[20];
	char fatherNode[20];
}XML_NODE_MSG;
#endif