#include <assert.h>
#include "loop_queue.h"
COND_MUTEX::COND_MUTEX()
{
    pthread_mutex_init(&cond_lock,NULL);
    pthread_cond_init(&cond,NULL);
}
COND_MUTEX::~COND_MUTEX()
{
    pthread_mutex_destroy(&cond_lock);
    pthread_cond_destroy(&cond);
}
static int nodeinitcount = 0;
static int nodedeinitcount = 0;
NODE::NODE(unsigned int node_size):
	NODE_SIZE(node_size),
    cmd(0),
    flag(-1),   
    packdata(NULL),
    need_deal(false),
    packdata_len(0), 
    next(NULL)
{
	printf("NODE init NO.%d\n",nodeinitcount++);
	packdata = new char[NODE_SIZE];
	assert(packdata);
    pthread_mutex_init(&pack_lock,NULL);
}

NODE::~NODE()
{
	printf("NODE deinit NO.%d\n",nodedeinitcount++);
    pthread_mutex_destroy(&pack_lock); 
    if(packdata)
    	delete[] packdata;
}
LOOPQUEUE::LOOPQUEUE(unsigned int maxcount,unsigned int nodesize):
MAX_QUEUE_SIZE(maxcount),
NODE_SIZE(nodesize),
Data_queue(NULL),
front(NULL),
rear(NULL),
node_count(0)
{
	pthread_mutex_init(&push_index_mutex,NULL);
	pthread_mutex_init(&pop_index_mutex,NULL);
	pthread_mutex_init(&node_count_mutex,NULL);
}
LOOPQUEUE::~LOOPQUEUE()
{
	pthread_mutex_destroy(&push_index_mutex);
	pthread_mutex_destroy(&pop_index_mutex);
	pthread_mutex_destroy(&node_count_mutex);
}
void LOOPQUEUE::InitQueue()
{
	if(MAX_QUEUE_SIZE==0 || NODE_SIZE==0)
    {
        printf("init_list error:queue_size or node_size is zero\n");
        return ;
    }
	Data_queue = (NODE**) malloc(MAX_QUEUE_SIZE*sizeof(NODE*));
	if(NULL == Data_queue)
    {
        printf("init_list malloc Data_queue failed\n");
        return ;
    }
    for(int i=0;i<MAX_QUEUE_SIZE;i++)
    {
    	*(Data_queue+i) =new  NODE(NODE_SIZE);
    }
    for(int i=0;i<MAX_QUEUE_SIZE-1;i++)
    {
    	(*(Data_queue+i))->need_deal = false;
        (*(Data_queue+i))->cmd=0x00;
        (*(Data_queue+i))->flag=i;
        (*(Data_queue+i))->next = *(Data_queue+i+1);
    }
    front = *Data_queue;
    rear = *Data_queue;
    (*(Data_queue+MAX_QUEUE_SIZE-1))->next = *Data_queue;   //a loop list
    (*(Data_queue+MAX_QUEUE_SIZE-1))->need_deal = false;
    (*(Data_queue+MAX_QUEUE_SIZE-1))->cmd=0x00;
    (*(Data_queue+MAX_QUEUE_SIZE-1))->flag=MAX_QUEUE_SIZE-1;
    #if 0
	NODE *nodeTmp = new  NODE(NODE_SIZE);
	/*
	依靠NODE构造函数初始化，如果为了防止
	 */
	front = nodeTmp;
	rear  = front;
	node_count = 0;
	printf("first node add:%p\n",nodeTmp );
	#endif
}
void LOOPQUEUE::deinitQueue()
{
	#if 0
	while(front)
	{
		NODE *tmpNode = front->next;
		delete front;
		front = tmpNode;
	}
	#endif
	printf("\n=====================now is to deinit Data_queue=====================\n");
	for(int i=0;i<MAX_QUEUE_SIZE;i++)
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
		free(Data_queue);
	}
	return;
}
int LOOPQUEUE::get_node_count()
{
	int nodeCount = 0;
	pthread_mutex_lock(&node_count_lock.cond_lock);
	nodeCount = node_count;
	pthread_mutex_unlock(&node_count_lock.cond_lock);
	return nodeCount;
}
void LOOPQUEUE::set_node_count()
{
	pthread_mutex_lock(&node_count_mutex);
	node_count++;
	pthread_mutex_unlock(&node_count_mutex);
	return;
}
bool LOOPQUEUE::push_queue(char* indata, unsigned int len,unsigned char cmdflag)
{
	if(rear==NULL)
	{
		printf("rear is null\n");
		return false;
	}
	if(get_node_count() < MAX_QUEUE_SIZE && !rear->need_deal)
	{
		// pthread_mutex_lock(&rear->pack_lock);
		if(len > NODE_SIZE)
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
		
		memset(rear->packdata,0,NODE_SIZE);
        memcpy(rear->packdata, indata ,len);
        rear->packdata_len = len;
        if(cmdflag!=0)
        	rear->cmd=cmdflag;
        rear->need_deal = true;
        rear = rear->next;
		// pthread_mutex_unlock(&rear->pack_lock);
		//此时通知发送线程
        pthread_mutex_lock(&node_count_lock.cond_lock);     //lock cond_lock
        if(node_count++ == 0)
        {
            pthread_cond_signal(&node_count_lock.cond);   //send signal to pthread_mutex_timewait()
        }
        pthread_mutex_unlock(&node_count_lock.cond_lock);   //unlock cond_lock
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
bool LOOPQUEUE::pop_queue(char *outdata,unsigned int &outdatalen,unsigned char *cmdFLAG)
{
    pthread_mutex_lock(&node_count_lock.cond_lock);      //lock cond_lock
    // printf("into pop_queue //cond_lock lock \n");
    timespec timeout;
    timeval now;
    long timeout_ms = 1000; // wait time 50ms
    gettimeofday(&now, NULL);
    long nsec = now.tv_usec * 1000 + (timeout_ms % 1000) * 1000000;
    timeout.tv_sec=now.tv_sec + nsec / 1000000000 + timeout_ms / 1000;
    timeout.tv_nsec=nsec % 1000000000; 
    if(node_count==0)
    {
        pthread_cond_timedwait(&node_count_lock.cond, &node_count_lock.cond_lock,&timeout); 
    } 
    if(node_count == 0)
    {
        pthread_mutex_unlock(&node_count_lock.cond_lock);    //unlock cond_lock
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
        pthread_mutex_unlock(&node_count_lock.cond_lock);    //unlock cond_lock
        front->need_deal = false;
        front = front->next;
        printf("pop success\n");
        return true;
    }
    // pthread_mutex_unlock(&front->pack_lock);      //unlock pack_lock
    pthread_mutex_unlock(&node_count_lock.cond_lock);    //unlock cond_lock
    front->need_deal = false;
    front = front->next;
    printf("anyway pop failed\n");
    return false;
}