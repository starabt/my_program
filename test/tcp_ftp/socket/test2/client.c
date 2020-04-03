#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 4321
#define BUFFER_SIZE 1024
int main(int argc, char const *argv[])
{
	int sockfd,sendbytes;
	char buf[BUFFER_SIZE];
	struct hostent *host;
	struct sockaddr_in serv_addr;

	if(argc<3) 
	{
		fprintf(stderr, "USAGE:./client Hostname (or a ip address) Text\n" );
		exit(1);
	}

	//gethostbyname(),analyze address
	if((host=gethostbyname(argv[1]))==NULL)
	{
		perror("gethostbyname");
		exit(1);


	}

	memset(buf,0,sizeof(buf));
	sprintf(buf,"%s",argv[2]);

	//build socket
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket");
		exit(1);

	}

	//set sockaddr_in argument
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(PORT);
	serv_addr.sin_addr=*((struct in_addr *)host->h_addr);
	memset(serv_addr.sin_zero,0,8);

	//connet(),requst the connection with server
	
	if((connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr)))==-1)
	{
		perror("connet");
		exit(1);
	}

	//send message to server
	if((sendbytes=send(sockfd,buf,strlen(buf),0))==-1)
	{
		perror("send");
		exit(1);
	}
	
	close(sockfd);
	exit(1);
		
}