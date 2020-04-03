#include <stdio.h>
#include <string.h>
#include "debug.h"
//#include "rand.h"
#include "malloc.h"
#include "md5.h"
//#include "timer.h"
//#include "message.h"
//#include "public.h"
#include "paramConfig.h"
//#include "vencParamEasy.h"
//#include "dcpInsLocal.h"
#include "const.h"
#include "confFile.h"
#include "mutex.h"
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

static CMutexLock g_MutexConfig;
static SYS_CONFIG g_sysConfig;

bool GetHostByName(char *hostIP,char *hostPort,int tcp_num)
{
    char domain[50];
    memset(domain,0,sizeof(domain));
    struct hostent *ht = NULL;
    char   **pptr;
    char   str[32];
    int resolve_flag=0;      

    switch(tcp_num)
    {
        case 0:
               memcpy(domain,PARAM_CONFIG_DEFAULT_DOMAIN_1,sizeof(PARAM_CONFIG_DEFAULT_DOMAIN_1)-1);
               memset(domain+sizeof(PARAM_CONFIG_DEFAULT_DOMAIN_1)-1,0,sizeof(domain)-(sizeof(PARAM_CONFIG_DEFAULT_DOMAIN_1)-1));
               memcpy(hostPort,PARAM_CONFIG_DEFAULT_DOMAIN_PORT_1,sizeof(PARAM_CONFIG_DEFAULT_DOMAIN_PORT_1)-1);
               memset(hostPort+sizeof(PARAM_CONFIG_DEFAULT_DOMAIN_PORT_1)-1,0,strlen(hostPort)-(sizeof(PARAM_CONFIG_DEFAULT_DOMAIN_PORT_1)-1));
               break;

        case 1:
               memcpy(domain,PARAM_CONFIG_DEFAULT_DOMAIN_2,sizeof(PARAM_CONFIG_DEFAULT_DOMAIN_2)-1);
               memset(domain+sizeof(PARAM_CONFIG_DEFAULT_DOMAIN_2)-1,0,sizeof(domain)-(sizeof(PARAM_CONFIG_DEFAULT_DOMAIN_2)-1));
               memcpy(hostPort,PARAM_CONFIG_DEFAULT_DOMAIN_PORT_2,sizeof(PARAM_CONFIG_DEFAULT_DOMAIN_PORT_2)-1);
               memset(hostPort+sizeof(PARAM_CONFIG_DEFAULT_DOMAIN_PORT_2)-1,0,strlen(hostPort)-(sizeof(PARAM_CONFIG_DEFAULT_DOMAIN_PORT_2)-1));
               break;

        case 2:
               memcpy(domain,PARAM_CONFIG_DEFAULT_DOMAIN_3,sizeof(PARAM_CONFIG_DEFAULT_DOMAIN_3)-1);
               memset(domain+sizeof(PARAM_CONFIG_DEFAULT_DOMAIN_3)-1,0,sizeof(domain)-(sizeof(PARAM_CONFIG_DEFAULT_DOMAIN_3)-1));
               memcpy(hostPort,PARAM_CONFIG_DEFAULT_DOMAIN_PORT_3,sizeof(PARAM_CONFIG_DEFAULT_DOMAIN_PORT_3)-1);
               memset(hostPort+sizeof(PARAM_CONFIG_DEFAULT_DOMAIN_PORT_3)-1,0,strlen(hostPort)-(sizeof(PARAM_CONFIG_DEFAULT_DOMAIN_PORT_3)-1));
               break;

        default:
            break;
    }

    for(int i=0;i<3;i++)
    {
        ht = gethostbyname(domain);
        if(ht != NULL)
        {
            printf("链路%d 域名：%s 第%d次解析成功\n",tcp_num+1,domain,1+i);
            for(pptr = ht->h_aliases; *pptr != NULL; pptr++)
                printf(" alias:%s\n",*pptr);

            pptr=ht->h_addr_list;
            for(; *pptr!=NULL; pptr++)
                printf(" address:%s\n",inet_ntop(ht->h_addrtype, *pptr, str, sizeof(str)));

            printf(" first address: %s\n",inet_ntop(ht->h_addrtype, ht->h_addr, str, sizeof(str)));
            sprintf(hostIP,"%s",inet_ntop(ht->h_addrtype, ht->h_addr, str, sizeof(str)));
            resolve_flag=1;
            break;
        }
        else
        {
            printf("链路%d 域名：%s 第%d次解析失败\n",tcp_num+1,domain,i+1);
            resolve_flag=0;
        }
    }

    if(resolve_flag==1)
        return true;
    else   
        return false;
}

