#ifndef __MUTEXW_H__
#define __MUTEXW_H__

#include <pthread.h>

// 普通锁
class ClMutexLock
{
public:
	ClMutexLock();
    ~ClMutexLock();
	void Lock();
	int Trylock();
	void Unlock();
  	pthread_mutex_t *GetMutex();
    
private:
	pthread_mutex_t m_mutex;
};

#define CMutexLock ClMutexLock
// 读写锁
class CRwLock  
{  
public:  
    CRwLock();  
    ~CRwLock();  
    void ReadLock();  
    void WriteLock();  
    void Unlock();  

private:  
    pthread_rwlock_t m_rwl;  
};

// 递归锁
class CMutexLockRecursive
{
public:
	CMutexLockRecursive();
    ~CMutexLockRecursive();
	void Lock();
	void Unlock();
	pthread_mutex_t *GetMutex();    
private:
	pthread_mutex_t m_mutex;
};
//定义一个条件锁结构体,队列中无数据时，进入休眠等待，当队列中有数据需要处理时，唤醒休眠
class COND_LOCK{
public:
    COND_LOCK();
    ~COND_LOCK();

    pthread_mutex_t cont_lock;
    pthread_cond_t cond;
};
// 安全锁,防止产生死锁
class CMutexLockGuard
{
public:
	explicit CMutexLockGuard( CMutexLock &mutex ) : m_mutex( mutex )  
    {
    	m_mutex.Lock();  
    }

    ~CMutexLockGuard() 
    {  
    	m_mutex.Unlock(); 
    }

private:
	CMutexLock& m_mutex;
};

#ifdef _svenXdvs_  // 仅仅用来方便调试而已
enum
{
  PTHREAD_MUTEX_TIMED_NP,
  PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_ADAPTIVE_NP
#ifdef __USE_UNIX98
  ,
  PTHREAD_MUTEX_NORMAL = PTHREAD_MUTEX_TIMED_NP,
  PTHREAD_MUTEX_RECURSIVE = PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK = PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_DEFAULT = PTHREAD_MUTEX_NORMAL
#endif
#ifdef __USE_GNU
  /* For compatibility.  */
  , PTHREAD_MUTEX_FAST_NP = PTHREAD_MUTEX_TIMED_NP
#endif
}
#endif 

#endif 

