#include "SaveAndPrintf_data.h"


/*********************************************
*func:		save_car_data()
*param:		data and 数据起始位 clientfd
*return		int i//返回数据长度
*descrp:	存储整车数据
**********************************************/
int save_car_data(unsigned char data[], int data_start_bit, int clientfd)
{
	int clientfdi = find_client_fd(clientfd);
	int i = 0;
	car_data_save[clientfdi].vehicle_state = data[data_start_bit + (i++)];
	car_data_save[clientfdi].charge_state = data[data_start_bit + (i++)];
	car_data_save[clientfdi].running_mode = data[data_start_bit + (i++)];
	car_data_save[clientfdi].car_speed = (data[data_start_bit + (i)]<<8) + data[data_start_bit + (i+1)];
	i+=2;
	car_data_save[clientfdi].mileage = (data[data_start_bit + (i)]<<24) + (data[data_start_bit + (i+1)]<<16) + (data[data_start_bit + (i+2)]<<8) + data[data_start_bit + (i+3)];
	i+=4;
	car_data_save[clientfdi].total_voltage = (data[data_start_bit + (i)]<<8) + data[data_start_bit + (i+1)];
	i+=2;
	car_data_save[clientfdi].total_current = (data[data_start_bit + (i)]<<8) + data[data_start_bit + (i+1)];
	i+=2;
	car_data_save[clientfdi].SOC = data[data_start_bit + (i++)];
	car_data_save[clientfdi].DC_CD_state = data[data_start_bit + (i++)];
	car_data_save[clientfdi].gear = data[data_start_bit + (i++)];
	car_data_save[clientfdi].insulation_resistance = (data[data_start_bit + (i)]<<8) + data[data_start_bit + (i+1)];
	i+=2;
	car_data_save[clientfdi].reserve = (data[data_start_bit + (i)]<<8) + data[data_start_bit + (i+1)];
	i+=2;
	return (i);
}

/*********************************************
*func:		save_battery_data()
*param:		data and 数据起始位 and clientfd
*return		void
*descrp:	存储燃料电池数据
**********************************************/
int save_battery_data(unsigned char data[], int data_start_bit, int clientfd)
{
	int clientfdi = find_client_fd(clientfd);
	int j;
	int i = 0;
	battery_data_save[clientfdi].battery_voltage = (data[data_start_bit + (i)]<<8) + data[data_start_bit + (i+1)];
	i+=2;
	battery_data_save[clientfdi].battery_current = (data[data_start_bit + (i)]<<8) + data[data_start_bit + (i+1)];
	i+=2;;
	battery_data_save[clientfdi].consumption_rate = (data[data_start_bit + (i)]<<8) + data[data_start_bit + (i+1)];
	i+=2;;
	battery_data_save[clientfdi].temperature_probe_number = (data[data_start_bit + (i)]<<8) + data[data_start_bit + (i+1)];
	i+=2;
	battery_data_save[clientfdi].probe_temperature[battery_data_save[clientfdi].temperature_probe_number];
	for(j=0; j<battery_data_save[clientfdi].temperature_probe_number; j++)
	{
		battery_data_save[clientfdi].probe_temperature[j] = data[data_start_bit + i + j];
	}
	i+= battery_data_save[clientfdi].temperature_probe_number;
	battery_data_save[clientfdi].temperature_max = (data[data_start_bit + (i)]<<8) + data[data_start_bit + (i+1)];
	i+=2;
	battery_data_save[clientfdi].temperature_max_code = data[data_start_bit + (i++)];	
	battery_data_save[clientfdi].H2_concentration_max = (data[data_start_bit + (i)]<<8) + data[data_start_bit + (i+1)];
	i+=2;
	battery_data_save[clientfdi].H2_concentration_max_sensor_code = data[data_start_bit + (i++)];
	battery_data_save[clientfdi].H2_pressure_max = (data[data_start_bit + (i)]<<8) + data[data_start_bit + (i+1)];
	i+=2;
	battery_data_save[clientfdi].H2_pressure_max_sensor_code = data[data_start_bit + (i++)];
	battery_data_save[clientfdi].high_pressure_DC_CD_state = data[data_start_bit + (i++)];
	return (i);
}

