#ifndef _HASH_MESSAGE_H
#define _HASH_MESSAGE_H

#include "mutex.h"

#define MAX_NODE 20000
#define MAX_MUTEX 40

typedef enum _Message_
{
    MSG_ID_HTTP_IP_GET,  //
    MSG_ID_NETWORK_0_CHANGE,      // 用于改变网络地址后, 重启与网络传输相关的线程
    MSG_ID_NETWORK_1_CHANGE,
    MSG_ID_NETWORK_2_CHANGE,
    MSG_ID_NETWORK_3_CHANGE,
    MSG_ID_NETWORK_4_CHANGE,
    
    MSG_ID_TCP0_REPLY_ERROR,   //TCP链路0回复消息错误
    MSG_ID_TCP1_REPLY_ERROR,   //TCP链路1回复消息错误
    MSG_ID_TCP2_REPLY_ERROR,   //TCP链路2回复消息错误
    MSG_ID_TCP3_REPLY_ERROR,   //TCP链路3回复消息错误
    MSG_ID_TCP4_REPLY_ERROR,   //TCP链路4回复消息错误
    MSG_ID_OPEN_SPOTCHECK_LINK,  //开启抽样检测链路
    MSG_ID_HUMAN_DISCONNECT,
    MSG_ID_HUMAN_CONNECT,
    MSG_ID_HUMAN_NOALARM,
    MSG_ID_HUMAN_ALARM,
    MSG_ID_REBOOT,              // 用于重启linux 系统.

    MSG_ID_NETWORK_MAINT_CONNECT,
    MSG_ID_LINK_0_LOGGED,
    MSG_ID_LINK_1_LOGGED,
    MSG_ID_LINK_2_LOGGED,
    MSG_ID_LINK_3_LOGGED,
    MSG_ID_LINK_4_LOGGED,
    MSG_ID_TD_CLIENT_STATUS_CHANGE1,
    MSG_ID_TD_CLIENT_STATUS_CHANGE2,
    MSG_ID_TD_CLIENT_STATUS_CHANGE3,
    MSG_ID_TD_CLIENT_STATUS_CHANGE4,
    MSG_ID_TD_CLIENT_SET_PARAM,
    MSG_ID_SET_POWERON_TIME_STATUE,
    MSG_ID_TIMER_WAKEUP,
    MSG_ID_LPM_WAKEUP
} MSG_ID_EN;

typedef struct msgNode
{
	int		msgId;
	int		msgLen;
	char *	msgBuf;
    
	struct msgNode * next;
    
} MSG_NODE;


// 专门用来发送指令型的数据
typedef struct _MsgCmd_
{
	unsigned int 	cmd;            // 指令
	unsigned int 	dataLen;        // 数据长度, 信令线程会用到,例如如果是转发指令,那么会指出转发数据的长度
	unsigned short	index;            // 当给信令线程发送指令的时候,指出对象是哪个用户
	char	    	unused[2];        // 对齐
	char             *pData;            // 该指令对应的数据
} MSG_CMD_T;

class CMessage
{
public:
	CMessage();
    ~CMessage();    
	int Send( int msgId, char* msgBuf, int msgLen );    
	int Recv( int msgId, char* msgBuf, int msgLen );
	bool Find( int msgId );

private:
	MSG_NODE *m_Node[MAX_NODE];
	ClMutexLock m_Mutex[MAX_MUTEX];
	void FreeNode( MSG_NODE* pNode );
	int GetNodeIndex( int msgId );
	int GetMutexIndex( int msgId );
};

int MessageSend( int nMsgId, char* pMsgBuf = NULL, int nMsgLen = 0 );
int MessageRecv( int nMsgId, char* pMsgBuf = NULL, int nMsgLen = 0 );
bool MessageFind( int nMsgId );

#endif 

