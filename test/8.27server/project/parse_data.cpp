#include "parse_data.h"

/*********************************************
*func:		parse_data()
*param:		buf//data for check
*return		void
*descrp:	解析数据

*author:	lam
*date:		2019.7.18
*ver:		v1.0.0
*change:	
**********************************************/
void parse_data(unsigned char data[], int clientfd)
{
	// save_data_log(data);
	if (printf_data_flag ==true)
	{
		printf_time(data);
	}	
	int data_parse_start_init = 30;//数据解析起始位
	int data_parse_start_bit = data_parse_start_init;
	if (printf_data_flag == true)
	{
		printf("数据位总数%d\n", data[23] - 6);
	}	
	for(data_parse_start_bit = data_parse_start_init; data_parse_start_bit < data[23] + 24; data_parse_start_bit++)
	{
		switch(data[data_parse_start_bit])
		{
			case(car_data):data_parse_start_bit = car_data_parse(data, data_parse_start_bit, clientfd);break;

			case(motor_data):/*printf("已进入motor_data函数\n");*/data_parse_start_bit += 13*data[data_parse_start_bit + 1];break;

			case(battery_data):data_parse_start_bit = battery_data_parse(data, data_parse_start_bit, clientfd);break;

			case(engine_data):/*printf("已进入engine_data函数\n");*/data_parse_start_bit += 5;break;

			case(car_location_data):/*printf("已进入car_location_data函数\n");*/data_parse_start_bit += 9;break;

			case(extremum_data):data_parse_start_bit = extremum_data_parse(data, data_parse_start_bit, clientfd);/*printf("极值数据结束位：%d\n", data_parse_start_bit);*/break;

			case(alarm_data):data_parse_start_bit = alarm_data_parse(data, data_parse_start_bit, clientfd);break;


			default:{
						//printf("未知上报数据\n");
					}
		}
	}
	data_respond(data, respond_success, clientfd);
}

/*********************************************
*func:		car_data_parse
*param:		data and data_start_bit clientfd
*return		int 返回该信息位最后一位
*descrp:	整车数据解析（存储和打印）
**********************************************/
int car_data_parse(unsigned char data[], int data_start_bit, int clientfd)
{
	//printf("已进入car_data函数\n");
	//data_start_bit为信息类型标志位位置
	int i;
	i = save_car_data(data, data_start_bit + 1, clientfd);	
	if (printf_data_flag == true)
	{
		printf_car_data(clientfd);
	}
	return(data_start_bit + i);
}

/*********************************************
*func:		battery_data_parse
*param:		data and data_start_bit and clientfd
*return		int 返回该信息位最后一位
*descrp:	燃料电池数据解析（存储和打印）
**********************************************/
int battery_data_parse(unsigned char data[], int data_start_bit, int clientfd)
{
	//printf("已进入battery_data函数\n");
	//data_start_bit为信息类型标志位位置
	int i = save_battery_data(data, data_start_bit + 1, clientfd);
	if (printf_data_flag == true)
	{
		printf_battery_data(clientfd);
	}	
	return(data_start_bit + i);
}

/*********************************************
*func:		extremum_data_parse
*param:		data and data_start_bit clientfd
*return		int 返回该信息位最后一位
*descrp:	整车数据解析（存储和打印）
**********************************************/
int extremum_data_parse(unsigned char data[], int data_start_bit, int clientfd)
{
	//printf("已进入extremum_data函数\n");
	//data_start_bit为信息类型标志位位置
	int i;
	i = save_extremum_data(data, data_start_bit + 1, clientfd);
	if (printf_data_flag == true)
	{
		printf_extremum_data(clientfd);
	}		
	return(data_start_bit + i);
}

/*********************************************
*func:		alarm_data_parse
*param:		data and data_start_bit clientfd
*return		int 返回该信息位最后一位
*descrp:	alarm数据解析（存储和打印）
**********************************************/
int alarm_data_parse(unsigned char data[], int data_start_bit, int clientfd)
{
	//printf("已进入alarm_data函数\n");
	//data_start_bit为信息类型标志位位置
	int i;
	i = save_alarm_data(data, data_start_bit + 1, clientfd);
	if (printf_data_flag == true)
	{
		printf_alarm_data(clientfd);
	}		
	return(data_start_bit + i);
}

