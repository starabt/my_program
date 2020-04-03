
#include "local_sock.h"
int main()
{
	LOCAL_SOCK client;
	int clientfd = client.client_connect(LOCAL_DOMAIN);
	printf("clientfd:%d\n", clientfd);
	if(clientfd<=0)
	{
		printf("client connect failed\n");
	}
	else
		printf("client connect success\n");
	return 0;

}
#if 0

#include <stdio.h>
#include <unistd.h>
 
#include <string.h>
 
#include <sys/types.h>
 
#include <sys/socket.h>
 
#include <sys/un.h>
 
#define UNIX_DOMAIN "/home/lxc/test/tmp"
 
int main(){
 
int connect_fd;
 
int ret;
 
char send_buff[1024];
 
int i;
 
static struct sockaddr_un srv_addr;
 
// creat unix socket
 
connect_fd=socket(PF_UNIX,SOCK_STREAM,0);
 
if(connect_fd<0){
 
perror("cannot creat socket");
 
return -1;
 
}
 
srv_addr.sun_family=AF_UNIX;
 
strcpy(srv_addr.sun_path,UNIX_DOMAIN);
 
//connect server
 
ret=connect(connect_fd,(struct sockaddr*)&srv_addr,sizeof(srv_addr));
 
if (ret<0){
 
perror("cannot connect server");
 
close(connect_fd);
 
return -1;
 
}
 
memset(send_buff,0,1024);
 
strcpy(send_buff,"message from client");
 
//send info server
 
write(connect_fd,send_buff,sizeof(send_buff));
 
close(connect_fd);
 
return 0;
 
}
#endif