static void SysConfigInitHead( PARAM_CONFIG_HEAD *pHead)
{
    if( NULL !=  pHead )
    {
        memset( pHead, 0x00, sizeof(*pHead) );
        memcpy( pHead->signature, PARAM_CONFIG_SIGNATURE, sizeof(pHead->signature) );
    }
    return;
}

static void SysConfigInitBaseInfo( PARAM_CONFIG_BASE_INFO *pBaseInfo )
{
    if( NULL != pBaseInfo )
    {
        memset( pBaseInfo, 0x00, sizeof(*pBaseInfo) );
        strncpy( pBaseInfo->devModel, DEV_MODEL, sizeof(pBaseInfo->devModel) - 1 );
        strncpy( pBaseInfo->hardwareVersion, DEV_HARDWARE_VERSION, sizeof(pBaseInfo->hardwareVersion) - 1 );
        // strncpy( pBaseInfo->softwareVersion, DEV_SOFTWARE_VERSION, sizeof(pBaseInfo->softwareVersion) - 1 );
        strncpy( pBaseInfo->configureVersion, DEV_CONFIG_VERSION, sizeof(pBaseInfo->configureVersion) - 1 );
        strncpy( pBaseInfo->devName, DEV_NAME, sizeof(pBaseInfo->devName) - 1 );
    }
    return;
}

static void SysConfigInitNetWork( PARAM_CONFIG_NETWORK *pNetwork )
{
    if( NULL != pNetwork )
    {
        memset( pNetwork, 0x00, sizeof(*pNetwork) * MAX_CONFIG_MONITOR_CENTER);
        pNetwork->centerTotalNum = PARAM_CONFIG_DEFAULT_CENTER_TOTAL_NUM;
        
        strncpy( pNetwork->centerip,PARAM_CONFIG_DEFAULT_MONITOR_IP1, sizeof(pNetwork->centerip) - 1 );
        strncpy( pNetwork->connectPort,PARAM_CONFIG_DEFAULT_MONITOR_PORT1, sizeof(pNetwork->connectPort) - 1 );
        // strncpy( pNetwork->uploadprotocoltype,UPLOAD_PROTOCOL_TYPE1, sizeof(pNetwork->uploadprotocoltype) - 1 );
        pNetwork->uploadprotocoltype=UPLOAD_PROTOCOL_TYPE1;
        pNetwork->centerNum = 1;
        pNetwork->link_status=0;
        pNetwork++;

        strncpy( pNetwork->centerip,PARAM_CONFIG_DEFAULT_MONITOR_IP2, sizeof(pNetwork->centerip) - 1 );
        strncpy( pNetwork->connectPort,PARAM_CONFIG_DEFAULT_MONITOR_PORT2, sizeof(pNetwork->connectPort) - 1 );
        // strncpy( pNetwork->uploadprotocoltype,UPLOAD_PROTOCOL_TYPE2, sizeof(pNetwork->uploadprotocoltype) - 1 );
        pNetwork->uploadprotocoltype=UPLOAD_PROTOCOL_TYPE2;
        pNetwork->centerNum = 2; 
        pNetwork->link_status=0;  
        pNetwork++;  

        strncpy( pNetwork->centerip,PARAM_CONFIG_DEFAULT_MONITOR_IP3, sizeof(pNetwork->centerip) - 1 );
        strncpy( pNetwork->connectPort,PARAM_CONFIG_DEFAULT_MONITOR_PORT3, sizeof(pNetwork->connectPort) - 1 );
        // strncpy( pNetwork->uploadprotocoltype,UPLOAD_PROTOCOL_TYPE3, sizeof(pNetwork->uploadprotocoltype) - 1 );
        pNetwork->uploadprotocoltype=UPLOAD_PROTOCOL_TYPE3;
        pNetwork->centerNum = 3;  
        pNetwork->link_status=0;
        pNetwork++; 

        strncpy( pNetwork->centerip,PARAM_CONFIG_DEFAULT_MONITOR_IP4, sizeof(pNetwork->centerip) - 1 );
        strncpy( pNetwork->connectPort,PARAM_CONFIG_DEFAULT_MONITOR_PORT4, sizeof(pNetwork->connectPort) - 1 );
        // strncpy( pNetwork->uploadprotocoltype,UPLOAD_PROTOCOL_TYPE4, sizeof(pNetwork->uploadprotocoltype) - 1 );
        pNetwork->uploadprotocoltype=UPLOAD_PROTOCOL_TYPE4;
        pNetwork->centerNum = 4;
        pNetwork->link_status=0;  
        pNetwork++;    

        strncpy( pNetwork->centerip,PARAM_CONFIG_DEFAULT_MONITOR_IP5, sizeof(pNetwork->centerip) - 1 );
        strncpy( pNetwork->connectPort,PARAM_CONFIG_DEFAULT_MONITOR_PORT5, sizeof(pNetwork->connectPort) - 1 );
        pNetwork->uploadprotocoltype=UPLOAD_PROTOCOL_TYPE5;
        pNetwork->centerNum = 5;  
        pNetwork->link_status=0;
        pNetwork++;  
    }
    return;
}

