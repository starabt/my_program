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
#include <sys/time.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "AES.h"
char Cal_BCC_CheckSum(const char *pData,int len)
{
    char uRet=0;
    for (int i=0;i<len;i++)
    {
        uRet^=pData[i];
    }
    return uRet;
}
/*void reply_server_func(char *msg,int msglen,int replyflag)
{
    unsigned char msgtemp[4096]={"\0"};
    memset(msgtemp,0,sizeof(msgtemp));
    unsigned short MSGlen=0;
    MSGlen=msglen;
    memcpy(msgtemp,msg,MSGlen);
    
    msgtemp[3]=replyflag;

    msgtemp[MSGlen-1]=Cal_BCC_CheckSum(msgtemp+2,MSGlen-3);
    send()
    return;
}*/
void create_upgrade_msg(char* data,int &datalen)
{
	int index = 0;
	data[index++] = 0x23;
	data[index++] = 0x23;
	data[index++] = 0x82;
	data[index++] = 0xFE;
	memset(data+index,0,17);
	index += 17;
	data[index++] = 0x01;
	data[index++] = 0x00;
	data[index++] = 0x00;
	memset(data+index,0,6);
	index+=6;
	data[index++] = 0x01;
	char ftp_url[] = "ftp://lxc:123456@200.200.4.193:10095/testV111.bin;";
	printf("strlen:%d\n", strlen(ftp_url));
	printf("sizeof:%d\n", sizeof(ftp_url));
	strcpy(data+index,ftp_url);
	index += strlen(ftp_url);
	printf("index:::::::::::::::::::%d\n",index );
	int len = (index - 24);
	data[22] = (len>>8) & 0xff;
	data[23] = len & 0xff;
	data[index] = Cal_BCC_CheckSum(data+2,index -2);
	// data[index] = 0x27;
	datalen = index+1;
	return;
}
	

