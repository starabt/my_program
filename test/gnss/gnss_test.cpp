#include <pthread.h>
#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <fcntl.h>
#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	if(argc != 2)
	{
		printf("run the program like: exe gnssDevName\n");
		exit(1);
	}
	int fd = open(argv[1], O_RDONLY | O_NOCTTY); 
	if(fd <= 0)
	{
		fprintf(stderr, "open %s failed:%s\n", argv[1],strerror(errno));
		exit(1);
	}
	int ret = -1;
	fd_set readfds;
	FD_ZERO(&readfds);
	
	struct timeval timeout = {1,0};
	char buf[1000] = {0};
	while(1)
	{
		FD_SET(fd,&readfds);
		if(select(fd+1,&readfds,NULL,NULL,&timeout) > 0)
		{
			if(FD_ISSET(fd,&readfds))
			{
				bzero(buf,sizeof(buf));
				ret = read(fd,buf,sizeof(buf));
				cout << buf;
				// printf("recv %d bytes data:%s\n",ret,buf );
				// write(fd,buf,ret);

			}
		}
	}
//	close(fd);
	return 0;
}