/*********************************************
*func:		data_respond
*param:		data  and 应答标识
*return		void
*descrp:	应答客服端

*author:	lam
*date:		2019.7.17
**********************************************/
void data_respond(unsigned char data[], unsigned char respond_name, int clientfd)
{	
	int i;
	int data_length = (data[22]<<8) + data[23] + 25;
	//计算新校验码
	data[3] = respond_name;		
	int BCC_code_resp = data[0];
	for (i = 0; i < data_length - 2; i++)
   	{       
   		BCC_code_resp ^= data[i + 1];
   	}
	data[data_length - 1] = BCC_code_resp;
	send(clientfd, data, data_length, 0);
	if (printf_data_flag == true)
	{
		printf("\n");
	}
}
/*判断数据命令*/
void command_check_service(int clientfd, unsigned char data[])
{
	if (command_check(data) != 0XFF && data[2] != command_heartbeat && data[2] != command_time && data[2] != command_modify_heartbeat_time)
	{
		data_log(clientfd, data);
	}
	// printf("enter command_check_service\n");
	switch(command_check(data))	
	{
		case command_login:login_service(data, clientfd);break;

		case command_logout:logout_service(data, clientfd);break;

		case command_time:time_service(data, clientfd);break;

		case 0x03:printf("补发数据.....................\n\n\n\n\n\n\n\n");

		case command_data:data_service(data, clientfd);break;

		case command_heartbeat:heartbeat_service(data, clientfd);break;
		
		case command_modify_heartbeat_time:modify_heartbeat_time(data, clientfd);break;

		case respond_param_query:respond_param_query_service(data);break;

		case respond_param_set:respond_param_set_service(data);break;

		case respond_remote_upgrade:respond_remote_upgrade_service(data, clientfd);break;

		case command_recv_log:command_recv_log_service(data, clientfd);break;

		default://printf("未知命令\n");
				break;
	}	
}

/*********************************************
*func:		command_check
*param:		data
*return		command_name or 0(若不是命令)
*descrp:	检查应答标示位，并返回命令标示

*author:	lam
*date:		2019.7.17
*ver:		v1.0.0
*change:	
**********************************************/
unsigned char command_check(unsigned char data[])
{
	unsigned char command_name, respond_name;
	command_name = data[2];
	respond_name = data[3];
	if (respond_name == 0xfe || respond_name == respond_success || respond_name == respond_fail)
	{
		return (command_name);
	}
	else return 0XFF;	
}

