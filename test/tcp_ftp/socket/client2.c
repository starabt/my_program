#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <time.h>

#define PORT 1234
#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
	int sockfd,sendbytes;
	char buf[BUFFER_SIZE];
	struct hostent *host;
	struct sockaddr_in serv_addr;
	if(argc<3)
	{
		fprintf(stderr,"USAGE:./client Hostname(or ip address) Text\n");
		exit(1);
	}
	host=gethostbyname(argv[1]);
	if(host==NULL)
	{
		perror("gethostbyname");
		exit(1);
	}

	memset(buf,0,BUFFER_SIZE);
	sprintf(buf,"%s",argv[2]);

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		perror("socket");
		exit(1);
	}

	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(PORT);
	serv_addr.sin_addr=*(struct in_addr *)host->h_addr;

	if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr))==-1)
	{
		perror("connect");
		exit(1);
	}

	sendbytes=send(sockfd,buf,strlen(buf),0);
	if(sendbytes<0)
	{
		perror("send");
		exit(1);
	}
	close(sockfd);
	return 0;

}