/*********************************************
*func:		save_extremum_data()
*param:		data and 数据起始位 clientfd
*return		void
*descrp:	存储极值数据	
**********************************************/
int save_extremum_data(unsigned char data[], int data_start_bit, int clientfd)
{
	int clientfdi = find_client_fd(clientfd);
	int i = 0;
	extremum_data_save[clientfdi].voltage_max_subsystem_num = data[data_start_bit + (i++)];
	extremum_data_save[clientfdi].voltage_max_single_num = data[data_start_bit + (i++)];
	extremum_data_save[clientfdi].voltage_max = (data[data_start_bit + (i)]<<8) + data[data_start_bit + (i+1)];
	i+=2;
	extremum_data_save[clientfdi].voltage_min_subsystem_num = data[data_start_bit + (i++)];
	extremum_data_save[clientfdi].voltage_min_single_num = data[data_start_bit + (i++)];
	extremum_data_save[clientfdi].voltage_min = (data[data_start_bit + (i)]<<8) + data[data_start_bit + (i+1)];
	i+=2;
	extremum_data_save[clientfdi].temperature_max_subsystem_num = data[data_start_bit + (i++)];
	extremum_data_save[clientfdi].temperature_max_probe_num = data[data_start_bit + (i++)];
	extremum_data_save[clientfdi].temperature_max = data[data_start_bit + (i++)];
	extremum_data_save[clientfdi].temperature_min_subsystem_num = data[data_start_bit + (i++)];
	extremum_data_save[clientfdi].temperature_min_probe_num = data[data_start_bit + (i++)];
	extremum_data_save[clientfdi].temperature_min = data[data_start_bit + (i++)];
	return (i);
}

/*********************************************
*func:		save_alarm_data()
*param:		data and 数据起始位 clientfd
*return		void
*descrp:	存储alarm数据
**********************************************/
int save_alarm_data(unsigned char data[], int data_start_bit, int clientfd)
{
	int clientfdi = find_client_fd(clientfd);
	int i = 0, j = 0;
	alarm_data_save[clientfdi].alarm_level_max = data[data_start_bit + (i++)];
	alarm_data_save[clientfdi].warning_mark = (data[data_start_bit + (i)]<<24) + (data[data_start_bit + (i+1)]<<16) + (data[data_start_bit + (i+2)]<<8) + data[data_start_bit + (i+3)];
	i+=4;
	alarm_data_save[clientfdi].energy_storage_fault_num = data[data_start_bit + (i++)];
	for(j=0; j<alarm_data_save[clientfdi].energy_storage_fault_num; j++)
	{
		alarm_data_save[clientfdi].energy_storage_fault_code[j] = (data[data_start_bit + (i)]<<24) + (data[data_start_bit + (i+1)]<<16) + (data[data_start_bit + (i+2)]<<8) + data[data_start_bit + (i+3)];
		i+=4;
	}
	alarm_data_save[clientfdi].motor_fault_num = data[data_start_bit + (i++)];
	for(j=0; j<alarm_data_save[clientfdi].motor_fault_num; j++)
	{
		alarm_data_save[clientfdi].motor_fault_code[j] = (data[data_start_bit + (i)]<<24) + (data[data_start_bit + (i+1)]<<16) + (data[data_start_bit + (i+2)]<<8) + data[data_start_bit + (i+3)];
		i+=4;
	}
	alarm_data_save[clientfdi].engine_fault_num = data[data_start_bit + (i++)];
	for(j=0; j<alarm_data_save[clientfdi].engine_fault_num; j++)
	{
		alarm_data_save[clientfdi].engine_fault_code[j] = (data[data_start_bit + (i)]<<24) + (data[data_start_bit + (i+1)]<<16) + (data[data_start_bit + (i+2)]<<8) + data[data_start_bit + (i+3)];
		i+=4;
	}
	alarm_data_save[clientfdi].other_fault_num = data[data_start_bit + (i++)];
	for(j=0; j<alarm_data_save[clientfdi].motor_fault_num; j++)
	{
		alarm_data_save[clientfdi].other_fault_code[j] = (data[data_start_bit + (i)]<<24) + (data[data_start_bit + (i+1)]<<16) + (data[data_start_bit + (i+2)]<<8) + data[data_start_bit + (i+3)];
		i+=4;
	}
	return (i);
}

