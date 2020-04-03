#include "serial.h"
#include <pthread.h>
#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#define UART_DEV "/dev/ttymxc2"
void* uart_recv(void *fd)
{
	int recv_fd = *(int*)fd;
	int ret = -1;
	fd_set readfds;
	FD_ZERO(&readfds);
	
	struct timeval timeout = {1,0};
	char buf[1000] = {0};
	while(1)
	{
		FD_SET(recv_fd,&readfds);
		if(select(recv_fd+1,&readfds,NULL,NULL,&timeout) > 0)
		{
			if(FD_ISSET(recv_fd,&readfds))
			{
				memset(buf,0,sizeof(buf));
				ret = read(recv_fd,buf,sizeof(buf));
				printf("recv %d bytes data:%s\n",ret,buf );
				// write(recv_fd,buf,ret);

			}
		}
	}
}
int main()
{
	USER_SERIAL mySerial;
	mySerial.open_serial(UART_DEV);
	mySerial.set_baudrate(115200);
	mySerial.set_parity(8,1,'n');
	pthread_t thread_recv;
	pthread_create(&thread_recv,NULL,uart_recv,&mySerial.serial_fd);
	pthread_detach(thread_recv);
	char buf[1000]={0};
	int ret = -1;
	while(1)
	{
		printf("input data to send:");
		bzero(buf,sizeof(buf));
		scanf("%s",buf);
		ret = write(mySerial.serial_fd,buf,strlen(buf));
		printf("send %d bytes data:%s\n",ret,buf );
	}
	return 0;
}