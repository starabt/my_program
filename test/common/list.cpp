/***********************************************************
    Copyright (C), 2016,Guang Zhou Tongda auto electric Co., Ltd.
    File name:      send_list.cc
    Author:         Gao Zhigang
    Version:        1.0
    Date:           2016/07/21
    Description:    recv队列类LIST
    History:
        Date            Author          Version       Modification
*************************************************************/
#include "list.h"
#include <time.h>
#include <sys/time.h>

//NODE 类
NODE::NODE():
    cmd(0),
    flag(0),
    need_deal(false),
    packdata_len(0),
    next(NULL)
{
    printf("NODE init\n");
    memset(packdata,0,sizeof(packdata));
    pthread_mutex_init(&pack_lock,NULL);
}

NODE::~NODE(){
    printf("NODE deinit\n");
    pthread_mutex_destroy(&pack_lock); 
}

//LIST 类
LIST::LIST():
    push(NULL),
    pop(NULL)
{
    printf("list init\n");
    pthread_mutex_init(&push_index_mutex, NULL);
    pthread_mutex_init(&pop_index_mutex, NULL);
}

LIST::~LIST()
{
    printf("list deinit\n");
    pthread_mutex_destroy(&push_index_mutex);
    pthread_mutex_destroy(&pop_index_mutex);
}

/*************************************************
    Function:       init_queue()
    Description:    环形链表初始化
*************************************************/
void LIST::init_list(NODE* data_list,NODE** in_list,NODE** out_list)
{
    unsigned int list_len = MAX_QUEUE_SIZE;
    *out_list = data_list;
    *in_list = data_list;
    for(unsigned int i = 0;i<list_len-1;i++)
    {
        (data_list+i)->need_deal = false;
        (data_list+i)->cmd=0x00;
        (data_list+i)->flag=i;
        (data_list+i)->next = data_list+i+1;
    }
    (data_list+list_len-1)->next = data_list;   //a loop list
    (data_list+list_len-1)->need_deal = false;
    (data_list+list_len-1)->cmd=0x00;
    (data_list+list_len-1)->flag=list_len-1;

    pthread_mutex_lock(&node_count_lock.cont_lock);     //lock cont_lock
    node_count = 0;
    pthread_mutex_unlock(&node_count_lock.cont_lock);   //unlock cont_lock
    return;
}

/*************************************************
    Function:       push_queue()
    Description:    添加一个数据包到队列中,成功返回 true,失败返回false
*************************************************/
bool LIST::push_queue(NODE** in_list,unsigned char* indata, unsigned int len,unsigned char cmdflag)
{
    unsigned int list_len = MAX_QUEUE_SIZE;
    for(unsigned int i=0;i< list_len;i++)
    {
        if(in_list == NULL)
        {
            printf("in_list is NULL_____________________\n");
            continue;
        }
        if(*in_list == NULL)
        {
            printf("*in_list is NULL_____________________\n");
            continue;
        }
        if(indata == NULL)
        {
            printf("indata is NULL_____________________\n");
            continue;
        }
        pthread_mutex_lock(&(*in_list)->pack_lock);  //上锁互斥锁
        // printf("(*in_list)->flag  %d\n",(*in_list)->flag );
        printf("(*in_list)->need_deal::::::::::::::%d\n",(*in_list)->need_deal );
        if(!(*in_list)->need_deal)
        {
            if(len  <= sizeof((*in_list)->packdata)) //数据长度小于等于一个node数组长度
            {
                memset((*in_list)->packdata,0,sizeof((*in_list)->packdata));
                memcpy((*in_list)->packdata, indata ,len);
                (*in_list)->packdata_len = len;
                if(cmdflag!=0)
                    (*in_list)->cmd=cmdflag;
                (*in_list)->need_deal = true;
                pthread_mutex_unlock(&((*in_list)->pack_lock));  ////解锁互斥锁 
                (*in_list) = (*in_list)->next;

                //此时通知发送线程
                pthread_mutex_lock(&node_count_lock.cont_lock);     //lock cont_lock
                if(node_count++ == 0)
                {
                    pthread_cond_signal(&node_count_lock.cond);   //send signal to pthread_mutex_timewait()
                }
                pthread_mutex_unlock(&node_count_lock.cont_lock);   //unlock cont_lock
                return true;
            }
            else  //数据长度大于node数组长度
            {
                /*********************
                *gzg:暂时不处理，丢弃，理论上应该进行分包处理
                *********************/
                pthread_mutex_unlock(&(*in_list)->pack_lock);  //解锁互斥锁 
                return false;  
            }   
        }
        pthread_mutex_unlock(&(*in_list)->pack_lock);  //解锁互斥锁
        (*in_list) = (*in_list)->next;
    }

    printf("recv 队列已满，请稍后。。。\n");
    return false;
}

/*************************************************
    Function:       pop_queue()
    Description:    从队列中取出一个数据包,成功返回pop_data,失败返回NULL
***************************************l**********/
bool LIST::pop_queue(NODE** out_list,unsigned char *outdata,unsigned int &outdatalen,unsigned char *cmdFLAG)
{
    pthread_mutex_lock(&node_count_lock.cont_lock);      //lock cont_lock
    // printf("into pop_queue //cont_lock lock \n");
    timespec timeout;
    timeval now;
    long timeout_ms = 1000; // wait time 50ms
    gettimeofday(&now, NULL);
    long nsec = now.tv_usec * 1000 + (timeout_ms % 1000) * 1000000;
    timeout.tv_sec=now.tv_sec + nsec / 1000000000 + timeout_ms / 1000;
    timeout.tv_nsec=nsec % 1000000000; 
    if(node_count==0)
    {
        pthread_cond_timedwait(&node_count_lock.cond, &node_count_lock.cont_lock,&timeout); 
    }
        
    if(node_count == 0)
    {
        // printf("here\n");
        pthread_mutex_unlock(&node_count_lock.cont_lock);    //unlock cont_lock
        return false;
    }
    pthread_mutex_lock(&(*out_list)->pack_lock);    //lock pack_lock
    if((*out_list)->need_deal)
    {
        outdatalen = (*out_list)->packdata_len;
        memcpy(outdata,(*out_list)->packdata,(*out_list)->packdata_len);
        (*out_list)->need_deal = false;
        if(cmdFLAG!=NULL)
            *cmdFLAG=(*out_list)->cmd;
        if(node_count!=0)
            node_count--;   
        pthread_mutex_unlock(&(*out_list)->pack_lock);      //unlock pack_lock
        pthread_mutex_unlock(&node_count_lock.cont_lock);    //unlock cont_lock
        (*out_list) = (*out_list)->next;
        return true;
    }
    pthread_mutex_unlock(&(*out_list)->pack_lock);      //unlock pack_lock
    pthread_mutex_unlock(&node_count_lock.cont_lock);    //unlock cont_lock
    (*out_list) = (*out_list)->next;
    return false;
}