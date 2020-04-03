#include "testpack.h"

void test1_datapack(int clientfd)
{
	unsigned char buffer1[2100];
	int i = 0;
	///第一个包
	int data_start_bit = 0;
	data_start_bit = i;
	const char *s1="##";//开头
	memcpy(buffer1 + i, s1, 2*sizeof(char));
	i+=2;
	buffer1[i++]=0x01;//命令标识
	buffer1[i++] = respond_success;//应答标志
	const char *s2="LFV2A2156C3333333";
	memcpy(buffer1+i,s2,17*sizeof(char));//唯一识别码
	i+=17;
	buffer1[i++]=0x01;//数据加密方式
	buffer1[i++]=0x00;
	buffer1[i++]=0xff;//数据单元长度
	time_t t;
	struct tm*lt;
	time (&t);//获取Unix时间戳
	lt = localtime(&t);
	//printf("tiem_front:%d\n", i);
	buffer1[i++]=lt->tm_year-100;
	buffer1[i++]=lt->tm_mon+1;
	buffer1[i++]=lt->tm_mday;
	buffer1[i++]=lt->tm_hour;
	buffer1[i++]=lt->tm_min;
	buffer1[i++]=lt->tm_sec;//数据采集时间
	buffer1[i++]=0;
	buffer1[i++]=1;//登ru流水号//buffer[31]
	const char *s3="83605337981605490187";
	memcpy(buffer1 + i, s3, 20*sizeof(char));//ICCID
	i += 20;
	buffer1[i++]=1;//可充电储能子系统数
	buffer1[i++]=12;//编码长度
	const char *s4="10fff01011ff";
	memcpy(buffer1 + i , s4, 12*sizeof(char));
	i += 12;
	for (int cc = 0; cc < 213; cc++)//data_length - 42
	{
		buffer1[i++] = cc;
	}
	int k;
	int buf_length = buffer1[data_start_bit + 23] + 25;		
	int BCC_code_resp=buffer1[data_start_bit];
	for (k = 0; k < buf_length-2; k++)
   	{       
   		BCC_code_resp^=buffer1[data_start_bit+k+1];
   	}
   	buffer1[i++] = BCC_code_resp;
	printf("buffer_Bcc1:%x\n", BCC_code_resp);
	
///////////////////////////////////////////////
	for (int j = 0; j < 5; ++j)
	{
		buffer1[i++] = '#';	
	}
//////////////////////////////////////////////
	data_start_bit = i;
	memcpy(buffer1 + i, s1, 2*sizeof(char));
	i+=2;
	buffer1[i++]=0x04;//命令标识
	buffer1[i++]= respond_success;//应答标志
	memcpy(buffer1+i,s2,17*sizeof(char));//唯一识别码
	i+=17;
	buffer1[i++]=0x01;//数据加密方式
	buffer1[i++]=0x00;
	buffer1[i++]=0x08;//数据单元长度
	lt = localtime(&t);
	buffer1[i++]=lt->tm_year-100;
	buffer1[i++]=lt->tm_mon+1;
	buffer1[i++]=lt->tm_mday;
	buffer1[i++]=lt->tm_hour;
	buffer1[i++]=lt->tm_min;
	buffer1[i++]=lt->tm_sec;//数据采集时间
	buffer1[i++]=0;
	buffer1[i++]=1;//登出流水号
	buf_length = buffer1[data_start_bit + 23] + 25;		
	BCC_code_resp=buffer1[data_start_bit];
	for (k = 0; k < buf_length-2; k++)
   	{       
   		BCC_code_resp^=buffer1[data_start_bit+k+1];
   	}
   	buffer1[i++] = BCC_code_resp;

	send(clientfd, buffer1, 1024, 0);
	printf("测试包1发送成功\n");

	//////////////////////////////////////////////////发送

}

void test2_datapack(int clientfd)
{

}

