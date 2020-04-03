#ifndef BUSX_PROTOCOL_GB32960_H
#define BUSX_PROTOCOL_GB32960_H
#define PACK_ALIGN	__attribute__((packed))

#define BUSX_GB32960_MSG_MIN_LEN 25
#define BUSX_GB32960_MSG_MAX_LEN 4096

#define BUSX_GB32960_MAX_FAULTCOUNT 30 //故障最大值
//消息头长度 从“起始字符”到“数据单元长度”
#define BUSX_GB32960_MSG_HEAD_LEN 24

//最大可充电储能子系统个数
#define BUSX_GB32960_MAX_REESS_NUM 2

//单体电压最大分包数量
#define REESS_VOLTAGE_MAX_PACK_NUM 3 //max subpack num

//GB32960协议缩略名
#define BUSX_GB32960_PROTOCOL_SHORT_NAME "GB32960"

//服务器（IP、端口）个数
#define GB32960_SERVER_MAX_NUM	2

//车辆登入数据内容最小长度
#define BUSX_GB32960_REGISTER_DATA_BODY_MIN_LEN 30
//识别码长度 不含\0
#define BUSX_GB32960_IDENTITY_CODE_LEN 17
//车牌长度
#define BUSX_GB32960_BUS_PLATE_LEN 9
//终端厂商代码长度
#define BUSX_GB32960_TERM_MANUFACTURE_CODE_LEN 4

//终端编号长度
#define BUSX_GB32960_TERM_NO_LEN 12
//电池厂商代码长度
#define BUSX_GB32960_BATTERY_MANUFACTURE_CODE_LEN 4
//SIM卡号长度
#define BUSX_GB32960_ICCID_LEN 20
//终端软件版本长度
#define BUSX_GB32960_TERM_SOFTWARE_VER_LEN 10

//车牌匹配成功
#define BUSX_GB32960_REGISTER_COMP_PLATE_SUCCESS 0x08
//终端匹配成功
#define BUSX_GB32960_REGISTER_COMP_TERM_SUCCESS 0x04
//电池匹配成功 
#define BUSX_GB32960_REGISTER_COMP_BATTERY_SUCCESS 0x02
//SIM匹配成功
#define BUSX_GB32960_REGISTER_COMP_SIM_SUCCESS 0x01
//应答注册结果消息长度
#define BUSX_GB32960_REGISTER_REPLY_MSG_LEN 27
//下发配置消息长度
#define BUSX_GB32960_ISSUE_CONFIGURE_MSG_LEN 72
//下发设置终端ip端口消息长度
#define BUSX_GB32960_ISSUE_SET_IP_PORT_MSG_LEN 32
//升级更新启动消息长度
#define BUSX_GB32960_UPGRADE_START_MSG_LEN 50
//校时消息长度
#define BUSX_GB32960_ADJUST_TIME_MSG_LEN 32
//设置实时数据上传周期消息长度
#define BUSX_GB32960_SET_RT_DATA_UPLOAD_CYCLE_MSG_LEN 27
//固件 硬件版本长度
#define BUSX_GB32960_VER_LEN 5
//参数值最大长度 主要针对域名
#define BUSX_GB32960_MAX_PAR_VALUE_LEN 100
//单帧数据最大参数个数
#define BUSX_GB32960_MAX_PAR_COUNT_PER_FRAME 64
//版本GB32960对应整车数据体长度
#define BUSX_GB32960_VEHICLE_DATA_LEN 20
//版本GB32960E单个驱动电机数据长度
#define BUSX_GB32960_ONE_MOTOR_DATA_LEN 12
//版本GB32960对应燃料电池数据最小长度
#define BUSX_GB32960_FUEL_CELL_DATA_MIN_LEN 18
//版本GB32960对应发动机数据体长度
#define BUSX_GB32960_ENGINE_DATA_LEN 5
//版本GB32960对应车辆位置数据体长度
#define BUSX_GB32960_LOCATION_DATA_LEN 9
//版本GB32960对应极值数据体长度
#define BUSX_GB32960_EXTREME_DATA_LEN 14
//版本GB32960对应报警数据体最小长度
#define BUSX_GB32960_ALARM_DATA_MIN_LEN 9