static void SysConfigInitCarInfo( PARAM_CONFIG_CAR_INFO *pCarInfo )
{
    //维保中，恢复出厂设置终端编号(如果有的话)与车架号一致；无终端编号的话为空
    #if 0
    if( NULL != pCarInfo )
    {
        char tempID[21];
        char buf[256];
        bzero(buf,256);
        sprintf(buf,"/APP/AppFile/.terminalID");            
        memset(tempID,0,sizeof(tempID));

        memset( pCarInfo, 0x00, sizeof(*pCarInfo) );

        //读终端编号文件
        int ret=ReadFile(buf,tempID,sizeof(tempID)-1);

        if((ret>0 && tempID[0] ==0) || ret==-1)//终端号文件不存在       
        {
            // strncpy( pCarInfo->devserialNo,'\0', sizeof(pCarInfo->devserialNo) - 1 );
            strncpy( pCarInfo->vin, PARAM_CONFIG_DEFAULT_DEV_VIN, sizeof(pCarInfo->vin) - 1 );  
            pCarInfo->vin[17]='\0';
        }
        else if(ret>0)
        {
            printf("terminalID has exist!\n");
            strncpy( pCarInfo->devserialNo,tempID, 13 );
            pCarInfo->devserialNo[20]='\0';
            strncpy( pCarInfo->vin, tempID, 13 );
            // pCarInfo->vin[17]='\0';
        }

        strncpy( pCarInfo->userinfo,USER_INFO, sizeof(pCarInfo->userinfo) - 1 );
    }
    #endif


    #if 1
    if( NULL != pCarInfo )
    {
        memset( pCarInfo, 0x00, sizeof(*pCarInfo) );
        // strncpy( pCarInfo->devserialNo, PARAM_CONFIG_DEFAULT_DEV_SERIAL_NUM, sizeof(pCarInfo->devserialNo) - 1 );
        // pCarInfo->devserialNo[20]='\0';
        strncpy( pCarInfo->vin, PARAM_CONFIG_DEFAULT_DEV_VIN, sizeof(pCarInfo->vin) - 1 );  
        pCarInfo->vin[17]='\0';
        strncpy( pCarInfo->userinfo,USER_INFO, sizeof(pCarInfo->userinfo) - 1 );
    }
    #endif

    return;
}