void test3_datapack(int clientfd)
{
	unsigned char buffer1[1024];
	int i = 0;
	///第一个包
	for (int f = 0; f < 3; ++f)
	{
		buffer1[i++] = '#';
	}
	int data_start_bit = i;
	const char *s1="##";//开头
	memcpy(buffer1 + i, s1, 2*sizeof(char));
	i+=2;
	buffer1[i++]=0x01;//命令标识
	buffer1[i++] = respond_success;//应答标志
	const char *s2="LFV2A2156C3333333";
	memcpy(buffer1+i,s2,17*sizeof(char));//唯一识别码
	i+=17;
	buffer1[i++]=0x01;//数据加密方式
	buffer1[i++]=0xff;
	buffer1[i++]=0xff;//数据单元长度
	time_t t;
	struct tm*lt;
	time (&t);//获取Unix时间戳
	lt = localtime(&t);
	buffer1[i++]=lt->tm_year-100;
	buffer1[i++]=lt->tm_mon+1;
	buffer1[i++]=lt->tm_mday;
	buffer1[i++]=lt->tm_hour;
	buffer1[i++]=lt->tm_min;
	buffer1[i++]=lt->tm_sec;//数据采集时间
	buffer1[i++]=0;
	buffer1[i++]=1;//登ru流水号//buffer[31]
	const char *s3="83605337981605490187";
	memcpy(buffer1 + i, s3, 20*sizeof(char));//ICCID
	i += 20;
	buffer1[i++]=1;//可充电储能子系统数
	buffer1[i++]=12;//编码长度
	const char *s4="10fff01011ff";
	memcpy(buffer1 + i , s4, 12*sizeof(char));
	i += 12;

	///第2个包
	data_start_bit = i;
	memcpy(buffer1 + i, s1, 2*sizeof(char));
	i+=2;
	buffer1[i++]=0x01;//命令标识
	buffer1[i++] = respond_success;//应答标志
	memcpy(buffer1+i,s2,17*sizeof(char));//唯一识别码
	i+=17;
	buffer1[i++]=0x01;//数据加密方式
	buffer1[i++]=0xff;
	buffer1[i++]=0xff;//数据单元长度
	lt = localtime(&t);
	//printf("tiem_front:%d\n", i);
	buffer1[i++]=lt->tm_year-100;
	buffer1[i++]=lt->tm_mon+1;
	buffer1[i++]=lt->tm_mday;
	buffer1[i++]=lt->tm_hour;
	buffer1[i++]=lt->tm_min;
	buffer1[i++]=lt->tm_sec;//数据采集时间
	buffer1[i++]=0;
	buffer1[i++]=1;//登ru流水号//buffer[31]

	data_start_bit = i;
	memcpy(buffer1 + i, s1, 2*sizeof(char));
	i+=2;
	buffer1[i++]=0x01;//命令标识
	buffer1[i++] = respond_success;//应答标志
	memcpy(buffer1+i,s2,17*sizeof(char));//唯一识别码
	i+=17;
	buffer1[i++]=0x01;//数据加密方式
	buffer1[i++]=0xff;
	buffer1[i++]=0xff;//数据单元长度
	lt = localtime(&t);
	//printf("tiem_front:%d\n", i);
	buffer1[i++]=lt->tm_year-100;
	buffer1[i++]=lt->tm_mon+1;
	buffer1[i++]=lt->tm_mday;
	buffer1[i++]=lt->tm_hour;
	buffer1[i++]=lt->tm_min;
	buffer1[i++]=lt->tm_sec;//数据采集时间
	buffer1[i++]=0;
	buffer1[i++]=1;//登ru流水号//buffer[31]

	data_start_bit = i;
	memcpy(buffer1 + i, s1, 2*sizeof(char));
	i+=2;
	buffer1[i++]=0x01;//命令标识
	buffer1[i++] = respond_success;//应答标志
	memcpy(buffer1+i,s2,17*sizeof(char));//唯一识别码
	i+=17;
	buffer1[i++]=0x01;//数据加密方式
	buffer1[i++]=0xff;
	buffer1[i++]=0xff;//数据单元长度
	lt = localtime(&t);
	//printf("tiem_front:%d\n", i);
	buffer1[i++]=lt->tm_year-100;
	buffer1[i++]=lt->tm_mon+1;
	buffer1[i++]=lt->tm_mday;
	buffer1[i++]=lt->tm_hour;
	buffer1[i++]=lt->tm_min;
	buffer1[i++]=lt->tm_sec;//数据采集时间
	buffer1[i++]=0;
	buffer1[i++]=1;//登ru流水号//buffer[31]

	data_start_bit = i;
	memcpy(buffer1 + i, s1, 2*sizeof(char));
	i+=2;
	buffer1[i++]=0x01;//命令标识
	buffer1[i++] = respond_success;//应答标志
	memcpy(buffer1+i,s2,17*sizeof(char));//唯一识别码
	i+=17;
	buffer1[i++]=0x01;//数据加密方式
	buffer1[i++]=0xff;
	buffer1[i++]=0xff;//数据单元长度
	lt = localtime(&t);
	//printf("tiem_front:%d\n", i);
	buffer1[i++]=lt->tm_year-100;
	buffer1[i++]=lt->tm_mon+1;
	buffer1[i++]=lt->tm_mday;
	buffer1[i++]=lt->tm_hour;
	buffer1[i++]=lt->tm_min;
	buffer1[i++]=lt->tm_sec;//数据采集时间
	buffer1[i++]=0;
	buffer1[i++]=1;//登ru流水号//buffer[31]

	data_start_bit = i;
	memcpy(buffer1 + i, s1, 2*sizeof(char));
	i+=2;
	buffer1[i++]=0x01;//命令标识
	buffer1[i++] = respond_success;//应答标志
	memcpy(buffer1+i,s2,17*sizeof(char));//唯一识别码
	i+=17;
	buffer1[i++]=0x01;//数据加密方式
	buffer1[i++]=0xff;
	buffer1[i++]=0xff;//数据单元长度
	lt = localtime(&t);
	//printf("tiem_front:%d\n", i);
	buffer1[i++]=lt->tm_year-100;
	buffer1[i++]=lt->tm_mon+1;
	buffer1[i++]=lt->tm_mday;
	buffer1[i++]=lt->tm_hour;
	buffer1[i++]=lt->tm_min;
	buffer1[i++]=lt->tm_sec;//数据采集时间
	buffer1[i++]=0;
	buffer1[i++]=1;//登ru流水号//buffer[31]



	///第一个包
	data_start_bit = i;
	memcpy(buffer1 + i, s1, 2*sizeof(char));
	i+=2;
	buffer1[i++]=0x01;//命令标识
	buffer1[i++] = respond_success;//应答标志
	memcpy(buffer1+i,s2,17*sizeof(char));//唯一识别码
	i+=17;
	buffer1[i++]=0x01;//数据加密方式
	buffer1[i++]=0x00;
	buffer1[i++]=0xff;//数据单元长度
	lt = localtime(&t);
	//printf("tiem_front:%d\n", i);
	buffer1[i++]=lt->tm_year-100;
	buffer1[i++]=lt->tm_mon+1;
	buffer1[i++]=lt->tm_mday;
	buffer1[i++]=lt->tm_hour;
	buffer1[i++]=lt->tm_min;
	buffer1[i++]=lt->tm_sec;//数据采集时间
	buffer1[i++]=0;
	buffer1[i++]=1;//登ru流水号//buffer[31]
	memcpy(buffer1 + i, s3, 20*sizeof(char));//ICCID
	i += 20;
	buffer1[i++]=1;//可充电储能子系统数
	buffer1[i++]=12;//编码长度
	memcpy(buffer1 + i , s4, 12*sizeof(char));
	i += 12;
	for (int cc = 0; cc < 213; cc++)//data_length - 42
	{
		buffer1[i++] = cc;
	}
	int buf_length = buffer1[data_start_bit + 23] + 25;		
	int BCC_code_resp=buffer1[data_start_bit];
	for (int k = 0; k < buf_length-2; k++)
   	{       
   		BCC_code_resp^=buffer1[data_start_bit+k+1];
   	}
   	buffer1[i++] = BCC_code_resp;

//////////////////////////////////////////////////////////////
   	/*
	data_start_bit = i;
	memcpy(buffer1 + i, s1, 2*sizeof(char));
	i+=2;
	buffer1[i++]=0x01;//命令标识
	buffer1[i++]= respond_success;//应答标志
	memcpy(buffer1+i,s2,17*sizeof(char));//唯一识别码
	i+=17;
	buffer1[i++]=0x01;//数据加密方式s
	buffer1[i++]=0x00;
	buffer1[i++]=0x08;//数据单元长度
	lt = localtime(&t);
	buffer1[i++]=lt->tm_year-100;
	buffer1[i++]=lt->tm_mon+1;
	buffer1[i++]=lt->tm_mday;
	buffer1[i++]=lt->tm_hour;
	buffer1[i++]=lt->tm_min;
	buffer1[i++]=lt->tm_sec;//数据采集时间
	buffer1[i++]=0;
	buffer1[i++]=1;//登出流水号
	int buf_length = buffer1[data_start_bit + 23] + 25;		
	int BCC_code_resp=buffer1[data_start_bit];
	for (int k = 0; k < buf_length-2; k++)
   	{       
   		BCC_code_resp^=buffer1[data_start_bit+k+1];
   	}
   	buffer1[i++] = BCC_code_resp;
   	printf("buffer_Bcc2:%x\n", BCC_code_resp);
   */
   	char buffer2[1024];
   	i = 0;
   	data_start_bit = i;
	memcpy(buffer1 + i, s1, 2*sizeof(char));
	i+=2;
	buffer2[i++]= 0x80;//命令标识
	buffer2[i++]= 0xFE;//应答标志
	memcpy(buffer2+i,s2,17*sizeof(char));//唯一识别码
	i+=17;
	buffer2[i++]=0x01;//数据加密方式
	buffer2[i++]=0x00;
	buffer2[i++]=0x0b;//数据单元长度
	lt = localtime(&t);
	buffer2[i++]=lt->tm_year-100;
	buffer2[i++]=lt->tm_mon+1;
	buffer2[i++]=lt->tm_mday;
	buffer2[i++]=lt->tm_hour;
	buffer2[i++]=lt->tm_min;
	buffer2[i++]=lt->tm_sec;//数据采集时间
	buffer2[i++] = 0x04;
	buffer2[i++] = 0x01;
 	buffer2[i++] = 0x02;
 	buffer2[i++] = 0x04;
 	buffer2[i++] = 0x05;
	buf_length = buffer2[data_start_bit + 23] + 25;		
	BCC_code_resp=buffer2[data_start_bit];
	for (int k = 0; k < buf_length-2; k++)
   	{       
   		BCC_code_resp^=buffer2[data_start_bit+k+1];
   	}
   	buffer2[i++] = BCC_code_resp;
   //	send(clientfd, buffer2, 512, 0);

   for (int b = 0; b < 0xffff; ++b)
   {
   		send(clientfd, buffer1, 0xffff, 0);
   		send(clientfd, buffer2, 0xffff, 0);
		printf("测试包3发送成功\n");
   }
 

}