//驱动电机最大个数
#define  BUSX_GB32960_MOTOR_MAX_COUNT 10
//燃料电池温度值最大个数
#define  BUSX_GB32960_FUEL_CELL_MAX_TEMPERTURE_COUNT 100
//可充电储能子系统数
#define BUSX_SUBREESS_MAX_COUNT 20
//可充电储能系统编码最大长度
#define BUSX_REESS_CODE_MAX_LEN 50
//车辆登出数据内容长度
#define BUSX_BUS_LOGOT_BODY_LEN 8
//参数查询应答，参数设置数据内容最小长度
#define BUSX_GB32960_QUERY_PAR_REPLY_BODY_MIN_LEN 7
/*
添加日期：2016-06-20
功能说明：消息错误分类
*/
enum BUSX_GB32960_MsgErrorType
{
	BUSX_GB32960_Msg_OK,   
	BUSX_GB32960_Msg_Head_Mark_Error,  //头标识错误
	BUSX_GB32960_Msg_Parse_Data_Body_Error,   //解析数据体错误
	BUSX_GB32960_Msg_Check_Sum_Error,  //校验和错误
	BUSX_GB32960_Msg_Len_Error,        //消息长度错误
	BUSX_GB32960_MSG_APR_POOL_NO_EXIST  //apr内存池不存在
};

/*
添加日期：2016-06-20
功能说明：命令枚举
*/
enum BUSX_GB32960_CMD
{
	BUSX_GB32960_CMD_Register=0x01,            //终端注册
	BUSX_GB32960_CMD_RT_Data_Upload=0x02,      //实时信息上报
	BUSX_GB32960_CMD_REISSUE_RT_DATA=0x03,         //补发信息上报
	BUSX_GB32960_CMD_LOGOUT=0X04,                 //车辆登出
	BUSX_GB32960_CMD_Heartbeat_Upload=0x07,     //心跳上传
	BUSX_GB32960_CMD_ADJUST_TIME=0X08,           //终端校时
	BUSX_GB32960_CMD_QUERY_PAR=0X80,             //查询命令
	BUSX_GB32960_CMD_SET_PAR=0X81,              //设置命令
	BUSX_GB32960_CMD_Control_Cmd=0x82,          //车载终端控制命令
	BUSX_GB32960_CMD_Upload_Cmd=0x83,			//日志上传命令
	BUSX_GZTDV10_AUTOWAKEUP_DATA_Cmd=0x6F,			//自动唤醒上传数据标识
};
/*
添加日期：2016-06-20
功能说明：命令应答类型
*/
enum BUSX_GB32960_REPLY_CLASSIFY
{
	BUSX_GB32960_REPLY_CLASSIFY_OK=0x01,  //应答标识
	BUSX_GB32960_REPLY_CLASSIFY_ERROR=0X02,  //错误 设置未成功
	BUSX_GB32960_REPLY_CLASSIFY_VIN_Repeat=0x03,  //VIN重复
	BUSX_GB32960_REPLY_CLASSIFY_SEND=0xFE,   //主动发送标识
};

/*
添加日期：2016-06-21
功能说明：命令单元数据体
*/
typedef struct _BUSX_GB32960_CMD_UNIT
{
	UINT8 cmdFlag;    //命令标识 BUSX_GB32960_CMD枚举
	UINT8 replyFlag;  //0xFE主动发起，0x01应答 由BUSX_GB32960_REPLY_CLASSIFY枚举
}PACK_ALIGN BUSX_GB32960_CMD_UNIT;
/*
添加日期：2016-06-20
功能说明：消息数据头结构体
*/
typedef struct _BUSX_GB32960_MSG_HEAD
{
	BUSX_GB32960_CMD_UNIT cmdUint;         //0xFE主动发起，0x01应答
	char  identityCode[BUSX_GB32960_IDENTITY_CODE_LEN+1];
	UINT8 encryFlag;   //加密标识 0x00不加密 0x01 RSA加密
	UINT16 dataBodyLen;  //数据单元长度
}PACK_ALIGN BUSX_GB32960_MSG_HEAD;

