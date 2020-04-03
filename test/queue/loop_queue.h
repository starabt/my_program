#ifndef _LOOP_QUEUE_H_
#define _LOOP_QUEUE_H_
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdint.h>
#include <sys/time.h>
#include <time.h>
#include <malloc.h>
// #include "mutex.h"
class COND_MUTEX
{
public:
  COND_MUTEX();
  virtual ~COND_MUTEX();
  pthread_mutex_t cond_lock;
  pthread_cond_t cond;
};
//目前暂时采取固定结点数和节点数据长度，后面看是否要采取动态分配方式

//定义一个结构体类型，标识队列中的一个node
class NODE{
public:
    NODE(unsigned int node_size = 1024);//默认1024字节，可通过初始化时传参改变
    virtual ~NODE();
    unsigned int NODE_SIZE;
    pthread_mutex_t pack_lock;          //互斥锁,因为push和pop都要修改need_deal标识，所以这里需要加一个互斥锁
    unsigned char cmd;
    int flag;   
    char *packdata;                     //存放要发送数据
    bool need_deal;                     //node中是否需要处理
    int packdata_len;                   //存放在node中的数据长度
    NODE *next;
};
class LOOPQUEUE{
public:
    LOOPQUEUE(unsigned int maxcount=10,unsigned int nodesize=1024);
    virtual ~LOOPQUEUE();
    unsigned int MAX_QUEUE_SIZE;
    unsigned int NODE_SIZE;
    NODE **Data_queue;   //MAX_QUEUE_SIZE个NODE的队列 //这个不应该放在这里 add by tony 2017-02-18
    NODE *front;       //入队列指针
    NODE *rear;        //出队列指针
    COND_MUTEX node_count_lock; //条件锁
    pthread_mutex_t push_index_mutex;
    pthread_mutex_t pop_index_mutex;

   //清零发送队列的数据，初始化数据包互斥锁
    void InitQueue(); 
    void deinitQueue();
    bool push_queue(char* indata, unsigned int len,unsigned char cmdflag=0);
    bool pop_queue(char *outdata,unsigned int &outdatalen,unsigned char *cmdFLAG=NULL);
private:
	int get_node_count();
	void set_node_count();
	pthread_mutex_t node_count_mutex;
    int node_count;         //记录有数据的node个数
};

#endif