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
#include <netdb.h>

int main(int argc, char *argv[])
{
        int sockfd;
        unsigned char buffer[1024];
        char writebuf[1024];
        unsigned char tmpbuf[256];
        struct sockaddr_in server_addr;
        struct hostent *host;
        int portnumber,nbytes,sendbytes;
        char data_send[]="hello,lxc~~~";
        const char *p[1024];
        p[1]="200.200.1.208";

        host=gethostbyname(p[1]);
        portnumber=10094;

        /*if(argc!=3)
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
        }*/

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
                exit(-1);
        }

        /* 连接成功了           */

        do 

       { 
            if((nbytes=recv(sockfd,buffer,1024,0))==-1){

                fprintf(stderr,"Read Error:%s\n",strerror(errno));
                exit(1);
            }
            buffer[nbytes]='\0';
            printf("nbytes:%d\n", nbytes);
            for (int j=0;j<nbytes;j++)
            {
                printf("%2x ",buffer[j] );
            }
            printf("\n");
            /*int i;
            for(i=0;i<nbytes;i++)
            {printf("%02x ",buffer[i]);}*/
            /*printf("s:%d,02x:%02x:\n",buffer[4],buffer[4]);
            printf("s:%d,02x:%02x:\n",buffer[3],buffer[3]);*/
            usleep(100*1000);
           /* if(sendbytes=send(sockfd,buffer,strlen(buffer),0)==-1){

                perror("send");
                exit(1);
            }*/

            if (0x01==buffer[1]){
                if(0x9A==buffer[4]){
                    printf("write:\n");
                    int i;
                    for (i=0;i<14;i++){
                        writebuf[i]=buffer[i+4];
                        writebuf[14]='\0';
                        
                    }
                    if(sendbytes=send(sockfd,writebuf,strlen(writebuf),0)==-1){
                        perror("send");
                        exit(1);
                    }
                    p[0]="write";

                    send(sockfd,p,2,0);

                }
                else if(0x86==buffer[4]){
                    printf("read:\n");
                    buffer[nbytes]='\0';
                    if(sendbytes=send(sockfd,buffer,strlen(buffer),0)==-1){
                        perror("send");
                        exit(1);
                    }
                }
                else if(0x13==buffer[4]){
                    printf("reset:\n");
                    buffer[nbytes]='\0';
                    if(sendbytes=send(sockfd,buffer,strlen(buffer),0)==-1){
                        perror("send");
                        exit(1);
                    }
                }
                else if(0x87==buffer[4]){
                    printf("apply:\n");
                    buffer[nbytes]='\0';
                    if(sendbytes=send(sockfd,buffer,nbytes,0)==-1){
                        perror("send");
                        exit(1);
                    }
                }
            }
            
            
        }while(1);
        /*usleep(100*1000);

        //send 
        if(write(sockfd,data_send,strlen(data_send))==-1)
                {
                        fprintf(stderr,"Write Error:%s\n",strerror(errno));
                        exit(1);
                }*/
        /* 结束通讯     */
        /*do
        {
               
                if((write(sockfd,data_send,strlen(data_send)))==-1) 
                {
                        perror("data_send");
                        exit(1);
                } 
                printf("please input what you want to sent to the server:\n");             
                scanf("%p",&data_send);


        }while(1);*/
        close(sockfd);
        exit(0);
}