/*
添加日期：2016-06-20
功能说明：枚举电池类型
*/
enum BUSX_GB32960_BATTERY_TYPT
{
	BUSX_GB32960_BATTERY_LEAD=0X01,    //铅酸电池
	BUSX_GB32960_BATTERY_NI_MH,        //镍氢电池
	BUSX_GB32960_BATTERY_FE,            //磷酸铁锂电池
	BUSX_GB32960_BATTERY_MAI,           //锰酸锂电池
	BUSX_GB32960_BATTERY_CAI,          //钴酸锂电池
	BUSX_GB32960_BATTERY_TM,            //三元材料电池
	BUSX_GB32960_BATTERY_PLL,           //聚合物锂离子电池
	BUSX_GB32960_BATTERY_OTHER,         //其它类型电池
};
/*
添加日期：2016-06-20
功能说明：注册命令消息体结构体
*/
typedef struct _BUSX_GB32960_BUS_LOGIN_DATA_BODY
{
	UINT8 dateTime[6];    //时间戳年（0~99） 月(1~12)  日(1~31)  时(0~23) 分(0~59) 秒(0~59)
	UINT16 serialNO;      //注册流水号                               //电池成组日期
	char ICCID[BUSX_GB32960_ICCID_LEN+1];                            //SIM卡号
	UINT8 subREESS_Count;        //可充电储能子系统个数 0~250
	UINT8 REESS_CodeLen;         //可充电储能系统编码长度 0~50 0表示不上传该编码
	char  REESS_Code[BUSX_SUBREESS_MAX_COUNT*BUSX_REESS_CODE_MAX_LEN+1];   //可充电储能系统编码
}PACK_ALIGN BUSX_GB32960_BUS_LOGIN_DATA_BODY;

/*
添加日期：2016-06-20
功能说明：终端控制消息体结构体
*/
typedef struct _BUSX_GB32960_CONFIGURE_DATA_BODY
{
	char plate[BUSX_GB32960_BUS_PLATE_LEN+1];
	char manufactureCode[BUSX_GB32960_TERM_MANUFACTURE_CODE_LEN+1];   //车载终端厂商编号
	char termNO[BUSX_GB32960_TERM_NO_LEN+1];                           //终端编号 
	UINT8 batteryPackTotal;                                        //蓄电池包总数
	char  batteryManufactureCode[BUSX_GB32960_BATTERY_MANUFACTURE_CODE_LEN+1];  //电池厂商代码
	UINT8 batteryType;                                       //电池类型  BUSX_GB32960_BATTERY_TYPT枚举
	UINT16  ratedEleQuantit;                                     //额定电量 单位 0.1kWh;
	UINT16 ratedVoltage;                                         //额定电压 单位0.1V
	UINT8  batteryPackDate[3];                                   //电池成组日期
}PACK_ALIGN BUSX_GB32960_CONFIGURE_DATA_BODY;


/************************************以下整车数据相关结构体**************************************************/
/*
添加日期：2016-06-22
功能说明：整车数据结构体 类型代码0x01 数据长度20byte
*/
typedef struct _BUSX_GB32960_VEHICLE_DATA
{
	UINT8  status;       //车辆状态 0x01车辆启动 0x02车辆熄火 0x03其它状态 0xFE表示异常 0xFF无效
	UINT8  charge_status;  //充电状态 0x01停车充电 0x02:行驶充电 0x03未充电状态 0x04充电完成 0xFE表示异常 0xFF表示无效
	UINT8  run_mode;       //运行模式 0x01纯电 0x02混动 0x03燃油 0xFE异常 0xFF无效
	UINT16 speed;       //车速单位0.1km/h 0km/h~220km/h  0xFFFE表示异常 0xFFFF表示无效
	UINT32 mileage;     //里程 单位0.1km 0~999999.9km 0xFFFFFFFE表示异常 0xFFFFFFFF表示无效
	UINT16 totalVoltage;     //总电压 最小单位0.1V 0~1000V 0xFFFE表示异常 0xFFFF表示无效
	UINT16 totalCurrent;     //总电流 偏移量-1000 最小单位0.1A  -1000A~1000A 0xFFFE表示异常 0xFFFF表示无效
	UINT8  soc;               //单位:1%  0%~100% 0xFE表示异常 0xFF无效
	UINT8  DC_DC_Status;     //DC/DC状态 0x01工作 0x02断开 0xFE表示异常 0xFF无效
	UINT8  gear;        //档位
	UINT16  IR;                      //绝缘电阻 单位：千欧姆 0~50000千欧姆 
	UINT8  app;         //加速踏板位置 单位%  0xFE表示异常 0xFF无效
	UINT8  bpp;         //制动踏板位置 单位%  0xFE表示异常 0xFF无效 0表示制动关 101(0x65)表示无具体行程情况下制动有效 0xFE表示异常 0xFF无效
}PACK_ALIGN BUSX_GB32960_VEHICLE_DATA;
/************************************以上整车数据相关结构体**************************************************/

