
/*******************************************************************************
**  (C) COPYRIGHT 2016 Haitu Tech CO.LTD 
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.09.16
**  description  : 报警
*******************************************************************************/

#include "debug.h"
#include "linuxFile.h"
#include "mutex.h"
#include "confFile.h"
#include "ptypes.h"
#include <fcntl.h>

#define CONFIG_FILE ".tdcancollect.conf"

static ClMutexLock g_confFileLock;
int ReadConfig( char *pBuf, int len )
{
    int fd;
    int ret = -1;
    char temp_filename[256];
    bzero(temp_filename,256);
    if(strlen(temp_filename)+strlen(APP_CONFIG_FILE_ROOTDIR)<sizeof(temp_filename))
    {
        sprintf(temp_filename,"%s/%s",APP_CONFIG_FILE_ROOTDIR,CONFIG_FILE);
        g_confFileLock.Lock();
        fd = Open( temp_filename, O_RDONLY );
        if( -1 == fd )
        {
            ERRORPRINT( "Open(%s) failed:%s!\r\n", temp_filename, STRERROR_ERRNO );        
            g_confFileLock.Unlock();
            return -1;
        }
        ret = Read( fd, pBuf, len );
        ret = ret > 0 ? 0 : -1;
        Close( fd );
        g_confFileLock.Unlock();
    }
    return ret;    
}

int WriteConfig( char *pBuf, int len )
{
    int fd;
    int ret = -1;
    
    g_confFileLock.Lock();

    char temp_filename[256];
    bzero(temp_filename,256);
    if(strlen(temp_filename)+strlen(APP_CONFIG_FILE_ROOTDIR)<sizeof(temp_filename))
    {
        sprintf(temp_filename,"%s/%s",APP_CONFIG_FILE_ROOTDIR,CONFIG_FILE);
        fd = open(temp_filename,O_CREAT|O_WRONLY|O_TRUNC,0777);
        if( -1 == fd )
        {
            ERRORPRINT( "Open(%s) failed:%s!\r\n", temp_filename, STRERROR_ERRNO );        
            g_confFileLock.Unlock();
            return -1;
        }
        ret = Write( fd, pBuf, len );
        if(fd>0)
            fsync(fd);
        ret = ret > 0 ? 0 : -1;
        Close( fd );
        g_confFileLock.Unlock();
    }
    
    return ret; 
}