/*********************************************
*func:		printf_time
*param:		data
*return		void
*descrp:	打印数据上报时间
**********************************************/
void printf_time(unsigned char data[])
{
	int i = 0;
	printf("采集时间：20%d-", data[24+(i++)]);
	printf("%02d-", data[24+(i++)]);
	printf("%02d", data[24+(i++)]);
	printf(" %02d:", data[24+(i++)]);
	printf("%02d:", data[24+(i++)]);
	printf("%02d\n", data[24+(i++)]);
}

/*********************************************
*func:		printf_car_data
*param:		car_data//存储的整车数据结构
*return		void
*descrp:	解析打印整车数据

*author:	lam
*date:		2019.7.20
*ver:		v1.0.0
*change:	
**********************************************/
void printf_car_data(int clientfd)
{
	int clientfdi = find_client_fd(clientfd);
	printf("整车数据...............................\n");
	printf("车辆状态:");
	switch(car_data_save[clientfdi].vehicle_state)
	{
		case(0x01):printf("启动\n");;break;

		case(0x02):printf("熄火\n");break;

		case(0x03):printf("其他状态\n");break;

		case(0xfe):printf("异常\n");break;

		case(0xff):printf("无效\n");break;

		default:{
					printf("未知");
				}
	}
	printf("充电状态:");
	switch(car_data_save[clientfdi].charge_state)
	{
		case(0x01):printf("停车充电\n");;break;

		case(0x02):printf("行驶充电\n");break;

		case(0x03):printf("未充电\n");break;

		case(0x04):printf("充电完成\n");break;

		case(0xfe):printf("异常\n");break;

		case(0xff):printf("无效\n");break;

		default:{
					printf("未知");
				}
	}
	printf("运行模式:");
	switch(car_data_save[clientfdi].running_mode)
	{
		case(0x01):printf("纯电\n");;break;

		case(0x02):printf("混动\n");break;

		case(0x03):printf("燃油\n");break;

		case(0xfe):printf("异常\n");break;

		case(0xff):printf("无效\n");break;

		default:{
					printf("未知");
				}
	}
	printf("车速:");
	switch(car_data_save[clientfdi].car_speed)
	{
		case(0xfffe):printf("异常\n");break;

		case(0xffff):printf("无效\n");break;

		default:{
					printf("%gkm/h\n", (double)(car_data_save[clientfdi].car_speed/10));
				}
	}
	printf("累计里程:");
	switch(car_data_save[clientfdi].mileage)
	{
		case(0xfffffffe):printf("异常\n");break;

		case(0xffffffff):printf("无效\n");break;

		default:{
					printf("%gkm\n", (double)(car_data_save[clientfdi].mileage/10));
				}
	}
	printf("总电压:");
	switch(car_data_save[clientfdi].total_voltage)
	{
		case(0xfffe):printf("异常\n");break;

		case(0xffff):printf("无效\n");break;

		default:{
					printf("%gV\n", (double)(car_data_save[clientfdi].total_voltage/10));
				}
	}
	printf("总电流:");
	switch(car_data_save[clientfdi].total_current)
	{
		case(0xfffe):printf("异常\n");break;

		case(0xffff):printf("无效\n");break;

		default:{
					printf("%gA\n", (double)(car_data_save[clientfdi].total_current/10 - 1000));
				}
	}
	printf("SOC:");
	switch(car_data_save[clientfdi].SOC)
	{
		case(0xfe):printf("异常\n");break;

		case(0xff):printf("无效\n");break;

		default:{
					printf("%%%d\n", car_data_save[clientfdi].SOC);
				}
	}
	printf("DC-CD状态:");
	switch(car_data_save[clientfdi].DC_CD_state)
	{
		case(0x01):printf("工作\n");break;

		case(0x02):printf("断开\n");break;

		case(0xfe):printf("异常\n");break;

		case(0xff):printf("无效\n");break;

		default:{
					printf("未知\n");
				}
	}
	printf("档位:");
	switch(car_data_save[clientfdi].gear & 0x30)
	{
		case(0x00):printf("无驱动力和制动力");break;

		case(0x01):printf("无驱动力有制动力");break;

		case(0x02):printf("有驱动力无制动力");break;

		case(0x03):printf("无驱动力和制动力");break;

		default:{
					printf("未知");
				}
	}
	char gear_new = car_data_save[clientfdi].gear & 0x0f;
	if(gear_new < 0x0d)
	{
		printf(" %d档\n", gear_new);
	}
	else
	{
		switch(gear_new)
		{
			case(0x0d):printf(" 倒档\n");break;

			case(0x0e):printf(" D档\n");break;

			case(0x0f):printf(" P档\n");break;
		}
	}
	printf("绝缘电阻:%d欧姆\n", car_data_save[clientfdi].insulation_resistance);
}

