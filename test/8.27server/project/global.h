#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <resolv.h>
#include <time.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <errno.h>
#include "buffer.h"

//命令标识
#define command_login 0x01
#define command_logout 0x04
#define command_data 0x02
#define command_resended_data 0x03
#define command_time 0x08
#define command_heartbeat 0x07
#define command_modify_heartbeat_time 0x09
#define command_recv_log 0x10
#define respond_param_query 0x80
#define respond_param_set 0x81
#define respond_remote_upgrade 0x82
//应答标识
#define respond_success 0x01
#define respond_fail 0x02
#define respond_vin_repeat 0x03
#define respond_command 0xfe

#define car_data 0x01
#define motor_data 0x02
#define battery_data 0x03
#define engine_data 0x04
#define car_location_data 0x05
#define extremum_data 0x06
#define alarm_data 0x07

#define BUFFER_SIZE 1024
#define data_buffer_length 10*1024//数据缓冲区长度
#define BACKLOG 5 
#define clientfds_max 50 
#define MAXBUF 1024//最大数据长度
#define vin_database_number 4//vin数据库数量
#define heartbeat_count_max 3
#define data_timeout 3//数据处理超时时间(s)

//整车数据
typedef struct{
	uint8_t vehicle_state;
	uint8_t charge_state;
	uint8_t running_mode;
	uint16_t car_speed;
	uint32_t mileage;
	uint16_t total_voltage;
	uint16_t total_current;
	uint8_t SOC;
	uint8_t DC_CD_state;
	uint8_t gear;
	uint16_t insulation_resistance;
	uint16_t reserve;
}data_car;
//燃料电池
typedef struct{
	uint16_t battery_voltage;
	uint16_t battery_current;
	uint16_t consumption_rate;
	uint16_t temperature_probe_number;
	uint8_t probe_temperature[65536];	
	uint16_t temperature_max;
	uint8_t temperature_max_code;	
	uint16_t H2_concentration_max;
	uint8_t H2_concentration_max_sensor_code;
	uint16_t H2_pressure_max;
	uint8_t H2_pressure_max_sensor_code;
	uint8_t high_pressure_DC_CD_state;
}data_battery;
//极值数据
typedef struct{
	uint8_t voltage_max_subsystem_num;
	uint8_t voltage_max_single_num;
	uint16_t voltage_max;
	uint8_t voltage_min_subsystem_num;
	uint8_t voltage_min_single_num;
	uint16_t voltage_min;
	uint8_t temperature_max_subsystem_num;
	uint8_t temperature_max_probe_num;
	uint8_t temperature_max;
	uint8_t temperature_min_subsystem_num;
	uint8_t temperature_min_probe_num;
	uint8_t temperature_min;
}data_extremum;
//alarm数据
typedef struct{
	uint8_t alarm_level_max;
	uint32_t warning_mark;
	uint8_t energy_storage_fault_num;
	uint32_t energy_storage_fault_code[252];
	uint8_t motor_fault_num;
	uint32_t motor_fault_code[252];
	uint8_t engine_fault_num;
	uint32_t engine_fault_code[252];
	uint8_t other_fault_num;
	uint32_t other_fault_code[252];
}data_alarm;

//上报数据存储变量
extern data_car car_data_save[clientfds_max];
extern data_battery battery_data_save[clientfds_max];
extern data_extremum extremum_data_save[clientfds_max];
extern data_alarm alarm_data_save[clientfds_max];

extern int clientfds[clientfds_max];//客户端的socketfd,50个元素，fds[0]~fds[49]

extern bool login_flag[clientfds_max];//登录成功标示位
extern bool printf_data_flag;
extern const char *car_vin_database[17];//车辆识别码
extern int server_sockfd;
extern int upgrade_sockfd;
extern uint8_t heartbeat_count[clientfds_max];
extern int heartbeat_time[clientfds_max];
extern const char *IP;
extern short PORT;
extern short UPGRADE_PORT;
extern pthread_mutex_t mutex;// 定义互斥锁，全局变量
extern Buffer clients_data_buffer[clientfds_max];
extern bool upgrade_flag;//升级服务启动标志位
extern FILE *LogFile;
extern bool modify_heartbeat_time_flag;

int getPortAndIP(int testSocket, char *IP);
#endif