/*
添加日期:2016-12-16
功能说明：单个驱动电机数据 类型编码0x02
*/
typedef struct _BUSX_GB32960_ONE_MOTOR_DATA
{
	UINT8 num;     //驱动电机序号 1~253
	UINT8 status;  //驱动电机状态 0x01耗电 0x02发电 0x03关闭状态 0x04准备状态 0xFE异常 0xFF无效
	UINT8 controlTemperture;  //驱动电机控制器温度 偏移值-40 -40~210摄氏度  0xFE表示异常  0xFF表示无效
	UINT16 speed;       //电机转速 数值偏移量-20000 单位1r/min 0xFFFE表示异常 0xFFFF表示无效
	UINT16 torque;      //电机转矩 数值偏移量-20000 单位0.1N.m 0xFFFE表示异常  0xFFFF表示无效
	UINT8 temperture;  //驱动电机温度 偏移值-40 -40~210摄氏度  0xFE表示异常  0xFF表示无效
	UINT16 voltage;     //电动机控制器输入电压 最小单位0.1V 0~1000V 0xFFFE表示异常 0xFFFF表示无效
	UINT16 dc_bus_current;  //电机控制器直流母线电流 偏移量-1000 最小单位0.1A  -1000A~1000A 0xFFFE表示异常 0xFFFF表示无效
}PACK_ALIGN BUSX_GB32960_ONE_MOTOR_DATA;
/*
添加日期:2016-12-16
功能说明：驱动电机数据 类型编码0x02
*/
typedef struct _BUSX_GB32960_MOTOR_DATA
{
	UINT8 motorCount;     //驱动电机个数
	BUSX_GB32960_ONE_MOTOR_DATA  motorData[BUSX_GB32960_MOTOR_MAX_COUNT];
}PACK_ALIGN BUSX_GB32960_MOTOR_DATA;

/*
添加日期:2016-12-16
功能说明：燃料电池数据 类型编码0x03
*/
typedef struct _BUSX_GB32960_FUEL_CELL_DATA
{
	UINT16 voltage;   //燃料电池电压 最小单位0.1V 0~1000V 0xFFFE表示异常 0xFFFF表示无效
	UINT16 current;   //燃料电池电流 偏移量-1000 最小单位0.1A  -1000A~1000A 0xFFFE表示异常 0xFFFF表示无效
	UINT16 fuelConsume;   //燃料消耗率 0~600000 单位0.01kg/100km 0xFFFFE表示异常 0xFFFF表示无效
	UINT16 tempertureProbeCount;  //温度探针总数 0xFFFE表示异常 0xFFFF表示无效
	UINT8  temperture[BUSX_GB32960_FUEL_CELL_MAX_TEMPERTURE_COUNT];  //探针温度值 偏移值-40 -40~200摄氏度 单位摄氏度
	UINT16 hydrogenSysMaxTemper;  //氢系统最高温度值 0~2400 偏移量40摄氏度 单位0.1摄氏度 0xFFFE表示异常 0xFFFF表示无效
	UINT8  maxTemperProbeNO;      //氢系统最高温度探针编号0xFFFE 0xFFFF
	UINT16 hydrogenMaxConcentration;  //氢气最高浓度0~50000 单位1mg/kg  0xFFFE表示异常 0xFFFF表示无效
	UINT8  hydrogenMaxConcentrationProbeNO;  //氢气最高浓度传感器代号 1~252 0xFE表示异常 0xFF表示无效
	UINT16 hydrogenMaxPressue;               //氢气最高压力1~1000 单位0.1MPa
	UINT8 hydrogenMaxPressueProbeNO;         //氢气最高压力传感器编号 1~252 0xFE表示异常 0xFF表示无效
	UINT8 highVoltageDC_DCStatus;           //高压DC_DC状态 0x01工作 0x02断开 0xFE表示异常  0xFF表示无效
}PACK_ALIGN BUSX_GB32960_FUEL_CELL_DATA;

