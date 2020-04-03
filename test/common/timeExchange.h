#ifndef __TIMEEXCHANGE_H__
#define __TIMEEXCHANGE_H__

#include <sys/time.h>
#define PACK_ALIGN  __attribute__((packed))
#define ONE_DAY_SECOND (24*3600)
typedef struct DATE_TIME_
{
	unsigned char year;
	unsigned char mon;
	unsigned char day;
	unsigned char hour;
	unsigned char min;
	unsigned char sec;
}DATE_TIME;
int FiTimeHumanToUtc( int year, int month, int day, int hour, int minute, int second );
void FiTimeUtcToHuman( int utc, int *pyear, int *pmonth, int *pday,
                        	int *phour, int *pminute, int *psecond );
void FiTimeUtcToWeekDay( int utc, int *weekday );
int FiTimeUtcToWeekSecond( int utc );

void NanosleepZero();
int TimeGetDatatime( char dtime[20] );
int TimeIsValidDatetime( int year, int mon, int day, int hour, int min, int sec );
int Time();
int Gettimeofday( struct timeval *tv, struct timezone *tz );
void AddnHour(struct tm* tiem_exc,unsigned int nHour);
void SubnHour(struct tm* tiem_exc,unsigned int nHour);
void AddnMin(struct tm* tiem_exc,unsigned int nMin);
void SubnMin(struct tm* tiem_exc,unsigned int nMin);
int diffzone();
bool systemtime_adjust(DATE_TIME adjTime);

#endif 

