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
        unsigned char codeMsg[2048]={0};
        unsigned char sendMsg[2048]={0};
        AES aes;

        int n;
        unsigned int e=257,j,p,q;
        clock_t enstart, enfinish;
        clock_t destart, definish;
        char key[16] = {0x2b, 0x7e, 0x15, 0x16,0x28, 0xae, 0xd2, 0xa6,0xab, 0xf7, 0x15, 0x88,0x09, 0xcf, 0x4f, 0x3c};  
        char plain[16] ;
        const char message[]="0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcde";
        char message2[4096]={0};
        
        printf("%d\n",strlen(message) );
        
        int w[4*(Nr+1)];  
        aes.KeyExpansion(key, w);//w: expanded key

        // 加密，输出密文
        enstart=clock();

    
    if (0!=strlen(message)%16)
    {
        #if 0
        memset(plain,0,sizeof(plain));
        for(i=0;i<strlen(message);i++)
        {
                message2[i]=message[i];
        }
        
        for(j=0;j<(16-strlen(message)%16);j++)
        {
                message2[i]=0x00;
                i++;
        }
        #endif
        int numPlain=strlen(message)/16 + 1;
        printf("numPlain:%d\n",numPlain );
        for(i=0;i<numPlain;i++)
        {
                memset(plain,0,sizeof(plain));
                for(j=0;j<16;j++)
                {
                        plain[j]=message[i*16+j];
                }
                aes.encrypt(plain, w);
                for(j=0;j<16;j++)
                {
                        codeMsg[i*16+j]=plain[j];
                }

        }
        n=numPlain*16;

    }
    else
    {
        for(i=0;i<strlen(message);i++)
        {
                message2[i]=message[i];
        }
        int numPlain=strlen(message)/16;
        for(i=0;i<numPlain;i++)
        {
                memset(plain,0,sizeof(plain));
                for(j=0;j<16;j++)
                {
                        plain[j]=message2[i*16+j];
                }
                aes.encrypt(plain, w);
                for(j=0;j<16;j++)
                {
                        codeMsg[i*16+j]=plain[j];
                }

        }
        n=numPlain*16;
    }
    enfinish=clock();
    cout<<"encryptT:"<<dec<<enfinish - enstart<<endl;

    cout << "the encrypted word:"<<endl;  
    for(int i=0; i<n; ++i)  
    {  
        printf("%x ",codeMsg[i] );  
        //if((i+1)%4 == 0)  
            //cout << endl;  
    }  
    cout << endl;  


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


         

        nbytes=write(new_fd,codeMsg,n);
        if(nbytes<=0)
        {
                perror("send message");
                exit(1);
        }
        printf("nbytes:%u\n",nbytes );
        #if 0
        do
        {
                printf("input the words you want to send:(end by enter)\n");
                memset(sendMsg,0,sizeof(sendMsg));
                gets(sendMsg);

                get_codeMsg(sendMsg,17,3233,codeMsg);//(unsigned char*,int e,int n,unsigned int *)
                nbytes=send(new_fd,codeMsg,sizeof(codeMsg),0);
                if(nbytes<0)
                {
                        perror("send message");
                        exit(1);
                }


        }while(1);
        #endif

        //get_codeMsg(heunsigned into,17,3233,codeMsg);
                
        /* 这个通讯已经结束     */
        close(new_fd);
        /* 循环下一个     */  
        
        close(sockfd);
        exit(0);
}