void test4_datapack(int clientfd)
{
	unsigned char buffer1[2100];
	int i = 0;
	///第一个包
	int data_start_bit = 0;
	data_start_bit = i;
	const char *s1="##";//开头
	memcpy(buffer1 + i, s1, 2*sizeof(char));
	i+=2;
	buffer1[i++]=0x01;//命令标识
	buffer1[i++] = respond_success;//应答标志
	const char *s2="LFV2A2156C3333333";
	memcpy(buffer1+i,s2,17*sizeof(char));//唯一识别码
	i+=17;
	buffer1[i++]=0x01;//数据加密方式
	buffer1[i++]=0x00;
	buffer1[i++]=0xff;//数据单元长度
	time_t t;
	struct tm*lt;
	time (&t);//获取Unix时间戳
	lt = localtime(&t);
	//printf("tiem_front:%d\n", i);
	buffer1[i++]=lt->tm_year-100;
	buffer1[i++]=lt->tm_mon+1;
	buffer1[i++]=lt->tm_mday;
	buffer1[i++]=lt->tm_hour;
	buffer1[i++]=lt->tm_min;
	buffer1[i++]=lt->tm_sec;//数据采集时间
	buffer1[i++]=0;
	buffer1[i++]=1;//登ru流水号//buffer[31]
	const char *s3="83605337981605490187";
	memcpy(buffer1 + i, s3, 20*sizeof(char));//ICCID
	i += 20;
	buffer1[i++]=1;//可充电储能子系统数
	buffer1[i++]=12;//编码长度
	const char *s4="10fff01011ff";
	memcpy(buffer1 + i , s4, 12*sizeof(char));
	i += 12;
	for (int cc = 0; cc < 213; cc++)//data_length - 42
	{
		buffer1[i++] = cc;
	}
	int buf_length = buffer1[data_start_bit + 23] + 25;		
	int BCC_code_resp=buffer1[data_start_bit];
	for (int k = 0; k < buf_length-2; k++)
   	{       
   		BCC_code_resp^=buffer1[data_start_bit+k+1];
   	}
   	buffer1[i++] = BCC_code_resp;
	printf("buffer_Bcc1:%x\n", BCC_code_resp);

//////////////////////////////////////////////param_query
	data_start_bit = i;
	memcpy(buffer1 + i, s1, 2*sizeof(char));
	i+=2;
	buffer1[i++]= 0x80;//命令标识
	buffer1[i++]= 0xFE;//应答标志
	memcpy(buffer1+i,s2,17*sizeof(char));//唯一识别码
	i+=17;
	buffer1[i++]=0x01;//数据加密方式
	buffer1[i++]=0x00;
	buffer1[i++]=0x0b;//数据单元长度
	lt = localtime(&t);
	buffer1[i++]=lt->tm_year-100;
	buffer1[i++]=lt->tm_mon+1;
	buffer1[i++]=lt->tm_mday;
	buffer1[i++]=lt->tm_hour;
	buffer1[i++]=lt->tm_min;
	buffer1[i++]=lt->tm_sec;//数据采集时间
	buffer1[i++] = 0x04;
	buffer1[i++] = 0x01;
 	buffer1[i++] = 0x02;
 	buffer1[i++] = 0x04;
 	buffer1[i++] = 0x05;
	buf_length = buffer1[data_start_bit + 23] + 25;		
	BCC_code_resp=buffer1[data_start_bit];
	for (int k = 0; k < buf_length-2; k++)
   	{       
   		BCC_code_resp^=buffer1[data_start_bit+k+1];
   	}
   	buffer1[i++] = BCC_code_resp;
	printf("buffer_Bcc2:%x\n", BCC_code_resp);

//////////////////////////////////////////////
	data_start_bit = i;
	memcpy(buffer1 + i, s1, 2*sizeof(char));
	i+=2;
	buffer1[i++]=0x04;//命令标识
	buffer1[i++]= respond_success;//应答标志
	memcpy(buffer1+i,s2,17*sizeof(char));//唯一识别码
	i+=17;
	buffer1[i++]=0x01;//数据加密方式
	buffer1[i++]=0x00;
	buffer1[i++]=0x08;//数据单元长度
	lt = localtime(&t);
	buffer1[i++]=lt->tm_year-100;
	buffer1[i++]=lt->tm_mon+1;
	buffer1[i++]=lt->tm_mday;
	buffer1[i++]=lt->tm_hour;
	buffer1[i++]=lt->tm_min;
	buffer1[i++]=lt->tm_sec;//数据采集时间
	buffer1[i++]=0;
	buffer1[i++]=1;//登出流水号
	buf_length = buffer1[data_start_bit + 23] + 25;		
	BCC_code_resp=buffer1[data_start_bit];
	for (int k = 0; k < buf_length-2; k++)
   	{       
   		BCC_code_resp^=buffer1[data_start_bit+k+1];
   	}
   	buffer1[i++] = BCC_code_resp;
   	printf("buffer_Bcc3:%x\n", BCC_code_resp);
	send(clientfd, buffer1, i + 4, 0);
	printf("测试包4发送成功\n");
}

