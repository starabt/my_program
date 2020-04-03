/*******************************************************************************
    Copyright (C), 2016,Guang Zhou Tongda auto electric Co., Ltd.
    File name:      monitor_process.cpp
    Author:         Tony gao
    Version:        1.0
    Date:           2018/03/28
    Description:    用来监测运行程序的内存内容
    History:
        Date            Author          Version       Modification
*******************************************************************************/
#include "monitor_process.h"

//func list
int creat_shemp(size_t  shm_size) ;
int get_infos_address(struct sys_infos_t **infos_addr);
void *deal_preview_thread_func(void*);
void deal_preview_func();
void deal_baseinfo();
void deal_spiinfo();
//definition
char share_mem_name[] ="/tmp/tmpshare";
pthread_t preview_thread;
COND_MUTEX preview_cond_mutex;


bool stop_deal_preview_func=false;
bool whileflag = true;
char preview_cmd = 0;

int creat_shemp(size_t  shm_size) 
{
	key_t info_key;
	int info_id;
	/*creat share memory of configure*/
	info_key = ftok("/tmp/tmpshare", 'X');
	info_id = shmget(info_key, shm_size, IPC_CREAT|IPC_EXCL|0660);
	if(-1 == info_id)
	{
		printf("error \n");
		if(17 == errno)
		{
			info_id = shmget(info_key, 0, IPC_EXCL|0660);
			shmctl(info_id, IPC_RMID, NULL);
		}
		info_id = shmget(info_key, sizeof(struct sys_infos_t), IPC_CREAT|IPC_EXCL|0660);
		if(-1 == info_id)
		{
			printf("<APP/SYS_INFOS>Create share memory fail!(%d)\n", errno);
			return -1;;
		}
	}
	else
	{
		printf("create success\n");
		return 0;
	}
	return 0;
}

int get_infos_address(struct sys_infos_t **infos_addr)
{
	key_t conf_key;
	int conf_id;

	// if(NULL == infos_addr)
	// 	return -1;
	/*creat share memory of configure*/
	conf_key = ftok(share_mem_name, 'X');
	conf_id = shmget(conf_key, 0, 0);
	if(-1 == conf_id)
	{
		printf("<APP/CHECK>Get share memory fail!(%s)\n", strerror(errno));
		return -1;
	}

	*infos_addr = (struct sys_infos_t *)shmat(conf_id, NULL, 0);
	if((struct sys_infos_t *)(-1) == (*infos_addr))
	{
		printf("<APP/CHECK>can not get memory address!(%s)\n", strerror(errno));
		return -1;	
	}
	return 0;
}

