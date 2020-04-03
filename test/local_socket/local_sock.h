#ifndef _LOCAL_SOCK_H_
#define _LOCAL_SOCK_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/socket.h>
#define LOCAL_DOMAIN "/home/lxc/test/tmp"
class LOCAL_SOCK
{
public:
	LOCAL_SOCK();
	virtual ~LOCAL_SOCK();
	int serv_wait_connect(const char* domain_path);
	int client_connect(const char* domain_path);
private:
	int serv_listen(const char* domain_path);
	int serv_accept(int listen_fd);
	char UINX_DOMAIN[256];
};
#endif