/*********************************************
*func:		printf_batttery_data
*param:		clientfd
*return		void
*descrp:	解析打印燃料电池数据

*author:	lam
*date:		2019.8.3
**********************************************/
void printf_battery_data(int clientfd)
{
	int clientfdi = find_client_fd(clientfd);
	printf("燃料电池数据...............................\n");
	printf("燃料电池电压:");
	switch(battery_data_save[clientfdi].battery_voltage)
	{
		case(0xfffe):printf("异常\n");break;

		case(0xffff):printf("无效\n");break;

		default:{
					printf("%gV\n", (double)(battery_data_save[clientfdi].battery_voltage/10));
				}
	}
	printf("燃料电池电流:");
	switch(battery_data_save[clientfdi].battery_current)
	{
		case(0xfffe):printf("异常\n");break;

		case(0xffff):printf("无效\n");break;

		default:{
					printf("%gA\n", (double)(battery_data_save[clientfdi].battery_current/10));
				}
	}
	printf("燃料消耗率:");
	switch(battery_data_save[clientfdi].consumption_rate)
	{
		case(0xfffe):printf("异常\n");break;

		case(0xffff):printf("无效\n");break;

		default:{
					printf("%gkg/100km\n", (double)(battery_data_save[clientfdi].battery_current/100));
				}
	}
	printf("温度探针总数:");
	switch(battery_data_save[clientfdi].temperature_probe_number)
	{
		case(0xfffe):printf("异常\n");break;

		case(0xffff):printf("无效\n");break;

		default:{
					printf("%d个\n", battery_data_save[clientfdi].temperature_probe_number);
					printf("温度值如下:\n");
					int i;
					for(i=0; i<battery_data_save[clientfdi].temperature_probe_number; i++)
					{
						printf("%d号探针:%d℃\n", i, battery_data_save[clientfdi].probe_temperature[i] - 40);
					}					
				}
	}
	printf("氢系统最高温度:");
	switch(battery_data_save[clientfdi].temperature_max)
	{
		case(0xfffe):printf("异常\n");break;

		case(0xffff):printf("无效\n");break;

		default:{
					printf("%g℃\n", (double)(battery_data_save[clientfdi].temperature_max/10 - 40));
				}
	}
	printf("最高温度探针代号:");
	switch(battery_data_save[clientfdi].temperature_max_code)
	{
		case(0xfe):printf("异常\n");break;

		case(0xff):printf("无效\n");break;

		default:{
					printf("%d\n", battery_data_save[clientfdi].temperature_max_code);
				}
	}
	printf("氢气最高浓度:");
	switch(battery_data_save[clientfdi].H2_concentration_max)
	{
		case(0xfffe):printf("异常\n");break;

		case(0xffff):printf("无效\n");break;

		default:{
					printf("%dmg/kg\n", 5*battery_data_save[clientfdi].H2_concentration_max/6);
				}
	}
	printf("氢气最高浓度传感器代号:");
	switch(battery_data_save[clientfdi].H2_concentration_max_sensor_code)
	{
		case(0xfe):printf("异常\n");break;

		case(0xff):printf("无效\n");break;

		default:{
					printf("%d\n", battery_data_save[clientfdi].H2_concentration_max_sensor_code);
				}
	}
	printf("氢气最高压力:");
	switch(battery_data_save[clientfdi].H2_pressure_max)
	{
		case(0xfffe):printf("异常\n");break;

		case(0xffff):printf("无效\n");break;

		default:{
					printf("%gMPa\n", (double)(battery_data_save[clientfdi].battery_current/10));
				}
	}
	printf("氢气最高压力传感器代号:");
	switch(battery_data_save[clientfdi].H2_concentration_max_sensor_code)
	{
		case(0xfe):printf("异常\n");break;

		case(0xff):printf("无效\n");break;

		default:{
					printf("%d\n", battery_data_save[clientfdi].H2_pressure_max_sensor_code);
				}
	}
	printf("高压DC/DC状态:");
	switch(battery_data_save[clientfdi].high_pressure_DC_CD_state)
	{
		case(0x01):printf("工作\n");break;

		case(0x02):printf("断开\n");break;

		case(0xfe):printf("异常\n");break;

		case(0xff):printf("无效\n");break;

		default:{
					printf("未知\n");
				}
	}

}