void *deal_preview_thread_func(void*)
{
	unsigned long timeout_ms = 0;	
	while(!stop_deal_preview_func)
	{
		switch(preview_cmd)
		{
			case BASE_INFO_CMD:
				timeout_ms = 1000;
				break;
			case NET_INFO_CMD:
			case SPI_INFO_CMD:
				timeout_ms = 100;
				break;	
			default:
				timeout_ms = 1000;
				break;
		}
		pthread_mutex_lock(&preview_cond_mutex.cond_lock);
		timespec timeout;
	    timeval now;
	    gettimeofday(&now, NULL);
	    gettimeofday(&now, NULL);
	    long nsec = now.tv_usec * 1000 + (timeout_ms % 1000) * 1000000;
	    timeout.tv_sec=now.tv_sec + nsec / 1000000000 + timeout_ms / 1000;
	    timeout.tv_nsec=nsec % 1000000000;
		pthread_cond_timedwait(&preview_cond_mutex.cond,&preview_cond_mutex.cond_lock,&timeout);
		deal_preview_func();
		pthread_mutex_unlock(&preview_cond_mutex.cond_lock);

		usleep(10*1000);
	}
	return NULL;
}
void deal_preview_func()
{
	switch(preview_cmd)
	{
		case ALOW_SHARE_CMD:
			l_system_infos->ALOW_SHARE_MEM=!l_system_infos->ALOW_SHARE_MEM;
			printf("l_system_infos->ALOW_SHARE_MEM:%d\n",l_system_infos->ALOW_SHARE_MEM );
			break;
		case BASE_INFO_CMD:
			deal_baseinfo();
			break;
		case SPI_INFO_CMD:
			deal_spiinfo();
			break;
		default:
			printf("unknown cmd...:%c\n",preview_cmd);
			break;
	}
	return;
}
void deal_baseinfo()
{
	printf("\n***************************************************************************************\n\n");
	printf("\n 时间：%04d-%02d-%02d %02d:%02d:%02d\t",l_system_infos->base_info.system_time[0]+2000,\
        l_system_infos->base_info.system_time[1],l_system_infos->base_info.system_time[2],l_system_infos->base_info.system_time[3],\
        l_system_infos->base_info.system_time[4],l_system_infos->base_info.system_time[5]);
	printf("网络状态:%s\t",(l_system_infos->base_info.connet_status?"连接":"断开"));
	if(l_system_infos->base_info.login_status)
	{
		printf("在线时间: %.2f min\t", l_system_infos->base_info.online_time);
		printf("登录状态：登录\n");
	}
	else
	{
		printf("掉线时间: %.2f min\t", l_system_infos->base_info.outline_time);
		printf("登录状态：未登录\n");
	}
	if(!l_system_infos->base_info.SIM_status)
    {
        printf("\nSIM卡号:0\t");
        printf("SIM卡:未检测到\t");  
		printf("3G信号:0   ");
    }
    else
    {
        printf("\nSIM卡号:%s\t",l_system_infos->base_info.ICCID);
        printf("SIM卡:检测到\t");
        printf("3G信号:%d    ",l_system_infos->base_info.DCEsignal);
    }
    printf("GPS卫星数量:%d\n\n",l_system_infos->base_info.gps_num);
    printf("服务器[%d] ip:%s\t",l_system_infos->base_info.clientnum,l_system_infos->base_info.serverIP);
    printf("port:%s\n\n",l_system_infos->base_info.serverPort);
    printf("软件版本: %s \t",l_system_infos->base_info.software_version);
	printf("硬件版本: %s \n\n",l_system_infos->base_info.hardware_version);
	printf("终端编号：%s\t",l_system_infos->base_info.terminalID);  
	printf("车架号：%s\n",l_system_infos->base_info.vin);
	printf("\nACC状态：%d\t",l_system_infos->base_info.acc_on);
	printf("充电状态：%d\n",l_system_infos->base_info.charge_on);
	printf("\n电压值：%f v\t\n",l_system_infos->base_info.voltage);
	printf("\n***************************************************************************************\n\n");
	return ;
}
void deal_spiinfo()
{
	static unsigned char bcc_send = 0x00;
	static unsigned char bcc_recv = 0x00;
	printf("bcc_send:%02x,%02x\n",bcc_send, l_system_infos->spi_info.spi_senddata[l_system_infos->spi_info.spi_sendlen-1]);
	if(bcc_send!=l_system_infos->spi_info.spi_senddata[l_system_infos->spi_info.spi_sendlen-1])
	{
		bcc_send =l_system_infos->spi_info.spi_senddata[l_system_infos->spi_info.spi_sendlen-1];
		printf("\nspi send msg: ");
	    {
	        for (int i = 0; i<l_system_infos->spi_info.spi_sendlen; i++) 
	        {
	            printf("%02X ",l_system_infos->spi_info.spi_senddata[i]);
	        }
	    }
	}
		
	if(bcc_recv!=l_system_infos->spi_info.spi_recvdata[l_system_infos->spi_info.spi_recvlen-1])
	{
		bcc_recv =l_system_infos->spi_info.spi_recvdata[l_system_infos->spi_info.spi_recvlen-1];
		printf("\nspi recv msg: ");
	    {
	        for (int i = 0; i<l_system_infos->spi_info.spi_recvlen; i++) 
	        {
	            printf("%02X ",l_system_infos->spi_info.spi_recvdata[i]);
	        }
	    }
	}

	return;
}
int main()
{
	#if 0
	int ret=creat_shemp(sizeof(struct sys_infos_t));
	key_t info_key;
	int info_id;
	struct sys_infos_t *l_system_infos=NULL;

	info_key = ftok("/tmp/tmpshare", 'X');
	info_id = shmget(info_key, 0, 0);
	if(info_id!=-1)
	{
		l_system_infos = (struct sys_infos_t *)shmat(info_id, NULL, 0);
		if((struct sys_infos_t *)(-1) == l_system_infos)
		{
			printf("Cat not get memory address!(%s)\n", strerror(errno));
			l_system_infos=NULL;
		}
	}
	#endif
	get_infos_address(&l_system_infos);
	if(l_system_infos != NULL)
	{
		pthread_create(&preview_thread,NULL,deal_preview_thread_func,NULL);
		pthread_detach(preview_thread);
		int ret=0,nread=0;
		char ch = 0;
		static char pre_ch = 0;
		fd_set inputs,allfds;
		struct timeval timeout;
		FD_ZERO(&inputs);
		FD_SET(0,&inputs);
		 
		while(whileflag)
		{
			printf("please choose preview mode, press 'q' to exit this program.\n"); 
		    printf("\t0) enter 0 to choose share data or not\n");
		    printf("\t1) preview base info \n");
		    printf("\t2) preview net info \n");
		    printf("\t3) preview spi info \n");
		    printf("\tq) quit\n");

			allfds = inputs;
			timeout.tv_sec =10;
			timeout.tv_usec = 500*1000;
			ret = select(FD_SETSIZE,&allfds,NULL,NULL,&timeout);
			switch(ret)
			{
				case 0:
					printf("timeout......\n");
					break;
				case -1:
					perror("select");
					break;
				default:
					if(FD_ISSET(0,&allfds))
					{
						// if(read(0,&ch,1)>0)
						if((ch = getchar())>0)
						{
							printf("read  from keyboard:%c\n",  ch);
							pre_ch = ch;
							if(ch != QUIT_CMD)
							{
								pthread_mutex_lock(&preview_cond_mutex.cond_lock);
					    		preview_cmd = pre_ch;
					    		pthread_cond_signal(&preview_cond_mutex.cond);
						    	pthread_mutex_unlock(&preview_cond_mutex.cond_lock);
							}
							else
							{
								whileflag=false;
								break;
							}
								
						}
						#if 0
						ioctl(0,FIONREAD,&nread);
						if(nread == 0)
						{
							printf("keyboard done\n" );
							continue;
						}
						else if(nread>0)
						{
							nread=read(0,&ch,1);
							printf("read  from keyboard:%c\n",  ch);
							pre_ch = ch;
						}
						else
						{
							perror("ioctl");
							exit(-1);
						}
						#endif
							
					}
					break;
			}
		}
	}

	return 0;
}
