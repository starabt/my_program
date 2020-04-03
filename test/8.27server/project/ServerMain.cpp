#include "global.h"
#include "buffer.h"
#include "clientfd.h"
#include "testpack.h"
#include "SaveAndPrintf_data.h"
#include "parse_data.h"
#include "tcpserver.h"
#include "sendfile.h"
#include "log.h"

void heartbeat_time_init(int time);
void server_socket_init();//创建socket 
void accept_clientfds_service();
void close_all_socket();
void create_keyboard_pthread();

bool BCC_check(unsigned char data[], int datahead_start_bit);
int get_data(unsigned char data[], int clientfd);
int search_datahead(unsigned char data[], int datahead_start_bit, int max_length);
int get_data_length(unsigned char data[], int datahead_start_bit);
int data_left_length(unsigned char data[], int datahead_start_bit);

void param_query(int clientfd, ...);
void param_set(int clientfd);
void remote_upgrade(int clientfd);

int main()
{	
	heartbeat_time_init(30);
	pthread_mutex_init(&mutex, NULL); // 初始化互斥锁，互斥锁默认是打开的
	server_socket_init();
	create_keyboard_pthread();
	accept_clientfds_service();
}


void *data_buffer(void *fd)
{	
	int clientfd = *(int*)fd;
	printf("clientfd:%d\n", clientfd);
	int clientfdi = find_client_fd(clientfd);
	unsigned char buffer[MAXBUF];
	bzero(buffer, MAXBUF);
	buffer_init(&clients_data_buffer[clientfdi], data_buffer_length);
	int data_length;
	while((data_length = get_data(buffer, clientfd)) > 0)
	{
		buffer_write_by_memcpy(&clients_data_buffer[clientfdi], (char*)buffer, data_length);
	}
	pthread_exit(NULL);
	
}

