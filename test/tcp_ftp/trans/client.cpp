/******* 客户端程序  client.c ************/
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
    unsigned int sockfd,i;
    unsigned int j;
    unsigned char  recv_buf[2048]={0};
    struct sockaddr_in server_addr;
    struct hostent *host;
    unsigned int portnumber,mbytes;
    char codeMsg[2048]={0};
    char initMsg[2048]={0};
    unsigned int initMsg_int[2048]={0};
    unsigned int recv_buf_int[2048]={0};

    AES aes;
    RSA rsa;
    clock_t enstart, enfinish;
    clock_t destart, definish;
    char RSAkey[]={bit_12};
    //char key[16] = {0x2b, 0x7e, 0x15, 0x16,0x28, 0xae, 0xd2, 0xa6,0xab, 0xf7, 0x15, 0x88,0x09, 0xcf, 0x4f, 0x3c};   
    unsigned char AESkey[16]={0};
    const char message[]="1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
    //int numPlain=strlen(message)/16;
    int w[4*(Nr+1)];  
    
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
    if(send(sockfd,RSAkey,1,0)<0)
    {
        perror("send RSAkey");
        exit(1);
    }
    do
    {
        mbytes=recv(sockfd, recv_buf_int,sizeof( recv_buf_int),0);
        if(mbytes<0)
        {
            perror("receive data");
            exit(1);
        }
        for(int i=0;i<mbytes;i++)
        {
            printf("%x ",recv_buf_int[i]);
        }
        recv_buf_int[mbytes/4]='\0';
        //rsa.GetPairKey(P_QPAIR[bit_12][p], P_QPAIR[bit_12][q]);
        printf("p:%u q:%u\n",P_QPAIR[bit_12][p], P_QPAIR[bit_12][q]);
            unsigned int d=rsa.get_d(const_e,(P_QPAIR[bit_12][p]-1)*(P_QPAIR[bit_12][q]-1));
            printf("d:%u\n", d);
            rsa.decrypt(recv_buf_int,mbytes/4,d,P_QPAIR[bit_12][p]*P_QPAIR[bit_12][q],initMsg_int);
            printf("mbytes:%u\n",mbytes);

            for(int i=0;i<(mbytes/4);i++)
            {
                printf("%x ",initMsg_int[i] );
            }
            printf("test1\n");
            for(int i=0;i<(mbytes/4);i++)
            {
                initMsg[i]=initMsg_int[i];
            }
            printf("test2\n");
            if(0xbb==initMsg[0] && 0x66==initMsg[mbytes/4-1])
            {
                printf("AESkey!\n");
                for(int i=1;i<17;i++)
                {
                    AESkey[i-1]=initMsg[i];
                    
                }
                printf("test6\n");
                for(int i=0;i<16;i++)
                {
                    printf("%x ",AESkey[i] );
                }
                printf("test7\n");
                usleep(1600);
                memset(initMsg,0,sizeof(initMsg));
                //AES encrypt data
                aes.KeyExpansion(AESkey, w);//w: expanded key
                unsigned int encryptNum=aes.encryptlong(message,w,codeMsg);
                printf("encryptNum%d\n",encryptNum );
                aes.decryptlong(codeMsg,w,initMsg);
                for(int i=0;i<encryptNum;i++)
                {
                    printf("%c ",initMsg[i] );
                }
                printf("test9\n" );
                cout<<endl;
                if(send(sockfd,codeMsg,encryptNum,0)<0)
                {
                    perror("send RSAkey");
                    exit(1);
                }
                printf("test8\n");
            }

            else
            {
                printf("test4\n");
                for(int i=0;i<mbytes/4;i++)
                {
                    printf("%x ",initMsg_int[i] );
                }
                printf("test5\n");
            }
        
        
        
    }while(1);


       

            
        
        
        

    close(sockfd);
    exit(0);
}
