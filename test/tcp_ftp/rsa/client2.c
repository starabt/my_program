/******* 客户端程序  client.c ************/
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
#include "RSA.h"

#define ll long long
int main(int argc, char *argv[])
{
        unsigned int sockfd,i;
        unsigned int j;
        unsigned int  recv_buf[2048]={0};
        struct sockaddr_in server_addr;
        struct hostent *host;
        int portnumber,nbytes;
        ll d,p,q;
        unsigned int atoiMsg[2048]={0};
        unsigned int initMsg[2048]={0};

        RSA rsa;

        //char data_send[]="hello,my name is lxc~~~";
        

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

        if((portnumber=atoi(argv[2]))<0)
        {
                fprintf(stderr,"Usage:%s hostname portnumber\a\n",argv[0]);
                exit(1);
        }

        /* 客户程序开始建立 sockfd描述符  */
        if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
        {
                fprintf(stderr,"Socket Error:%s\a\n",strerror(errno));
                exit(1);
        }

        /* 客户程序填充服务端的资料       */
        bzero(&server_addr,sizeof(server_addr));
        server_addr.sin_family=AF_INET;
        server_addr.sin_port=htons(portnumber);
        server_addr.sin_addr=*((struct in_addr *)host->h_addr);

        /* 客户程序发起连接请求         */ 
        if(connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1)
        {
                fprintf(stderr,"Connect Error:%s\a\n",strerror(errno));
                exit(1);
        }

        /* 连接成功了           */
        do
        {
            memset(recv_buf,0,sizeof(recv_buf));
            nbytes=recv(sockfd,recv_buf,sizeof(recv_buf),0);
            if(nbytes<0)
            {
                perror("receive data");
                exit(1);
            }
            for(i=0;i<nbytes;i++)
            {
                printf("%d ",recv_buf[i] );
            }
            printf("plesase input the e,p,q to get the real words\n");
            scanf("%lld%lld%lld",&d,&p,&q);
            rsa.get_initMsg(recv_buf,d,p*q,initMsg);//(unsigned int *cArray,int dd,int nn,unsigned int *mArray)
            for (i=0;i<nbytes;i++)
            {
                printf("%c",initMsg[i] );
            }
        }while(1);
        
        

        close(sockfd);
        exit(0);
}