/*
添加日期:2016-12-16
功能说明：发动机数据 类型编码0x04
*/
typedef struct _BUSX_GB32960_ENGINE_DATA
{
	UINT8 status;     //发动机状态 0x01启动 0x02关闭 0xFE表示异常  0xFF表示无效
	UINT16 crankshaftSpeed;  //曲轴转速 0~60000 单位1r/min 0xFFFE表示异常 0xFF表示无效
	UINT16 fuelConsume;      //燃料消耗率 0~60000最小计量单位0.01L/100km 0xffFE表示异常 0xFFFF表示无效
}PACK_ALIGN BUSX_GB32960_ENGINE_DATA;


/************************************以下定位数据相关结构体**************************************************/
/*
添加日期：2016-06-22
功能说明：定位数据结构体 数据类型编码0x05 数据长度9字节
*/
typedef struct _BUSX_GB32960_LOCATION_DATA
{
	UINT8 status;       //bit0 0有效 1无效(当数据通信正常，而不能获取定位信息时，发送最后一次有效定位信息，并将定位状态设置为无效)；
						//bit1 0北纬 1南纬；bit2 0东经 1西经
	UINT32 lon;         //经度 以度为单位的值乘以10的6次方
	UINT32 lat;         //纬度 同上
}PACK_ALIGN BUSX_GB32960_LOCATION_DATA;
/************************************以上定位数据相关结构体**************************************************/

/************************************以下极值数据相关结构体**************************************************/
/*
添加日期：2016-06-22
功能说明：极值数据结构体 数据类型编码0x06  长度14字节
*/
typedef struct _BUSX_GB32960_EXTREME_VALUE_DATA
{
	UINT8  maxVoltageCellInSubREESSNO;    //最高电压电池子系统号 1~250  0xFE表示异常 0xFF表示无效
	UINT8  maxVoltageCellNO;           //最高电压单体代号 1~250  0xFE表示异常 0xFF表示无效
	UINT16 maxCellVoltage;           //电池单体电压最高值 单位0.001V  0xFFFE表示异常 0xFFFF表示无效
	UINT8  minVoltageCellInSubREESSNO;    //最低电压电池子系统序号 1~250 0xFE表示异常 0xFF表示无效
	UINT8  minVoltageCellNO;           //最低电压电池单体代号 1~250  0xFE表示异常 0xFF表示无效
	UINT16 minCellVoltage;           //最低单体电压值 单位0.001V   0xFFFE表示异常 0xFFFF表示无效

	UINT8  maxTempertureSubREESSNO;       //最高温子系统号 1~250  0xFE表示异常 0xFF表示无效
	UINT8  maxTempertureProbeNO;     //最高温度探针序号 1~250  0xFE表示异常 0xFF表示无效
	UINT8  maxTemperture;             //最高温度值 偏移值-40 单位摄氏度 -40~210 0xFE表示异常 0xFF表示无效
	UINT8  minTempertureSubREESSNO;       //最低温度子系统号 1~250  0xFE表示异常 0xFF表示无效
	UINT8  minTempertureProbeNO;     //最低温度探针序号 1~250  0xFE表示异常 0xFF表示无效
	UINT8  minTemperture;             //最低温度值 偏移值-40 单位摄氏度 -40~210 0xFE表示异常 0xFF表示无效
}PACK_ALIGN BUSX_GB32960_EXTREME_VALUE_DATA;
/************************************以上极值数据相关结构体**************************************************/

/************************************以下报警数据相关结构体**************************************************/
/*
添加日期：2016-06-22
功能说明：报警数据结构体 数据类型编码0x07 最小长度 9
*/
typedef struct _BUSX_GB32960_ALARM_DATA
{
	UINT8 maxAlarmLevel;      //最高报警等级 0~3 0表示无故障 1表示一级故障，不影响车辆正常行驶的故障
								//2表示二级故障 指代影响车辆性能，需驾驶员限制形式的故障
								//3表示3级故障，为最高级别故障，指代驾驶员应立即停车处理或请求救援。
								//0xFE表示异常 0xFF表示无效
	UINT32 geAlarmMask;      //通用报警标识位 见协议

	UINT8 batteryFaultCount;    // 可充电储能装置故障总数 值域：0~252 0xFE表示异常 0xFF表示无效
	UINT32 batteryFaultMask[BUSX_GB32960_MAX_FAULTCOUNT];  //可充电储能装置故障代码列表

	
	UINT8 motorFaultCount;      //驱动电机故障总数 0~252 0xFE表示异常 0xFF表示无效
	UINT32 motorFaultMask[BUSX_GB32960_MAX_FAULTCOUNT]; //驱动简介故障代码列表
	

	UINT8 engineFaultCount;    //发动机故障总数 0~252 0xFE表示异常 0xFF表示无效
	UINT32 engineFaultMask[BUSX_GB32960_MAX_FAULTCOUNT];  //发动机故障代码列表

	UINT8 otherFaultCount;   //其它故障总数
	UINT32 otherFaultMask[BUSX_GB32960_MAX_FAULTCOUNT]; //其它故障代码列表

}PACK_ALIGN BUSX_GB32960_ALARM_DATA;
/************************************以上报警数据相关结构体**************************************************/


