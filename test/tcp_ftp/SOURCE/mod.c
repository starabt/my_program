#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const char message[10]= "hello lxcc";
unsigned int codeMsg[]={0};

int mod(int m,int e,int n)
{
	int result=((m%n)*(m%n))%n;
	int i=0;
	for(i=2;i<e;i++)
	{
		result=(result*(m%n))%n;
	}
	return result;
}
int get_codeMsg(const char *mArray,int ee,int nn,unsigned int *cArray)
{
	int i,r;//r is remainder
	for (i=0;i<strlen(mArray);i++)
	{
		r=mod(mArray[i],ee,nn);
		//printf("r:%d ", r);
		cArray[i]=(nn+r);
		printf("n+r:%d ",nn+r );
		printf("cA:%d ", cArray[i]);
	}
	printf("sizeof:%d",sizeof(cArray) );
	
}

int get_initMsg(unsigned int *cArray,int dd,int nn,unsigned int *mArray)
{
	int i=0,r;
	//printf("size2:%d\n",(cArray) );
	while(cArray[i]>1000)
	{
		r=mod(cArray[i],dd,nn);
		mArray[i]=r;
		printf("mA:%d ",mArray[i] );
		i++;
	}
	return 0;

}


/*int main()
{
	printf("%d\n",mod(5,2,3) );
	return 0;
}*/
/*int main(int argc, char const *argv[])
{
	printf("m^e mod n :(m,e,n)%d\n",mod(atoi(argv[1]),atoi(argv[2]),atoi(argv[3])) );
	return 0;
}*/
int main()
{
	unsigned int initMsg[256]={0};
	unsigned char initMsg2[1024]={0};
	int i;
	for(i=0;i<strlen(message);i++)
	{
		printf("msgx:%x ",message[i] );
		//printf("test[%d]:%d\n",i,test[i] );
	}
	printf("\n");
	for(i=0;i<strlen(message);i++)
	{
		//printf("test[%d]:%x\n",i,test[i] );
		printf("msgd:%d ",message[i] );
	}
	printf("\n");
	printf("%d\n",mod(7,19,234) );
	printf("%d\n",mod(31,17,3233) );
	get_codeMsg(message,17,4453,codeMsg);
	printf("\n");
	printf("%c\n",50);
	get_initMsg(codeMsg,2033,4453,initMsg);
	int len=sprintf(initMsg2, "%u",initMsg[1] );
	sprintf(initMsg2+3,"%u",initMsg[2]);
	printf("len:%d\n",len);
	printf("initMsg2:%d\n",initMsg2[0]);
	printf("initMsg2:%d\n",initMsg2[1]);
	printf("initMsg2:%d\n",initMsg2[2]);
	for(i=0;i<10;i++)
	{
		printf("%c",initMsg[i]);
	}
	printf("\n");
	//char a='48';
	
	return 0;
}