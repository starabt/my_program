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
        unsigned int d,p,q;
        unsigned char codeMsg[2048]={0};
        unsigned char initMsg[2048]={0};

        AES aes;
        clock_t enstart, enfinish;
        clock_t destart, definish;
        unsigned char key[16] = {0x2b, 0x7e, 0x15, 0x16,0x28, 0xae, 0xd2, 0xa6,0xab, 0xf7, 0x15, 0x88,0x09, 0xcf, 0x4f, 0x3c};  
        char plain[16] ;    
        const char message[]="1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
        //int numPlain=strlen(message)/16;
        unsigned int w[4*(Nr+1)];  
        aes.KeyExpansion(key, w);//w: expanded key

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
       
            //memset(recv_buf,0,sizeof(recv_buf));
            mbytes=read(sockfd,codeMsg,sizeof(codeMsg));
            if(mbytes<0)
            {
                perror("receive data");
                exit(1);
            }
            unsigned int numPlain=mbytes/16;
            printf("mbytes:%d numPlain:%d\n",mbytes,numPlain );
            // 解密，输出明文
            destart=clock();
            for(i=0;i<numPlain;i++)
            {
                memset(plain,0,sizeof(plain));
                for(j=0;j<16;j++)
                {
                    plain[j]=codeMsg[i*16+j];
                }
                aes.decrypt(plain, w);
                for(j=0;j<16;j++)
                {
                    initMsg[i*16+j]=plain[j];
                }

            }
            #if 0
            if (0!=strlen(message)%16)
            {
                memset(plain,0,sizeof(plain));
                for(j=0;j<strlen(message)-16*numPlain;j++)
                {
                    plain[j]=codeMsg[numPlain*16+j];
                }
                aes.decrypt(plain,w);
                for(j=0;j<strlen(message)-16*numPlain;j++)
                {
                    initMsg[16*numPlain+j]=plain[j];
                }
            #endif
            definish=clock();
            cout<<"decryptT:"<<dec<<definish- destart<<endl;
            for(int i=0; i<strlen(message); ++i)  
            {  
                printf("%c",initMsg[i]);  
            }  
            cout << endl; 
        
        
        

        close(sockfd);
        exit(0);
}
