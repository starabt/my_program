#include <assert.h>
#include <malloc.h>
#include "loop_queue.h"

// static int nodeinitcount = 0;
// static int nodedeinitcount = 0;


/**
 * function QUEUENODE:队列节点构造函数
 * description : 调用构造函数的时候（实例化类对象），将按照node_size（默认1024）大小分配内存存放数据
 */
QUEUENODE::QUEUENODE(unsigned int node_size):
	QUEUENODE_SIZE(node_size),
    cmd(0),
    flag(-1),   
    need_deal(false),
    packdata_len(0), 
    next(NULL)
{
	// printf("QUEUENODE init NO.%d\n",nodeinitcount++);
	packdata = new char[QUEUENODE_SIZE];
	assert(packdata);
    pthread_mutex_init(&pack_lock,NULL);
}
/**
 * function ~QUEUENODE：队列节点类析构函数
 * description ：对构造函数分配的内存进行回收
 */
QUEUENODE::~QUEUENODE()
{
	// printf("QUEUENODE deinit NO.%d\n",nodedeinitcount++);
    pthread_mutex_destroy(&pack_lock); 
    if(packdata)
    	delete[] packdata;
}
/**
 * function LOOP_QUEUE ：队列构造函数
 * param maxcount：节点数 默认10
 * param nodesize：节点大小 默认1024
 */
LOOP_QUEUE::LOOP_QUEUE(unsigned int maxcount,unsigned int nodesize):
QUEUE_SIZE(maxcount),
QUEUENODE_SIZE(nodesize),
Data_queue(NULL),
front(NULL),
rear(NULL),
node_count(0)
{
    printf("LOOP_QUEUE init begin\n");
	pthread_mutex_init(&push_index_mutex,NULL);
	pthread_mutex_init(&pop_index_mutex,NULL);
    printf("LOOP_QUEUE init end\n");
}
LOOP_QUEUE::~LOOP_QUEUE()
{
	pthread_mutex_destroy(&push_index_mutex);
	pthread_mutex_destroy(&pop_index_mutex);
}
/**
 * [LOOP_QUEUE::InitQueue 初始化循环队列，依据队列构造函数传入的节点数和节点大小，预先分配空间]
 */
void LOOP_QUEUE::InitQueue()
{
	if(QUEUE_SIZE==0 || QUEUENODE_SIZE==0)
    {
        printf("init_list error:queue_size or node_size is zero\n");
        return ;
    }
    // Data_queue = (QUEUENODE**) malloc(QUEUE_SIZE*sizeof(QUEUENODE*));
	Data_queue = new QUEUENODE*[QUEUE_SIZE];
	if(NULL == Data_queue)
    {
        printf("init_list malloc Data_queue failed\n");
        return ;
    }
    for(unsigned int i=0;i<QUEUE_SIZE;i++)
    {
    	*(Data_queue+i) =new  QUEUENODE(QUEUENODE_SIZE);
    }
    for(unsigned int i=0;i<QUEUE_SIZE-1;i++)
    {
    	(*(Data_queue+i))->need_deal = false;
        (*(Data_queue+i))->cmd=0x00;
        (*(Data_queue+i))->flag=i;
        (*(Data_queue+i))->next = *(Data_queue+i+1);
    }
    front = *Data_queue;
    rear = *Data_queue;
    (*(Data_queue+QUEUE_SIZE-1))->next = *Data_queue;   //a loop list
    (*(Data_queue+QUEUE_SIZE-1))->need_deal = false;
    (*(Data_queue+QUEUE_SIZE-1))->cmd=0x00;
    (*(Data_queue+QUEUE_SIZE-1))->flag=QUEUE_SIZE-1;
    #if 0
	QUEUENODE *nodeTmp = new  QUEUENODE(QUEUENODE_SIZE);
	/*
	依靠QUEUENODE构造函数初始化，如果为了防止
	 */
	front = nodeTmp;
	rear  = front;
	node_count = 0;
	printf("first node add:%p\n",nodeTmp );
	#endif
}
/**
 * [LOOP_QUEUE::deinitQueue 队列去初始化，回收各节点及队列指针]
 */
