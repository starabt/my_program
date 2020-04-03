#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstdlib>  
#include <iostream>  

#include "debug.h"
#include "timeExchange.h"


//人工日期转换成 LINUX UTC 时间
int FiTimeHumanToUtc( int year, int month, int day, int hour, int minute, int second )
{
	time_t ret;
	struct tm t;
    
	t.tm_year = year-1900;
	t.tm_mon = month-1;
	t.tm_mday = day;
	t.tm_hour = hour;
	t.tm_min = minute;
	t.tm_sec = second;
	ret = mktime( &t );
	if ( ret < 0 ) 
    {
    	ERRORPRINT( "%04d-%02d-%02d %02d:%02d:%02d\r\n", year, month, day, hour, minute, second );
    	return 0;
    }
    
	return ret;
}

//LINUX UTC时间转换成人工日期
void FiTimeUtcToHuman( int utc, int *pyear, int *pmonth, int *pday,
                        	int *phour, int *pminute, int *psecond )
{
	struct timeval tv;
	struct tm tm;
    
	if ( utc < 0 )
    {
    	SVPrint( "Invalid UTC time,do not set time before 1970-1-1 00:00:00.\r\n" );
    	utc = 0;
    }
	tv.tv_sec     = utc;
	tv.tv_usec     = 0;
	localtime_r( &tv.tv_sec,&tm );

	if ( pyear != NULL )    *pyear = tm.tm_year+1900;
	if ( pmonth != NULL )    *pmonth = tm.tm_mon+1;
	if ( pday != NULL )        *pday = tm.tm_mday;
	if ( phour != NULL )    *phour = tm.tm_hour;
	if ( pminute != NULL )    *pminute = tm.tm_min;
	if ( psecond != NULL )    *psecond = tm.tm_sec;
}

//LINUX UTC时间转换成一个星期的第几天
void FiTimeUtcToWeekDay( int utc, int *weekday )
{
	struct timeval tv;
	struct tm tm;
    
	if ( utc < 0 )
    {
    	SVPrint( "Invalid UTC time,do not set time before 1970-1-1 00:00:00.\r\n" );
    	utc=0;
    }
	tv.tv_sec = utc;
	tv.tv_usec = 0;
	localtime_r( &tv.tv_sec, &tm );
	if ( NULL != weekday )
        *weekday = tm.tm_wday;    
}

//LINUX UTC时间转换成一个星期的第几秒
int FiTimeUtcToWeekSecond( int utc )
{
	return (utc + ONE_DAY_SECOND*4) % (ONE_DAY_SECOND*7);
}

/************************************************************************
* fn: 休眠0 秒的时间,用来多线程的时分复用调度
*************************************************************************/
void NanosleepZero()
{
	static struct timespec tszero = { 0, 0 };
	nanosleep( &tszero, NULL );
}

/***************************************************************************
* 获取linux 下data 命令显示的时间
* dtime[20]: 存放 "2013-05-18 18:28:36"
*****************************************************************************/
int TimeGetDatatime( char dtime[20] )
{  
	int ret = -1;
	struct tm *pNow=NULL;
  	struct tm tmNow;
  	memset(&tmNow,0,sizeof(tmNow));       
	time_t tNow = time(NULL);  
    
	pNow = localtime_r( &tNow, &tmNow );    
	if( NULL != pNow )
    {
    	strftime( dtime, 20, "%Y-%m-%d %H:%M:%S", &tmNow );  
    	ret = 0;
    }
	return ret;  
}

/*************************************************************************
* fn: 检查给定的时间是否合法
* 返回: 0, 非法, 1, 合法
**************************************************************************/
int TimeIsValidDatetime( int year, int mon, int day, int hour, int min, int sec )
{
	int maxDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
	if ( ((year%4==0)&&(year%100!=0))||(year%400==0) ) 
    {
    	maxDays[1] += 1; // 闰年
    }
    
	if ( year < 1970 ) return 0;
	if ( mon < 1 || mon > 12 ) return 0;
	if ( day < 1 || day > maxDays[mon-1] ) return 0;
	if ( hour < 0 || hour > 23 ) return 0;
	if ( min < 0 || min > 59 ) return 0;
	if ( sec < 0 || sec > 59 ) return 0;
    
	return 1;
}

/**
 * 增加n小时后得到新的日期时间,tiem_exc :time to exchange
 */
void AddnHour(struct tm* tiem_exc,unsigned int nHour)
{
	int maxDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	tiem_exc->tm_year +=1900;
	tiem_exc->tm_mon +=1;
	if((tiem_exc->tm_year%4 == 0 && tiem_exc->tm_year%100 != 0) || tiem_exc->tm_year%400 == 0)
	{
		maxDays[1] += 1; // 闰年
	}
	tiem_exc->tm_hour += nHour;
	if(tiem_exc->tm_hour >= 24)//加完超过24小时
	{
		tiem_exc->tm_hour -= 24;//将小时减去24
		tiem_exc->tm_mday ++ ;//天数加一

		if(tiem_exc->tm_mday >= maxDays[tiem_exc->tm_mon-1] +1)//天数加一后是否超过当月天数,
		{
			tiem_exc->tm_mday=1;
			if((++tiem_exc->tm_mon) > 12)//月数加一
			{
				tiem_exc->tm_year ++;//
				tiem_exc->tm_mon = 1;//若月数加一后超过12月，年数加一，月数置为一月
			}
		}
	}
	tiem_exc->tm_year -=1900;
	tiem_exc->tm_mon -= 1;
	return;
}
/**
 * 减少n小时后得到新的日期时间,tiem_exc :time to exchange
 */
