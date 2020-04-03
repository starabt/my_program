/********************************************************************************
**  (C) COPYRIGHT 2016 Haitu Tech CO.LTD 
**  author        :  xMusk
**  version       :  v1.0
**  date           :  2013.10.10
**  description  : ��malloc �庯����װ; �ṩָ�븴�ƵĽӿ�
********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "mutex.h"
#include "malloc.h"

/* ===== ��malloc �庯����װ���� ===== */
void *MeAlloc( long nbytes, const char *file, int line )
{    
	void *ptr = ( void * )malloc( nbytes );
	if ( ptr == NULL )
    	Print( "Malloc Memory Failed, file: %s, line: %d !\r\n", file, line );
        
	return ptr;
}

void *MeCalloc( long count, long nbytes, const char *file, int line )
{    
	void *ptr = ( void * )calloc( count, nbytes );
	if ( ptr == NULL )
    	Print( "Calloc Memory Failed, file: %s, line: %d !\r\n", file, line );
        
	return ptr;
}

void MeFree( void *ptr, const char *file, int line )
{
	if ( ptr != NULL ) free( ptr );
}

void *MeRealloc( void *ptr, long nbytes, const char *file, int line )
{    
	ptr = ( void * )realloc( ptr, nbytes );
	if ( ptr == NULL )
    	Print( "Realloc Memory Failed, file: %s, line: %d !\r\n", file, line );
        
	return ptr;
}
/* ===== end ��malloc �庯����װ���� ===== */

/* ===== ����ָ�븴�ƵĲ��� ===== */
#define		SHARE_MEMORY_FLAG		0xCCBB2828
static ClMutexLock	s_ShareMemMutex;

void *ShareMeAlloc( long nbytes, const char *file, int line )
{    
	long size = nbytes + sizeof(long)*2;
	long *ptr = ( long * )malloc( size );
	if ( ptr == NULL )
    {
    	Print( "Malloc Share Memory Failed, file: %s, line: %d !\r\n", file, line );
    }
	else
    {
        *ptr = SHARE_MEMORY_FLAG;
        *(ptr + 1) = 1;
    }        
    
	return (void *)(ptr + 2);
}

void *ShareMeCalloc( long count, long nbytes, const char *file, int line )
{    
	long size = nbytes + sizeof(long)*2;
	long *ptr = ( long * )calloc( count, size );
	if ( ptr == NULL )
    {
    	Print( "Calloc Share Memory Failed, file: %s, line: %d !\r\n", file, line );
    }
	else
    {
        *ptr = SHARE_MEMORY_FLAG;
        *(ptr + 1) = 1;
    }        
	return (void *)(ptr + 2);
}

void ShareMeFree( void *ptr, const char *file, int line )
{
	if ( ptr != NULL )
    {
    	long *pmem = (long *)ptr - 2;
    	if ( *pmem == (long)SHARE_MEMORY_FLAG )
        {
        	s_ShareMemMutex.Lock();
            *(pmem + 1) -= 1;
        	if ( *(pmem + 1) == 0 ) 
            {                
            	free( pmem );
            }
        	s_ShareMemMutex.Unlock();
        }
    	else
        {
        	ERRORPRINT( "Free Share Memory Failed, file: %s, line: %d !\r\n", file, line );
            
        }
    }    
}

void *ShareMeCopy( void *ptr, const char *file, int line )
{
	if ( ptr == NULL )
    {
#if 0
    	Print( "Copy Share Memory Failed, Can't Copy NULL ptr; "
                "file: %s, line: %d !\r\n", file, line );
#endif
    	return NULL;
    }
        
	long *pmem = (long *)ptr - 2;
	if ( *pmem == (long)SHARE_MEMORY_FLAG )
    {
    	s_ShareMemMutex.Lock();
        *(pmem + 1) += 1;
    	s_ShareMemMutex.Unlock();
    	return ptr;
    }
	else
    {
    	ERRORPRINT( "Copy Share Memory Failed, Copy Error ptr; "
                "file: %s, line: %d !\r\n", file, line );
        
    }
	return NULL;
}
/* ===== end ����ָ�븴�ƵĲ��� ===== */

/****************************************************************************
* �����ڴ������������free
* ptr: ��free ��ָ��
* bShareMem: PDATA_FROM_E
*****************************************************************************/
void FreeMs( void *ptr, int bShareMem )
{
	if( PDATA_FROM_SHAREMALLOC == bShareMem )
    {
    	ShareFree( ptr );
    }
	else
    {
    	Free( ptr );
    }
}