void LOOP_QUEUE::deinitQueue()
{
	#if 0
	while(front)
	{
		QUEUENODE *tmpNode = front->next;
		delete front;
		front = tmpNode;
	}
	#endif
	printf("\n=====================now is to deinit Data_queue=====================\n");
	for(unsigned int i=0;i<QUEUE_SIZE;i++)
	{
		if(*(Data_queue+i))
		{
			printf("Data_queue[%d] is not null\n", i);
			delete *(Data_queue+i);
		}

	}
	if(Data_queue!=NULL)
	{
		printf("Data_queue is not NULL\n");
        // free(Data_queue);
		delete[] Data_queue;
	}
	return;
}
int LOOP_QUEUE::get_node_count()
{
	int nodeCount = 0;
	pthread_mutex_lock(&node_count_lock.cont_lock);
	nodeCount = node_count;
	pthread_mutex_unlock(&node_count_lock.cont_lock);
	return nodeCount;
}
/**
 * [LOOP_QUEUE::push_queue 将数据压入队列尾]
 * @param  indata  [待压入队列的数据 传入]
 * @param  len     [待压入数据的长度 传入]
 * @param  cmdflag [命令字 不一定所有应用都用到，因此传默认值0作区分]
 * @return         [true：成功 false：失败]
 */
bool LOOP_QUEUE::push_queue(char* indata, unsigned int len,unsigned char cmdflag)
{
	if(rear==NULL)
	{
		printf("rear is null\n");
		return false;
	}
	if(get_node_count() < QUEUE_SIZE && !rear->need_deal)
	{
		// pthread_mutex_lock(&rear->pack_lock);
		if(len > QUEUENODE_SIZE)
		{
			printf("the length of the data is over node size\n");

			// pthread_mutex_unlock(&rear->pack_lock);
			return false;
		}
		if(rear->packdata == NULL)
        {
            printf("rear->packdata is NULL ............\n");
            // pthread_mutex_unlock(&rear->pack_lock);
            return false;
        }
		
		memset(rear->packdata,0,QUEUENODE_SIZE);
        memcpy(rear->packdata, indata ,len);
        rear->packdata_len = len;
        if(cmdflag!=0)
        	rear->cmd=cmdflag;
        rear->need_deal = true;
        rear = rear->next;
		// pthread_mutex_unlock(&rear->pack_lock);
		//此时通知发送线程
        pthread_mutex_lock(&node_count_lock.cont_lock);     //lock cont_lock
        if(node_count++ == 0)
        {
            pthread_cond_signal(&node_count_lock.cond);   //send signal to pthread_mutex_timewait()
        }
        pthread_mutex_unlock(&node_count_lock.cont_lock);   //unlock cont_lock
        printf("push success................\n");
        return true;
	}
	else
	{
		printf("queue is full \n");
		return false;
	}
	printf("anyway push failed\n");
    return false;
}
/**
 * [LOOP_QUEUE::pop_queue 从队列头取出数据]
 * @param  outdata    [取出数据容器 传出]
 * @param  outdatalen [取出的数据长度 传出]
 * @param  cmdFLAG    [命令字 不一定所有应用都用到，因此传默认值NULL作区分]
 * @return            [true：成功 false：失败]
 */
bool LOOP_QUEUE::pop_queue(char *outdata,unsigned int &outdatalen,unsigned char *cmdFLAG)
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
        pthread_mutex_unlock(&node_count_lock.cont_lock);    //unlock cont_lock
        return false;
    }
    
    // pthread_mutex_lock(&front->pack_lock);    //lock pack_lock
    if(front->need_deal)
    {
        outdatalen = front->packdata_len;
        memcpy(outdata,front->packdata,front->packdata_len); 
        if(cmdFLAG!=NULL)
        	*cmdFLAG=front->cmd;
        if(node_count>0)
            node_count--;   
        // pthread_mutex_unlock(&front->pack_lock);      //unlock pack_lock
        pthread_mutex_unlock(&node_count_lock.cont_lock);    //unlock cont_lock
        front->need_deal = false;
        front = front->next;
        printf("pop success\n");
        return true;
    }
    // pthread_mutex_unlock(&front->pack_lock);      //unlock pack_lock
    pthread_mutex_unlock(&node_count_lock.cont_lock);    //unlock cont_lock
    front->need_deal = false;
    front = front->next;
    printf("anyway pop failed\n");
    return false;
}