void SubnHour(struct tm* tiem_exc,unsigned int nHour)
{
	int maxDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	tiem_exc->tm_year +=1900;
	tiem_exc->tm_mon +=1;
	if((tiem_exc->tm_year%4 == 0 && tiem_exc->tm_year%100 != 0) || tiem_exc->tm_year%400 == 0)
	{
		maxDays[1] += 1; // 闰年
	}
	tiem_exc->tm_hour -= nHour;
	if(tiem_exc->tm_hour < 0)
	{
		tiem_exc->tm_hour += 24;//减完小于零则小时数加24
		if(tiem_exc->tm_mday  == 1 ) //当天是1号时
		{
			if(tiem_exc->tm_mon == 1)
			{
				tiem_exc->tm_mon =12;//表示12月份
				tiem_exc->tm_year --;//若月份是1月,则变为12月，年份减一	
			}
			else
			{
				tiem_exc->tm_mon --;//当月不是一月，月份减一

			}
			tiem_exc->tm_mday = maxDays[tiem_exc->tm_mon-1];//日期变为当月天数

		}
		else
		{
			tiem_exc->tm_mday -- ;//当天不是1号，直接天数减一
		}
	}
	tiem_exc->tm_year -=1900;
	tiem_exc->tm_mon -= 1;
	return;
}
/**
 * [AddnMin 增加nMin分钟]
 * @param tiem_exc [要修改的时间]
 * @param nMin     [增加分钟数]
 */
void AddnMin(struct tm* tiem_exc,unsigned int nMin)
{
	tiem_exc->tm_min += nMin;
	if(tiem_exc->tm_min >= 60 )
	{
		AddnHour(tiem_exc,1);
		tiem_exc->tm_min -= 60;
		return;
	}
	else
		return;
}
/**
 * [SubnMin 减去nMin分钟]
 * @param tiem_exc [要修改的时间]
 * @param nMin     [减去分钟数]
 */
void SubnMin(struct tm* tiem_exc,unsigned int nMin)
{
	int diffMin=0;
	diffMin = tiem_exc->tm_min - nMin;
	if(diffMin < 0)
	{
		SubnHour(tiem_exc,1);
		tiem_exc->tm_min = tiem_exc->tm_min+60 - nMin;
		return;
	}
	else
		tiem_exc->tm_min -= nMin;
	return;
}
/**
 * [diffzone 计算当地时间和gmt时间的时区差]
 * @return [时差（小时）]
 */
int diffzone()
{
	struct tm gm_time,local_time;
	time_t time_now = time(NULL);
#if !defined(WIN32)
	gmtime_r(&time_now,&gm_time);
	localtime_r(&time_now,&local_time);
#else
	gmtime_s(&time_now,&gm_time);
	localtime_s(&time_now,&local_time);
#endif
	if(local_time.tm_mday != gm_time.tm_mday)
		return local_time.tm_hour+24 - gm_time.tm_hour;
	else
		return local_time.tm_hour - gm_time.tm_hour;
}

/*************************************************************************
* fn: time() 函数封装
**************************************************************************/
int Time()
{
	return time( NULL );
}

int Gettimeofday( struct timeval *tv, struct timezone *tz )
{
	return gettimeofday( tv, tz );
}
bool systemtime_adjust(DATE_TIME adjTime)
{
    int server_UTC_time=0;
    int system_UTC_time=0;
    printf("adjTime:%d-%d-%d %d:%d:%d\n",adjTime.year+2000,adjTime.mon,adjTime.day,\
    	adjTime.hour,adjTime.min,adjTime.sec );
    if(TimeIsValidDatetime(adjTime.year+2000,adjTime.mon,adjTime.day,\
    	adjTime.hour,adjTime.min,adjTime.sec)==1)
    {
    	server_UTC_time=FiTimeHumanToUtc(adjTime.year+2000,adjTime.mon,adjTime.day,\
    	adjTime.hour,adjTime.min,adjTime.sec);
    	system_UTC_time=Time();
    	if((server_UTC_time-system_UTC_time)>=5 ||(system_UTC_time-server_UTC_time)>=5)
    	{
    		struct timeval tv;
            tv.tv_sec = server_UTC_time;
            tv.tv_usec = 0;
            if(settimeofday(&tv, (struct timezone *) 0) < 0)
            {
                printf("Set system datetime error!\n");
                return false;
            }
            else
            {
            	printf("Set system datetime success!\n");
            	return true;
            }
    	}
    	else
    	{
    		printf("system time no need to adjust\n");
    		return true;
    	}
    }
    else
    	return false;
}

       
