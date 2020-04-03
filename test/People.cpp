//程序文件People.cpp
#include "People.h"
#include <iostream>
#include <cstring>
#include <string.h>
using namespace std;
People::People(char* name,char* sex,float height)
{
	strcpy(this->name,name);
	strcpy(this->sex,sex);
	this->height=height;
}
People::~People(void)
{
}
void People::showInfo()
{
	cout<<"姓名："<<name<<"，性别"<<sex<<"，身高"<<height;
}