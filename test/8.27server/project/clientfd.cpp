#include "clientfd.h"
/*********************************************
*func:		add_new_clientfd()
*param:		sockfd
*return		int
*descrp:	添加客户端成员
**********************************************/
void add_new_clientfd(int clientfd)
{
	int i;
	for (i = 0; i < clientfds_max; i++)
	{
		if (clientfds[i] == 0)
		{
			clientfds[i] = clientfd;
			break;
		}
		else if (i == clientfds_max -1 && clientfds[i] != 0)
		{
			printf("客户端数量达上限\n");
			//close(clientfd);
			break;
		}
	}
}

/*********************************************
*func:		find_client_fd
*param:		客户端套接字
*return		套接字所在数组位置
*descrp:	寻找客户端套接字
**********************************************/
int find_client_fd(int fd)
{	
	int i;
	for (i = 0; i < clientfds_max; i++)
	{
		if (clientfds[i] == fd)
		{
			return(i);
		}
	}
	return -1;
}

/*********************************************
*func:		rm_clientfd()
*param:		clientfd
*return		void
*descrp: 	删除客户端成员
**********************************************/
void rm_clientfd(int clientfd)
{
	int i;
	for (i = 0; i < clientfds_max; i++)
	{
		if (clientfds[i] == clientfd)
		{
			clientfds[i] = 0;
		}
	}
}

/*********************************************
*func:		printf_clientfd
*param:		void
*return		void
*descrp:	打印已连接的套接字
**********************************************/
void printf_clientfd()
{
	for (int i = 0; i < clientfds_max; ++i)
	{
		if (clientfds[i])
		{
			printf("client_socket %d\n", clientfds[i]);
		}
	}
}