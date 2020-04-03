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
#include "AES.h"
#include "RSA.h"
#include <time.h>
using namespace std;

int main(int argc, char *argv[])
{
        
    socklen_t sockfd,new_fd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    unsigned int sin_size,portnumber,i;
    unsigned int  nbytes;
    char buffer[20480];
    char codeMsg[2048]={0};
    unsigned int codeMsg_int[2048]={0};
    char initMsg[2048]={0};
    unsigned initMsg_int[2048]={0};
    char sendMsg[2048]={0};
    char recv_buf[2048]={0};
    AES aes;
    RSA rsa;

        
    unsigned int j;
    clock_t enstart, enfinish;
    clock_t destart, definish;
    unsigned char key[16] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
    unsigned char send_key[18]={0xbb,0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c,0x66};  
    char plain[16];
    const char message[]={0xaa,0x01,0x01,0x07,0x86,0x8f,0x00,0x55};
    char message2[4096]={0};
 


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


    do
    {
        nbytes=recv(new_fd,recv_buf,sizeof(recv_buf),0);
        if(nbytes<=0)
        {
            perror("recv ");
            exit(1);
        }
        for(int i=0;i<nbytes;i++)
        {
            printf("%d ",recv_buf[i] );
        }
        cout<<endl;
        //if the recv word is the sign of RSA key,the encrypt the key of AES and send it back
        if(nbytes==1 && (bit_12==recv_buf[0] || bit_13==recv_buf[0] || bit_14==recv_buf[0] || bit_15==recv_buf[0] || bit_16==recv_buf[0])) 
        {
            printf("cipher bits:%d\n",recv_buf[0] );
            //rsa.GetPairKey(P_QPAIR[recv_buf[0]][p], P_QPAIR[recv_buf[0]][q]); 
            printf("test\n");
            printf("e:%u ,n:%u\n",const_e,(P_QPAIR[recv_buf[0]][p])*(P_QPAIR[recv_buf[0]][q]) );
            rsa.encrypt(send_key, sizeof(send_key),const_e,57311, codeMsg_int);
            //printf codeMsg

            for(int i=0;i<18;i++)
            {
                printf("%u ", codeMsg_int[i]);
            }
            rsa.decrypt(codeMsg_int, sizeof(send_key),4865,57311, initMsg_int);

            cout<<"initMsg_int:"<<endl;
            for(int i=0;i<18;i++)
            {
                printf("%x ", initMsg_int[i]);
            }
            printf("test0\n");
            if(send(new_fd,codeMsg_int,sizeof(send_key)*4,0)<0)
            {
                perror("send_key");
            }
            memset(codeMsg_int,0,sizeof(codeMsg_int));
            memset(recv_buf,0,sizeof(recv_buf));
        }
        else
        {
            printf("test2\n");
            int w[4*(Nr+1)];  
            aes.KeyExpansion(key, w);//w: expanded key
            unsigned int recvBytes=aes.decryptlong(recv_buf,w,initMsg);
            for(int i=0;i<recvBytes;i++)
            {
                printf("%c",initMsg[i] );
            }
            printf("test3\n");
            memset(recv_buf,0,sizeof(recv_buf));
        }
        

    }while(1);    

                
    /* 这个通讯已经结束     */
    close(new_fd);
    /* 循环下一个     */  
        
    close(sockfd);
    exit(0);
}
