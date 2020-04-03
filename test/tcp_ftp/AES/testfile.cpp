#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <time.h>
#include "AES.h"
using namespace std;

unsigned char ranMsg(unsigned char *buf)
{
	srand((unsigned) time(NULL));
	for(int i=0;i<100;i++)
	{
		buf[i]=rand()%255;
	}
}
unsigned int cmp(unsigned char *buf1,unsigned char *buf2,unsigned int len)
{
    for(int i=0;i<len;i++)
    {
        if(buf1[i]!=buf2[i])
        {
            return 0;
            break;
        }
    }
    return 1;
}
int main()
{
	unsigned char a[]="123456";
	unsigned char b[]="123456";
	unsigned char MsgBuf[1024]={0};
	printf("cmp:%u\n",cmp(a,b,6) );
	/*ranMsg(MsgBuf);
	FILE *ifile;
	ifile=fopen("dataIN.txt","a");
	//ifile.open();
	for (int i=0;i<strlen(hello);i++)
	{
		ifile << hello[i];

	}
	fwrite(MsgBuf,1,100,ifile);
	fwrite("\n",1,1,ifile);
	fclose(ifile);*/
	
	return 0;	
	
}