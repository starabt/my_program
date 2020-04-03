#include "tcpserver.h"

int socket_create(const char* ip,const int port)  //创建一个监听套接字
{
	if((NULL==ip) || (port<0))
	{
		//print_log()
		return -1;
	}

	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		//print_log();
		return -1;
	}

	int op=1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&op,sizeof(op));
	
	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_port=htons(port);
	local.sin_addr.s_addr=inet_addr(ip);

	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		//print_log();
		return -1;
	}

	if(listen(sock,5)<0)
	{
		//print_log();
		return -1;
	}
	return sock;
}

int socket_accept(int sock)     //接受连接
{
	struct sockaddr_in peer;
	socklen_t len=sizeof(peer);

	int connfd=accept(sock,(struct sockaddr*)&peer,&len);
	if(connfd<0)
	{
		//print_log()
		return -1;
	}
	return connfd;
}

int recv_data(int sock,char* buf,int bufsize)  //从sock读取数据
{
	memset(buf,0,bufsize);
	ssize_t s=recv(sock,buf,bufsize,0);
	if(s<=0)
		return -1;
	return s;
}

int send_response(int sock,int code)   //发送响应码到sock
{
	int stat_code=htonl(code);
	if(send(sock,&stat_code,sizeof(stat_code),0)<0)
	{
		//print_log()
		return -1;
	}
	return 0;
}