/*********************************************
*func:		client_service
*param:		&fd
*return		null
*descrp:	receive data from clients, process and respond

*author:	lam
*date:		2019.8.3
**********************************************/
void *client_service(void *fd)
{
	int clientfd = *(int*)fd;
	int clientfdi = find_client_fd(clientfd);//取得套接字描述符在描述符数组中的位置
	pthread_mutex_unlock(&mutex);//线程互斥锁关闭
	unsigned char buffer[MAXBUF + 24];//数据接受缓存
	unsigned char data[8*MAXBUF];//被拆分的单个数据包
	int data_length = 0;//检测数据长度位的值
	int read_data_length;
	//定时用，nowtime-lasttime=定时时间
	time_t lasttime, lasttime_wait;
	time_t nowtime, nowtime_wait;
	time(&lasttime);
	time(&lasttime_wait);
    while (clientfds[clientfdi] > 0)
	{
		sleep(1);
       	bzero(buffer, MAXBUF);
       	if (buffer_available_read(&clients_data_buffer[clientfdi]) > 0)
       	{
       		read_data_length = buffer_read_by_memcpy(&clients_data_buffer[clientfdi], (char*)buffer, MAXBUF);//recv数据进buffer，成功则返回true	
       	}
       	// else{printf("no data\n");}
       	int datahead_start_bit = 0;//数据头(##)位
		while (datahead_start_bit >= 0)
		{
			//printf("enter data_parse\n");
			//返回数据头在buffer中的位置，若无数据头则返回-1，循环结束
			if ((datahead_start_bit = search_datahead(buffer, datahead_start_bit, read_data_length)) != -1)
			{
				// printf("enter_datahead\n");
				//数据长度位是否在buffer里
				if (read_data_length - datahead_start_bit < 24)
				{
					// printf("数据长度位不在buffer里\n");
					int add_buffer_length = read_data_length - datahead_start_bit;
					buffer_read_by_memcpy(&clients_data_buffer[clientfdi], (char*)(buffer + read_data_length + 1), add_buffer_length);
					read_data_length += add_buffer_length;
				}
				//检测数据长度位所在的值是否超过最大限定值8k
				if ((data_length = get_data_length(buffer, datahead_start_bit)) == -1)
				{
					// printf("检测数据长度位所在的值超过最大限定值8k\n");
					datahead_start_bit += 1;
					continue;
				}
				//检测数据长度位值是否大于数据缓冲区目前所存数据
				time(&nowtime_wait);//判断数据等待超时，data_timeout为全局变量
				if (data_length > buffer_available_read(&clients_data_buffer[clientfdi]) + read_data_length - datahead_start_bit)
				{
					//printf("检测数据长度位值大于数据缓冲区目前所存数据\n");
					if (nowtime_wait - lasttime_wait >= data_timeout)
					{
						datahead_start_bit += 1;
						lasttime_wait = nowtime_wait;
						continue;
					}
					continue;
				}
				lasttime_wait = nowtime_wait;
				// printf("开始提取数据\n");
				// 提取一包数据进data
				bzero(data, 8*MAXBUF);
				if (data_length > read_data_length - datahead_start_bit)
				{
					// printf("数据长度大于buffer长\n");
					int left_len = data_length - (read_data_length - datahead_start_bit);
					memcpy(data, buffer + datahead_start_bit, read_data_length - datahead_start_bit);
					buffer_only_read_by_memcpy(&clients_data_buffer[clientfdi], (char*)(data + (read_data_length - datahead_start_bit)), left_len);
					//异或校验
					// printf("data_avail_read_lengthxxxxx:%d\n", buffer_available_read(&clients_data_buffer[clientfdi]));
					if (BCC_check(data, 0) == true)
					{
						// printf("检验正确\n");
						buffer_read_by_memcpy(&clients_data_buffer[clientfdi], (char*)(data + (read_data_length - datahead_start_bit)), left_len);
						command_check_service(clientfd, data);//数据解析函数
						bzero(buffer, 8*1024);
						read_data_length = buffer_read_by_memcpy(&clients_data_buffer[clientfdi], (char*)buffer, MAXBUF);
						datahead_start_bit = 0;
					}
					else
					{
						// printf("检验错误\n");
						datahead_start_bit += 1;
					}
				}
				else
				{
					// printf("数据正常处理\n");
					memcpy(data, buffer + datahead_start_bit, data_length);
					//异或校验
					if (BCC_check(data, 0) == true)
					{
						// printf("检验正确\n");
						command_check_service(clientfd, data);//数据解析函数
						// printf("数据处理完毕\n");
						datahead_start_bit += (buffer[datahead_start_bit + 22]<<8) + buffer[datahead_start_bit + 23] + 25;//下个数据头位
					}
					else
					{
						// printf("检验错误\n");
						datahead_start_bit += 1;
					}
				}
			}//end if
		}//end while
		if (modify_heartbeat_time_flag == true)
		{
			time(&lasttime);
			modify_heartbeat_time_flag = false;
		}		
		time(&nowtime);
		//心跳数据，间隔heartbeat_time
		if (nowtime - lasttime >= heartbeat_time[clientfdi] && login_flag[clientfdi] == true)
		{
			//每隔一段时间，heartbeat_cout自加，若客户端发送心跳数据则被清0
			heartbeat_count[clientfdi]++;
			// printf("heartbeat_count:%d\n", heartbeat_count[clientfdi]);
			//若无心跳数据，自加至一定值则判断为掉线
			if (heartbeat_count[clientfdi] > heartbeat_count_max)
			{
				work_log(clientfd, "%s\n", "disconnect and logout");
				heartbeat_count[clientfdi] = 0;
				heartbeat_time[clientfdi] = 30;//间隔时间初始化为30秒
				printf("网络异常，socket %d连接已断开\n", clientfd);
				login_flag[clientfdi] = false;
				close(clientfd);
				rm_clientfd(clientfd);
				
				break;
			}
			lasttime = nowtime;
		}
		// printf("clientfd:%d login_flag[clientfdi]:%d\n", clientfd,login_flag[clientfdi]);
    }//end while
    pthread_exit(NULL);
}

