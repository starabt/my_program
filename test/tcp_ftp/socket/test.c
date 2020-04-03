#include <stdio.h>
#include <string.h>
#define BOY "lxc"
void hello(void)
{
	printf("hello %s",BOY);
	return;
}
int add(int x,int y)
{
	return x+y;
}
int main()
{
	int x,y;
	hello();
	printf("input two num:x and y\n");
	scanf("%d%d",&x,&y);
	add(x,y);
	printf("the boy %s is so handsome\n",BOY);
	printf("haige is so handsome!!!\n");
	printf("haige is so handsome!!!");
	return 1;
}
