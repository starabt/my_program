#include "People.h"

class CStudent:public People//继承People基类
{
public:
	CStudent(char* name,char* sex,float height,float score);//学生派生类构造函数
	void CStu_showInfo();//学生派生类信息展示
private:
	float score;
};