static void SysConfigInitCan( PARAM_CONFIG_CAN *pcan )
{
    int i=0;
    if( NULL != pcan )
    {
        memset( pcan, 0x00, sizeof(*pcan)* MAX_CONFIG_CAN_NUM);
        unsigned char can_count = PARAM_CONFIG_DEFAULT_CAN_TOTAL_NUM;
        pcan->cantotalnum = can_count;
        pcan->baudRate=DEV_DEFAULT_CAN_BAUDRATE1;

        strncpy( pcan->candevname,CAN_DEFAULT_CAN_DEVNAME0, sizeof(pcan->candevname) - 1 );
        pcan->candevname[sizeof(pcan->candevname)-1]= '\0';
        strncpy( pcan->cancollectprotocoltype,CAN_COLLECT_PROTOCOL_TYPE0, sizeof( pcan->cancollectprotocoltype) - 1 );
        pcan->canPort =i++;
        
        pcan++;
        pcan->cantotalnum = can_count;
        pcan->baudRate=DEV_DEFAULT_CAN_BAUDRATE2;
        strncpy( pcan->candevname,CAN_DEFAULT_CAN_DEVNAME1, sizeof(pcan->candevname) - 1 );
        pcan->candevname[sizeof(pcan->candevname)-1]= '\0';
        strncpy( pcan->cancollectprotocoltype,CAN_COLLECT_PROTOCOL_TYPE1, sizeof( pcan->cancollectprotocoltype) - 1 );
        pcan->canPort =i++;

        pcan++;
        pcan->cantotalnum = can_count;
        pcan->baudRate=DEV_DEFAULT_CAN_BAUDRATE3;
        strncpy( pcan->candevname,CAN_DEFAULT_CAN_DEVNAME2, sizeof(pcan->candevname) - 1 );
        pcan->candevname[sizeof(pcan->candevname)-1]= '\0';
        strncpy( pcan->cancollectprotocoltype,CAN_COLLECT_PROTOCOL_TYPE2, sizeof( pcan->cancollectprotocoltype) - 1 );
        pcan->canPort =i;
    }
    return;
}

static void SysConfigInitFtp(  PARAM_CONFIG_FTP *pftp )
{
    if( NULL != pftp )
    {
        memset( pftp, 0x00, sizeof(*pftp) );
        pftp->enable = PARAM_CONFIG_DEFAULT_FTP_ENABLE;
        pftp->port = PARAM_CONFIG_DEFAULT_FTP_PORT;
        
        strncpy(pftp->ip,PARAM_CONFIG_DEFAULT_FTP_IP, sizeof(pftp->ip) - 1 );
        strncpy(pftp->user,PARAM_CONFIG_DEFAULT_FTP_USER, sizeof(pftp->user) - 1 );
        strncpy(pftp->passwd,PARAM_CONFIG_DEFAULT_FTP_PASSWD, sizeof(pftp->passwd) - 1 );
   
    }
    return;
}

static void SysConfigInitCycletime(  PARAM_CONFIG_CYCLE_TIME *pcycletime )
{
    if( NULL != pcycletime )
    {
        memset( pcycletime, 0x00, sizeof(*pcycletime) );
        pcycletime->local_save_time_cycle = PARAM_CONFIG_DEFAULT_LOCAL_SAVE_TIME;
        pcycletime->rtmsg_upload_cycle = PARAM_CONFIG_DEFAULT_RTMSG_UPLOAD_TIME;
        pcycletime->alarmmsg_upload_cycle = PARAM_CONFIG_DEFAULT_ALARM_UPLOAD_TIME;
        pcycletime->heartbeat_upload_cycle = PARAM_CONFIG_DEFAULT_HEARTBEAT_TIME;
        pcycletime->c_reply_overtime = PARAM_CONFIG_DEFAULT_C_REPLY_OVERTIME;
        pcycletime->s_reply_overtime = PARAM_CONFIG_DEFAULT_S_REPLY_OVERTIME;
        pcycletime->login_interval_after3times = PARAM_CONFIG_DEFAULT_LOGIN_INTERVAL_TIME;
    }
    return;
}

/*
* SYS_CONFIG每添加一个成员都要修改下面两个函数
*/
PARAM_CONFIG_STORE_HEAD g_storeHead;
static void SysConfigInitStoreHead( PARAM_CONFIG_STORE_HEAD *pStoreHead )
{
    if( NULL != pStoreHead )
    {
        memcpy(pStoreHead->mark, PARAM_CONFIG_MARK, 16);
        pStoreHead->size            = sizeof(g_sysConfig);
        pStoreHead->totalMembers     = INDEX_PARAM_CONFIG_TOTAL;

        pStoreHead->memberSize[INDEX_PARAM_CONFIG_HEAD]
                                = sizeof(g_sysConfig.head);
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_BASE_INFO]
                                = sizeof(g_sysConfig.baseInfo);
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_NETWORK]
                                = sizeof(g_sysConfig.network);
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_CAR_INFO]
                                = sizeof(g_sysConfig.carinfo);
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_CAN]
                                = sizeof(g_sysConfig.can);

        pStoreHead->memberSize[INDEX_PARAM_CONFIG_FTP]
                                = sizeof(g_sysConfig.ftp);
        pStoreHead->memberSize[INDEX_PARAM_CYCLE_TIME]
                                = sizeof(g_sysConfig.cycletime);

    }
    return;
}

