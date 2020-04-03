#include "CStudent.h"
#include <iostream>
using namespace std;
CStudent::CStudent(char* name,char* sex,float height,float score):People(name,sex,height)//派生类构造函数引用基类构造函数
{
	this->score = score;
}
void CStudent::CStu_showInfo()
{
	/*引用基类信息展示函数，再进一步展示自己新增的信息*/
	showInfo();
	cout<<",成绩:"<<score;
}
int main()
{
	CStudent *stu1 = new CStudent("zhangsan","boy",175.0,90);
	stu1->CStu_showInfo();
	delete stu1;
	return 0;
}