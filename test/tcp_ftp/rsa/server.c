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
        //printf("sizeof:%d",sizeof(cArray) );
        
}

int main(int argc, char *argv[])
{
        int sockfd,new_fd;
        struct sockaddr_in server_addr;
        struct sockaddr_in client_addr;
        int sin_size,portnumber,i;
        const char hello[]="Hello! Are You Fine?";
        int nbytes;
        char buffer[1024];
        unsigned int codeMsg[256]={0};
        unsigned char sendMsg[1024]={0};

        
        


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

        //while(1)
        //{
                /* 服务器阻塞,直到客户程序建立连接  */
                sin_size=sizeof(struct sockaddr_in);
                if((new_fd=accept(sockfd,(struct sockaddr *)(&client_addr),&sin_size))==-1)
                {
                        fprintf(stderr,"Accept error:%s\n\a",strerror(errno));
                        exit(1);
                }

                fprintf(stderr,"Server get connection from %s\n",
                inet_ntoa(client_addr.sin_addr));



                get_codeMsg(hello,17,3233,codeMsg);
                for(i=0;i<strlen(hello);i++)
                {
                        sprintf(sendMsg+i*4,"%d",codeMsg[i]);
                }

                if(write(new_fd,sendMsg,(strlen(hello)*4))<0)
                {
                        fprintf(stderr,"Write Error:%s\n",strerror(errno));
                        exit(1);
                }

                /*usleep(100*1000);

                if((nbytes=read(sockfd,buffer,1024))==-1)
                {
                        fprintf(stderr,"Read Error:%s\n",strerror(errno));
                        exit(1);
                }
                buffer[nbytes]='\0';
                printf("I have received:%s\n",buffer);*/
                /* 这个通讯已经结束     */
                close(new_fd);
                /* 循环下一个     */  
        //}
        close(sockfd);
        exit(0);
}