/*********************************************
*func:		keyboard()
*param:		void
*return		void
*descrp:	检查键盘输入指令

*author:	lam
*date:		2019.8.1
*ver:		v1.0.1
*change:	
**********************************************/
void *keyboard(void*)
{
    char msg[MAXBUF];
    for(;;)
    {
        fgets(msg, MAXBUF, stdin);
        //enter sendmsg mode
        if (!strcmp(" \n", msg))//输入空隔进入命令模式，可进行参数查询设置
        {
        	printf_data_flag = false;
        	printf("\nEnter \"sendmsg\" mode...\n");
        	printf("which socket do you want to sendmsg to?\n");
        	for(;;)
        	{
        		scanf("%s", msg);
        		if (!strcmp("Quit", msg))//键盘输入Quit，则终止服务器运行
        		{
        		 	goto Quit;
        		}
        		else if (!strcmp("quit", msg))//quit，退出命令模式
        		{
        			goto quit;
        		}
        		else if (!strcmp("list", msg))//列出现已连接的所有客户端套接字名
        		{
        			printf_clientfd();
        		}
        		else
        		{
        		 	int connectfd = atoi(msg);//指定客户端套接字描述符进行数据发送
        		 	if (connectfd !=0 && find_client_fd(connectfd) != -1)
        		 	{
        		 		printf("............socket %d.............\n", connectfd);
        		 		printf("order: 1.param_query 2.param_set 3.remote_upgrade 4.return\n");
        		 		bool order_flag = true;
        		 		while(order_flag)
        		 		{
        		 			char order_num[MAXBUF];
        		 			scanf("%s", order_num);
        		 			if (!strcmp("Quit", order_num))
        		 			{
        		 				goto Quit;
        		 			}
        		 			if (!strcmp("quit", order_num))
			        		{
			        			goto quit;
			        		}
	        		 		switch(atoi(order_num))
	        		 		{
	        		 			case 1: param_query(connectfd, 0x0d, 0x0e, 0x0f, 0x10, -1);//参数查询
	        		 					//param_query(connectfd, 0x04, 0x05, 0x07, 0x08, 0x09, -1);
	        		 					break;
	        		 			case 2:param_set(connectfd);break;//参数设置
	        		 			case 3:remote_upgrade(connectfd);upgrade_flag = true;break;//远程升级包
	        		 			case 4:	order_flag = false;//返回，重新指定客户端
	        		 					printf("which socket do you want to sendmsg to?\n");break;

	        		 			case 5: printf("test1\n");test1_datapack(connectfd);
	        		 					break;
	        		 			case 6: test2_datapack(connectfd);
	        		 					break;
	        		 			case 7: test3_datapack(connectfd);
	        		 					break;
	        		 			case 8: test4_datapack(connectfd);
	        		 					break;
	        		 			case 9: test5_datapack(connectfd);
	        		 					break;
	        		 		}
						} 		 				
        		 	}
        		 	else//指定的客户端不存在
        		 	{
        		 		printf("Not found!Please enter again!\n");
        		 	}
        		} 
        	}
        }
        else if (!strcmp("log\n", msg))
        {
        	// search_log();
        }
        //exit sendmsg mode and display data from client
	   	if (!strcmp("quit\n",msg))
		{
quit:		printf_data_flag = true;
		}
		//exit program
        if (!strcmp("Quit\n",msg))
        {
Quit:      	printf("Bye...\n");
            close_all_socket();
            break;
        }
    }
    exit(0);
}