/************************************以下可充电储能系统电压相关结构体**************************************************/
/*
添加日期：2017-03-17
功能说明：可充电储能子系统电压数据格式
*/
typedef struct _BUSX_GB32960_SUB_REESS_VOLTAGE
{
    UINT8 subREESSNO;              //可充电储能子系统号(动力蓄电池包序号) 1~250
    UINT16 voltage;     //电压 最小单位0.1V 0~1000V 0xFFFE表示异常 0xFFFF表示无效
    UINT16 current;     //电流 偏移量-1000 最小单位0.1A  -1000A~1000A 0xFFFE表示异常 0xFFFF表示无效
    UINT16 cellBatteryAmount;   //单体电池个数 1~65531 0xFFFE表示异常 0xFFFF表示无效
    UINT16 cellBatteryBegNO;   //本帧单体电池起始序号 1~65531 0xFFFE表示异常 0xFFFF表示无效 
                                //当本帧单体个数超过200时，应拆分成多帧传输
    UINT8  cellBatteryAmountFrame;   //该包包括单体电池个数 1~200 
    // UINT16 pCellVoltage[400];   //单体蓄电池电压值
    UINT8 pCellVoltage[200*2];   //单体蓄电池电压值
}PACK_ALIGN BUSX_GB32960_SUB_REESS_VOLTAGE;

/*
添加日期：2017-03-17
功能说明：可充电储能系统的电压数据 数据类型编码0x08
*/
typedef struct _BUSX_GB32960_REESS_VOLTAGE
{
    UINT8  subREESSAmount;    //可充电储能子系统总数
    BUSX_GB32960_SUB_REESS_VOLTAGE subREESSVoltage[BUSX_GB32960_MAX_REESS_NUM];  //可充电储能子系统电压信息列表
}PACK_ALIGN BUSX_GB32960_REESS_VOLTAGE;

/************************************以上可充电储能系统电压相关结构体**************************************************/

/************************************以下可充电储能系统温度相关结构体**************************************************/
/*
添加日期：2017-03-17
功能说明：可充电储能子系统的温度信息
*/
typedef struct _BUSX_GB32960_SUB_REESS_TEMPERATURE
{
    UINT8 subREESSNO;           //可充电储能子系统号
    UINT16 probeAmount;     //该可充电储能子系统探针总数 1~65531 0xFFFE表示异常  0xFFFF表示无效
    UINT8 pProbeValue[250]; //温度探针温度值0~165 偏移量-40 单位摄氏温度  0xFE表示异常 0xFF表示无效
}PACK_ALIGN BUSX_GB32960_SUB_REESS_TEMPERATURE;

/*
添加日期：2017-03-17
功能说明：可充电储能系统温度信息 数据类型编码0x09
*/
typedef struct _BUSX_GB32960_REESS_TEMPERATURE
{
    UINT8  subREESSAmount;     //可充电储能子系统总数
    BUSX_GB32960_SUB_REESS_TEMPERATURE pSubREESSTemperature[BUSX_GB32960_MAX_REESS_NUM];
}PACK_ALIGN BUSX_GB32960_REESS_TEMPERATURE;
/************************************以上可充电储能系统温度相关结构体**************************************************/

