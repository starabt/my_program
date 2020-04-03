#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int socket_create(const char* ip,const int port);
int socket_accept(int sock);
// int socket_connect(const char* ip,const int port);
int recv_data(int sock,char* buf,int bufsize);
int send_response(int sock,int code);

#endif