int main(int argc, char *argv[])
{
	// time_t time_now;
 //    tm* timeinfo;
	int reSendCount=0;
	bool sign= true;
    int sockfd,new_fd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int portnumber;
    socklen_t sin_size;
    unsigned char sendBuf[1024]={'\0'};
    unsigned char recvBuf[1024]={'\0'};


    int nbytes;
    int mbytes;
    unsigned char buffer[1024]={'\0'};
    unsigned char cmd_sign;
    char reply_sign;

    unsigned char aesKey[16]={'\0'};
    AES aes;
    aes.SetAESkey(aesKey);
    // aes.GetAESkey(aesKey);
    // aes.SetNrNk();
    unsigned int w[4*(10+1)]={'\0'}; 
    aes.KeyExpansion((unsigned char *)aesKey, w);//w: expanded key

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

    /* avoid Bind error:Address already in use*/
    unsigned int value = 1;
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,(void *)&value,sizeof(int));

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
        static int count = 0;
        // if(count < 5)
        // 	count ++ ;  
        if(count == 0)
        {

        	count ++;
        	int uplen = 0;
        	char buff[1024] = {0};
        	memset(buff,0,sizeof(buff));
        	create_upgrade_msg(buff,uplen);
        	printf("upgrade pack:::::::::::::::\n");
        	for(int i=0;i<uplen;i++)
        		printf("%02x ", buff[i]);
        	printf("\n");
        	send(new_fd,buff,uplen,0);
        }
        // if(recv(new_fd,hello,strlen(hello),1)==-1)
        // {
        //         fprintf(stderr,"Write Error:%s\n",strerror(errno));
        //         exit(1);
        // }
        // printf("hello:%s\n",hello );
        // memset(hello,0,sizeof(hello));
        usleep(1*1000);
        nbytes=recv(new_fd,recvBuf,sizeof(recvBuf),0);
        printf(" nbytes  %d\n", nbytes);
        if(nbytes<=0)
        {
            perror("recv");
            close(new_fd);
            close(sockfd);
            // break;
            exit(1);
        }
        else
        {
        	if(recvBuf[2] == 0x01 || recvBuf[2] == 0x07 )
			{
				time_t time_now;
			tm* timeinfo;
			time(&time_now);
			timeinfo = localtime(&time_now);
			char timeBuf[128];
			memset(timeBuf,0,sizeof(timeBuf));
			sprintf(timeBuf,"%04d-%02d-%02d %02d:%02d:%02d",timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
				printf("*************recv auto wakeup Msg %s**********\n",timeBuf);
				reSendCount ++;
				#if 1
				for(int i=0;i<nbytes;i++)
			{
			    printf("%02x ",recvBuf[i] );
			}
			#endif
			printf("\n------------reSendCount:%d-------------------------------------------\n",reSendCount);
			}
	        
	        
	        // printf("buffer:%s\n",recvBuf );
	        // aes.decryptlong(recvBuf,nbytes,w,buffer);
	        // printf("*************decryptMsg**********\n");
	        // for (int k=0;k<nbytes;k++)
	        // {
	        //     printf("%02x ",buffer[k] );
	        // }
	        cmd_sign=recvBuf[2];
	        reply_sign=recvBuf[3];
	        printf("cmd_sign:%02x,reply_sign:%02x\n", recvBuf[2],reply_sign);

	        // switch(cmd_sign)
	        // {
	        if(recvBuf[2] == 0x02)
	        {
	        	continue;
	            if(reply_sign==0xfffffffe)
	            {
	                printf("into success\n");
	                unsigned char Msg1[]={0x23,  0x23,   0x01,   0x01,   0x54,   0x44,   0x67,   0x7A,   0x67,   0x74,   0x65,   0x73,   0x74,   0x31,   0x37,   0x31,   0x30,   0x31,   0x30,   0x30,   0x31,   0x01,   0x00,   0x1E,   0x11,   0x0B,   0x11,   0x0E,   0x0C,   0x3A,   0x00,   0x05,   0x38,   0x39,   0x38,   0x36,   0x30,   0x32,   0x42,   0x31,   0x31,   0x39,   0x31,   0x37,   0x35,   0x30,   0x30,   0x36,   0x30,   0x36,   0x38,   0x31,   0x01,   0x00,   0x2f};
	                // int MsgLen1=aes.encryptlong(Msg1,sizeof(Msg1),w,sendBuf);
	                mbytes=send(new_fd,Msg1,sizeof(Msg1),0);
	                if(mbytes<=0)
	                {
	                    perror("send");
	                    exit(0);    
	                }
	                #if 0
	                 printf("reply login\n");
	                memset(sendBuf,'\0',sizeof(sendBuf));
	                if(sign )  
	                {  
	                    usleep(1000);
	                    int offset=0;
	                    char ftpUrl[]="ftp://lxc:123456@200.200.4.193:10095/LuXicanTest20180503.tar";
	                    unsigned char Msg2[128]={'\0'};
	                    Msg2[offset++]=0x23;
	                    Msg2[offset++]=0x23;
	                    Msg2[offset++]=0x83;
	                    Msg2[offset++]=0xfe;
	                    memcpy(Msg2+offset,"TDgzgtest17101001",17);
	                    offset += 17;
	                    Msg2[offset++]=0x01;
	                    Msg2[offset++]=0x00;
	                    Msg2[offset++]=15+strlen(ftpUrl);
	                    Msg2[offset++]=0x02;//logtype
	                    Msg2[offset++]=0x01;//clientNo
	                    Msg2[offset++]=0x12;//time begin
	                    Msg2[offset++]=0x04;
	                    Msg2[offset++]=0x05;
	                    Msg2[offset++]=0x00;
	                    Msg2[offset++]=0x00;
	                    Msg2[offset++]=0x00;//
	                    Msg2[offset++]=0x12;
	                    Msg2[offset++]=0x05;
	                    Msg2[offset++]=0x05;
	                    Msg2[offset++]=0x00;
	                    Msg2[offset++]=0x00;
	                    Msg2[offset++]=0x00;//time end
	                    Msg2[offset++]=0x2d;
	                    
	                    memcpy(Msg2+offset,ftpUrl,strlen(ftpUrl));
	                    offset += strlen(ftpUrl);
	                    Msg2[offset++]=Cal_BCC_CheckSum((const char *)Msg2+2,offset-1);

	                    // unsigned char Msg2[]={0x23,  0x23,   0x83,   0xfe,   0x54,   0x44,   0x67,   0x7A,   0x67,   0x74,   0x65,   0x73,   0x74,   0x31,   0x37,   0x31,   0x30,   0x31,   0x30,   0x30,   0x31,   0x01,   0x00,   0x36,   0x04,  0x01,  0x17,   0x11,   0x18,   0x00,   0x00,   0x00,   0x18,   0x01,   0x22,   0x00,   0x00,   0x00,   0x2d,   0x66,    0x74,   0x70,   0x3A,   0x2F,   0x2F,   0x6C,   0x78,   0x63,   0x3A,   0x31,   0x32,   0x33,   0x34,   0x35,   0x36,   0x40,   0x32,   0x30,   0x30,   0x2E,   0x32,   0x30,   0x30,   0x2E,   0x31,   0x2E,   0x32,   0x30,   0x38,   0x3A,   0x31,   0x30,   0x30,   0x39,   0x34,   0x2F,   0x74,   0x65,   0x73,   0x74,   0x2E,   0x74,   0x61,   0x72, 0x3D};        
	                    
	                    // Msg2[sizeof(Msg2)-1]=Cal_BCC_CheckSum((const char *)Msg2+2,sizeof(Msg2)-3);
	                    // printf("Msg2[sizeof(Msg2)-1]:%02x\n",Msg2[sizeof(Msg2)-1] );
	                    // int MsgLen2=aes.encryptlong(Msg2,sizeof(Msg2),w,sendBuf);
	                    
	                    mbytes=send(new_fd,Msg2,offset,0);
	                    if(mbytes<=0)
	                    {
	                        perror("send");
	                        exit(0);    
	                    }
	                    printf("send upload cmd\n");
	                    memset(sendBuf,'\0',sizeof(sendBuf));
	                    sign = false;
	                    printf("sign:::::::::::::::::::::::::::::%d\n",sign );

	                }
	                #endif
	            }
	        }
	   		
	        else 
	        {
	            if(recvBuf[2] != 0x03  && recvBuf[2] != 0x6f && recvBuf[2] != 0x82)
	            {
	            	char tempBuf[1024];
	            	memset(tempBuf,0,sizeof(tempBuf));
	                if(recvBuf[2] == 0x02 && nbytes > 93)
	                	printf("recvBuf[93]:%02x,recvBuf[94]:%02x\n",recvBuf[93],recvBuf[94] );
	            	if(recvBuf[2] == 0x02 && nbytes > 93 && recvBuf[93]==0x23 && recvBuf[94]==0x23)
	            	{
	            		memcpy(tempBuf,recvBuf,93);
	            		tempBuf[3]=0x01;
	            		tempBuf[92]=Cal_BCC_CheckSum(tempBuf+2,93-3);
	            		send(new_fd,tempBuf,93,0);

	            		memset(tempBuf,0,sizeof(tempBuf));
	            		memcpy(tempBuf,recvBuf+93,nbytes-93);
	            		tempBuf[3]=0x01;
	            		tempBuf[nbytes-1 -93]=Cal_BCC_CheckSum(tempBuf+2,nbytes-3-93);
	            		send(new_fd,tempBuf,nbytes-93,0);
	            	}
	            	else if(recvBuf[2] == 0x08)
		            {
		            	memset(tempBuf,0,sizeof(tempBuf));
		            	recvBuf[3]=0x01;
		            	recvBuf[21]=0;
		            	recvBuf[22]=0;
		            	recvBuf[23]=0x06;
		            	time_t time_now;
					    tm* timeinfo;
					    time(&time_now);
					    timeinfo = localtime(&time_now);
		            	recvBuf[24]=(1900 + timeinfo->tm_year)%100;
		            	recvBuf[25]=1 + timeinfo->tm_mon;
		            	recvBuf[26]=timeinfo->tm_mday;
		            	recvBuf[27]=timeinfo->tm_hour;
		            	recvBuf[28]=timeinfo->tm_min;
		            	recvBuf[29]=timeinfo->tm_sec;
		            	memcpy(tempBuf,recvBuf,30);
		            	tempBuf[30] = Cal_BCC_CheckSum(tempBuf+2,31-3);
		            	send(new_fd,tempBuf,31,0);

		            }
		            // else if(recvBuf[2] = 0x01)
		            // {
		            // 	int uplen = 0;
		            // 	memset(tempBuf,0,sizeof(tempBuf));
		            // 	create_upgrade_msg(tempBuf,uplen);
		            // 	send(new_fd,tempBuf,uplen,0);
		            // }
		            // else if(recvBuf[2] == 0x07)
		            // {
		            // 	static int heart_count = 0;
		            // 	if(heart_count < 1)
		            // 	{
		            // 		heart_count++;
		            // 		memcpy(tempBuf,recvBuf,nbytes);
			           //      tempBuf[3]=0x01;
			           //      tempBuf[nbytes-1]=Cal_BCC_CheckSum(tempBuf+2,nbytes-3);
			           //      send(new_fd,tempBuf,nbytes,0);
		            // 	}
		            // }

	               	else
	               	{
	               		memcpy(tempBuf,recvBuf,nbytes);
		                tempBuf[3]=0x01;
		                tempBuf[nbytes-1]=Cal_BCC_CheckSum(tempBuf+2,nbytes-3);
		                send(new_fd,tempBuf,nbytes,0);
	               	}
	                 
	            }
		            
	            else
	            {
	            	char logReplyType = recvBuf[3];
	            	switch(logReplyType)
	            	{
	            		case 0x01:
	            			printf("reply success\n");
	            		break;
	            		case 0x02:
	            			printf("reply fail\n" );
	            		break;
	            		case 0x03:
	            			printf("upload success\n");
	            			break;
	            		case 0x04:
	            			printf("upload fail \n");
	            			break; 
	            		case 0x05:
	            			printf("log not exist\n");
	            			break;
	            		case 0x06:
	            			printf("FTP connect fail\n");
	            			break;
	            		case 0x07:
	            			printf("FTP login fail\n");
	            			break;
	            		default :
	            		break;

	            	}
	            }
	            
	        }

	        // }
	        memset(buffer,0,sizeof(buffer));
        } 
         
        /* 这个通讯已经结束     */
        
        /* 循环下一个     */  
    }while(1);
    close(new_fd);
    close(sockfd);
    exit(0);
}
