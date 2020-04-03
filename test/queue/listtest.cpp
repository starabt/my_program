#include <pthread.h>
#include <string.h>
// #include "list.h"
#include "loop_queue.h"
//队列长度和节点长度，根据不同需求设定长度
#define QUEUE_SIZE 10	
#define NODE_SIZE 8192	
//队列名称，依据不同业务命名
LOOPQUEUE *list;

bool stop_push = false;
bool stop_pop = false;
/**
 * 压队列测试线程函数
 */
void *push_thread_func(void*)
{
	static int count = 0;
	char data[NODE_SIZE] = {0};
	while(!stop_push)
	{
		if(list != NULL)
		{
			memset(data,0,sizeof(data));
			sprintf(data,"this is NO.%d data",count++);
			list->push_queue((unsigned char*)data,strlen(data));
		}
		else
			return NULL;
		sleep(1);
	}
	printf("now is to exit push_thread_func\n");
	return NULL;
}
/**
 * 取队列测试线程函数
 */
void *pop_thread_func(void*)
{
	unsigned char data[NODE_SIZE] = {0};
	unsigned int dataLen = 0;
	while(!stop_pop)
	{
		if(list != NULL)
		{
			if(list->pop_queue(data,dataLen))
				printf("pop data:%s\n",data );
			else
			{
				printf("pop failed\n");
				usleep(500*1000);
			}
		}
		else
		{
			printf("list is NULL\n");
			return NULL;
		}
	}
	printf("now is to exit pop_thread_func\n");
	return NULL;
}
int main(int argc, char const *argv[])
{
	list = new LOOPQUEUE(QUEUE_SIZE,NODE_SIZE);
	if(list == NULL )
	{
		printf("create list failed\n");
		return -1;
	}
	list->InitQueue();
	
	pthread_t push_thr = -1;
	pthread_t pop_thr = -1;

	pthread_create(&push_thr,NULL,push_thread_func,NULL);
	pthread_detach(push_thr);
	sleep(QUEUE_SIZE+1);//测试先让队列存满
	pthread_create(&pop_thr,NULL,pop_thread_func,NULL);
	pthread_detach(pop_thr);
	//维持20s
	for(int i = 0;i<10;i++)
	{
		sleep(1);
	}
	stop_pop = true;
	stop_push = true;
	list->deinitQueue();
	delete list;
	return 0;
}