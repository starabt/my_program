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
#include "RSA.h"

#define ll long long
int main(int argc, char *argv[])
{
        
        unsigned int sockfd,new_fd;
        struct sockaddr_in server_addr;
        struct sockaddr_in client_addr;
        int sin_size,portnumber,i;
        const char hello[]="Hello! Are You Fine?";
        ll nbytes;
        char buffer[2048];
        unsigned int codeMsg[2048]={0};
        unsigned int sendMsg[2048]={0};
        RSA rsa;
        ll e=257;
        ll P_Qbuf[1024]={0};
        clock_t enstart, enfinish;
        clock_t destart, definish;
        const char message[2048]="123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";

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

        fprintf(stderr,"Server get connection from %s\n",inet_ntoa(client_addr.sin_addr));

        ll numOfP_Q=rsa.getPrime(240,280,P_Qbuf);
        printf("num:%lld\n",numOfP_Q );
        for(i=0;i<numOfP_Q;i++)
        {
                for(j=1;j<numOfP_Q;j++)
                {

                        if(1==rsa.judge_prime_two(P_Qbuf[i],P_Qbuf[j])&& 1==rsa.judge_prime_two((P_Qbuf[i]-1)*(P_Qbuf[j]-1),e))
                        {
                                p=P_Qbuf[i];
                                printf("p:%lld\n",p );
                                q=P_Qbuf[j];
                                printf("q:%lld\n",q );
                                break;
                        }
                }
                break;
        }

        if(1==rsa.judge_prime_two((p-1)*(q-1),e))
        {
                enstart=clock();
                rsa.get_codeMsg(message,e,p*q,codeMsg);
                enfinish=clock();
                printf("entime:%ld\n",enfinish-enstart );
                codeMsg[strlen(message)]='\0';
                ll d=rsa.get_d(e,(p-1)*(q-1));
                printf("d(x):%llx\n",d );
                printf("d(d):%lld\n",d );
        }
        nbytes=send(new_fd,codeMsg,sizeof(codeMsg),0);
        if(nbytes<0)
        {
                perror("send message");
                exit(1);
        }
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

        //get_codeMsg(hello,17,3233,codeMsg);
                
        /* 这个通讯已经结束     */
        close(new_fd);
        /* 循环下一个     */  
        
        close(sockfd);
        exit(0);
}
