
#ifndef _USER_SERIAL_H_
#define _USER_SERIAL_H_

#include <unistd.h>     
#include <sys/types.h>  
#include <sys/stat.h> 
#include <sys/ioctl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>




class USER_SERIAL
{
public:
	USER_SERIAL();
	virtual ~USER_SERIAL();

	//打开串口
	bool open_serial(const char* dev_name);
	//设置串口波特率
	bool set_baudrate(int baud);
	//设置数据位，停止位，校验位
	bool set_parity(int databits,int stopbits,int parity);
	//关闭串口
	bool close_serial();

	int serial_fd;
	
};


#endif