//恢复默认配置
void SysConfigpRestoreDefaultParam()
{
    g_MutexConfig.Lock();
    SysConfigInitCarInfo(&g_sysConfig.carinfo);
    SysConfigInitCan(g_sysConfig.can);
    SysConfigInitFtp(&g_sysConfig.ftp);
    SysConfigInitCycletime(&g_sysConfig.cycletime);

    g_MutexConfig.Unlock();
    return;
}


// 恢复包含网络在内的基本参数
static void SysConfigRestoreFactoryConfNeed()
{
    g_MutexConfig.Lock();
    SysConfigInitStoreHead( &g_storeHead );
    SysConfigInitHead( &g_sysConfig.head );
    SysConfigInitBaseInfo( &g_sysConfig.baseInfo);
    SysConfigInitNetWork( g_sysConfig.network);

    g_MutexConfig.Unlock();
    return;
}

// 恢复出网络以外的基本参数
static void SysConfigRestoreFactoryConfNeedNoNet()
{
    g_MutexConfig.Lock();

    SysConfigInitStoreHead( &g_storeHead );
    SysConfigInitHead( &g_sysConfig.head );
    SysConfigInitBaseInfo( &g_sysConfig.baseInfo);

    g_MutexConfig.Unlock();
    return;
}

//恢复出厂配置，恢复包含网络的参数为出厂配置
void SysConfigRestoreFactoryConf()
{
    SysConfigRestoreFactoryConfNeed();
    SysConfigpRestoreDefaultParam();
    return;
}

//恢复出厂配置，恢复除网络参数以外的参数为出厂配置
void SysConfigSetDefaultParam()
{
    SysConfigRestoreFactoryConfNeedNoNet();
    SysConfigpRestoreDefaultParam();
    return;
}

static char *g_pMemberAddr[PARAM_CONFIG_MAX_MEMBERS];
void SysConfigInitMemberAddr()
{
    g_pMemberAddr[INDEX_PARAM_CONFIG_HEAD]                  = (char *)&g_sysConfig.head;
    g_pMemberAddr[INDEX_PARAM_CONFIG_BASE_INFO]             = (char *)&g_sysConfig.baseInfo;
    g_pMemberAddr[INDEX_PARAM_CONFIG_NETWORK]               = (char *)g_sysConfig.network;
    g_pMemberAddr[INDEX_PARAM_CONFIG_CAR_INFO]           = (char *)&g_sysConfig.carinfo;
    g_pMemberAddr[INDEX_PARAM_CONFIG_CAN]   = (char *)g_sysConfig.can;

    g_pMemberAddr[INDEX_PARAM_CONFIG_FTP]          = (char *)&g_sysConfig.ftp;
    g_pMemberAddr[INDEX_PARAM_CYCLE_TIME]          = (char *)&g_sysConfig.cycletime;
    return;
}

static int checkconfigMd5( PARAM_CONFIG_STORE_HEAD storeHead, char *pBuf, int bufLen )
{
    int ret = FI_FAIL;
    char key[16];
    int configLen = sizeof(storeHead) + storeHead.size;

    if(configLen + MD5_KEY_SIZE <= bufLen)
    {
        ret = Md5GenerateKey( (unsigned char *)pBuf, (unsigned int)configLen, (unsigned char *)key );
        if(FI_SUCCESS == ret)
        {
            if(0 != memcmp( pBuf + configLen, key, MD5_KEY_SIZE))
            {
                ERRORPRINT("check MD5 failed!\r\n");
                PrintHex("flash MD5 :", (unsigned char*)(pBuf + configLen), MD5_KEY_SIZE, "\r\n" );
                PrintHex("gen MD5   :", (unsigned char*)key, MD5_KEY_SIZE, "\r\n" );
                ret = FI_FAIL;
            }
        }
    }

    return ret;
}

