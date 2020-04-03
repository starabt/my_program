#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdarg.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>

int ftp_sock;
int passive_sock;
char username[]="lxc";
char userpwd[]="123456";
char serv_ip[]="200.200.4.193";
unsigned short serv_port=10095;
// char local_dir[]="/home/lxc/lxc/test/main.cpp";
char local_dir[]="/home/lxc/lxc/ftp/test_upload.cpp";
char remote_dir[]="/";
char recv_buf[1024];
char ftpcmd[32];

bool close_ftp()
{
    if (passive_sock>0)
    {
        close(passive_sock);
        passive_sock = -1;
    }
    if(ftp_sock>0)
    {
        close(ftp_sock);
        ftp_sock = -1;
    }
    return true;
}

static int isDigit(char ch) {
    if (ch >= '0' && ch <='9') {
        return 1;
    } else {
        return 0;
    }
}

static void getNumbersAfter(char *str, char flag, long int *num, int count) {
    int pos = 0;
    while (str[pos] != flag) {
        pos ++;
    }
    int j;
    for (j = 0; j < count; j++) {
        while (!isDigit(str[pos])) {
            pos ++;
        }
        num[j] = 0;
        while (isDigit(str[pos])) {
            num[j] = num[j] * 10 + (str[pos] - '0');
            pos ++;
        }
    }
}

int main()
{
	ftp_sock = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in servaddr;
    bzero(&(servaddr.sin_zero),8);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(serv_port);
    inet_pton(AF_INET,serv_ip,&servaddr.sin_addr);

    int ret = connect(ftp_sock,(struct sockaddr*)&servaddr,sizeof(servaddr));
    if(ret<0)
    {
    	printf("connect error\n");

    }

    read(ftp_sock,recv_buf,sizeof(recv_buf));
    printf("%s\n",recv_buf );

    sprintf(ftpcmd,"%s%s\r\n","USER ",username);
    if(send(ftp_sock,ftpcmd,strlen(ftpcmd),0)<0)
    {
    	printf("send ftpcmd USER error\n");
    }
    usleep(100*1000);
    memset(recv_buf,0,sizeof(recv_buf));
    if(read(ftp_sock,recv_buf,sizeof(recv_buf))<0)
    {
    	printf("recv ftp msg error\n");
    }
    printf("\n*****  start  **********\n%s:%s\n********  end  ********\n", ftpcmd,recv_buf);

    sprintf(ftpcmd,"%s%s\r\n","PASS ",userpwd);
    if(send(ftp_sock,ftpcmd,strlen(ftpcmd),0)<0)
    {
    	printf("send ftpcmd PASS error\n");
    }
    usleep(100*1000);

    memset(recv_buf,0,sizeof(recv_buf));
    if(read(ftp_sock,recv_buf,sizeof(recv_buf))<0)
    {
    	printf("recv ftp msg error\n");
    }
    printf("\n*****  start  **********\n%s:%s\n********  end  ********\n", ftpcmd,recv_buf);



    memset(ftpcmd,0,sizeof(ftpcmd));
    sprintf(ftpcmd,"%s\r\n","PASV");
    if(send(ftp_sock,ftpcmd,strlen(ftpcmd),0)<0)
    {
    	printf("send ftpcmd PASV error\n");
    	close_ftp();
    	return -1;
    }
    usleep(100*1000);

    memset(recv_buf,0,sizeof(recv_buf));
    if(read(ftp_sock,recv_buf,sizeof(recv_buf))<0)
    {
    	printf("recv ftp msg error\n");
    }
    printf("\n*****  start  **********\n%s:%s\n********  end  ********\n", ftpcmd,recv_buf);
    long int temp[6]; // 解析服务器消息
    getNumbersAfter(recv_buf, '(', temp, 6);
    int portNo = temp[4] * 256 + temp[5]; // 获取端口号

    char serverIP[32]; // 获取ip
    memset(serverIP,0,sizeof(serverIP));
    sprintf(serverIP,"%d.%d.%d.%d",temp[0],temp[1],temp[2],temp[3]);
    printf("被动模式IP端口：%s:%d\n",serverIP,portNo);

    struct sockaddr_in data_addr;
    data_addr.sin_family = AF_INET;
    inet_pton(AF_INET, serverIP, &data_addr.sin_addr);
    data_addr.sin_port = htons(portNo);
    passive_sock = socket(AF_INET,SOCK_STREAM,0);
    if(passive_sock < 0)
    {
        printf("FTP 创建被动模式socket失败\n");
        close_ftp();
        return false;
    }

    //连接数据传输socket
    ret = connect(passive_sock,(struct sockaddr*)&data_addr,sizeof(data_addr));
    if(ret < 0)
    {
    	printf("passive_sock error\n");
    }

    memset(ftpcmd,0,sizeof(ftpcmd));
    sprintf(ftpcmd,"%s%s\r\n","SIZE ",local_dir);
    if(send(ftp_sock,ftpcmd,strlen(ftpcmd),0)<0)
    {
    	printf("send ftpcmd SIZE error\n");
    	close_ftp();
    	return -1;
    }
    usleep(100*1000);

    memset(recv_buf,0,sizeof(recv_buf));
    if(read(ftp_sock,recv_buf,sizeof(recv_buf))<0)
    {
    	printf("recv ftp msg error\n");
    }
    printf("\n*****  start  **********\n%s:%s\n********  end  ********\n", ftpcmd,recv_buf);

    memset(ftpcmd,0,sizeof(ftpcmd));
    sprintf(ftpcmd,"%s\r\n","CWD /");
    if(send(ftp_sock,ftpcmd,strlen(ftpcmd),0)<0)
    {
    	printf("send ftpcmd CWD error\n");
    	close_ftp();
    	return -1;
    }
    usleep(100*1000);

    memset(recv_buf,0,sizeof(recv_buf));
    if(read(ftp_sock,recv_buf,sizeof(recv_buf))<0)
    {
    	printf("recv ftp msg error\n");
    }
    printf("\n*****  start  **********\n%s:%s\n********  end  ********\n", ftpcmd,recv_buf);


    memset(ftpcmd,0,sizeof(ftpcmd));
    sprintf(ftpcmd,"%s%s\r\n","STOR ",local_dir);
    if(send(ftp_sock,ftpcmd,strlen(ftpcmd),0)<0)
    {
    	printf("send ftpcmd STOR error\n");
    	close_ftp();
    	return -1;
    }
    usleep(100*1000);

    memset(recv_buf,0,sizeof(recv_buf));
    if(read(ftp_sock,recv_buf,sizeof(recv_buf))<0)
    {
    	printf("recv ftp msg error\n");
    }
    printf("\n*****  start  **********\n%s:%s\n********  end  ********\n", ftpcmd,recv_buf);

    sleep(10);
    return 0;


}