#include "log.h"

void data_log(int clientfd, unsigned char data[])
{
	// printf("存储日志中...\n");
	int data_length = (data[22]<<8) + data[23] + 25;
	unsigned char data_type[25] = {0};
	char IP_name[15] = {0};
	int PORT_name = getPortAndIP(clientfd, IP_name);
	data_type_check(data_type, data);
	TIME timenow;
	int i = 0;
	timenow.tm_year = data[24+(i++)];
	timenow.tm_mon = data[24+(i++)];
	timenow.tm_mday = data[24+(i++)];
	timenow.tm_hour = data[24+(i++)];
	timenow.tm_min = data[24+(i++)];
	timenow.tm_sec = data[24+(i++)];
	select_datalog_file(timenow);
	FILE *LogFile = fopen("../log/datalog/today.log", "a+");
	fprintf(LogFile, "%s:%04d-%02d-%02d %02d:%02d:%02d\n", "recv_time", timenow.tm_year + 2000, timenow.tm_mon, timenow.tm_mday, timenow.tm_hour, timenow.tm_min, timenow.tm_sec);
	fprintf(LogFile, "%s:%s %s:%d\n", "IP", IP_name, "PORT", PORT_name);
	fprintf(LogFile, "%s:%s\n", "data_type", data_type);
	for (int i = 0; i < data_length; ++i)
	{
		fprintf(LogFile, "%02x", data[i]);
	}
	fprintf(LogFile, "\n\n");	
	fclose(LogFile);
	// printf("日志存储完成!\n");
}

void work_log(int clientfd, const char *format, ...)
{
	char IP_name[15] = {0};
	int PORT_name = getPortAndIP(clientfd, IP_name);
	// sleep(2);
	va_list arg;
	va_start(arg, format);
	select_worklog_file();
	FILE *LogFile = fopen("../log/worklog/today.log", "a+");
	fprintf(LogFile, "%s:%s %s:%d\n", "IP", IP_name, "PORT", PORT_name);
	fprintf(LogFile, "%s", "STATUS:");
	vfprintf(LogFile, format, arg);
	fclose(LogFile);
	va_end(arg);
}

void err_log(const char *format, ...)
{
	va_list arg;
	va_start(arg, format);
	select_errorlog_file();
	FILE *LogFile = fopen("../log/errorlog/today.log", "a+");
	vfprintf(LogFile, format, arg);
	fclose(LogFile);
	va_end(arg);
}

void select_worklog_file()
{
	FILE *LogFile;
	LogFile = fopen("../log/worklog/today.log", "a+");
	//get current time
	time_t current_time;
	time(&current_time);
	struct tm current_time_tm;
	localtime_r(&current_time, &current_time_tm);
	//get the last time when file was wrote
	struct stat stat_buf;
	stat("../log/worklog/today.log", &stat_buf);
	struct tm file_tm ;
	localtime_r(&stat_buf.st_mtime, &file_tm);
	if (current_time_tm.tm_year != file_tm.tm_year || current_time_tm.tm_mon != file_tm.tm_mon || current_time_tm.tm_mday != file_tm.tm_mday || current_time_tm.tm_min != file_tm.tm_min)
	{
		rename("../log/worklog/fivedaysago.log", "../log/worklog/sixdaysago.log");
		rename("../log/worklog/fourdaysago.log", "../log/worklog/fivedaysago.log");
		rename("../log/worklog/threedaysago.log", "../log/worklog/fourdaysago.log");
		rename("../log/worklog/twodaysago.log", "../log/worklog/threedaysago.log");
		rename("../log/worklog/onedayago.log", "../log/worklog/twodaysago.log");
		rename("../log/errorlog/today.log", "../log/datalog/onedayago.log");
	}
	fprintf(LogFile, "time:%04d-%02d-%02d %02d:%02d:%02d\n", current_time_tm.tm_year + 1900, current_time_tm.tm_mon, current_time_tm.tm_mday, current_time_tm.tm_hour, current_time_tm.tm_min, current_time_tm.tm_sec);
	fclose(LogFile);
}

