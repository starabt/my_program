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

int main(int argc, char *argv[])
{
        int sockfd;
        const char buffer[]="hello";
        struct sockaddr_in server_addr;
        struct hostent *host;
        int portnumber,nbytes;
        char data_send[]="hello,my name is lxc~~~";

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
       //  while(1)
       // { 
       //  if((nbytes=send(sockfd,buffer,strlen(buffer),0))==-1)
       //         {
       //                 fprintf(stderr,"Read Error:%s\n",strerror(errno));
       //                 exit(1);
       //         }
       //         printf("test\n");
       //         //buffer[nbytes]='\0';
       //         //printf("I have received:%s\n",buffer);
       //  }

        /*usleep(100*1000);

        //send 
        if(write(sockfd,data_send,strlen(data_send))==-1)
                {
                        fprintf(stderr,"Write Error:%s\n",strerror(errno));
                        exit(1);
                }*/
        /* 结束通讯     */
        int flag=0;
        do
        {
          
                if((write(sockfd,data_send,strlen(data_send)))==-1) 
                {
                        perror("data_send");
                        exit(1);
                } 
                printf("please input what you want to sent to the server:\n");             
                
                flag++;
                usleep(300*1000);

        }while(flag<24);
        close(sockfd);
        exit(0);
}