//读取配置文件到g_sysConfig结构体
static int GetSysConfigStruct( char *pBuf, int bufLen )
{
    uint    i;
    int ret = FI_FAIL;
    int offset, copySize;
    PARAM_CONFIG_STORE_HEAD storeHead;
    memset(&storeHead,0,sizeof(storeHead) );
    memcpy( &storeHead, pBuf, sizeof(storeHead) );

    //printf( "#########storeHead.mark(%s)!\r\n", storeHead.mark );

    if( 0 != memcmp(PARAM_CONFIG_MARK, storeHead.mark, strlen(PARAM_CONFIG_MARK)) ) // 没有这个可能导致checkconfigMd5()段错误
    {
        ERRORPRINT( "Param Mark wrong, use default param!\r\n" );
        ERRORPRINT("!!!!config file str is:%s\n",storeHead.mark);
        return FI_FAILED;
    }

    ret = checkconfigMd5( storeHead, pBuf, bufLen );
    SVPrint( "checkconfigMd5 ret(%d), totalMembers(%d)!\r\n", ret, storeHead.totalMembers );
    if( FI_SUCCESS == ret && storeHead.totalMembers <= PARAM_CONFIG_MAX_MEMBERS)
    {
        offset = sizeof(storeHead);
        for(i = 0; i < storeHead.totalMembers; i++)
        {
            if( offset + storeHead.memberSize[i] < bufLen )
            {
                copySize = g_storeHead.memberSize[i] < storeHead.memberSize[i]? g_storeHead.memberSize[i] : storeHead.memberSize[i];

                memcpy(g_pMemberAddr[i], pBuf + offset, copySize);
                offset += storeHead.memberSize[i];
            }
        }
        ret = FI_SUCCESS;
    }

    return ret;
}


// 初始化系统配置
void InitParamConfig()
{
    int ret;
    char *pBuf = NULL;
    SysConfigInitMemberAddr();
    SysConfigRestoreFactoryConf();

#if 1
    pBuf = (char *)Malloc( MAX_PARAM_CONFIG_SIZE );
    if(NULL != pBuf)
    {
        ret = ReadConfig( pBuf, MAX_PARAM_CONFIG_SIZE );
        if(FI_SUCCESS == ret)
        {
            ret = GetSysConfigStruct( pBuf, MAX_PARAM_CONFIG_SIZE );
            if(FI_SUCCESS != ret)
            {
                printf("Get sys config from config partition failed, to read backup!\r\n");
            }
        }
        if( FI_SUCCESS != ret)
        {
            printf("####read config file error!\n#####\n");
        }
        if( 0 != ret )  //这种情况一般是没有配置文件导致
        {
            SaveParamConfig();//生成配置文件
        }
        Free(pBuf);
    }
#endif  
    return;
}


//把配置保存到配置文件
int SaveParamConfig()
{
    int ret = -1;
    int configLen = sizeof(g_storeHead) + sizeof(g_sysConfig);
    int bufLen =  configLen + MD5_KEY_SIZE;
    char *pBuf = (char *)Malloc( bufLen );
    if ( NULL == pBuf ) return ret;
    g_MutexConfig.Lock();
    memcpy( pBuf, &g_storeHead, sizeof(g_storeHead) );
    memcpy( pBuf + sizeof(g_storeHead), &g_sysConfig, sizeof(g_sysConfig) );
    ret = Md5GenerateKey( (unsigned char *)pBuf, (unsigned int)configLen,
                            (unsigned char *)pBuf + configLen );
    if(FI_SUCCESS == ret) ret = WriteConfig( pBuf, bufLen );
    //if(FI_SUCCESS == ret) ret = WriteConfigBackup( pBuf, bufLen );
    // system("sync");

    g_MutexConfig.Unlock();
    Free( pBuf );

    // system("sync");
    return ret;
}


