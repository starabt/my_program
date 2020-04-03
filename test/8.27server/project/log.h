#ifndef _LOG_H_
#define _LOG_H_

#include "global.h"
#include <unistd.h>
#include "SaveAndPrintf_data.h"

typedef struct TIME
{
	int tm_year;
	int tm_mon;
	int tm_mday;
	int tm_hour;
	int tm_min;
	int tm_sec;
}TIME;

void data_log(int clientfd, unsigned char data[]);
void err_log(const char *format, ...);
void work_log(int clientfd,const char *format, ...);
void data_type_check(unsigned char data_type[],unsigned char data[]);
void select_datalog_file(TIME timenow);
void select_errorlog_file();
void select_worklog_file();
/*void search_log();
int get_len(unsigned char data[]);
int read_one_data_from_file(unsigned char data[], FILE *flie);*/

#endif