/*升级服务*/
void *upgrade_service(void*)
{
	char code_recv[20];
	char code_send[5];
	bzero(code_recv, 20);
	bzero(code_send, 5);
	while(1)
	{	
		while(upgrade_flag == true) 
		{
			sleep(1);
			printf("等待进入升级\n");
		}
		printf("进入升级\n");
		int clientfd = socket_accept(upgrade_sockfd);  //接受连接
/*		printf("文件传输...\n");
		process_conn_client(clientfd);
		printf("传输完成\n");
*/		if (clientfd == -1)
		{
			continue;
		}
		memcpy(code_send, "220", 3);
		if(send(clientfd, &code_send, 3, 0) <= 0)
		{
			continue;
		}
		while(1)
		{
			recv_data(clientfd, code_recv, 20);
			if (!strcmp(code_recv, "USER lampro\r\n"))
			{
				memcpy(code_send, "331", 3);
				send(clientfd, &code_send, 3, 0);
				break;
			}
		}
		while(1)
		{
			recv_data(clientfd, code_recv, 20);
			if (!strcmp(code_recv, "PASS ljs12345\r\n"))
			{
				memcpy(code_send, "230", 3);
				send(clientfd, &code_send, 3, 0);
				break;
			}
		}
		sleep(1);
		printf("文件传输...\n");
		process_conn_client(clientfd);
		printf("传输完成\n");
		upgrade_flag = false;
		close(clientfd);
		// test1_datapack(clientfd); 				
	}
}

/*********************************************
*func:		heartbeat_time_init
*param:		void
*return		void
*descrp:	心跳数据间隔初始化(3秒)
**********************************************/
void heartbeat_time_init(int time)
{
	for (int i = 0; i < clientfds_max; ++i)
	{
		heartbeat_time[i] = time;
	}
}
/*********************************************
*func:		create_keyboard_pthread
*param:		void
*return		void
*descrp:	创建键盘输入线程
**********************************************/
void create_keyboard_pthread()
{
	void *keyboard(void*);
	//创建一个线程，对服务器程序进行管理（关闭）
	pthread_t keyboard_thread;
	pthread_create(&keyboard_thread, NULL, keyboard, NULL);	
}

