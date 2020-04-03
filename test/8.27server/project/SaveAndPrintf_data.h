/*********************解析数据（存储和打印函数）**************************/
#ifndef _SAVEANDPRINTF_DATA_H_
#define _SAVEANDPRINTF_DATA_H_

#include "global.h"
#include "clientfd.h"
#include <string.h>
#include <stdio.h>

int save_car_data(unsigned char data[], int data_start_bit, int clientfd);
int save_battery_data(unsigned char data[], int data_start_bit, int clientfd);
int save_extremum_data(unsigned char data[], int data_start_bit, int clientfd);
int save_alarm_data(unsigned char data[], int data_start_bit, int clientfd);

void printf_time(unsigned char data[]);

void printf_car_data(int clientfd);
void printf_battery_data(int clientfd);
void printf_alarm_data(int clientfd);
void printf_extremum_data(int clientfd);

void printf_param(unsigned char data[]);

#endif