void test5_datapack(int clientfd)
{
	unsigned char buffer1[2048];
	unsigned char buffer2[512];
	unsigned char buffer3[512];
	unsigned char buffer4[512];
	int i = 0;
	///第一个包
	int data_start_bit = i;
	const char *s1="##";//开头
	memcpy(buffer1 + i, s1, 2*sizeof(char));
	i+=2;
	buffer1[i++]=0x01;//命令标识
	buffer1[i++] = respond_success;//应答标志
	const char *s2="LFV2A2156C3333333";
	memcpy(buffer1+i,s2,17*sizeof(char));//唯一识别码
	i+=17;
	buffer1[i++]=0x01;//数据加密方式
	buffer1[i++]=0x07;
	buffer1[i++]=0xe7;//数据单元长度
	time_t t;
	struct tm*lt;
	time (&t);//获取Unix时间戳
	lt = localtime(&t);
	buffer1[i++]=lt->tm_year-100;
	buffer1[i++]=lt->tm_mon+1;
	buffer1[i++]=lt->tm_mday;
	buffer1[i++]=lt->tm_hour;
	buffer1[i++]=lt->tm_min;
	buffer1[i++]=lt->tm_sec;//数据采集时间
	buffer1[i++]=0;
	buffer1[i++]=1;//登ru流水号//buffer[31]
	const char *s3="83605337981605490187";
	memcpy(buffer1 + i, s3, 20*sizeof(char));//ICCID
	i += 20;
	buffer1[i++]=1;//可充电储能子系统数
	buffer1[i++]=12;//编码长度
	const char *s4="10fff01011ff";
	memcpy(buffer1 + i , s4, 12*sizeof(char));
	i += 12;

	for (int cc = 0; cc < 446; cc++)//data_length - 42
	{
		buffer1[i++] = 9;
	}
	send(clientfd, buffer1, 512, 0);
////////////////////////////////////////
	for (int cc = 0; cc < 512; ++cc)
	{
		buffer2[cc] = 9;
	}
	send(clientfd, buffer2, 512, 0);
///////////////////////////////////////
	for (int cc = 0; cc < 512; ++cc)
	{
		buffer3[cc] = 9;
	}
	send(clientfd, buffer3, 512, 0);
/////////////////////////////////////
	for (int cc = 0; cc < 511; ++cc)
	{
		buffer4[cc] = 9;
	}
   	buffer4[511] = 254;
   	send(clientfd, buffer4, 512, 0);
	printf("测试包4发送成功\n");
}