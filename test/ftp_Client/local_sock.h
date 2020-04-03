#ifndef _LOCAL_SOCK_H_
#define _LOCAL_SOCK_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/socket.h>
#define LOCAL_DOMAIN "/mnt/mtd/nsd/program/bin/tmp" //must be the absolute path
class LOCAL_SOCK
{
public:
	LOCAL_SOCK();
	virtual ~LOCAL_SOCK();
	int serv_wait_connect(const char* domain_path);
	void close_serv();
	int get_servfd();

	int client_connect(const char* domain_path);
	void close_client();
	int get_clientfd();
private:
	int serv_listen(const char* domain_path);
	int serv_accept(int listen_fd);
	int serv_fd;
	int client_fd;
	char UINX_DOMAIN[256];
};
#endif