void select_errorlog_file()
{
	FILE *LogFile;
	LogFile = fopen("../log/errorlog/today.log", "a+");
	//get current time
	time_t current_time;
	time(&current_time);
	struct tm current_time_tm;
	localtime_r(&current_time, &current_time_tm);
	//get the last time when file was wrote
	struct stat stat_buf;
	stat("../log/errorlog/today.log", &stat_buf);
	struct tm file_tm ;
	localtime_r(&stat_buf.st_mtime, &file_tm);
	if (current_time_tm.tm_year != file_tm.tm_year || current_time_tm.tm_mon != file_tm.tm_mon || current_time_tm.tm_mday != file_tm.tm_mday || current_time_tm.tm_min != file_tm.tm_min)
	{
		rename("../log/errorlog/fivedaysago.log", "../log/errorlog/sixdaysago.log");
		rename("../log/errorlog/fourdaysago.log", "../log/errorlog/fivedaysago.log");
		rename("../log/errorlog/threedaysago.log", "../log/errorlog/fourdaysago.log");
		rename("../log/errorlog/twodaysago.log", "../log/errorlog/threedaysago.log");
		rename("../log/errorlog/onedayago.log", "../log/errorlog/twodaysago.log");
		rename("../log/errorlog/today.log", "../log/datalog/onedayago.log");
	}
	fprintf(LogFile, "[%04d-%02d-%02d %02d:%02d:%02d]", current_time_tm.tm_year + 1900, current_time_tm.tm_mon, current_time_tm.tm_mday, current_time_tm.tm_hour, current_time_tm.tm_min, current_time_tm.tm_sec);
	fclose(LogFile);
}

void select_datalog_file(TIME timenow)
{
	FILE *LogFile;
	LogFile = fopen("../log/datalog/today.log", "a+");
	struct stat stat_buf;
	stat("../log/datalog/today.log", &stat_buf);
	struct tm*lt;
	lt = localtime(&stat_buf.st_mtime);
	if (lt->tm_year - 100 != timenow.tm_year || lt->tm_mon + 1 != timenow.tm_mon || lt->tm_mday != timenow.tm_mday || lt->tm_min != timenow.tm_min)
	{
		rename("../log/datalog/fivedaysago.log", "../log/datalog/sixdaysago.log");
		rename("../log/datalog/fourdaysago.log", "../log/datalog/fivedaysago.log");
		rename("../log/datalog/threedaysago.log", "../log/datalog/fourdaysago.log");
		rename("../log/datalog/twodaysago.log", "../log/datalog/threedaysago.log");
		rename("../log/datalog/onedayago.log", "../log/datalog/twodaysago.log");
		rename("../log/datalog/today.log", "../log/datalog/onedayago.log");
	}
	fclose(LogFile);
}

void data_type_check(unsigned char data_type[],unsigned char data[])
{
	switch(data[2])
	{
		case command_login:memcpy(data_type, "login", 5);break;
		case command_logout:memcpy(data_type, "logout", 6);break;
		// case command_time:memcpy(data_type, "time_modify", 11);break;
		case command_resended_data:memcpy(data_type, "resended_data", 13);break;
		case command_data:memcpy(data_type, "data", 4);break;
		// case command_heartbeat:memcpy(data_type, "heatbeat", 8);break;
		case command_modify_heartbeat_time:memcpy(data_type, "heatbeat_time_modify", 20);break;
		case respond_param_query:memcpy(data_type, "respond_param_query", 19);break;
		case respond_param_set:memcpy(data_type, "respond_param_set", 17);break;
		case respond_remote_upgrade:memcpy(data_type, "respond_remote_upgrade", 22);break;
	}
}



/*void search_log()
{
	unsigned char data[8*1024];
	FILE *LogFile = fopen("Data.log", "r+");
	printf("enter search_log\n");
	for (int i = 0; i < 50; i++)
	{
		memset(data, 0, 8*1024);
		if (read_one_data_from_file(data, LogFile) < 0)
		{
			printf("break\n");
			break;
		}
		printf_time(data);
	}
	fclose(LogFile);
	printf("end search_log\n");
	size = fread(buffer, sizeof(char), 100, LogFile);
	offset = lseek(fileno(stream), 0, SEEK_CUR);

}

int read_one_data_from_file(unsigned char data[], FILE *file)
{	
	int len_add;
	ssize_t size = read(fileno(file), data, 24);
	if (size <= 0)
	{
		return -1;
	}
	if((len_add = get_len(data)) == -1)
	{
		printf("return\n");
		return -1;
	}
	size = read(fileno(file), data+24, len_add+2);
	if (size <= 0)
	{
		return -1;
	}
	return 0;
}

int get_len(unsigned char data[])
{
	int len = (data[22]<<8) + data[23];
	if (len < 8*1024 - 25 && len > 0)
	{
		return(len);
	}
	else
	{
		return(-1);
	}
}*/