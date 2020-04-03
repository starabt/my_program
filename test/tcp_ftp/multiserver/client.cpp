#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>


int main(int argc, char const *argv[])
{
	int sockfd;
	int len;
	struct sockaddr_in server_addr;
	int ret=0;
	char ch = 'A';
	struct hostent *host;
	int portnum=0;
	
	if(argc!=3)
    {
        fprintf(stderr,"Usage:%s hostname portnumber\a\n",argv[0]);
        exit(1);
    }

    if((host=gethostbyname(argv[1]))==NULL)
    {
        fprintf(stderr,"Gethostname error\n");
        exit(1);
    }

    if((portnum=atoi(argv[2]))<0)
    {
        fprintf(stderr,"Usage:%s hostname portnumber\a\n",argv[0]);
        exit(1);
    }
    sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		fprintf(stderr, "create socket %s\n",strerror(errno) );
		exit(1);
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	// server_addr.sin_addr=*((struct in_addr *)host->h_addr);
	server_addr.sin_port = htons(portnum);

	/* 客户程序发起连接请求         */ 
    if(connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1)
    {
        fprintf(stderr,"Connect Error:%s\a\n",strerror(errno));
        exit(-1);
    }
    write(sockfd,&ch,1);
    read(sockfd,&ch,1);
    printf("char get from server = %c\n",ch );
    close(sockfd);
	return 0;
}