/*********************************************
*func:		server_socket_init
*param:		void
*return		void
*descrp:	套接字初始化（创建和监听）

*author:	lam
*date:		2019.7.17
**********************************************/
void server_socket_init()
{
	//create sockfd for remote upgrade
	if ((upgrade_sockfd = socket_create(IP, UPGRADE_PORT)) == -1)
	{
		char tmp_log[256];
        sprintf(tmp_log,"%s%s","create upgrade socket error:",strerror(errno));
		err_log("%s\n", tmp_log);
		exit(-1);
	}
	void *upgrade_service(void*);
	//创建一个线程，对服务器程序进行管理（关闭）
	pthread_t id;
	pthread_create(&id, NULL, upgrade_service, NULL);	
	//create sockfd
    if ((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		char tmp_log[256];
        sprintf(tmp_log,"%s%s","create server socket error:",strerror(errno));
		err_log("%s\n", tmp_log);
        exit(-1);
    }
	const int on = 1;
	setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	//bind ip and port
    struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(IP);
    if (bind(server_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
	{
        char tmp_log[256];
        sprintf(tmp_log,"%s%s","bind error:",strerror(errno));
		err_log("%s\n", tmp_log);
        exit(-1);
    }
	//socket_listen
	if (listen(server_sockfd, BACKLOG) == -1)
	{
        char tmp_log[256];
        sprintf(tmp_log,"%s%s","listen error:",strerror(errno));
		err_log("%s\n", tmp_log);
        exit(-1);
    }
	printf("server has started up,waiting for connection\n");
}

/*********************************************
*func:		accept_clientfds_service
*param:		void
*return		void
*descrp:	接受客户端连接并创建线程通信

*author:	lam
*date:		2019.7.17
**********************************************/
void accept_clientfds_service()
{
	while(1)
	{
		int client_sockfd;		
		struct sockaddr_in client_addr;
	    socklen_t len = sizeof(client_addr);
		pthread_mutex_lock(&mutex);
		if ((client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_addr, &len)) == -1)
	    {
	  		char tmp_log[256];
        	sprintf(tmp_log,"%s%s","accept error:",strerror(errno));
			err_log("%s\n", tmp_log);
			printf("fail connection\n");
	        continue;
	    }
		else
		{
			printf("server: got connection from %s, port %d, socket %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), client_sockfd);
		}
		work_log(client_sockfd, "%s\n", "connect but not login");
		add_new_clientfd(client_sockfd);
		//针对当前套接字创建一个线程，对当前套接字的消息进行处理
		void *client_service(void *fd);//客户端数据处理函数（线程）
		void *data_buffer(void *fd);
		pthread_t buffer_thread;
		pthread_t tid;
	  	pthread_create(&tid, NULL, client_service, &client_sockfd);
	  	pthread_create(&buffer_thread, NULL, data_buffer, &client_sockfd);	
		pthread_detach(tid);
	}
}

/*********************************************
*func:		close_all_socket
*param:		void
*return		void
*descrp:	关闭所有套接字
**********************************************/
void close_all_socket()
{
	work_log(0, "%s\n", "close_all_socket");
	close(server_sockfd);
	for (int i = 0; i < clientfds_max; ++i)
	{
		if (clientfds[i])
		{
			close(clientfds[i]);
		}
	}
}

/*********************************************
*func:		get_data
*param:		data clientfd
*return		int(data_length)
*descrp:	get data from client
**********************************************/
int get_data(unsigned char data[], int clientfd)
{
	bzero(data, MAXBUF);
	int ret = recv(clientfd, data, MAXBUF, 0);
   	if (ret > 0)
	{
   		return (ret);
    }
    else
    {
    	work_log(clientfd, "%s\n", "logout");
    	login_flag[find_client_fd(clientfd)] = false;
    	heartbeat_count[find_client_fd(clientfd)] = 0;
    	close(clientfd);
		rm_clientfd(clientfd);
		printf("socket %d已退出\n\n", clientfd);
		return 0;
    }
    
}

/*********************************************
*func:		search_datahead
*param:		data and datahead_start_bit
*return		datahead_bit
*descrp:	寻找数据头位置
**********************************************/
int search_datahead(unsigned char data[], int datahead_start_bit, int max_length)
{
	int i;
	for (i = datahead_start_bit; i < max_length; i++)
	{
		if (data[i] == '#')
		{
			if (data[i + 1] == '#')
			{
				return(i);
			}
			else i++;
		}
	}
	return(-1);
}

/*********************************************
*func:		get_data_length
*param:		data and datahead_start_bit
*return		data_length
*descrp:	数据长度位的值
**********************************************/
int get_data_length(unsigned char data[], int datahead_start_bit)
{
	int data_length = (data[22 + datahead_start_bit]<<8) + data[23 + datahead_start_bit] + 25;
		// printf("长度位为:(%x)(%x)\n", data[22 + datahead_start_bit], data[23 + datahead_start_bit]);
	if ( 0 <= data_length && data_length < 8*MAXBUF)
	{
		return (data_length);
	}
	return(-1);
}

/*********************************************
*func:		BCC_check()
*param:		data for check
*return		bool:ture or false
*descrp:	数据异或校验

*author:	lam
*date:		2019.7.31
change:     add datahead_start_bit
**********************************************/
bool BCC_check(unsigned char data[], int datahead_start_bit)
{
	//异或校验
	int data_length = (data[22 + datahead_start_bit]<<8) + data[23 + datahead_start_bit] + 25;
	if (data_length > 8*1024 || data_length < 0)
	{
		return false;
	}
	int BCC_code = data[datahead_start_bit];
	for (int i = 0; i < data_length - 2; i++)
	{       
	   	BCC_code ^= data[datahead_start_bit + i + 1];
	}
	if (BCC_code == data[datahead_start_bit + data_length - 1])
	{
		//printf("BCC_code:%x\n", BCC_code);
		return(true);
	}
	else
	{
		return(false);
	}
}

/*********************************************
*func:		data_left_length
*param:		data, datahead_start_bit
*return		前半包长
*descrp:	求取分包数据前半包长

*author:	lam
*date:		2019.8.1
**********************************************/
int data_left_length(unsigned char data[], int datahead_start_bit)
{
	for (int i = MAXBUF - 1; i >= 0; i--)
	{
		if (data[i] != 0)
		{
			return (i + 1 - datahead_start_bit);
		}
	}
	return(-1);
}

/************************************************************
*func:		param_query()
*param:		查询参数（clientfd，参数，...，-1）
*descrp:	
*author:	Lam
*date:		2019.8.3
************************************************************/
void param_query(int clientfd, ...)
{
	//获取Unix时间戳
	time_t t;
	struct tm*lt;
	time (&t);
	lt = localtime(&t);
    va_list arg_ptr;    
    va_start(arg_ptr, clientfd);
	unsigned char data[MAXBUF];
	unsigned char param_num = 0;//查询参数数量
	int j = 0;
    while(j != -1 )
    {
		param_num++;
        j = va_arg(arg_ptr, int);
		if(j != -1) data[30 + param_num] = (unsigned char)j;	
    }
	param_num -=1;
	printf("参数个数：%d\n", param_num);
	data[30] = param_num;
    va_end(arg_ptr);
	const char *s1 = "##";//开头
	memcpy(data, s1, 2*sizeof(char));
	data[2] = 0x80;//命令标识
	data[3] = 0xFE;//应答标志
	const char *s2 = "LFV2A2156C3333333";
	memcpy(data+4,s2,17*sizeof(char));//唯一识别码
	data[21] = 0x01;//数据加密方式
	data[22] = 0x00;
	data[23] = param_num + 7;//数据单元长度
	data[24] = lt->tm_year-100;
	data[25] = lt->tm_mon+1;
	data[26] = lt->tm_mday;
	data[27] = lt->tm_hour;
	data[28] = lt->tm_min;
	data[29] = lt->tm_sec;//数据采集时间
	//计算校验码
	int k;
	int data_length = data[23] + 25;		
	int BCC_code_resp=data[0];
	for (k = 0; k < data_length - 2; k++)
   	{       
   		BCC_code_resp ^= data[k + 1];
   	}
	data[data_length - 1] = BCC_code_resp;
	send(clientfd, data, data_length, 0);
}

/************************************************************
*func:		param_set
*param:		clientfd
*descrp:	设置参数
*author:	Lam
*date:		2019.8.3
************************************************************/
void param_set(int clientfd)
{
	//获取Unix时间戳
	time_t t;
	struct tm*lt;
	time (&t);
	lt = localtime(&t);
	srand((int)time(0));
	int param_num;
	unsigned char buf[MAXBUF];
	const char *s1 = "##";//开头
	memcpy(buf, s1, 2*sizeof(char));
	buf[2] = 0x81;//命令标识
	buf[3] = 0xFE;//应答标志
	const char *s2 = "LFV2A2156C3333333";
	memcpy(buf+4,s2,17*sizeof(char));//唯一识别码
	buf[21] = 0x01;//数据加密方式
	buf[22] = 0x00;
	buf[24] = lt->tm_year-100;
	buf[25] = lt->tm_mon+1;
	buf[26] = lt->tm_mday;
	buf[27] = lt->tm_hour;
	buf[28] = lt->tm_min;
	buf[29] = lt->tm_sec;//数据采集时间
	int i = 30;
	buf[i++] = 4;
	buf[i++] = 0x07;  //硬件版本
	const char *s3 = "addww";
	memcpy(buf + i, s3, 5*sizeof(char));
	i+=5;
	buf[i++] = 0x04;   //服务平台域名长度
	buf[i++] = 8 + 8;
	buf[i++] = 0x05; //服务平台域名
	const char *s5 = "www.";
	memcpy(buf + i, s5, 4*sizeof(char));
	i+=4;
	int j;
	for(j=0; j<8; j++)
	{
		do
		{
			buf[i] = rand()%0x80;
		}while((buf[i] < 48 || buf[i] > 57) && (buf[i] < 65 || buf[i] > 90) && (buf[i] < 97 || buf[i] > 122));
		i++;
	}
	const char *s6 = ".com";
	memcpy(buf + i, s6, 4*sizeof(char));
	i+=4;
	buf[i++] = 0x08;  //固件版本
	const char *s4 = "lbwcc";
	memcpy(buf + i, s4, 5*sizeof(char));
	i+=5;

/*
	buf[i++] = 0x01;   //存储时间周期
	buf[i++] = rand()%0xeb;
	buf[i++] = rand()%0x61;
	buf[i++] = 0x02;   //正常信息上报时间周期
	buf[i++] = rand()%0x03;
	buf[i++] = rand()%0x059;
	buf[i++] = 0x03;   //报警存储时间周期
	buf[i++] = rand()%0xeb;
	buf[i++] = rand()%0x61;

	buf[i++] = 0x06;   //服务平台端口
	buf[i++] = rand()%0x100;
	buf[i++] = rand()%0xfe;

	buf[i++] = 0x09;//心跳发送周期
	buf[i++] = rand()%0xf1;
	buf[i++] = 0x0a;//终端应答超时时间
	buf[i++] = rand()%0x03;
	buf[i++] = rand()%0x59;
	buf[i++] = 0x0b;//平台应答超时时间
	buf[i++] = rand()%0x03;
	buf[i++] = rand()%0x59;
	buf[i++] = 0x0c;//间隔时间
	buf[i++] = rand()%0xf1;
	buf[i++] = 0x0d;//公共平台域名长度
	buf[i++] = rand()%0x100;
	buf[i++] = 0x0e;//公共平台域名
	for(j=0; j< buf[i-2]; j++)
	{
		buf[i] = rand()%0x80;
		i++;
	}
	buf[i++] = 0x0f;//公共平台端口
	buf[i++] = rand()%0x100;	
	buf[i++] = rand()%0xfc;
	buf[i++] = 0x10;//抽样监测位
	buf[i++] = rand()%0x03;
*/
	buf[23] = i - 30 + 6;//数据单元长度
	//计算校验码
	int k;
	int buf_length = buf[23] + 25;		
	int BCC_code_resp = buf[0];
	for (k = 0; k < buf_length - 2; k++)
   	{       
   		BCC_code_resp ^= buf[k + 1];
   	}
	buf[buf_length - 1] = BCC_code_resp;
	send(clientfd, buf, buf_length, 0);
	printf("参数设置数据已发送\n");
}

/************************************************************
*func:		remote_upgrade
*param:		clientfd 套接字描述符
*descrp:	向客户端发送升级命令
*author:	Lam
*date:		2019.8.3
************************************************************/
void remote_upgrade(int clientfd)
{
	//获取Unix时间戳
	time_t t;
	struct tm*lt;
	time (&t);
	lt = localtime(&t);
	srand((int)time(0));
	int param_num;
	unsigned char buf[MAXBUF];
	const char *s0 = "##";//开头
	memcpy(buf, s0, 2*sizeof(char));
	buf[2] = 0x82;//命令标识
	buf[3] = 0xFE;//应答标志
	const char *s1 = "LFV2A2156C3333333";
	memcpy(buf + 4, s1, 17*sizeof(char));//唯一识别码
	buf[21] = 0x01;//数据加密方式
	buf[24] = lt->tm_year-100;
	buf[25] = lt->tm_mon+1;
	buf[26] = lt->tm_mday;
	buf[27] = lt->tm_hour;
	buf[28] = lt->tm_min;
	buf[29] = lt->tm_sec;//数据采集时间
	int i = 30;
	buf[i++] = 1;//参数个数
	buf[i++] = 0x01;//远程升级命令

	const char *s2 = "tcp://lampro:ljs12345@192.168.43.222:2547/client1";
	memcpy(buf + i, s2, 46*sizeof(char));//拨号点名称
	i+=46;
	buf[23] = i - 30 + 6;//data_length

	int k;
	int buf_length = buf[23] + 25;		
	int BCC_code_resp=buf[0];
	for (k = 0; k < buf_length-2; k++)
   	{       
   		BCC_code_resp^=buf[k+1];
   	}
	buf[buf_length-1] = BCC_code_resp;
	send(clientfd, buf, buf_length, 0);
}