/*
添加日期：2016-06-22
功能说明：枚举实时信息类型
*/
enum BUSX_GB32960_RT_MSG_BLOCK_TYPE
{
	BUSX_GB32960_RT_MSG_BLOCK_VEHICLE_DATA=0x01,  //整车数据
	BUSX_GB32960_RT_MSG_BLOCK_MOTOR_DATA,   //驱动电机数据
	BUSX_GB32960_RT_MSG_BLOCK_FUEL_CELL,    //燃料电池数据
	BUSX_GB32960_RT_MSG_BLOCK_ENGINE_DATA,  //发动机数据
	BUSX_GB32960_RT_MSG_LOCATION_DATA,       //定位数据
	BUSX_GB32960_RT_MSG_EXTREME_VALUE,     //极值数据
	BUSX_GB32960_RT_MSG_ALARM_DATA=0X07,   //报警数据
	BUSX_GB32960_RT_MSG_BLOCK_CELL_BATTERY_VOLTAGE=0x08, //单体电池电压数据
	BUSX_GB32960_RT_MSG_BLOCK_BATTERY_TEMPERATURE=0x09, //电池温度数据
};
/*
添加日期：2016-06-22
功能说明：实时信息数据块结构体
*/
typedef struct _BUSX_GB32960_RT_MSG_BLOCK
{
	UINT8 msgType;         //信息类型 由BUSX_GB32960_RT_MSG_BLOCK_TYPE枚举
	void *pMsgBlock;       //信息块
}PACK_ALIGN BUSX_GB32960_RT_MSG_BLOCK;
/*
添加日期：2016-06-22
功能说明：实时数据结构体,以下成员放置在数据buf的前部，
电压数据保存在紧随此结构体对象的存储空间,
电池温度保存位置紧随电压数据保存位置
*/
typedef struct _BUSX_GB32960_RT_DATA
{
	BUSX_GB32960_VEHICLE_DATA vehicleData;             //整车数据
	BUSX_GB32960_MOTOR_DATA motorData;        //驱动电机数据
	BUSX_GB32960_FUEL_CELL_DATA fuelCellData;    //燃料电池数据
	BUSX_GB32960_ENGINE_DATA engineData;       //发动机数据
	BUSX_GB32960_LOCATION_DATA locationData;               //定位数据
	BUSX_GB32960_EXTREME_VALUE_DATA extremeData;           //极值数据
	BUSX_GB32960_ALARM_DATA  alarmData;                //报警数据
	BUSX_GB32960_REESS_VOLTAGE pREESSVoltage[REESS_VOLTAGE_MAX_PACK_NUM];   //电压 
	BUSX_GB32960_REESS_TEMPERATURE pREESSTemper;    //电池温度
}PACK_ALIGN BUSX_GB32960_RT_DATA;

#if 0
enum ENUM_BUSX_GB32960_CONTROL_CMD_TYPE
{
	BUSX_GB32960_CONTROL_CMD_MATCH_DATA_ISSUE=0x01,  //终端匹配数据下发
	BUSX_GB32960_CONTROL_CMD_IP_ISSUE=0x02,        //IP地址下发
	BUSX_GB32960_CONTROL_CMD_ADJUST_TIME=0X03,    //校时
	BUSX_GB32960_CONTROL_CMD_SET_RT_DATA_UPLOAD_CYCLE=0X04,  //设置实时数据上传周期
	BUSX_GB32960_CONTROL_CMD_UPGRADE_START=0xAA,   //终端软件更新启动
	BUSX_GB32960_CONTROL_CMD_UPGRADE_SEND_DATA=0xBB,  //终端记录包数据传输
};

enum ENUM_BUSX_GB32960_REPLY_RESULT
{
	BUSX_GB32960_REPLY_FAIL=0X00,  //失败
	BUSX_GB32960_REPLY_SUCESS=0XAA,  //成功
	BUSX_GB32960_REPLY_CHECK_SUCESS=0XBB,  //校验正确
};

/*
添加日期：2016-08-04
功能说明：终端对控制指令的应答
*/
typedef struct _BUSX_GB32960_CONTROL_CMD_REPLY
{
	ENUM_BUSX_GB32960_CONTROL_CMD_TYPE cmdType;
	ENUM_BUSX_GB32960_REPLY_RESULT result;
	UINT16 packNO;  //包序号，对终端记录包数据传输应答时有效
}PACK_ALIGN BUSX_GB32960_CONTROL_CMD_REPLY;

#endif 

