#ifndef _PARSE_DATA_H_
#define _PARSE_DATA_H_

#include "SaveAndPrintf_data.h"
#include "log.h"
#include <stdio.h>
#include <unistd.h>
#include <cstdlib>

unsigned char command_check(unsigned char data[]);
void command_check_service(int clientfd, unsigned char data[]);
void login_service(unsigned char data[], int clientfd);
void time_service(unsigned char data[], int clientfd);
void data_service(unsigned char data[], int clientfd);
void heartbeat_service(unsigned char data[], int clientfd);
void logout_service(unsigned char data[], int clientfd);
void modify_heartbeat_time(unsigned char data[], int clientfd);
void respond_param_query_service(unsigned char data[]);
void respond_param_set_service(unsigned char data[]);
void respond_remote_upgrade_service(unsigned char data[], int clientfd);
void command_recv_log_service(unsigned char data[], int clientfd);
bool vin_compare(unsigned char data[]);

void parse_data(unsigned char data[], int clientfd);
int car_data_parse(unsigned char data[], int data_start_bit, int clientfd);
int battery_data_parse(unsigned char data[], int data_start_bit, int clientfd);
int extremum_data_parse(unsigned char data[], int data_start_bit, int clientfd);
int alarm_data_parse(unsigned char data[], int data_start_bit, int clientfd);

void data_respond(unsigned char data[], unsigned char respond_name, int clientfd);

#endif