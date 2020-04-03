#include "local_sock.h"
LOCAL_SOCK::LOCAL_SOCK()
{}
LOCAL_SOCK::~LOCAL_SOCK()
{
	memset(UINX_DOMAIN,0,sizeof(UINX_DOMAIN));
}
int LOCAL_SOCK::serv_wait_connect(const char* domain_path)
{
	printf("local_sock server domain:%s\n", domain_path);
	int accept_fd = -1;
	int listen_fd = -1;
	listen_fd =serv_listen(domain_path);
	printf("serv_listen listen_fd:%d\n",listen_fd);
	if(listen_fd > 0)
	{
		accept_fd=serv_accept(listen_fd);
	}
	printf("serv_accept accept_fd:%d\n",accept_fd);

	return accept_fd;
}
int LOCAL_SOCK::client_connect(const char* domain_path)
{
	printf("local_sock client domain:%s\n", domain_path);
	int connect_fd =-1;
	struct sockaddr_un client_un;
	connect_fd = socket(AF_UNIX,SOCK_STREAM,0);
	if(connect_fd < 0)
	{
		perror(" client create local socket error");
		return -1;
	}
	client_un.sun_family = AF_UNIX;
	strcpy(client_un.sun_path,domain_path);
	if(connect(connect_fd,(struct sockaddr*)&client_un,sizeof(client_un)) < 0)
	{
		perror("client local socket connect error");
		close(connect_fd);
		return -1;
	}
	printf("connect connect_fd:%d\n",connect_fd);
	return connect_fd;
}
int LOCAL_SOCK::serv_listen(const char* domain_path)
{
	if(domain_path == NULL)
		strcpy(UINX_DOMAIN,"./tmp");
	else
		strcpy(UINX_DOMAIN,domain_path);
	int serv_fd=-1;
	struct sockaddr_un serv_un;
	/*	create socket */
	serv_fd = socket(AF_UNIX,SOCK_STREAM,0);
	if(serv_fd < 0)
	{
		perror("creat local socket error");
		return -1;
	}
	unlink(UINX_DOMAIN); 	/*in case it already exist*/
	/* fill in socket address structure*/
	memset(&serv_un,0,sizeof(serv_un));
	serv_un.sun_family = AF_UNIX;
	memcpy(serv_un.sun_path,UINX_DOMAIN,strlen(UINX_DOMAIN)); 

	/*	bind the UINX_DOMAIN to the descripter	*/
	if(bind(serv_fd,(struct sockaddr *)&serv_un,sizeof(serv_un)) < 0 )
	{
		perror("local socket bind error");
		close(serv_fd);
		return -2;
	}
	/*	listen */
	int MAX_LISTEN_NUM = 10;
	if(listen(serv_fd,MAX_LISTEN_NUM) < 0 )
	{
		perror("local socket listen error");
		close(serv_fd);
		return -3;
	}
	return (serv_fd);
}
int LOCAL_SOCK::serv_accept(int listen_fd)
{
	int client_fd = -1;
	socklen_t len=0;
	struct sockaddr_un accept_un;
	/*	allocate enough space for longest domain_path plus terminating null*/
	len = sizeof(accept_un);
	client_fd = accept(listen_fd,(struct sockaddr*)&accept_un,&len);
	if(client_fd < 0)
	{
		perror("local socket accept error");
		unlink(UINX_DOMAIN);
		return -1;
	}
	unlink(accept_un.sun_path);
	return client_fd;
}