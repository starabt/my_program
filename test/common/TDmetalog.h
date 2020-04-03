/******************************************************************************

 Copyright (C), 2005-2016, TongDa Auto Electric. Co., Ltd.

 ******************************************************************************
 File Name            :   TDmetalog.h
 Author             :   Tony
 Created              :   2017/03/30
 Last Modified        :
 Description          :   Common log function interface
 Function List        :
time
<<<<<<< .mine
list
=======
test
>>>>>>> .r113
 ******************************************************************************/


#ifndef _TDMETALOG_H_
#define _TDMETALOG_H_

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <string.h>
#include <syslog.h>
#include <libgen.h>

#ifdef __cplusplus
extern "C" {
#endif

#define    __LOG_TB_DEPTH             5
#define    __LOG_TB_FNAME_LEN         127


struct __log_addr_
{
  unsigned offset;
  char file[__LOG_TB_FNAME_LEN + 1];
};


struct __log_traceback_buffer_ {
        struct __log_addr_ entry[__LOG_TB_DEPTH];
        unsigned          n;
        unsigned          skip;
        unsigned          max;
};



extern void
__log_get_traceback_(struct __log_traceback_buffer *tb, unsigned depth, unsigned skip);


#define LOG(_prio_, _fmt_, ...)                                                 \
        syslog((_prio_), "[%s:%d] " _fmt_, basename(__FILE__), __LINE__, ## __VA_ARGS__)


#define LOG_TB(_prio_, _fmt_, ...)                                              \
do {                                                                            \
        struct __log_traceback_buffer _tb_;                                     \
        __log_get_traceback(&_tb_, __LOG_TB_DEPTH, 1);                          \
        syslog((_prio_),                                                        \
               "[%s:%d/%s:%#x %s:%#x %s:%#x %s:%#x %s:%#x] " _fmt_,             \
               basename(__FILE__), __LINE__,                                    \
               _tb_.entry[0].file, _tb_.entry[0].offset,                        \
               _tb_.entry[1].file, _tb_.entry[1].offset,                        \
               _tb_.entry[2].file, _tb_.entry[2].offset,                        \
               _tb_.entry[3].file, _tb_.entry[3].offset,                        \
               _tb_.entry[4].file, _tb_.entry[4].offset, ## __VA_ARGS__);       \
} while(0)


#define LOG_CONSOLE(_prio_, _fmt_, ...)                                         \
    syslog((_prio_), "[CONSOLE] " _fmt_, ## __VA_ARGS__)

/*
 * Name: XXX_LOG
 *
 * Description: same as LOG(LOG_XXX, ...)
 *
 */
 /*********************************************************
0 debug       –有调式信息的，日志信息最多
1 info        –一般信息的日志，最常用
2 notice      –最具有重要性的普通条件的信息
3 warning     –警告级别
4 err         –错误级别，阻止某个功能或者模块不能正常工作的信息
5 crit        –严重级别，阻止整个系统或者整个软件不能正常工作的信息
6 alert       –需要立刻修改的信息
7 emerg       –内核崩溃等严重信息
***********************************************************/
#if 0
#define EMERG_LOG(...)  LOG(LOG_EMERG, __VA_ARGS__)
#define ALERT_LOG(...)  LOG(LOG_ALERT, __VA_ARGS__)
#define CRIT_LOG(...)   LOG(LOG_CRIT, __VA_ARGS__)
#define ERR_LOG(...)    LOG(LOG_ERR, __VA_ARGS__)
#define WARN_LOG(...)   LOG(LOG_WARNING, __VA_ARGS__)
#define NOTE_LOG(...)   LOG(LOG_NOTICE, __VA_ARGS__)
#define INFO_LOG(...)   LOG(LOG_INFO, __VA_ARGS__)
#define DEBUG_LOG(...)  LOG(LOG_DEBUG, __VA_ARGS__)
#endif

#define EMERG_LOG printf
#define EMERG_LOG printf
#define ALERT_LOG  printf
#define CRIT_LOG  printf
#define ERR_LOG  printf
#define WARN_LOG printf
#define NOTE_LOG printf
#define INFO_LOG printf
#define DEBUG_LOG  printf

/*
 * Name: XXX_LOG_TB
 *
 * Description: same as LOG_TB(LOG_XXX, ...)
 *
 */
#define EMERG_LOG_TB(...)  LOG_TB(LOG_EMERG, __VA_ARGS__)
#define ALERT_LOG_TB(...)  LOG_TB(LOG_ALERT, __VA_ARGS__)
#define CRIT_LOG_TB(...)   LOG_TB(LOG_CRIT, __VA_ARGS__)
#define ERR_LOG_TB(...)    LOG_TB(LOG_ERR, __VA_ARGS__)
#define WARN_LOG_TB(...)   LOG_TB(LOG_WARNING, __VA_ARGS__)
#define NOTE_LOG_TB(...)   LOG_TB(LOG_NOTICE, __VA_ARGS__)
#define INFO_LOG_TB(...)   LOG_TB(LOG_INFO, __VA_ARGS__)
#define DEBUG_LOG_TB(...)  LOG_TB(LOG_DEBUG, __VA_ARGS__)


/*
 * Name: XXX_LOG_CON
 *
 * Description: same as LOG_TB(LOG_XXX, ...)
 *
 */
#define EMERG_LOG_CON(...)  LOG_CONSOLE(LOG_EMERG, __VA_ARGS__)
#define ALERT_LOG_CON(...)  LOG_CONSOLE(LOG_ALERT, __VA_ARGS__)
#define CRIT_LOG_CON(...)   LOG_CONSOLE(LOG_CRIT, __VA_ARGS__)
#define ERR_LOG_CON(...)    LOG_CONSOLE(LOG_ERR, __VA_ARGS__)
#define WARN_LOG_CON(...)   LOG_CONSOLE(LOG_WARNING, __VA_ARGS__)
#define NOTE_LOG_CON(...)   LOG_CONSOLE(LOG_NOTICE, __VA_ARGS__)
#define INFO_LOG_CON(...)   LOG_CONSOLE(LOG_INFO, __VA_ARGS__)
#define DEBUG_LOG_CON(...)  LOG_CONSOLE(LOG_DEBUG, __VA_ARGS__)


/*******************************************************************************
 *
 *                                Fatal Error Logs
 *
 ******************************************************************************/

/*
 * Name: FATAL
 *
 * Description:
 *   This function generates a fatal error log that includes the location (file
 *   name and line number) in the source code file where this function is called
 *   along with text to provide additional data for debugging purposes
 *
 *   After the log is generated the process is aborted.
 *
 * Input Parameters:
 *   formatted string containing text to be captured in the log
 *
 *   Note: in addition to standard formatting, the following is also supported:
 *      %m - prints a string representation of the errno value (no additional
 *           argument needs to be supplied for this)
 *
 * Returns:
 *   Nothing
 */
#define FATAL(...) do { ALERT_LOG(__VA_ARGS__); abort(); } while(0)
#define FATAL_TB(...) do { ALERT_LOG_TB(__VA_ARGS__); abort(); } while(0)

#ifdef __cplusplus
}
#endif

#endif  //_TDMETALOG_H_