/*
* 获取系统配置
* index : 参见SYS_CONFIG里面的INDEX_ 宏
  pBuf  : buf,out
  len   : 获取的长度
  n     : 如果SYS_CONFIG的某个成员是个数组, n表示数组的第几个成员
*/
int GetParamConfig( int index, void *pBuf, int len, int n)
{
    int ret;
    char *pGetBuf;

    if( NULL == pBuf || len <= 0 || len > (int)sizeof(g_sysConfig) )
    {
        SVPrint("NULL == pBuf || len <= 0 || len > sizeof(g_sysConfig)\r\n");
        return FI_FAIL;
    }

    g_MutexConfig.Lock();
    ret = FI_SUCCESS;
    pGetBuf = NULL;
    switch( index )
    {
    case INDEX_PARAM_CONFIG_HEAD:
        pGetBuf = (char *)&g_sysConfig.head;
        break;
    case INDEX_PARAM_CONFIG_BASE_INFO:
        pGetBuf = (char *)&g_sysConfig.baseInfo;
        break;
    case INDEX_PARAM_CONFIG_NETWORK:
        if( n >= 0 && n < MAX_CONFIG_MONITOR_CENTER )
            pGetBuf = (char *)&g_sysConfig.network[n];
        else    ret = FI_FAIL;
        break;
    case INDEX_PARAM_CONFIG_CAR_INFO:
            pGetBuf = (char *)&g_sysConfig.carinfo;
        break;
    case INDEX_PARAM_CONFIG_CAN:
        if( n >= 0 && n < MAX_CONFIG_CAN_NUM ) 
            pGetBuf = (char *)&g_sysConfig.can[n];
        else    ret = FI_FAIL;
        break;

    case INDEX_PARAM_CONFIG_FTP:
            pGetBuf = (char *)&g_sysConfig.ftp;
        break;

    case INDEX_PARAM_CYCLE_TIME:
            pGetBuf = (char *)&g_sysConfig.cycletime;
        break;
    
    default:
        SVPrint("GetParamConfig failed:index(%d)!\r\n",index);
        ret = FI_FAIL;
        break;
    } // end switch
    if(NULL != pGetBuf && FI_SUCCESS == ret)
    {
        memcpy( pBuf, pGetBuf, len );
    }
    g_MutexConfig.Unlock();

    return ret;
}

/*
* 设置系统配置
* index : 参见SYS_CONFIG里面的INDEX_ 宏
  pBuf  : buf,out
  len   : 获取的长度
  n     : 如果SYS_CONFIG的某个成员是个数组, n表示数组的第几个成员
*/
int SetParamConfig( int index, void *pBuf, int len, int n)
{
    int ret=0;
    char *pSetAddr;

    if( NULL ==pBuf || len <= 0 || len > (int)sizeof(g_sysConfig) )
    {
        SVPrint("NULL == pBuf || len <= 0 || len > sizeof(g_sysConfig)\r\n");
        return FI_FAIL;
    }

    g_MutexConfig.Lock();
    ret = FI_SUCCESS;
    pSetAddr = NULL;
    switch( index )
    {
    case INDEX_PARAM_CONFIG_HEAD:
        pSetAddr = (char *)&g_sysConfig.head;
        break;
    case INDEX_PARAM_CONFIG_BASE_INFO:
        pSetAddr = (char *)&g_sysConfig.baseInfo;
        break;
    case INDEX_PARAM_CONFIG_NETWORK:
        if( n >= 0 && n < MAX_CONFIG_MONITOR_CENTER )
            pSetAddr = (char *)&g_sysConfig.network[n];
        else    ret = FI_FAIL;
        break;
    case INDEX_PARAM_CONFIG_CAR_INFO:
           pSetAddr = (char *)&g_sysConfig.carinfo;
        break;
    case INDEX_PARAM_CONFIG_CAN:
        if( n >= 0 && n < MAX_CONFIG_CAN_NUM ) 
            pSetAddr = (char *)&g_sysConfig.can[n];
        else    ret = FI_FAIL;
        break;

    case INDEX_PARAM_CONFIG_FTP:
        pSetAddr = (char *)&g_sysConfig.ftp;
        break;
        
    case INDEX_PARAM_CYCLE_TIME:
        pSetAddr = (char *)&g_sysConfig.cycletime;
        break;
    default:
        SVPrint("GetParamConfig failed:index(%d)!\r\n", index);
        ret = FI_FAIL;
        break;
    }
    if(NULL != pSetAddr && FI_SUCCESS == ret)
    {
        memcpy(pSetAddr, pBuf, len);
    }
    g_MutexConfig.Unlock();

    ret=SaveParamConfig();
    return ret;
}