/*********************************************
*func:		printf_extremum_data
*param:		clientfd
*return		void
*descrp:	解析打印极值数据

*author:	lam
*date:		2019.8.3
**********************************************/
void printf_extremum_data(int clientfd)
{
	int clientfdi = find_client_fd(clientfd);
	printf("极值数据...............................\n");
	printf("最高电压电池子系统号:");
	switch(extremum_data_save[clientfdi].voltage_max_subsystem_num)
	{
		case(0xfe):printf("异常\n");break;

		case(0xff):printf("无效\n");break;

		default:{
					printf("%d\n", extremum_data_save[clientfdi].voltage_max_subsystem_num);
				}
	}
	printf("最高电压电池单体代号:");
	switch(extremum_data_save[clientfdi].voltage_max_single_num)
	{
		case(0xfe):printf("异常\n");break;

		case(0xff):printf("无效\n");break;

		default:{
					printf("%d\n", extremum_data_save[clientfdi].voltage_max_single_num);
				}
	}
	printf("最高电池单体电压值:");
	switch(extremum_data_save[clientfdi].voltage_max)
	{
		case(0xfffe):printf("异常\n");break;

		case(0xffff):printf("无效\n");break;

		default:{
					printf("%gV\n", (double)(extremum_data_save[clientfdi].voltage_max/1000));
				}
	}
	printf("最低电压电池子系统号:");
	switch(extremum_data_save[clientfdi].voltage_min_subsystem_num)
	{
		case(0xfe):printf("异常\n");break;

		case(0xff):printf("无效\n");break;

		default:{
					printf("%d\n", extremum_data_save[clientfdi].voltage_min_subsystem_num);
				}
	}
	printf("最低电压电池单体代号:");
	switch(extremum_data_save[clientfdi].voltage_min_single_num)
	{
		case(0xfe):printf("异常\n");break;

		case(0xff):printf("无效\n");break;

		default:{
					printf("%d\n", extremum_data_save[clientfdi].voltage_min_single_num);
				}
	}
	printf("最低电池单体电压值:");
	switch(extremum_data_save[clientfdi].voltage_max)
	{
		case(0xfffe):printf("异常\n");break;

		case(0xffff):printf("无效\n");break;

		default:{
					printf("%gV\n", (double)(extremum_data_save[clientfdi].voltage_min/1000));
				}
	}
	printf("最高温度子系统号:");
	switch(extremum_data_save[clientfdi].temperature_max_subsystem_num)
	{
		case(0xfe):printf("异常\n");break;

		case(0xff):printf("无效\n");break;

		default:{
					printf("%d\n", extremum_data_save[clientfdi].temperature_max_subsystem_num);
				}
	}
	printf("最高温度探针序号:");
	switch(extremum_data_save[clientfdi].temperature_max_probe_num)
	{
		case(0xfe):printf("异常\n");break;

		case(0xff):printf("无效\n");break;

		default:{
					printf("%d\n", extremum_data_save[clientfdi].temperature_max_probe_num);
				}
	}
	printf("最高温度值:");
	switch(extremum_data_save[clientfdi].temperature_max)
	{
		case(0xfe):printf("异常\n");break;

		case(0xff):printf("无效\n");break;

		default:{
					printf("%d℃\n", extremum_data_save[clientfdi].temperature_max - 40);
				}
	}
	printf("最低温度子系统号:");
	switch(extremum_data_save[clientfdi].temperature_min_subsystem_num)
	{
		case(0xfe):printf("异常\n");break;

		case(0xff):printf("无效\n");break;

		default:{
					printf("%d\n", extremum_data_save[clientfdi].temperature_min_subsystem_num);
				}
	}
	printf("最低温度探针序号:");
	switch(extremum_data_save[clientfdi].temperature_min_probe_num)
	{
		case(0xfe):printf("异常\n");break;

		case(0xff):printf("无效\n");break;

		default:{
					printf("%d\n", extremum_data_save[clientfdi].temperature_min_probe_num);
				}
	}
	printf("最低温度值:");
	switch(extremum_data_save[clientfdi].temperature_min)
	{
		case(0xfe):printf("异常\n");break;

		case(0xff):printf("无效\n");break;

		default:{
					printf("%d℃\n", extremum_data_save[clientfdi].temperature_min - 40);
				}
	}
}

