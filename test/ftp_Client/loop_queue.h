#ifndef LOOP_QUEUE_H_
#define LOOP_QUEUE_H_
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdint.h>
#include <sys/time.h>
#include <time.h>
#include <malloc.h>
#include "mutex.h"
//目前暂时采取固定结点数和节点数据长度，后面看是否要采取动态分配方式
// class COND_LOCK{
// public:
//     COND_LOCK();
//     ~COND_LOCK();

//     pthread_mutex_t cont_lock;
//     pthread_cond_t cond;
// };
//定义一个结构体类型，标识队列中的一个node
class QUEUENODE{
public:
    QUEUENODE(unsigned int node_size = 1024);//默认1024字节，可通过初始化时传参改变
    virtual ~QUEUENODE();
    unsigned int QUEUENODE_SIZE;
    pthread_mutex_t pack_lock;          //互斥锁,因为push和pop都要修改need_deal标识，所以这里需要加一个互斥锁
    unsigned char cmd;
    int flag;   
    char *packdata;                     //存放要发送数据
    bool need_deal;                     //node中是否需要处理
    int packdata_len;                   //存放在node中的数据长度
    QUEUENODE *next;
};
class LOOP_QUEUE{
public:
    LOOP_QUEUE(unsigned int maxcount=10,unsigned int nodesize=1024);
    virtual ~LOOP_QUEUE();
    unsigned int QUEUE_SIZE;
    unsigned int QUEUENODE_SIZE;
    QUEUENODE **Data_queue;   //MAX_QUEUE_SIZE个QUEUENODE的队列 //这个不应该放在这里 add by tony 2017-02-18
    QUEUENODE *front;       //入队列指针
    QUEUENODE *rear;        //出队列指针
    COND_LOCK node_count_lock; //条件锁
    pthread_mutex_t push_index_mutex;
    pthread_mutex_t pop_index_mutex;

   //清零发送队列的数据，初始化数据包互斥锁
    void InitQueue(); 
    void deinitQueue();
    bool push_queue(char* indata, unsigned int len,unsigned char cmdflag=0);
    bool pop_queue(char *outdata,unsigned int &outdatalen,unsigned char *cmdFLAG=NULL);
private:
	int get_node_count();
    int node_count;         //记录有数据的node个数
};

#endif