void command_recv_log_service(unsigned char data[], int clientfd)
{
	printf("enter recv_logfile_service\n\n\n\n\n\n\n\n\n");
	// if(login_flag[find_client_fd(clientfd)] == true)
	{
		int data_length = (data[22]<<8) + data[23] + 25;
		printf("data_length:%d\n", data_length);
		int colon_bit;
		for(colon_bit = 36; colon_bit < data_length - 1; colon_bit++)	
		{
			if (data[colon_bit] == ':')
			{
				break;				
			}
		}
		printf("colon_bit:%d\n", colon_bit);
		// ftp://192.168.43.214:23666a
		char IP[15] = {0};
		memcpy(IP, data + 36, colon_bit-36);
		printf("IP:%s\n", IP);
		int num_str_port = data_length-colon_bit-2;
		if (num_str_port < 4)
		{
			return;
		}
		printf("num_str_port:%d\n", num_str_port);
		int PORT = 0;
		char tmp[1] = {0};
		for (int i = 0; i < num_str_port; ++i)
		{
			PORT = PORT*10;
			tmp[0] = data[colon_bit + 1 + i];
			PORT += atoi(tmp);
			printf("\n");
		}
		printf("PORT:%d\n", PORT);
		//create sockfd for recieving logfile
		static int recv_logfile_sockfd;				/*socket描述符*/
		struct sockaddr_in server_addr;			/*服务器地址结构*/
		if ((recv_logfile_sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		{
			char tmp_log[256];
	        sprintf(tmp_log,"%s%s","create upgrade socket error:",strerror(errno));
			err_log("%s\n", tmp_log);
			exit(-1);
		}
		bzero(&server_addr, sizeof(server_addr));	/*清零*/
		server_addr.sin_family = AF_INET;					/*协议族*/
		server_addr.sin_addr.s_addr = htonl(INADDR_ANY);	/*本地地址*/
		server_addr.sin_port = htons(PORT);				/*服务器端口*/
		/*将用户输入的字符串类型的IP地址转为整型*/
		inet_pton(AF_INET, IP, &server_addr.sin_addr);	
		/*连接服务器*/
		if ((connect(recv_logfile_sockfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr))) == -1)
		{
			return;
		}
		void *recv_logfile_service(void*sockfd);
		pthread_t recv_logfile_thread;
	  	pthread_create(&recv_logfile_thread, NULL, recv_logfile_service, &recv_logfile_sockfd);
		pthread_detach(recv_logfile_thread);
		printf("recv_logfile_sockfd:%d\n", recv_logfile_sockfd);
	}
}

void *recv_logfile_service(void*sockfd)
{
	int fd = *((int*)sockfd);
	printf("fd:%d\n", fd);
	ssize_t size = 0;
	char buffer[BUFFER_SIZE];
	FILE *stream;
	strcpy(buffer,"请输入传输的文件路径：\n");
	int size2;
	if((size2 = send(fd, buffer, BUFFER_SIZE, 0)) == -1)
	{
		printf("send wrong\n");
	}
	else
	{
		printf("size:%d\n", size2);
	}

	int length=0;
	char buffer_add[BUFFER_SIZE]={'\0'};

	printf("enter recv path name\n");

	for(;;){
		size = read(fd, buffer, BUFFER_SIZE-length);
		if(size <= 0){
			pthread_exit(0);
		}
		strcat(buffer_add, buffer);
		length+=size;
		if(length>=BUFFER_SIZE) break;
	}
	char file_name[100] = {0};
	for (int i = strlen(buffer_add)-1; i >= 0; i--)
	{
		if (buffer_add[i] == '/')
		{
			memcpy(file_name, buffer_add+i+1, strlen(buffer_add)-i-1);
			break;
		}
	}
	time_t current_time = time(0);
	struct tm lt;
	localtime_r(&current_time, &lt);
	char time_str[50];
	sprintf(time_str, "%d-%02d-%02d ", lt.tm_year+1900, lt.tm_mon+1, lt.tm_mday);
	printf("time:%s\n", time_str);
	bzero(buffer_add, BUFFER_SIZE);
	memcpy(buffer_add, "../log/clientlog/", 17);
	memcpy(buffer_add+17, time_str, strlen(time_str));
	memcpy(buffer_add+17+strlen(time_str), file_name, strlen(file_name));
	if((stream=fopen(buffer_add, "w"))==NULL) pthread_exit(0);
	for(;;){
		size = read(fd, buffer, BUFFER_SIZE);
		printf("read_size:%d\n", size);
		if(size <= 0){
			break;
		}
		int write_len=fwrite(buffer, sizeof(char), size, stream);
	}
	fclose(stream);
	pthread_exit(0);
	close(fd);
}

/*升级命令发送成功应答*/
void respond_remote_upgrade_service(unsigned char data[], int clientfd)
{
	if(login_flag[find_client_fd(clientfd)] == true)
	{
		if(data[3] == respond_success)
		{
			printf("升级服务成功\n");			
		}
		else
		{
			printf("无法升级\n");
		}
	}
}

/*********************************************
*func:		respond_param_query_service
*param:		buf
*return		void
*descrp:	参数查询是否成功
**********************************************/
void respond_param_query_service(unsigned char data[])
{
	if(data[3] == respond_success)
	{
		printf("数据查询成功\n");
		printf_param(data);
		printf("\n");
	}
	else
	{
		printf("数据查询失败\n");
	}
}

/*********************************************
*func:		respond_param_set_service
*param:		buf
*return		void
*descrp:	参数设置是否成功
**********************************************/
void respond_param_set_service(unsigned char data[])
{
	if(data[3] == respond_success)
	{
		printf("数据设置成功\n");
	}
	else
	{
		printf("数据设置失败\n");
	}
}

/*********************************************
*func:		login_service
*param:		data and client_socket
*return		NULL
*descrp:	登录标示码识别

*author:	lam
*date:		2019.7.17
*ver:		v1.0.0
*change:	
**********************************************/
void login_service(unsigned char data[], int clientfd)
{
	int clientfdi = find_client_fd(clientfd);
	//比对成功且未重复登录
	if ((vin_compare(data) == true) && (login_flag[clientfdi] == false))
	{
		//printf("比对成功\n");
		data_respond(data, respond_success, clientfd);
		login_flag[clientfdi] = true;
		work_log(clientfd, "%s\n", "login");
	}
	//重复登录
	else if (login_flag[clientfdi] == true)
	{
		if (printf_data_flag == true)
		{
			printf("重复\n");
		}		
		data_respond(data, respond_vin_repeat, clientfd);
		work_log(clientfd, "%s\n", "relogin");
	}
	//比对失败
	else
	{
		if (printf_data_flag == true)
		{
			printf("比对失败\n");
		}
		data_respond(data, respond_fail, clientfd);
		work_log(clientfd, "%s\n", "fail to login");
	}
}

/*********************************************
*func:		logout_service
*param:		data
*return		void
*descrp:	

*author:	lam
*date:		2019.7.17
**********************************************/
void logout_service(unsigned char data[], int clientfd)
{
	int clientfdi = find_client_fd(clientfd);
	if (login_flag[clientfdi] == false)
	{
		if (printf_data_flag == true)
		{
			printf("对方未先登录\n");
		}
		data_respond(data, respond_fail, clientfd);

	}	
	else
	{
		work_log(clientfd, "%s\n", "logout");
		if (printf_data_flag == true)
		{
			printf("对方登出\n");
		}	
		data_respond(data, respond_success, clientfd);
		rm_clientfd(clientfd);
		close(clientfd);
		heartbeat_count[find_client_fd(clientfd)] = 0;
		heartbeat_time[find_client_fd(clientfd)] = 3;
		login_flag[clientfdi] = false;

	}
}

/*********************************************
*func:		data_service
*param:		buf
*return		void
*descrp:	解析数据并回应
**********************************************/
void data_service(unsigned char data[], int clientfd)
{
	if (login_flag[find_client_fd(clientfd)] == true)
	{
		parse_data(data, clientfd);
	}
}

/*********************************************
*func:		time_service
*param:		data
*return		void
*descrp:	
**********************************************/
void time_service(unsigned char data[], int clientfd)
{
	if(login_flag[find_client_fd(clientfd)] == true)
	{		
		time_t t;
		struct tm*lt;
		time (&t);//获取Unix时间戳
		lt = localtime(&t);
		data[23] += 6; //数据单元长度
		data[24]=lt->tm_year-100;
		data[25]=lt->tm_mon+1;
		data[26]=lt->tm_mday;
		data[27]=lt->tm_hour;
		data[28]=lt->tm_min;
		data[29]=lt->tm_sec;//数据采集时间
		if (printf_data_flag == true)
		{
			printf("校时数据\n");
		}		
		data_respond(data, respond_success, clientfd);
	}
}

/*********************************************
*func:		modify_heartbeat_time
*param:		data
*return		void
*descrp:	修改定时时间
**********************************************/
void modify_heartbeat_time(unsigned char data[], int clientfd)
{
	int i = find_client_fd(clientfd);
	if (login_flag[find_client_fd(clientfd)] == true)
	{	
		modify_heartbeat_time_flag = true;	
		heartbeat_time[i] = data[24];
		if (printf_data_flag == true)
		{
			printf("client_sockfd:%d 时间修改为:%d\n", clientfd, heartbeat_time[i]);
		}		
		data_respond(data, respond_success, clientfd);
	}
}

/*********************************************
*func:		heartbeat_service
*param:		buf
*return		void                                              
*descrp:	回应心跳数据
**********************************************/
void heartbeat_service(unsigned char data[], int clientfd)
{
	if (login_flag[find_client_fd(clientfd)] == true)
	{	
		if (printf_data_flag == true)
		{
			printf("心跳数据\n");
		}	
		heartbeat_count[find_client_fd(clientfd)] = 0;
		data_respond(data, respond_success, clientfd);
	}
}

/*********************************************
*func:		vin_compare
*param:		data
*return		void
*descrp:	车辆识别码比对

*author:	lam
*date:		2019.7.17
**********************************************/
bool vin_compare(unsigned char data[])
{
	uint8_t car_vin_length = 17;
	char car_vin[car_vin_length + 1];	
	//标识码识别
	//截取客户端识别码
	memcpy(car_vin, data + 4, car_vin_length*sizeof(char));
	car_vin[car_vin_length] = 0x00;
	//识别码数据库比较
	int i;
	bool vin_cmp_flag = false;
	for (i = 0; i < vin_database_number; i++)
	{
		if (strcmp(car_vin, car_vin_database[i]) == 0)
		{
			vin_cmp_flag = true;
			printf("比对成功，VIN码为:%s\n", car_vin_database[i]);
			break;
		}
	}
	return(vin_cmp_flag);	
}