void printf_alarm_data(int clientfd)
{
	int clientfdi = find_client_fd(clientfd);
	int i;
	printf("报警数据...............................\n");
	printf("最高报警等级:");
	printf("%d\n", alarm_data_save[clientfdi].alarm_level_max);
	printf("报警标志:");
	printf("%x\n", alarm_data_save[clientfdi].warning_mark);
	printf("可充电电子储能装置故障数:");
	printf("%d\n", alarm_data_save[clientfdi].energy_storage_fault_num);
	printf("可充电电子储能装置故障代码列表如下:\n");
	for(i=0; i<alarm_data_save[clientfdi].engine_fault_num; i++)
	{
		printf("%d号故障代码:%x\n", i, alarm_data_save[clientfdi].engine_fault_code[i]);
	}		
	printf("驱动电机故障数:");
	printf("%d\n", alarm_data_save[clientfdi].energy_storage_fault_num);
	printf("驱动电机故障代码列表如下:\n");
	for(i=0; i<alarm_data_save[clientfdi].engine_fault_num; i++)
	{
		printf("%d号故障代码:%x\n", i, alarm_data_save[clientfdi].engine_fault_code[i]);
	}
	printf("发动机故障数:");
	printf("%d\n", alarm_data_save[clientfdi].motor_fault_num);
	printf("发动机故障代码列表如下:\n");
	for(i=0; i<alarm_data_save[clientfdi].motor_fault_num; i++)
	{
		printf("%d号故障代码:%x\n", i, alarm_data_save[clientfdi].motor_fault_code[i]);
	}
	printf("其他故障数:");
	printf("%d\n", alarm_data_save[clientfdi].other_fault_num);
	printf("其他故障代码列表如下:\n");
	for(i=0; i < alarm_data_save[clientfdi].other_fault_num; i++)
	{
		printf("%d号故障代码:%x\n", i, alarm_data_save[clientfdi].other_fault_code[i]);
	}		
}

