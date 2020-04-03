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
int main(int argc, char const *argv[])
{
	int server_sockfd,client_sockfd;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	fd_set temp_fds,readfds;
	int portnum = 0;
	int ret = 0;
	if(argc != 2)
	{
		fprintf(stderr, "Usage:%s portnum\n",argv[0] );
		exit(1);
	}
	if((portnum=atoi(argv[1]))<0)
	{
		fprintf(stderr,"Usage:%s portnum\n",argv[0] );
		exit(1);
	}
	/* 服务器端开始建立socket描述符 */
    if((server_sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)  
    {
        fprintf(stderr,"Socket error:%s\n\a",strerror(errno));
        exit(1);
    }

    /* avoid Bind error:Address already in use*/
    unsigned int value = 1;
    setsockopt(server_sockfd,SOL_SOCKET,SO_REUSEADDR,(void *)&value,sizeof(int));

    /* 服务器端填充 sockaddr结构  */ 
    bzero(&server_addr,sizeof(struct sockaddr_in));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    server_addr.sin_port=htons(portnum);

    /* 捆绑sockfd描述符  */ 
    if(bind(server_sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1)
    {
        fprintf(stderr,"Bind error:%s\n\a",strerror(errno));
        exit(1);
    }

    /* 监听sockfd描述符  */
    if(listen(server_sockfd,5)==-1)
    {
        fprintf(stderr,"Listen error:%s\n\a",strerror(errno));
        exit(1);
    }

    FD_ZERO(&temp_fds);
    FD_SET(server_sockfd,&temp_fds);
    while(1)
    {
    	char ch=0;
    	int nread=0;
    	readfds = temp_fds;

    	printf("server waiting...\n");
    	ret = select(FD_SETSIZE,&readfds,NULL,NULL,NULL);
    	if(ret <= 0)
    	{
    		perror("server");
    		close(server_sockfd);
    		break;
    	}
    	else
    	{
    		for(int fd=0;fd<FD_SETSIZE;fd++)
    		{
    			if(FD_ISSET(fd,&readfds))
    			{
    				socklen_t client_len=0;
    				client_len = sizeof(struct sockaddr);
    				if(fd == server_sockfd)//server fd is active
    				{
    					client_sockfd = accept(server_sockfd,(struct sockaddr*)&client_addr,&client_len);
    					if(client_sockfd == -1)
    					{
    						fprintf(stderr, "accept error %s\n", strerror(errno));
    						close(server_sockfd);
    						exit(1);
    					}
    					else
    					{
    						FD_SET(client_sockfd,&temp_fds);
    						printf("adding client on fd %d\n", client_sockfd);
    					}
    				}
    				else//client fd is active
    				{
    					ioctl(fd,FIONREAD,&nread);
    					if(nread == 0)
    					{
    						close(fd);
    						FD_CLR(fd,&temp_fds);
    						printf("removing client on fd %d\n",fd );
    					}
    					else
    					{
    						read(fd,&ch,1);
    						sleep(3);
    						printf("serving client on fd %d\n",fd );
    						ch++;
    						write(fd,&ch,1);
    						// FD_CLR(fd,&temp_fds);
    						// close(fd);
    					}
    				}
    			}
    		}
    	}

    }
	return 0;
}