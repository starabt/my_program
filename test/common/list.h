#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdint.h>
#include "mutex.h"
//目前暂时采取固定结点数和节点数据长度，后面看是否要采取动态分配方式
#define MAX_QUEUE_SIZE 64    //队列长度,即对列中的node个数
#define MAX_PACKDATA_SIZE 2048  //每个node最多可以存放的字符数

//定义一个结构体类型，标识队列中的一个node
class NODE{
public:
    NODE();
    virtual ~NODE();

    pthread_mutex_t pack_lock;          //互斥锁,因为push和pop都要修改need_deal标识，所以这里需要加一个互斥锁
    unsigned char cmd;
    int flag;   
    char packdata[MAX_PACKDATA_SIZE];   //存放要发送数据
    bool need_deal;                     //node中是否需要处理
    int packdata_len;                   //存放在node中的数据长度
    NODE *next;
};


class LIST{
public:
    LIST();
    virtual ~LIST();

    NODE datalist[MAX_QUEUE_SIZE];   //MAX_QUEUE_SIZE个NODE的队列 //这个不应该放在这里 add by tony 2017-02-18
    NODE *push;       //入队列指针
    NODE *pop;        //出队列指针
    COND_LOCK node_count_lock; //条件锁
    pthread_mutex_t push_index_mutex;
    pthread_mutex_t pop_index_mutex;
   //清零发送队列的数据，初始化数据包互斥锁
    void init_list(NODE* data_list,NODE** in_list,NODE** out_list); 
    bool push_queue(NODE** in_list,unsigned char* indata, unsigned int len,unsigned char cmdflag=0);
    bool pop_queue(NODE** out_list,unsigned char *outdata,unsigned int &outdatalen,unsigned char *cmdFLAG=NULL);   
protected:
    int node_count;         //记录有数据的node个数
};
#endif