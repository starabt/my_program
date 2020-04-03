#include "global.h"

int clientfds[clientfds_max] = {0};

//上报数据存储变量
data_car car_data_save[clientfds_max];
data_battery battery_data_save[clientfds_max];
data_extremum extremum_data_save[clientfds_max];
data_alarm alarm_data_save[clientfds_max];

bool login_flag[clientfds_max] = {0};//登录成功标示位
bool printf_data_flag = true;
const char *car_vin_database[17]={"15767131226000000","123456789ABCDEFG","01234567891234567","LFV2A2156C3333333"};//车辆识别码
int server_sockfd;
int upgrade_sockfd;
uint8_t heartbeat_count[clientfds_max] = {0};
int heartbeat_time[clientfds_max];
const char *IP = "192.168.12.240";
short PORT = 10222;
short UPGRADE_PORT = 10024;
pthread_mutex_t mutex;// 定义互斥锁，全局变量
Buffer clients_data_buffer[clientfds_max];
bool upgrade_flag = false;
FILE *LogFile;
bool modify_heartbeat_time_flag = false;

int getPortAndIP(int testSocket, char IP[])
{
	char *IP_str;
	sockaddr_in clientaddr;
	uint nlen = (uint)sizeof(clientaddr);
	getpeername(testSocket, (sockaddr*)&clientaddr, &nlen);
	int port= ntohs(clientaddr.sin_port);
    IP_str = inet_ntoa(clientaddr.sin_addr);
   	memcpy(IP, IP_str, strlen(IP_str));
	return port;
}

/*bool getIP(int testSocket, char *IP)
{
	sockaddr_in sockAddr;
	uint nlen = (uint)sizeof(sockAddr);
	if (getsockname(testSocket, (sockaddr*)&sockAddr, &nlen) == -1)
	{
		IP = NULL;
		return false;
	}
	else
	{
		IP = inet_ntoa(sockAddr.sin_addr);
		return true;
	}
	
}*/