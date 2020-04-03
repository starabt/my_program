/******* 服务器程序  (server.c) ************/
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "RSA.h"
#include <time.h>
using namespace std;

#define ll long long
int main(int argc, char *argv[])
{
        
        socklen_t sockfd,new_fd;
        struct sockaddr_in server_addr;
        struct sockaddr_in client_addr;
        unsigned int sin_size,portnumber,i;
        const char hello[]="Hello! Are You Fine?";
        unsigned int  nbytes;
        char buffer[2048];
        unsigned int codeMsg[2048]={0};
        unsigned int sendMsg[2048]={0};
        RSA rsa;

        ll e=257,j,p,q;
        ll numOfP_Q;
        ll P_Qbuf[1024]={0};
        clock_t enstart, enfinish;
        clock_t destart, definish;
        const char message[]="12345678901234567890123456789012345678901234567890123456789012345678901234567890";

        if(argc!=2)
        {
                fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]);
                exit(1);
        }

        if((portnumber=atoi(argv[1]))<0)
        {
                fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]);
                exit(1);
        }

        /* 服务器端开始建立socket描述符 */
        if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)  
        {
                fprintf(stderr,"Socket error:%s\n\a",strerror(errno));
                exit(1);
        }

        /* 服务器端填充 sockaddr结构  */ 
        bzero(&server_addr,sizeof(struct sockaddr_in));
        server_addr.sin_family=AF_INET;
        server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
        server_addr.sin_port=htons(portnumber);

        /* 捆绑sockfd描述符  */ 
        if(bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1)
        {
                fprintf(stderr,"Bind error:%s\n\a",strerror(errno));
                exit(1);
        }

        /* 监听sockfd描述符  */
        if(listen(sockfd,5)==-1)
        {
                fprintf(stderr,"Listen error:%s\n\a",strerror(errno));
                exit(1);
        }

        
        /* 服务器阻塞,直到客户程序建立连接  */
        sin_size=sizeof(struct sockaddr_in);
        new_fd=accept(sockfd,(struct sockaddr *)&client_addr,&sin_size);
        if(new_fd==-1)
        {
                fprintf(stderr,"Accept error:%s\n\a",strerror(errno));
                exit(1);
        }

        fprintf(stderr,"Server get connection from %s\n",inet_ntoa(client_addr.sin_addr));
        printf("please input p,q\n");
        scanf("%lld%lld",&p,&q);
        memset(codeMsg,0,sizeof(codeMsg));
        rsa.get_codeMsg(message,e,p*q,codeMsg);
        for(i=0;i<strlen(message);i++)
        {
                printf("%u ",codeMsg[i] );
        }
        nbytes=send(new_fd,codeMsg,strlen(message)*4,0);
        if(nbytes<0)
        {
                perror("send message");
                exit(1);
        }
        printf("nbytes%u\n",nbytes );
        close(new_fd);
        close(sockfd);
        return 0;

}