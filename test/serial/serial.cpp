#include "serial.h"

USER_SERIAL::USER_SERIAL():serial_fd(-1)
{
}
USER_SERIAL::~USER_SERIAL()
{
	if(serial_fd > 0)
	{
		close(serial_fd);
	}
}


/**************************************************************************
时间:2017/07/20/  创建 

功能说明：打开485串口
参数   ：无
返回值 ：bool类型, false--打开失败 , true--打开成功
**************************************************************************/
bool USER_SERIAL::open_serial(const char* dev_name)
{
	int fd = open(dev_name, O_RDWR | O_NOCTTY); 
	if(-1 == fd)
	{
		perror(dev_name);
		return false;
	}
	else
	{
		serial_fd = fd;
		return true;
	}
}

//---------------------------------------------------------
//设置串口波特率
bool USER_SERIAL::set_baudrate(int baud)
{
	int baud_arr[] = {B115200,B57600, B38400, B19200, B9600, B4800, B2400, B1200, B300};
	int name_arr[] = {115200,57600,38400,19200,9600,4800,2400,1200,300};
	struct termios opt;
	bool flag = false;
	tcgetattr(serial_fd,&opt); // get the default settings

	for(unsigned int i = 0;i<(sizeof(baud_arr)/sizeof(int));i++)
	{
		if(baud == name_arr[i])
		{
			tcflush(serial_fd,TCIOFLUSH); //refresh the IO buffer
			cfsetispeed(&opt,baud_arr[i]); //set the input baud rate
			cfsetospeed(&opt,baud_arr[i]); //set the output baud rate
			int status  = tcsetattr(serial_fd,TCSANOW,&opt);
			if(0 != status)
			{
				perror("设置波特率出错！\n");
			}
			else
			{
				flag = true;
			}
			tcflush(serial_fd,TCIOFLUSH);
		}
	}
	return flag;
}


//-------------------------------------------------------
//设置数据位，停止位和校验位
bool USER_SERIAL::set_parity(int databits,int stopbits,int parity)
{
	struct termios opt;
	if(tcgetattr(serial_fd,&opt) != 0)
	{
		perror("setup serial 1");
		return(false);
	}
	opt.c_cflag &= ~CSIZE;
	switch(databits)
	{
		case 7:
		opt.c_cflag |= CS7;
		break;
		case 8:
		opt.c_cflag |= CS8;
		break;
		default:
		printf("不支持的数据位\n");
		return(false);
	}
	switch(stopbits)
	{
		case 1:
		opt.c_cflag &= ~CSTOPB; //one stop bits
		break;
		case 2:
		opt.c_cflag |= CSTOPB;//two stop bits
		break;
		default:
		printf("不支持的停止位\n");
		return(false);
	}
	switch(parity)
	{
		case 'n':
		case 'N':
		opt.c_cflag &= ~PARENB;//clean parity
		opt.c_iflag &= ~INPCK;//enable parity checking
		break;

		case 'o':
		case 'O':
		opt.c_cflag |= (PARODD | PARENB); //set odd parity
		opt.c_iflag |= INPCK;//unable parity checking
		break;

		case 'e':
		case 'E':
		opt.c_cflag |= PARENB;
		opt.c_cflag &= ~PARODD; //set odd parity
		opt.c_iflag |= INPCK;
		break;

		default:
		printf("不支持的奇偶校验位\n");
		return(false);

	}
	
	opt.c_cflag |= (CLOCAL | CREAD);

    opt.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
 
    opt.c_oflag &= ~OPOST;
    opt.c_oflag &= ~(ONLCR | OCRNL);    //添加的
 
    opt.c_iflag &= ~(ICRNL | INLCR);
    opt.c_iflag &= ~(IXON | IXOFF | IXANY);    //添加的
	opt.c_cc[VTIME] = 1;
	opt.c_cc[VMIN] = 0;

	tcflush(serial_fd,TCIFLUSH); /* Update the options and do it NOW */
	if (tcsetattr(serial_fd,TCSANOW,&opt) != 0)
	{
	perror("SetupSerial 3");
	return (false);
	}
	return (true);
}


/**************************************************************************
时间:2017/07/20/  创建 

功能说明：关闭串口
参数   ：无
返回值 ：true--关闭成功  false--关闭失败
**************************************************************************/
bool USER_SERIAL::close_serial()
{
	if(serial_fd > 0)
	{
		close(serial_fd);
		return true;
	}
	else
		return false;
}


//---------------------------------------------------------
//按照协议解析数据
// void USER_SERIAL::deal_raw_data(const UINT8* serial_data,UINT32 len)
// {
// 	return ;
// }