void printf_param(unsigned char data[])
{
	int param_num = data[30];
	uint8_t param_id_bit = 31;
	int management_platform_domain_name_length;
	int common_platform_domain_name_length;
	char management_platform_domain_name[256] = {0};;
	char common_platform_domain_name[256] = {0};
	char hardware_version[5] = {0};
	char firmware_version[5] = {0};
	for (int i = 0; i < param_num; ++i)
	{
		switch (data[param_id_bit])
		{
			case 0x01:	printf("车载终端本地存储周期:%dms\n", (data[param_id_bit + 1]<<8) + data[param_id_bit + 2]);
						param_id_bit += 3;break;
			case 0x02:	printf("信息上报时间周期:%ds\n", (data[param_id_bit + 1]<<8) + data[param_id_bit + 2]);
						param_id_bit += 3;break;
			case 0x03:	printf("报警时信息上报时间周期:%dms\n", (data[param_id_bit + 1]<<8) + data[param_id_bit + 2]);
						param_id_bit += 3;break;		

			case 0x04:	management_platform_domain_name_length = data[param_id_bit + 1];
						printf("远程服务与管理平台域名长度:%d\n", management_platform_domain_name_length);
						param_id_bit += 2;break;
			case 0x05:	memcpy(management_platform_domain_name, data + param_id_bit + 1, management_platform_domain_name_length);
						printf("远程服务与管理平台域名:%s\n", management_platform_domain_name);
						param_id_bit += management_platform_domain_name_length + 1;break;
			case 0x06:	printf("远程服务与管理平台端口:%x\n", (data[param_id_bit + 1]<<8) + data[param_id_bit + 2]);
						param_id_bit += 3;break;

			case 0x07:	memcpy(hardware_version, data + param_id_bit + 1, 5*sizeof(char));
						printf("硬件版本:%s\n", hardware_version);
						param_id_bit += 6;break;
			case 0x08:	memcpy(firmware_version, data + param_id_bit + 1, 5*sizeof(char));
						printf("固件版本:%s\n", firmware_version);
						param_id_bit += 6;break;
			case 0x09:	printf("车载终端心跳发送周期:%ds\n", data[param_id_bit + 1]);
						param_id_bit += 2;break;
			case 0x0a:	printf("终端应答超时时间:%ds\n", (data[param_id_bit + 1]<<8) + data[param_id_bit + 2]);
						param_id_bit += 3;break;
			case 0x0b:	printf("平台应答超时时间:%ds\n", (data[param_id_bit + 1]<<8) + data[param_id_bit + 2]);
						param_id_bit += 3;break;
			case 0x0c:	printf("登入间隔时间:%ds\n", data[param_id_bit + 1]);
						param_id_bit += 2;break;
			case 0x0d:	common_platform_domain_name_length = data[param_id_bit + 1];
						printf("公共平台域名长度:%d\n", common_platform_domain_name_length);
						param_id_bit += 2;break;						
			case 0x0e:	memcpy(common_platform_domain_name, data + param_id_bit + 1, common_platform_domain_name_length);
						printf("公共平台域名:%s\n", common_platform_domain_name);
						param_id_bit += common_platform_domain_name_length + 1;break;
			case 0x0f:	printf("公共平台端口:%x\n", (data[param_id_bit + 1]<<8) + data[param_id_bit + 2]);
						param_id_bit += 3;break;
			case 0x10:	printf("抽样监测:%x\n", data[param_id_bit + 1]);
						param_id_bit += 2;break;
			default:i = param_num;printf("wrong!!!!!!!\n");;break;
		}
	}
	
}

