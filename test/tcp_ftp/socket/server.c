/******* 服务器程序  (server.c) ************/
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
        int sockfd,new_fd;
        struct sockaddr_in server_addr;
        struct sockaddr_in client_addr;
        int sin_size,portnumber;
        char sendBuf[1024]={'\0'};
        int nbytes;
        int mbytes;
        char buffer[1024]={'\0'};
        char cmd_sign;
        char reply_sign;

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
                if((new_fd=accept(sockfd,(struct sockaddr *)(&client_addr),&sin_size))==-1)
                {
                        fprintf(stderr,"Accept error:%s\n\a",strerror(errno));
                        exit(1);
                }

                fprintf(stderr,"Server get connection from %s\n",
                inet_ntoa(client_addr.sin_addr));
        do
        {
                
                // if(recv(new_fd,hello,strlen(hello),1)==-1)
                // {
                //         fprintf(stderr,"Write Error:%s\n",strerror(errno));
                //         exit(1);
                // }
                // printf("hello:%s\n",hello );
                // memset(hello,0,sizeof(hello));
                usleep(1*1000);
                nbytes=recv(new_fd,buffer,sizeof(buffer),0);
                printf(" nbytes  %d\n", nbytes);
                if(nbytes<=0)
                {
                        perror("recv");
                        close(new_fd);
                        exit(1);
                }
                for(int i=0;i<nbytes;i++)
                {
                        printf("%02x ",buffer[i] );
                }
                printf("\n");
                printf("buffer:%s\n",buffer );
                cmd_sign=buffer[2];
                reply_sign=buffer[3];
                printf("cmd_sign:%02x,reply_sign:%02x\n", cmd_sign,reply_sign);

                switch(cmd_sign)
                {
                        case 0x01:
                        if(reply_sign==0xfffffffe)
                        {
                                printf("into success\n");
                                char sendBuf1[]={0x23,  0x23,   0x01,   0x01,   0x54,   0x44,   0x67,   0x7A,   0x67,   0x74,   0x65,   0x73,   0x74,   0x31,   0x37,   0x31,   0x30,   0x31,   0x30,   0x30,   0x31,   0x01,   0x00,   0x1E,   0x11,   0x0B,   0x11,   0x0E,   0x0C,   0x3A,   0x00,   0x05,   0x38,   0x39,   0x38,   0x36,   0x30,   0x32,   0x42,   0x31,   0x31,   0x39,   0x31,   0x37,   0x35,   0x30,   0x30,   0x36,   0x30,   0x36,   0x38,   0x31,   0x01,   0x00,   0x2f};
                                mbytes=send(new_fd,sendBuf1,sizeof(sendBuf1),0);
                                if(mbytes<=0)
                                {
                                    perror("send");
                                    exit(0);    
                                }
                                 printf("reply login\n");
                                memset(sendBuf1,'\0',sizeof(sendBuf1));
                                char sendBuf2[]={0x23,  0x23,   0x83,   0xfe,   0x54,   0x44,   0x67,   0x7A,   0x67,   0x74,   0x65,   0x73,   0x74,   0x31,   0x37,   0x31,   0x30,   0x31,   0x30,   0x30,   0x31,   0x01,   0x00,   0x36,   0x02,   0x17,   0x10,   0x01,   0x00,   0x00,   0x00,   0x17,   0x11,   0x11,   0x00,   0x00,   0x00,   0x28,   0x66,   0x74,   0x70,   0x3A,   0x2F,   0x2F,   0x6C,   0x78,   0x63,   0x3A,   0x31,   0x32,   0x33,   0x34,   0x35,   0x36,   0x40,   0x32,   0x30,   0x30,   0x2E,   0x32,   0x30,   0x30,   0x2E,   0x31,   0x2E,   0x32,   0x30,   0x36,   0x3A,   0x31,   0x30,   0x30,   0x39,   0x35,   0x2F,   0x6C,   0x6F,   0x67,   0x3f};        
                                mbytes=send(new_fd,sendBuf2,sizeof(sendBuf2),0);
                                if(mbytes<=0)
                                {
                                    perror("send");
                                    exit(0);    
                                }
                                printf("send upload cmd\n");
                                memset(sendBuf2,'\0',sizeof(sendBuf2));
                        }

                }
                memset(buffer,0,sizeof(buffer));
                /* 这个通讯已经结束     */
                
                /* 循环下一个     */  
        }while(1);
        
        close(sockfd);
        exit(0);
}
