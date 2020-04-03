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

int mod(int m,int e,int n)
{
    int result=((m%n)*(m%n))%n;
    int i=0;
    for(i=2;i<e;i++)
    {
        result=(result*(m%n))%n;
    }
    return result;
}
int get_codeMsg(const char *mArray,int ee,int nn,unsigned int *cArray)
{
    int i,r;//r is remainder
    for (i=0;i<strlen(mArray);i++)
    {
        r=mod(mArray[i],ee,nn);
        //printf("r:%d ", r);
        cArray[i]=(nn+r);
        printf("n+r:%d ",nn+r );
        printf("cA:%d ", cArray[i]);
    }
    printf("sizeof:%d",sizeof(cArray) );
    
}

int get_initMsg(unsigned int *cArray,int dd,int nn,unsigned int *mArray)
{
    int i=0,r;
    //printf("size2:%d\n",(cArray) );
    while(cArray[i]!='\0')
    {
        r=mod(cArray[i],dd,nn);
        mArray[i]=r;
        printf("mA:%d ",mArray[i] );
        i++;
    }
    return 0;

}

int main(int argc, char *argv[])
{
        int sockfd,i;
        char buffer[1024];
        struct sockaddr_in server_addr;
        struct hostent *host;
        int portnumber,nbytes;
        unsigned int cipher_code;
        unsigned int atoiMsg[1024]={0};
        unsigned int initMsg[1024]={0};

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

        while(1)

       { 
        if((nbytes=read(sockfd,buffer,1024))==-1)
        {
            fprintf(stderr,"Read Error:%s\n",strerror(errno));
            exit(1);
        }
        buffer[nbytes]='\0';
        printf("%s\n",buffer );
        for(i=0;i<(nbytes/4);i++)
        {
            atoiMsg[i]=(buffer[0+i*4]-48)*1000+(buffer[1+i*4]-48)*100+(buffer[2+i*4]-48)*10+buffer[3+i*4]-48;
            printf("%d ", atoiMsg[i]);
        }
        printf("please input the cipher code to get the real words:\n");
        scanf("%d",&cipher_code);
        get_initMsg(atoiMsg,cipher_code,3233,initMsg);
        for(i=0;(i<nbytes/4);i++)
        {
            printf("%c",initMsg[i] );
        }
        }     

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