/*
添加日期:2017-01-06
功能说明:枚举参数类型
*/
enum ENUM_BUSX_GB32960_PAR
{
	BUSX_GB32960_PAR_SAVE_CYCLE=1,        //本地存储周期 0xFFFE异常 0xFFFF无效 1~60000 单位1ms
	BUSX_GB32960_PAR_UPLOAD_CYCLE,        //正常信息上报周期 0xFFFE异常 0xFFFF无效 1~600，单位s
	BUSX_GB32960_PAR_ALARM_UPLOAD_CYCLE,  //出现报警数据时上报周期，0xFFFE异常 0xFFFF无效 1~60000 单位1ms
	BUSX_GB32960_PAR_MANAGER_PLAT_URL_LEN, //远程服务与管理平台域名长度
	BUSX_GB32960_PAR_MANAGER_PLAT_URL,     //远程服务与管理平台域名
	BUSX_GB32960_PAR_MANAGER_PLAT_PORT,    //远程服务与管理平台端口
	BUSX_GB32960_PAR_HARDWARE_VER,         //硬件版本
	BUSX_GB32960_PAR_SOFTWARE_VER,         //固件版本
	BUSX_GB32960_PAR_HEART_CYCLE,          //心跳发送周期
	BUSX_GB32960_PAR_TERM_REPLY_TIMEOUT,   //终端应答超时时间
	BUSX_GB32960_PAR_PLAT_REPLY_TIMEOUT,   //平台应答超时时间
	BUSX_GB32960_PAR_FOURTH_CONNECT_INTERVAL, //连续三次登陆失败后，第四次登陆间隔时间
	BUSX_GB32960_PAR_SERVICE_PLAT_URL_LEN,  //公共平台域名长度
	BUSX_GB32960_PAR_SERVICE_PLAT_URL,        //公共平台域名
	BUSX_GB32960_PAR_SERVICE_PLAT_PORT,       //公共平台端口
	BUSX_GB32960_PAR_IS_SAMPLING,			//是否处于抽样监测中
};

/*
添加日期:2017-05-16
功能说明:参数值定义
*/
typedef struct _BUSX_GB32960_SERVER_MSG
{
	UINT8	protocoltype;
	UINT32 ip;
	UINT16 port;
}PACK_ALIGN BUSX_GB32960_SERVER_MSG;

typedef struct _BUSX_GB32960_URL_VALUE
{
	UINT8 len;
	char csUrlValue[BUSX_GB32960_MAX_PAR_VALUE_LEN+1];
}PACK_ALIGN BUSX_GB32960_URL_VALUE;
/*
添加日期:2017-01-06
功能说明:参数值定义
*/
typedef union _BUSX_GB32960_PAR_VALUE
{
	UINT16 u16Value;
	UINT8 u8Value;
	char csVerValue[BUSX_GB32960_VER_LEN+1];
	char stringval[256];
	BUSX_GB32960_SERVER_MSG servermsg[GB32960_SERVER_MAX_NUM];
	BUSX_GB32960_URL_VALUE urlValue;
}PACK_ALIGN BUSX_GB32960_PAR_VALUE;

/*
添加日期:2017-01-06
功能说明:单个参数“ID 值对”信息
*/
typedef struct _BUSX_GB32960_PAR_ID_VALUE
{
	UINT8 parID;     //参数ID
	BUSX_GB32960_PAR_VALUE value;    //参数值
}PACK_ALIGN BUSX_GB32960_PAR_ID_VALUE;
/*
添加日期:2017-01-06
功能说明:参数查询应答，与参数设置数据体格式
*/
typedef struct _BUSX_GB32960_PAR_QUERY_SET_BODY
{
	UINT8 time[6];                   //时间
	UINT8 parCount;                  //参数个数
	BUSX_GB32960_PAR_ID_VALUE parID2Value[BUSX_GB32960_MAX_PAR_COUNT_PER_FRAME];
	int iBodyLen;                    //在数据包中数据内容长度
}PACK_ALIGN BUSX_GB32960_PAR_QUERY_SET_BODY;

/*
添加日期:2017-08-08
功能说明:流水号结构体，用来存储流水号
*/
typedef struct _SERIAL_LOCAL_SERIALNUM_SAVE_STRUCT_
{
    struct tm  tminfo;
    UINT16 SerialNum;
}PACK_ALIGN SERIALNUM_TIME;


typedef struct _gps_for_log
{
    double lat;
    double lon;  
}PACK_ALIGN gps_for_log;

/*
添加日期:2017-08-08
功能说明:流水号结构体，用来存储流水号
*/
typedef struct errorreply_time
{
    time_t Errortime;
    UINT16 count;
}PACK_ALIGN ERROR_REPLY_TIME;




typedef struct 
{
	UINT8 gps_status;
    UINT32 gps_longitude;//经度
    UINT32 gps_latitude;//纬度
}PACK_ALIGN GPS_DATA;
#undef PACK_ALIGN
#endif