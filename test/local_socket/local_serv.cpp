
#include "local_sock.h"

int main()
{
	LOCAL_SOCK serv;
	int servfd = serv.serv_wait_connect(LOCAL_DOMAIN);
	printf("servfd:%d\n", servfd);
	if(servfd<=0)
	{
		printf("serv_wait_connect failed\n");
	}
	else
		printf("serv_wait_connect success\n");
	return 0;
}
#if 0

#include <stdio.h>
#include <unistd.h>
 
#include <sys/socket.h>
 
#include <sys/types.h>
 
#include <sys/un.h>
 
// #define UNIX_DOMAIN "/home/lxc/test/UNIX.domain"
#define UNIX_DOMAIN "./UNIX.domain"
 
 
 
int main(){
 
 
 
socklen_t clt_addr_len;
 
int listen_fd;
 
int com_fd;
 
int ret;
 
int i;
 
static char rcv_buff[1024];
 
socklen_t len;
 
struct sockaddr_un clt_addr;
 
struct sockaddr_un srv_addr;
 
listen_fd=socket(AF_UNIX,SOCK_STREAM,0);
 
if(listen_fd<0){
 
perror("connect creat communication socket");
 
}
 
// set srv_addr param
 
srv_addr.sun_family=AF_UNIX;
 
strncpy(srv_addr.sun_path,UNIX_DOMAIN,sizeof(srv_addr.sun_path)-1);
 
unlink(UNIX_DOMAIN);
 
//bind sockfd&addr
 
ret=bind(listen_fd,(struct sockaddr*)&srv_addr,sizeof(srv_addr));
 
if(ret<0){
 
perror("cannot bind server socket");
 
close(listen_fd);
 
unlink(UNIX_DOMAIN);
 
return -1;
 
}
 
//listen sockfd
 
ret=listen(listen_fd,1);
 
if(ret<0){
 
perror("cannot listen sockfd");
 
close(listen_fd);
 
unlink(UNIX_DOMAIN);
 
return -1;
 
}
 
//have connect requst use accept
 
len=sizeof(clt_addr);
 
com_fd=accept(listen_fd,(struct sockaddr*)&clt_addr,&len);
 
if(com_fd<0){
 
perror("cannot accept requst");
 
close(listen_fd);
 
unlink(UNIX_DOMAIN);
 
return -1;
 
}
 
//read and printf client send info
 
printf("\n******info********\n");
 
//for(i=0,i<4,i++){
 
for(i=0;i<4;i++){
 
memset(rcv_buff,0,1024);
 
int num = read(com_fd,rcv_buff,sizeof(rcv_buff));
 
printf("message from client %d : %s\n",num,rcv_buff);
 
}
 
close(com_fd);
 
close(listen_fd);
 
unlink(UNIX_DOMAIN);
 
return 0;
 
 
 
}
#endif