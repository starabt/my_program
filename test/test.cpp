
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#define NDEBUG 1
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/wait.h>
#include <stdarg.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <dirent.h>
#include <deque>
#include <sstream>
// #include <hash_map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <thread> 
#include <queue>
using namespace std;

typedef enum 
{
	SUCCESS_NO_ALIAS = 		0,//升级成功，没有别名文件替换
	PACK_ERR = 				1,//升级包路径错误
	CHECK_ERR = 			2,//升级包校验错误
	PACK_HEAD_ERR = 		3,//升级包包头错误
	SAVE_FILE_ERR = 		4,//将升级包中的文件保存到本地错误
	BIN_FALG_NO_FIT = 		5,//校验升级包包头升级类型不匹配
	MOUNT_ERR = 			6,//mount备份区错误
	ROMFS_ERR = 			7,//内核区错误
	TYPE_UNKNOWN = 			8,//升级类型未定义
	REPLACE_FILE_ERR = 		9,//生成别名文件替换名单错误
	APP_FAIL_LAST = 		10,//升级内核时前次升级APP失败
	KERNEL_FAIL_LAST = 		11,//升级APP时前次内核升级失败
	MKDIR_ERR = 			12,//创建文件夹错误且不是因为已存在
	VER_PATH_ERR = 			13,//软件版本号文件错误
	WRITE_VER_ERR = 		14,//写软件版本号文件错误
	VERSION_ERR = 			15,//软件版本号校验错误
	SUCCESS_WITH_ALIAS = 	20,//升级成功，有别名文件替换
}UPGRADE_STATUS;
int enum_ret()
{

	printf("now is to exit enum_ret\n");
	return SUCCESS_NO_ALIAS;
}
void printa()
{
	printf("hello world\n");
	exit(EXIT_SUCCESS);
}
int large_num = 0;
int small_num = 0;
int greatest_divisor = 0;
int get_greatest_divisor(int a,int b)
{
	
	if(a%b != 0)
	{
		get_greatest_divisor(b,a%b);
	}
	else
		return b;
	
}
int test_goto(int a)
{
	int i = 0;
	for(i=0;i<5;i++)
	{
		if(i>a)
			goto err_goto;
		printf("%d ",i );
	}
err_goto:
	printf("end is %d ",i );
	return i;
}
typedef enum
{
	HELLO = 0,
}hello_enum;
enum hello_enum2 
{
	HELLO2 = 1,
};
typedef struct 
{
	char name[10];
	int age;
}HUMAN;
int write_human_msg(HUMAN *human_msg,unsigned int len)
{
	FILE *fp = fopen("./human_msg","wb+");
	if(fp == NULL)
	{
		perror("open file");
		return -1;
	}
	int ret = fwrite((char*)human_msg,1,len,fp);
	if(ret <= 0)
	{
		perror("write file");

	}
	fclose(fp);
	return ret;
}
int read_human_msg(HUMAN *human_msg,unsigned int len)
{
	FILE *fp = fopen("./human_msg","rb+");
	if(fp == NULL)
	{
		perror("read open file");
		return -1;
	}
	int ret = fread((char*)human_msg,1,len,fp);
	if(ret <= 0)
	{
		perror("read file");
	}
	fclose(fp);
	return ret;
}
typedef struct
{
    double  latitude;   /**<   Latitude.*/
    double  longitude;  /**<   Longitude.*/
    float   accuracy;   /**<   Accuracy.*/
}QL_LOC_INJECT_LOCATION_INTO_T;

int write_inject_loc_info(QL_LOC_INJECT_LOCATION_INTO_T *inject_loc_info,unsigned int len)
{
    FILE *fp = fopen("./inject_loc_info","wb+");
    if(fp == NULL)
    {
        perror("open file");
        return -1;
    }
    char* tempbuf =(char*) malloc(len);
    if(tempbuf == NULL)
    {
        perror("malloc ");
        return -1;
    }
    memset(tempbuf,0,len);
    memcpy(tempbuf,inject_loc_info,len);
    int ret = fwrite(tempbuf,1,len,fp);
    if(ret <= 0)
    {
        perror("write file");

    }
    free(tempbuf);
    fclose(fp);
    return ret;
}
int read_inject_loc_info(QL_LOC_INJECT_LOCATION_INTO_T *inject_loc_info,unsigned int len)
{
    FILE *fp = fopen("./inject_loc_info","rb+");
    if(fp == NULL)
    {
        perror("read open file");
        return -1;
    }
    char* tempbuf =(char*) malloc(len);
    if(tempbuf == NULL)
    {
        perror("malloc ");
        return -1;
    }
    memset(tempbuf,0,len);
    int ret = fread(tempbuf,1,len,fp);
    if(ret <= 0)
    {
        perror("read file");
    }
    memcpy(inject_loc_info,tempbuf,len);
    free(tempbuf);
    fclose(fp);
    return ret;
}

void test_NULL(int *age,void* struc=NULL)
{
	if(struc == NULL)
	{
		printf("struc is NULL.....\n");
		return;
	}
	if(age == NULL)
	{
		printf("NULL...........\n");
		return ;
	}
	else
	{
		printf("age:%d\n",*age );
		return;
	}
}
#define DELIVER 1

#define SHARE_STRING 1
#define SHARE_SINGLE 0
template  <typename SHARETYPE> 
static void share_write(char type,SHARETYPE* monitor_msg,SHARETYPE* msg,void *struct_p=NULL,int monitor_msglen=0,int msglen=0)
{

    if(struct_p == NULL)
    {
    	printf("the struct put in is NULL.........\n");
    	return;
    }
    
    switch(type)
    {
        case SHARE_SINGLE:
            *monitor_msg = *msg;
            printf("monitor_msg:%d\n", *monitor_msg);
            break;
        case SHARE_STRING:
            memset(monitor_msg,0,monitor_msglen);
            memcpy(monitor_msg,msg,msglen);
            printf("monitor_msg:%s\n", monitor_msg);
            break;
        default:
            break;
    }
    return;
}
unsigned long long getn(int n)
{
	unsigned long long sum = 1;
	for(int i=1;i<=n;i++)
	{
		sum *= i;
		// printf("%d\n",sum );
	}
	// printf("getn sum:%ld\n",sum );
	return sum;
}
unsigned long long getn_reurrence(int n)
{
	if(n>0)
	{
		return n*getn_reurrence(n-1);
	}
	else
		return 1;
}

#define TEST_FUNC(fmt...) \
do \
{ \
	test_func(__FUNCTION__,__LINE__,fmt);\
}while(0)
void test_func(const char* func,int line,const char * fmt,...)
{
	printf("func:%s,line:%d\n",func,line );
}
// void test_func2()
// {
// 	test_func();
// }
template <class T> 
class CAL
{
public:
	CAL(){}
	virtual ~CAL(){}
public:
	T add(T a,T b)
	{
		return a+b;
	}
	T sub(T a,T b)
	{
		return a-b;
	}
	T mul(T a,T b)
	{
		return a*b;
	}
	T div(T a,T b)
	{
		return a/b;
	}
};

using namespace std;

int quote_num  = 1;
const int & test_quote()
{
	return quote_num;
}
int geti(int i)
{
	printf("i:%d\n",i );
	return i;
}

// char *srcs ="55AA0456415433303030363034303106021533060113061C1211310704F7BAE8184C44390000069003E32CE1000711CD7803E32CE10C02C80D008003E32CE18100D21ED0820233060113061C12113B0704F7BAE0184C44390000069003E32CE10007110AD703E32CE10C02BC0D008003E32CE18100D25C2F820233060113061C1212090704F7BAE0184C44390000069003E32CE1000711487303E32CE10C02BC0D008003E32CE18100D299CB820233060113061C1212130704F7BAD9184C441C0000069003E32CE100071185C303E32CE10C02C80D008003E32CE18100D2D71B820233060113061C12121D0704F7BAD9184C441C0000069003E32CE1000711C30403E32CE10C02BC0D008003E32CE18100D3145C820233060113061C1212270704F7BAD9184C441C0000069003E32CE1000711FF9903E32CE10C02AF0D008003E32CE18100D350F1820233060113061C1212310704F7BAD9184C441C0000069003E32CE10007113CB403E32CE10C02BC0D008003E32CE18100D38E0C820233060113061C12123B0704F7BA66184C4503000005A003E32CE9000719A18F03E32CE90C03DB0D068003E32CE98100D3F2E7820133060113061C1213090704F7BD0B184C44C900020CE403E32D02000732B45D03E32D020C07080D268003E32D028100D505B5820133060113061C1213130704F7C5A6184C428900040D3403E32D130007433F0D03E32D130C04D50D328003E32D138100D59065820133060113061C12131D0704F7E17E184C3D7900040DB603E32D430007738D9703E32D430C04580D288003E32D438100D5DEEF820133060113061C1213270704F7ED31184C3CCC0002000003E32DA80007D8FBFC03E32DA80C060E0D1C8003E32DA88100D64D54820133060113061C1213310704F7F6E5184C3C7600010E0603E32DFB00082B4FE003E32DFB0C041A0D0C8003E32DFB8100D6A138820133060113061C12133B0704F7F8AB184C3C3C00000DE803E32E04000834950703E32E040C028A0D008003E32E048100D6E65F820233060113061C1214090704F7F8C0184C3C3C00000DE803E32E04000834CC2003E32E040C02BC0D008003E32E048100D71D78820233060113061C1214130704F7F8C8184C3C5900000DE803E32E0400083404B303E32E040C02A30D008003E32E048100D7560B820233060113061C12141D0704F7F8C8184C3C5900000DE803E32E040008343DD503E32E040C02AF0D008003E32E048100D78F2D820233060113061C1214270704F7F8C8184C3C7600000DE803E32E040008347E0503E32E040C03130D028003E32E048100D7CF5D820133060113061C1214310704F7FA3E184C3C5900000DE803E32E0D00083DCF3103E32E0D0C02960D008003E32E0D8100D82089820233060113061C1214310704F7FA3E184C3C5900000DE803E32E0D00083DCF3103E32E0D0C02960D008003E32E0D8100D82089820233060113061C1214310704F7FA3E184C3C5900000DE803E32E0D00083DCF3103E32E0D0C02960D008003E32E0D8100D820898202";
char *srcs =NULL;
void StrToHex(unsigned char *pbDest, unsigned char *pbSrc, int nLen)
{
    char h1,h2;
    unsigned char s1,s2;
    int i;
    for (i=0; i<nLen; i++)
    {
      h1 = pbSrc[2*i];
      h2 = pbSrc[2*i+1];
      s1 = toupper(h1) - 0x30;
      if (s1 > 9) 
      s1 -= 7;
      s2 = toupper(h2) - 0x30;
      if (s2 > 9) 
      s2 -= 7;
      pbDest[i] = s1*16 + s2;
    }
}
unsigned char Crc(char* src, int len)
{
	unsigned char tbl[] =
	{
	    0x3B, 0x26, 0x01, 0x1C, 0x4F, 0x52, 0x75, 0x68, 0xD3, 0xCE, 0xE9, 0xF4, 0xA7, 0xBA, 0x9D, 0x80,
	    0xF6, 0xEB, 0xCC, 0xD1, 0x82, 0x9F, 0xB8, 0xA5, 0x1E, 0x03, 0x24, 0x39, 0x6A, 0x77, 0x50, 0x4D,
	    0xBC, 0xA1, 0x86, 0x9B, 0xC8, 0xD5, 0xF2, 0xEF, 0x54, 0x49, 0x6E, 0x73, 0x20, 0x3D, 0x1A, 0x07,
	    0x71, 0x6C, 0x4B, 0x56, 0x05, 0x18, 0x3F, 0x22, 0x99, 0x84, 0xA3, 0xBE, 0xED, 0xF0, 0xD7, 0xCA,
	    0x28, 0x35, 0x12, 0x0F, 0x5C, 0x41, 0x66, 0x7B, 0xC0, 0xDD, 0xFA, 0xE7, 0xB4, 0xA9, 0x8E, 0x93,
	    0xE5, 0xF8, 0xDF, 0xC2, 0x91, 0x8C, 0xAB, 0xB6, 0x0D, 0x10, 0x37, 0x2A, 0x79, 0x64, 0x43, 0x5E,
	    0xAF, 0xB2, 0x95, 0x88, 0xDB, 0xC6, 0xE1, 0xFC, 0x47, 0x5A, 0x7D, 0x60, 0x33, 0x2E, 0x09, 0x14,
	    0x62, 0x7F, 0x58, 0x45, 0x16, 0x0B, 0x2C, 0x31, 0x8A, 0x97, 0xB0, 0xAD, 0xFE, 0xE3, 0xC4, 0xD9,
	    0x1D, 0x00, 0x27, 0x3A, 0x69, 0x74, 0x53, 0x4E, 0xF5, 0xE8, 0xCF, 0xD2, 0x81, 0x9C, 0xBB, 0xA6,
	    0xD0, 0xCD, 0xEA, 0xF7, 0xA4, 0xB9, 0x9E, 0x83, 0x38, 0x25, 0x02, 0x1F, 0x4C, 0x51, 0x76, 0x6B,
	    0x9A, 0x87, 0xA0, 0xBD, 0xEE, 0xF3, 0xD4, 0xC9, 0x72, 0x6F, 0x48, 0x55, 0x06, 0x1B, 0x3C, 0x21,
	    0x57, 0x4A, 0x6D, 0x70, 0x23, 0x3E, 0x19, 0x04, 0xBF, 0xA2, 0x85, 0x98, 0xCB, 0xD6, 0xF1, 0xEC,
	    0x0E, 0x13, 0x34, 0x29, 0x7A, 0x67, 0x40, 0x5D, 0xE6, 0xFB, 0xDC, 0xC1, 0x92, 0x8F, 0xA8, 0xB5,
	    0xC3, 0xDE, 0xF9, 0xE4, 0xB7, 0xAA, 0x8D, 0x90, 0x2B, 0x36, 0x11, 0x0C, 0x5F, 0x42, 0x65, 0x78,
	    0x89, 0x94, 0xB3, 0xAE, 0xFD, 0xE0, 0xC7, 0xDA, 0x61, 0x7C, 0x5B, 0x46, 0x15, 0x08, 0x2F, 0x32,
	    0x44, 0x59, 0x7E, 0x63, 0x30, 0x2D, 0x0A, 0x17, 0xAC, 0xB1, 0x96, 0x8B, 0xD8, 0xC5, 0xE2, 0xFF
	};

	unsigned  char crc = 0;
	unsigned char tmp = 0;
	for (int i = 0; i < len; i++)
	{
		tmp =crc ^ src[i];
	    crc = tbl[tmp];
	}
	return crc;
}
class A
{
public:
	A(int num1){printf("into 1 :%d\n",num1 );}
	A(){printf("into zero\n");}
	A(int num1,int num2){printf("into 1 :%d,%d\n",num1,num2 );}
	int setnum()
	{
		return makenum();
	}
	int num;
private:
	int makenum()
	{
		printf("father.............\n");
		num = 1;
		return num;
	}
	
};
class B:public A
{
public:
	using A::setnum;
private:
	int makenum()
	{
		printf("son.............\n");
		num = 2;
		return num;
	}
	
};
unsigned char Cal_BCC_CheckSum(unsigned char *pData,size_t len)
{
    unsigned char uRet=0;
    for (size_t i=0;i<len;i++)
    {
        uRet^=pData[i];
    }
    return uRet;
}
void * tmp_thd(void*)
{
	printf("thread_pid:%ld\n",pthread_self() );
	for(int i = 0;i<5;i++)
	{
		printf("i:%d\n",i );
		sleep(1);
	}
	
	// int ret = 24;
	// pthread_exit(&ret);
	return NULL;
}
unsigned char* retHello()
{
	// unsigned char hello[] = "hello lxc";return hello;
	return NULL;
}
char* retHello2()
{
	char *hello = new char[10];
	strcpy(hello,"hello lxc");
	delete[] hello;
	return hello;
}
char* retHello3()
{
	char *hello = (char*)malloc(10); 
	strcpy(hello,"hello lxc");
	free(hello);
	return hello;
}
// #include "externCtest.h"
/*pthread_mutex_t call_back_mtx ;
pthread_cond_t call_back_cond ;
typedef void (*CALL_BACK_FUNC)(int);
void* call_back_thrd_func(void *call_back_func)
{
	CALL_BACK_FUNC callBackFunc = *call_back_func;
	pthread_
}*/

typedef struct 
{
	int a;
	int b;
}Son;
Son son1={1,2};
void func2(int *data,int datalen)
{
	char tmp[100]={0};
	memcpy(tmp,&son1,sizeof(son1));
	memcpy(tmp+4,data,datalen);
	
	memcpy(&son1,tmp,sizeof(tmp));
	// memcpy(&son1+1,data,datalen);
}
#define _CMD_LEN (256)

static int _system (char *cmd);


//extern int __libc_fork (void);
static int _system (char *command)
{
    int pid = 0;
    int status = 0;
    char *argv[4];
    extern char **environ;

    if (NULL == command) {
        return -1;
    }

    pid = vfork();        /* vfork() also works */
    if (pid < 0) {
        return -1;
    }

    if (0 == pid) {             /* child process */

        close(pid);
        // argv[0] = "sh";
        // argv[1] = "-c";
        argv[2] = command;
        argv[3] = NULL;

        execve ("/bin/sh", argv, environ);    /* execve() also an implementation of exec() */

        exit (127);
    }

    // else
    /* wait for child process to start */
    do
    {
        if (waitpid (pid, &status, 0) < 0) {
            if (errno != EINTR) {
                return status;
            }
            else {
                return status;
            }
        }
    } while (1);


    return 0;
}



int systemDeal(const char *format, ...)
{
    char cmdBuff[_CMD_LEN];
    va_list vaList;

    va_start (vaList, format);
    vsnprintf ((char *)cmdBuff, sizeof(cmdBuff), format, vaList);
    va_end (vaList);

    return _system ((char *)cmdBuff);
}
typedef struct 
{
	char a1;
	short a2;
	int a3;
	char a4;
} test_t;
int *p2=NULL;
void testp(int *p,int **pp,int a)
{
	printf("a add:%p\n",&a );
	printf("testp p before add:%p\n",p );
	printf("testp pp before add:%p\n",pp );
	printf("testp p2 before add:%p\n",p2 );
	p = &a;
	p2 = &a;
	printf("testp p after add:%p\n",p );
	printf("testp pp after add:%p\n",pp );
	printf("testp p2 after add:%p\n",p2 );
	return;
}
#include <string>
typedef struct 
{
	int age;
	string name;
}Human;
bool thrflag;
void thread_fun()
{
	printf("thread_fun thr:%ld\n",pthread_self() );
}
// void *thread_func1(void* val)
// {
// 	printf("enter anykey to exit this thread\n");
// 	getchar();
// 	pthread_cancel(pthread_self());
// 	perror("pthread_cancel");
// 	return NULL;
// }
#include <algorithm>
// template <typename T>
// vector<size_t> sort_indexes(const vector<T> &v) {

//     vector<size_t> idx(v.size());
//     for(int i=0;i<v.size();i++)
//     {
//       idx[i]=i;
//     }
//   //  // sort indexes based on comparing values in v
//     std::sort(idx.begin(), idx.end(),[&v](size_t i1, size_t i2) {return v[i1] < v[i2];});

//    return idx;

// }
#include <iostream>
#include <list>
#include <algorithm>  
 
#include <stdlib.h>
#include <string.h>
 
typedef struct info_s
{
	int nNumber;
	int value;
	bool operator==(struct info_s b) const  
   {  
	   return this->nNumber == b.nNumber;  
   }  
	
   bool operator!=(struct info_s b) const  
   {  
	   return this->nNumber != b.nNumber;  
   }  
	
   bool operator>=(struct info_s b) const  
   {  
	   return this->nNumber >= b.nNumber;  
   }  
   
   bool operator<=(struct info_s b) const  
   {  
	   return this->nNumber <= b.nNumber;  
   }  
 
	 bool operator>(struct info_s b) const  
	 {	
		 return this->nNumber > b.nNumber;  
	 }	
	 
	 bool operator<(struct info_s b) const  
	 {	
		 return this->nNumber < b.nNumber;  
	 }	
 
}info_t;
typedef std::list< info_t > list_t;
 
void append(list_t &List, info_t &info)
{
	std::cout<<"***append****"<<std::endl;
	List.push_back(info);
}
void find_one(list_t &List,info_t info )
{
 
	std::cout<<"find_one"<<std::endl;  
 
	list_t::iterator iter ;
 
	iter = std::find(List.begin(),List.end(), info);
 
	if(iter != List.end())
	{
		std::cout<<"find it"<<std::endl; 
	}
	else
	{
		std::cout<<"not find it"<<std::endl; 
	}
 
}

// void Sort(list_t & List)
// {
// 	std::cout<<"Sort it"<<std::endl; 
// 	List.sort();
// 	for_each(List);
// }
void for_each_delete(list_t &List)
{
	list_t::iterator iter;
	for(iter = List.begin(); iter != List.end() ;)
	{
		std::cout<< "delete before  iter->number:"<<iter->nNumber <<std::endl;
		iter =  List.erase(iter);
		std::cout<< "delete  after iter->number:"<< iter->nNumber <<std::endl;
	}
 
}
typedef struct _node_
{
	int id;
	int num;
}Node;
 
class findid
{
public:
	findid(int whatId):id(whatId){}
	bool operator()(Node inNode){return (inNode.id)==id;}
private:
	int id;
};
class AA
{
public:
	virtual void print()=0;

};
void AA::print()
{
	printf("this is A\n");
}
class BB:public AA{
public:
	void print()
	{
		printf("this is B\n");
	}
};
class CC:public AA{
	public:
	CC(int num =10)
	{
		c =num;
	}
	void print()
	{
		printf("this is C\n");
	}
	void printc()
	{
		printf("this is C:%d\n",c);
	}
private:
	int c;
};

int create_dir(const char *sPathName)
{
	char DirName[256];  
	strcpy(DirName, sPathName);  
	int i,len = strlen(DirName);
	for(i=1; i<len; i++)  
	{  
		if(DirName[i]=='/')  
		{  
			DirName[i] = 0; 
			if(access(DirName, F_OK)!=0)  
			{  
				if(mkdir(DirName, 0755)==-1)  
				{   
					printf("mkdir   error\n");   
					return -1;   
				}  
			}  
			DirName[i] = '/';  

		}  
	}  

	return 0;  
}
bool getFiles(std::string cate_dir,std::vector<std::string> &files,std::vector<std::string> &emptyDir)  
{  
     std:cout << "the file to scanf:" << cate_dir << std::endl; 
    bool ret = false;
    DIR *dir;  
    struct dirent *ptr;  

    if ((dir=opendir(cate_dir.c_str())) == NULL)  
    {  
        perror("Open dir error...");  
        return false;
    }  
    else
    {
        while ((ptr=readdir(dir)) != NULL)  
        {  
            if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir  
                    continue;  
            else if(ptr->d_type == 8) 
            {
            	// std::cout << ptr->d_name << std::endl;
                //printf("d_name:%s/%s\n",basePath,ptr->d_name);  
                files.push_back(cate_dir+'/'+ptr->d_name);
                ret = true;  
            } 
            else if(ptr->d_type == 4) 
            {
            	if(!getFiles(cate_dir+'/'+ptr->d_name,files,emptyDir))
            		emptyDir.push_back(cate_dir+'/'+ptr->d_name);
            }   
            else 
                continue; 
        }  
        closedir(dir); 
    }

    return ret;  
}
static const int NUM = 10;
class testNode
{
public:
	// testNode(){}
	explicit testNode(int a_):a(a_){}
	~testNode(){}
	void printa()
	{
		printf("%d:%s\n",a,symbol.c_str() );
	}
	void init(const string& symbol_)
	{
		symbol = symbol_;
	}
	int a;
	string symbol;
	// std::vector<testNode*> v;
};
/*class testNode2:public testNode
{
public:
	testNode2(){}
	~testNode2(){}
	int a;
	// std::vector<testNode*> v;
};*/
template <class T>
class tempClass
{
public:
	tempClass();
	~tempClass();
	T printT(const T& t)
	{
		t.printa();
	}

};
void get_time_str(time_t time,string &timeStr)
{
    char timeTmp[20]={0};
    struct tm localTime;
    localtime_r(&time,&localTime);
    snprintf(timeTmp,strlen("1970-01-01 00:00:00"),"%04d-%02d-%02d %02d:%02d:%02d",localTime.tm_year+1900,localTime.tm_mon,\
        localTime.tm_mday,localTime.tm_hour,localTime.tm_min,localTime.tm_sec);
    timeStr = timeTmp;
    // return timeTmp;
}
void get_fileTime(const char* path,string& mtime)
{
	struct stat buf;
    int result;
 
    //获得文件状态信息
 
    result =stat( path, &buf );
 
    //显示文件状态信息
 
   if( result != 0 )
       perror( "显示文件状态信息出错" );//并提示出错的原因，如No such file or directory（无此文件或索引）
 
    else
    {
 		struct tm localTime;
 		char time_str[20];
        printf("file:%s,文件大小: %ld\n",path, buf.st_size);
        // localtime_r(&buf.st_ctime,&localTime);

        // printf("文件创建时间: %s,%s", ctime(&buf.st_ctime),get_time_str(buf.st_ctime));
        // localtime_r(&buf.st_atime,&localTime);
        // printf("访问日期: %s,%s", ctime(&buf.st_atime),get_time_str(buf.st_atime));
        localtime_r(&buf.st_mtime,&localTime);
        memset(time_str,0,sizeof(time_str));
        get_time_str(buf.st_mtime,mtime);
        // mtime = time_str;
        printf("最后修改日期: %s,%s", ctime(&buf.st_mtime),mtime.c_str());
 
    }
}
int get_one(int N)
{
	if(N==0)
		return 0;
	if(N%2 == 0)
		return get_one(N/2);
	else
		return get_one(N/2)+1;
}
int getAddSum(int N)
{
	if(N==0)
		return 0;
	else
		return N+getAddSum(N-1);
}
int get_charsize(char str[100])
{
	// printf("str:%s\n",str );
	// printf("strlen:%d\n",strlen(str) );
	// printf("sizeof:%d\n",sizeof(str) );
	return sizeof(str);
}
int add(int a,int b)
{
	return a+b;
}
int add(int a)
{
	return a+add(1,1);
}

template<class T>
string straddx(const string& strsrc,T addx)
{
	string istr;
	std::stringstream ss;
	ss << strsrc << addx;
	ss >> istr;
	return istr;
}
#include <type_traits>
typedef struct TTYPE_
{
	int a;
}TTYPE;
template<class TYPE>
void checkType(TYPE type)
{
	if(is_same<TYPE,int>::value)
		cout << " It is int" <<endl;
	else if(is_same<TYPE,TTYPE>::value)
		cout << " It is TTYPE" <<endl;
	else
		cout << "unknown type" <<endl;
	return;
}
static int statica = 1;
int& geta()
{
	return statica;
}
bool largeSorter(const char a,const char b)
{
	return a > b;
}
void elimDups(string & word)
{
	sort(word.begin(),word.end(),largeSorter);
	auto end_uni = unique(word.begin(),word.end());
	word.erase(end_uni,word.end());
}
static int swapcount = 0;
void swap(int &a,int &b)
{
	
	int tmp = a;
	a = b;
	b = tmp;
	return;
}
void sortM(int ary[],int len)
{
	for(int i=0;i<len;i++)
	{
		for(int j=i;j<len;j++)
		{
			swapcount++;
			if(ary[j]<ary[i])
				swap(ary[j],ary[i]);
		}
	}
}
void bubbleSort(int arr[], int bgn, int end)
{
    /*isLoop用于指示依次遍历中是否发生元素交换，若没有，则已是有序数列，退出即可*/
    bool isLoop = true;
    for (int i = end; i > bgn; --i)
    {
        isLoop = false;
        for (int j = bgn + 1; j < i; ++j)
        {
        	swapcount++;
            if (arr[j] < arr[j - 1])
            {
                swap(arr[j], arr[j - 1]);
                isLoop = true;
            }
        }
    }
}
bool threeSumOnce(vector<int>& nums,vector<vector<int>> &res,int i,int j,bool positive=true)
{
	vector<int> obj(3);
	if(!positive)
	{
		for(int k=j-1;nums[k]>0;k--)
		{
			if(nums[i]+nums[k]+nums[j] == 0)
	        {
	            obj[0] = nums[i];
	            obj[1] = nums[k];
	            obj[2] = nums[j];
	            if(find(res.begin(),res.end(),obj) == res.end())
	                res.push_back(obj);
	            return true;
	        }
		}
	}
	else
	{
		for(int m=i+1;nums[m]<0;m++)
		{
			if(nums[i]+nums[m]+nums[j] == 0)
            {
                obj[0] = nums[i];
                obj[1] = nums[m];
                obj[2] = nums[j];
                if(find(res.begin(),res.end(),obj) == res.end())
                    res.push_back(obj);
                return true;
            }
		}
	}
	return false;
		
}
vector<vector<int>> threeSum(vector<int>& nums) {
    int step = 1;
    printf("begin sort\n");
    sort(nums.begin(),nums.end());
    printf("finish sort\n");
    vector<vector<int>> res;
    vector<int> obj(3,0);
    int lastMaxIdx = nums.size()-1;
    int i=0;
    int j=nums.size()-1;
    if(j<2)
    	return res;
    char exist_zero = -1;
    while(nums[i]<=0 && nums[j]>=0 && j-i>=2)
    {
    	// printf("3 numi:%d,numj:%d\n",nums[i],nums[j] );
    	if(nums[j]+nums[i] <= 0 )
    	{
    		int tmpj = j;
    		while(nums[tmpj]+nums[tmpj-1]+nums[i]>=0)
    		{
    			for(int k=tmpj-1;k>=0 && nums[k]>=0;k--)
                {
                    if(nums[i]+nums[k]+nums[tmpj] == 0)
                    {
                        obj[0] = nums[i];
                        obj[1] = nums[k];
                        obj[2] = nums[tmpj];
                        if(find(res.begin(),res.end(),obj) == res.end())
                            res.push_back(obj);
                    }
                }
                if(nums[i]==nums[i+1]&& nums[i]==0)
                {
                    i++;
                    break;
                }
                while(nums[i]==nums[i+1])
                {
                    i++;
                }
                tmpj--;
    		}
    		i++;
    	}


    	else
    	{
    		int tmpi = i;
    		while(nums[tmpi]+nums[tmpi+1]+nums[j]<=0)
    		{
    			for(int m=tmpi+1;m<nums.size() && nums[m]<=0;m++)
                {
                    if(nums[tmpi]+nums[m]+nums[j] == 0)
                    {
                        obj[0] = nums[tmpi];
                        obj[1] = nums[m];
                        obj[2] = nums[j];
                        if(find(res.begin(),res.end(),obj) == res.end())
                            res.push_back(obj);
                        
                        continue;
                    }
                }
                if(nums[j]==nums[j-1]&& nums[j]==0)
                {
                    j++;
                    break;
                }
                while(nums[j]==nums[j-1])
                {
                    j--;
                }
                tmpi++;
    		}
    		j--;
    	}
    	
    		
    }
    return res;

}
string longestPalindrome(string s) {
    int wholeIdx=0;
    int size=s.size();
    int singleIdx=size-1;
    string res;
    int tmpStep = 0;
    bool get_res=true;
    int MaxLen=0;
    while(wholeIdx+MaxLen<size)
    {
        for(singleIdx=size-1;singleIdx>wholeIdx+MaxLen || singleIdx==0;singleIdx--)
        {
            for(tmpStep=0;tmpStep <= (singleIdx-wholeIdx)/2;tmpStep++)
            {
                if(s[wholeIdx+tmpStep]==s[singleIdx-tmpStep])
                {
                    get_res = true;
                    
                }
                else
                {
                	get_res = false;
                	break;
                }

            }
            if(get_res)
            {
                get_res=true;
                // res = s.substr(wholeIdx,singleIdx+1);
                res = string(s.begin()+wholeIdx,s.begin()+singleIdx+1);
                MaxLen = singleIdx-wholeIdx;
                break;
            }
        }
        wholeIdx++;
    }
    return res;
}
static int INT_MIN =(0-pow(2,31));
static int INT_MAX =(pow(2,31)-1);
int myAtoi(string str) {
    int idx = 0;
    bool negative = false;
    for(;idx<str.size();idx++)
    {
        if(str[idx]==' ')
        {
            idx++;
            continue;
        }
        
        else if((str[idx] == '-' || str[idx]=='+') )
        {
            if(idx == str.size()-1 || str[idx+1]<'0' || str[idx+1]>'9')
                return 0;
            if(str[idx] == '-')
            {
                negative = true;
                cout << "negative" << endl;
                
            }
            idx++;
            break;
            
        }
        else if(str[idx]>='0' && str[idx]<='9')
        {
            break;
        }
        else 
            return 0;
    }
    long tmpN = 0;
    int single =0;
    for(;idx<str.size();idx++)
    {
        if(str[idx]<'0' || str[idx]>'9')
            break;
        // cout << str[idx] << " ";
        single = str[idx]-'0';
        tmpN = (tmpN*10+single);
    }
    if(negative)
        tmpN = 0-tmpN;
    if(tmpN<INT_MIN)
        tmpN = INT_MIN;
    else if(tmpN > INT_MIN)
        tmpN = INT_MAX;
    return tmpN;
}
void sortStr(vector<string>& strs)
{
    sort(strs.begin(),strs.end(),[](const string& str1,const string& str2){return str1.size()<str2.size();});
}


bool checkValid(char c)
{
    if(c=='(' || c==')' || c=='[' || c==']' || c=='{' || c=='}')
        return true;
    return false;
}
std::map<char,char> flagMap;

bool isValid(string s) {
    int size = s.size();
    if(size<2 || size%2 != 0)
        return false;
    string tmpStr;
    
    size_t strLen = 0;
    for(int i=0;i<size;i++)
    {
    	printf("111111111\n");
        if(!checkValid(s[i]))
            return false;
        if(tmpStr.empty() || s[i] != flagMap[tmpStr[strLen-1]])
        {
        	printf("22222222222\n");
            tmpStr.push_back(s[i]);
            strLen++;
        }
        else 
        {
        	printf("3333333333333\n");
        	cout << "tmpStr before:" << tmpStr << endl;
            tmpStr.pop_back();
            cout << "tmpStr after:" << tmpStr << endl;
            strLen--;
        }
    }
    cout << "tmpStr:" << tmpStr << endl;
    if(tmpStr.empty())
        return true;
    return false;
}
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
ListNode* getSmallL(ListNode** pl1, ListNode** pl2)
{
    ListNode* tmpL=NULL;
    if((*pl1)->val <= (*pl2)->val)
    {
        tmpL = (*pl1);
        pl1 = &(*pl1)->next;
    }
    else{
        tmpL = (*pl2);
        pl2 = &(*pl2)->next;
    }
    return tmpL;
}
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    // if(l1==NULL && l2==NULL)
    //     return NULL;
    // else if(l1==NULL && l2!=NULL)
    //     return l2;
    // else if(l1!=NULL && l2==NULL)  
    //     return l1;
      
    ListNode resL=ListNode(0);
    ListNode *curL=&resL;
    
    while(l1!=NULL && l2!=NULL)
    {
        if(l1->val <= l2->val)
	    {
	        curL->next = l1;
	        curL=curL->next;
	        l1 = l1->next;
	    }
	    else
	    {
	    	curL->next = l2;
	    	curL=curL->next;
	        l2 = l2->next;
	    }
    }
    if(l1==NULL)
        curL->next=l2;
    else
        curL->next=l1;
    return resL.next;
}
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    if(l1==NULL && l2==NULL)
        return NULL;
    else if(l1!=NULL && l2==NULL)
        return l1;
    else if(l1==NULL && l2!=NULL)
        return l2;
    ListNode *resL=l1;
    ListNode *lastNode = l2;
    ListNode *curNode=resL;
    int up=0; 
    int sum = 0;
    bool touchEnd = false;
    while(l1!=NULL && l2!=NULL)
    {
        sum = l1->val + l2->val + up;
        
        curNode->val = sum%10;
        up = sum/10;
        if(curNode->next)
            curNode = curNode->next;
        else if(l2->next)
        {
        	curNode->next = l2->next;
            curNode = curNode->next;
            break;

        }
        else
        {
            touchEnd = true;
            if(up)
            {
            	lastNode->val = up;
                lastNode->next =NULL;
                curNode->next=lastNode;
                goto RETRUENRES;
            }
        }
        l1=l1->next;
        l2=l2->next;
    }
    if(curNode)
    {
        while(up)
        {
            if(curNode)
            {
                sum = curNode->val  + up;
                curNode->val = sum%10;
                up = sum/10;
                if(curNode->next)
                    curNode = curNode->next;
                else
                {
                    if(up)
                    {
                        lastNode->val = up;
                        lastNode->next =NULL;
                        curNode->next=lastNode;
                        break;
                    }
                }
            }
        }
    }
RETRUENRES:
    return resL;
}
void displayL(ListNode* l)
{
	while(l!=NULL)
	{
		cout << l->val << " ";
		l=l->next;
	}
	cout << endl;
}

int search(vector<int>& nums, int target) {
    int size = nums.size();
    if(size == 0 )
        return -1;
    
    int Hidx = size-1;
    int Lidx = 0;
    int midIdx = Lidx;
    bool bLeft = true;
    while(Hidx>=Lidx)
    {   
        midIdx = Lidx+(Hidx +1 - Lidx)/2;
        if(bLeft)
        {
        	printf("Lidx:%d,midIdx:%d\n",Lidx,midIdx );
            if(nums[Lidx]==target)
                return Lidx;
            else if(nums[Lidx] < target && \
            	(target <=nums[midIdx] || target > nums[Hidx]))
            {
                Hidx = midIdx;
                bLeft = false;
            }
            else 
            {
                Lidx = midIdx+1;
                bLeft = true;
            }
            printf("0  Lidx:%d,Hidx:%d,midIdx:%d\n",Lidx,Hidx,midIdx );
        }
        else
        {
        	printf("Hidx:%d,midIdx:%d\n",Hidx,midIdx );
            if(nums[Hidx]==target)
                return Hidx;
            else if(target <nums[Hidx]  && \
            	(target >= nums[midIdx] || nums[Lidx] >target))
            {
                Lidx = midIdx;
                bLeft = false;
            }
            else
            {
                Hidx = midIdx-1;
                bLeft = true;
            }
            printf("1  Lidx:%d,Hidx:%d,midIdx:%d\n",Lidx,Hidx,midIdx );
        }
    }
    return -1;
}
int ctoi(char c)
{
    return c-'0';
}
char itoc(int i)
{
    return i+'0';
}
string mulSingle(string num,char single,int idx)
{
	int size = num.size();
    string res(size+idx+1,'0');
    
    int up=0;
    int sum=0;
    int singleN = ctoi(single);
    for(int i=size-1;i>=0;i--)
    {
        sum = ctoi(num[i])*singleN+up;
        res[i+1] = itoc(sum%10);
        up=sum/10;
        // printf("singleN:%d,ctoi(num[i]):%d,sum:%d,i:%d,c:%c,up:%d\n",singleN,ctoi(num[i]),sum,sum%10,itoc(sum%10),up );
    }
    res[0]=itoc(up);
    return res;
}
string addStr(std::vector<string > &nums)
{
	int maxSize = nums[nums.size()-1].size();
	string res(maxSize+1,'0');
	cout << "res:" << res << endl;
	int sum = 0;
	int up = 0;
	
	for(int i=0;i<maxSize;i++)
	{
		for(int inum=0;inum<nums.size();inum++)
		{
			if(nums[inum].size()>i)
				sum+=ctoi(nums[inum][nums[inum].size()-i-1]);
			cout << "size:" << nums[inum].size()<<endl;
		}
		sum+=up;
		res[maxSize-i]=itoc(sum%10);
		up=sum/10;
		printf("sum:%d,i:%d,c:%c,up:%d,res:%s\n",sum,sum%10,itoc(sum%10),up,res.c_str() );
		sum=0;
		
	}
	res[0]=itoc(up);
	int j=0;
	while(res[j]=='0' && j!=res.size()-1)
		j++;
	return string(res.begin()+j,res.end());
	// return res;
}
string multiply(string num1, string num2) {
	string res;
    int size1 = num1.size();
    int size2 = num2.size();
    if(size1* size2 == 0)
        return res;
    std::vector<string > nums;
    for(int i=size1-1;i>=0;i--)
    {
    	nums.push_back(mulSingle(num2,num1[i],size1-i-1));
    }
    cout << "--------------------------" <<endl;
    for(auto it=nums.begin();it!=nums.end();it++)
    	cout<< *it << " ";
    cout << endl;
    return addStr(nums);
}

int strStr(string haystack, string needle) {
    int sizeh=haystack.size();
    int sizen=needle.size();
    if(sizen==0)
        return 0;
    if(sizeh < sizen)
        return -1;
    int resIdx=-1;
    bool get_needle=true;
    for(int i=0;i<sizeh-sizen+1;i++)
    {
        if(haystack[i]==needle[0])
        {
        	cout << "i:" << i << endl;
        	cout << "needle:" << needle << endl;
        	get_needle=true;
            for(int j=1;j<sizen;j++)
            {
            	cout << "needle[j]:" << needle[j] << endl;
            	cout << "j:" << j <<"needle[j]:" << needle[j] << "haystack[i+j]；" << haystack[i+j] << endl;
                if(needle[j]!=haystack[i+j])
                {
                    get_needle = false;
                    break;
                }
                
            }
            cout << "get_needle:" << get_needle << endl;
            if(get_needle)
            {
                resIdx=i;
                goto RETURN;
            }
        }
    }
RETURN:
    return resIdx;
}
int zhishu()
{
    long num;
    cin>>num;
    if(num <2)
    {
        cout << num << " ";
        return 0;
    }
        
    int i=2;
    do
    {
        while(num%i==0)
        {
            cout << i << " ";
            num /=i;
        }
        i++;
    }while(i!=num);
    cout << i << " ";
    return 0;
}
int getNearInt()
{
	float num;
    cin >> num;
    int a=num/1;
    int b=(num+0.5)/1;
    
    return a==b?a:b;
}
int combineTable()
{
	int cnt;
    cin >> cnt;
    map<int,int> table;
    int a,b;
    map<int,int>::iterator it;
    for(int i=0;i<cnt;i++)
    {
        scanf("%d%d",&a,&b);
        it=table.find(a);
        if(it==table.end())
        {
            table.insert(pair<int,int>(a,b));
        }
        else
        {
            it->second +=b;
        }
    }
    for(auto itable=table.begin();itable!=table.end();itable++)
    {
        cout << itable->first << " " << itable->second << endl;
    }
    return 0;
}
int uniqueInt()
{
	string intStr;
	cin >> intStr;
	string res;
	for(int i = intStr.size()-1;i>=0;i--)
	{
		if(find(res.begin(),res.end(),intStr[i])==res.end())
			res.push_back(intStr[i]);
	}
	cout << res.size() << endl;
	return 0;
}
int reverceLine()
{
	string line;
	getline(cin,line);
	size_t idx=0;
	while(1)
	{
		idx = line.find_last_of(' ');
		if(idx==string::npos)
		{
			cout << line ;
			break;
		}
		else
		{
			cout << string(line.begin()+idx+1,line.end()) << " ";
			line = string(line.begin(),line.begin()+idx);
		}
	}
	return 0;
}
int sortLine()
{
	int n,i=0;
	string str;
	vector<string> strs;
	while(cin>>str)
	{
		if(str[0]>='0' && str[0]<='9')
		{
			n=atoi(str.c_str());
			continue;
		}
		// cout << str << endl;
		// cout << "i:" << i << "n:" << n << endl;
		strs.push_back(str);
		i++;
		if(i>=n)
			break;
	}
	sort(strs.begin(),strs.end());
	for(auto it=strs.begin();it!=strs.end();it++)
	{
		cout << *it << endl;
	}
}
int atob()
{
	int num;
	int cnt=0;
	cin >> num;
	while(num!=0)
	{
		if(num%2!=0)
			cnt++;
		num /=2;
	}
	cout << cnt<< endl;
	return cnt;
}
class res
{
public:
	res(int v_,int p_,int idx_):v(v_),p(p_),idx(idx_)
	{}
	virtual ~res(){}
	int v;
	int p;
	int idx;
	int get_value(){
		return v*p;
	}
};
class mainres:public res
{
public:
	std::vector<res> subres;

};
#if 0
int buy()
{
	int N,m;
	scanf("%d%d%d",&N,&m);
	int v,p,q;
	vector<mainres> allres;
	int idx=1;
	for(int i=0;i<m;i++)
	{
		scanf("%d%d%d",&v,&p,&q);
		if(q==0)
		{
			mainres.push_back(mainres(v,p,idx));
			idx++;
		}
		else
		{
			mainres[q-1].subres.push_back(res(v,p,q));
		}

	}
	int max=0;
	for(int i=0;i<mainres.size();i++)
	{
		if()
	}
}
#endif
#if 1
int movePos()
{
	int x=0,y=0;
	string line;
	cin >> line;
	string cmd;
	size_t idx=0;
	size_t size = 0;
	int step=0;
	while(!line.empty())
	{
		idx = line.find_first_of(';');
		if(idx!=string::npos)
		{
			cmd=string(line.begin(),line.begin()+idx);
			line = string(line.begin()+idx+1,line.end());
			size=cmd.size();
			if(size<2 || size > 3)
				continue;
			for(int i=1;i<size;i++)
			{
				if(cmd[i]>='0' && cmd[i]<='9')
				{
					step = step*10+ctoi(cmd[i]);
				}
				else
				{
					step = 0;
					break;
				}
			}
			switch(cmd[0])
			{
				case 'A':
					x-=step;
					break;
				case 'S':
					y -= step;
					break;
				case 'W':
					y += step;
					break;
				case 'D':
					x += step;
					break;
				default:
				break;
			}
			step = 0;
		}
		else
			break;
	}
	cout << x << "," << y << endl;
	return 0;
}
int stoi(string& single,int len=-1)
{
	int num=0;
	int size=single.size();
	if(len!=-1)
		size = len;
	for(int i=0;i<size;i++)
	{
		if(single[i]<'0' || single[i]>'9')
			break;
		num=num*10+ctoi(single[i]);
	}
	return num;
}
bool checkone(string& single)
{
	int num=stoi(single);
	
	int cnt=0;
	while(num!=0)
	{
		if(num%2==0)
			return false;
		num /=2;
	}
	return true;
}
bool ipvalid(const string& ip,bool isip=true)
{
	// cout << "ip:" << ip << endl;
	int cnt=0;
	int idx1 = 0;
	int idx2 = 0;
	int tmpi=0;
	string single;
	bool bRet = true;
	for(int i=0;i<=ip.size();i++)
	{

		if(i==ip.size() || ip[i]=='.')
		{
			if(single.empty()  || stoi(single)>255)
				return false;
			else if(!isip)
			{
				if(single!="0" && !checkone(single))
					bRet = false;
			}
			single.erase(single.begin(),single.end());
		}
		else
		{
			single.push_back(ip[i]);
		}
	}
	return bRet;
}

void checkIP()
{
	string line;
	int Acnt=0;
	int Bcnt=0;
	int Ccnt=0;
	int Dcnt=0;
	int Ecnt=0;
	int Errcnt=0;
	int Pricnt=0;
	int idx = 0;
	string ip;
	int ipfirst=0;
	while(cin>>line)
	{
		idx=line.find('~');
		if(idx==string::npos)
			continue;
		ip=string(line.begin(),line.begin()+idx);
		if(ipvalid(ip))
		{
			ipfirst = stoi(ip,3);
			if(ip.compare(0,2,"10")==0 || ip.compare(0,6,"172.16")==0 || ip.compare(0,7,"192.168")==0)
				Pricnt++;
			if(ipfirst>=1 &&  ipfirst <= 126)
				Acnt++;
			else if(ipfirst>=128 &&  ipfirst <= 191)
				Bcnt++;
			else if(ipfirst>=192 &&  ipfirst <= 223)
				Ccnt++;
			else if(ipfirst>=224 &&  ipfirst <= 239)
				Dcnt++;
			else if(ipfirst>=240 &&  ipfirst <= 255)
				Ecnt++;
		}
		else
		{
			Errcnt++;
		}
		ip=string(line.begin()+idx+1,line.end());
		if(!ipvalid(ip,false))
			Errcnt++;
	}
	cout << Acnt << " " << Bcnt << " " << Ccnt << " "<< Dcnt << " "<< Ecnt << " "<< Errcnt << " "<< Pricnt << " "<<endl;
	return;
}
string stradd(string str)
{
	int num=atoi(str.c_str());
	num++;
	char tmpStr[128]={0};
	sprintf(tmpStr,"%d",num);
	return string(tmpStr);
}
void recordLog()
{
	string line;
	int idx1 = 0,idx2=0;
	string fileName;
	string log;
	
	string lineN;
	vector<string> logs(8);
	vector<int> cnts(8,0);
	vector<string>::iterator it;
	bool getNumChar=false;
	int logCnt=0;
	bool exist = false;
	while(getline(cin,line) && line.size()>2)
	{
		idx1 = line.find_last_of('\\');
		idx2 = line.find_first_of(' ');
		if(idx1 != string::npos || idx2 != string::npos)
		{
			fileName = string(line.begin()+idx1+1,line.begin()+idx2);
			if(fileName.size()>16)
				fileName = string(fileName.begin()+fileName.size()-16,fileName.end());
			line = string(line.begin()+idx2+1,line.end());
		}
		else
			continue;
		getNumChar=false;
		for(int i=0;i<line.size();i++)
		{
			
			if(line[i]>='0' && line[i] <='9')
			{
				lineN.push_back(line[i]);
				getNumChar=true;
			}
			else if(getNumChar)
				break;
		}
		log = fileName + " " + lineN;
		lineN.erase(lineN.begin(),lineN.end());

		exist=false;
		int idx = 0;
		for(;idx<logs.size();idx++)
		{
			// if(log.compare(0,log.size(),logs[idx])==0)
			if(log==logs[idx])
			{
				cnts[idx]++;
				
				exist = true;
				break;
			}
		}
		// it = find(logs.begin(),logs.end(),[log](string logi ){
		// 	return log==string(logi.begin(),logi.begin()+log.size());
		// });
		// if(it == logs.end())
		if(!exist)
		{
			cout << "logCnt0:" << logCnt << endl;
            cnts[logCnt%8]=1;
			logs[logCnt%8] = log;
			logCnt++;
            cout << "logCnt1:" << logCnt << endl;
		}
		// else
		// {
		// 	idx1=logs[idx].find_last_of(' ');
		// 	cnt=string(logs[idx].begin()+idx1+1,logs[idx].end());
		// 	logs[idx].erase(logs[idx].begin()+idx1+1);
		// 	cnt=stradd(cnt);
		// 	logs[idx]=logs[idx]+cnt;
		// }
		for(int i=0;i<logs.size();i++)
		{
	        if(cnts[i]!=0)
			    cout << logs[i] << " " <<cnts[i] <<endl;
		}
	}
	for(int i=0;i<logs.size();i++)
	{
        if(cnts[i]!=0)
		    cout << logs[i] << " " <<cnts[i] <<endl;
	}
	return;
}
vector<string> nums={"zero","one","two","three","four","five","six","seven","eight","nine","ten",\
				"eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
vector<string> ntens={"twenty","thirty","forty","fifty","sixty","seventy","eighty","ninty"};
vector<string> nns={"thousand","milion","bilion"};
int mulNum(int num,int mul)
{
	for(int i=0;i<mul;i++)
	{
		num *= 10;
	}
	return num;
}
string parseNum(long N)
{
	int i=0;
	long num=0;
	int single = N%10;
	vector<string> resTmp;
	string res;
	while(N>0)//>
	{
		single = N%10;
		N/=10;
		num+=mulNum(single,i%3);
		if(i%3==0)
		{
			if(i%9==0 && i>=9)
				resTmp.push_back("billion");
			else if(i%6==0 && i>=6)
				resTmp.push_back("million");
			else if(i%3==0 && i>=3)
				resTmp.push_back("thousand");
			// if(single!=0)
				resTmp.push_back(nums[single]);
		}
		else if(i%3==1)
		{
			if(single<=1)
			{
				// if(num%10!=0)
					resTmp.pop_back();
				resTmp.push_back(nums[num]);
			}
			else if(single>1)
			{
				if(num%10==0)
					resTmp.pop_back();
				resTmp.push_back(ntens[single-2]);
			}
		}
		else//2
		{	

			if(num%100!=0&& num>=100)
				resTmp.push_back("and");
			else if(resTmp[resTmp.size()-1]=="zero")
				resTmp.pop_back();
			if(single!=0)
			{
				resTmp.push_back("handred");
				resTmp.push_back(nums[single]);
			}
			num=0;
		}
		i++;
	}
	for(auto it=resTmp.rbegin();it!=resTmp.rend();it++)
		res = res +  *it + " ";
	return res;
}
class POS{
	
public:
	POS(int x_,int y_):x(x_),y(y_){}
	~POS(){}
	bool operator==(const POS& pos)
	{
		if(pos.x==this->x && pos.y==this->y)
			return true;
		return false;
	}
	int x;
	int y;
};
enum TURN
{
	TURNRIGHT=1,
	TURNUP=2,
	TURNLEFT=3,
	TURNDOWN=4,
	UNKNOWNTURN,
};
void get_back(vector<int> &xpos,vector<int> &ypos,int &x,int &y,int lastIdx)
{
	x=xpos[lastIdx];
	y=ypos[lastIdx];
	while(xpos.size()>lastIdx+1)
	{
		xpos.pop_back();
		ypos.pop_back();
	}
}
void runmaze(int Y,int X,vector<vector<int> >& maze,vector<int> &xpos,vector<int> &ypos)
{
	/*先往下走，再往右走，两个方向交替*/
	
	int x=0,y=0;
	bool xturn=true,yturn=true;
	TURN turn=UNKNOWNTURN;
	int lastXpos=x;
	int lastYpos=y;
	int lastIdx=0;
	TURN lastTurn=UNKNOWNTURN;
	int idx=0;
	xpos.push_back(x);
	ypos.push_back(y);
	idx++;
	if(x+1<X && maze[y][x+1] == 0)
		turn=TURNRIGHT;
	if(y+1<Y && maze[y+1][x] == 0)
	{
		if(turn==UNKNOWNTURN)
			turn=TURNUP;
		lastTurn=TURNUP;
		lastXpos=x;
		lastYpos=y;
		lastIdx=idx;
	}
	while((x!=X-1 || y !=Y-1) && idx<=X*Y )
	{
		switch(turn)
		{
			case TURNRIGHT:
				
			case TURNLEFT:
				if(turn==TURNRIGHT)
					x++;
				else
					x--;
				turn=UNKNOWNTURN;
				if(y+1<Y && maze[y+1][x] == 0)//向上
					turn=TURNUP;
				if(x+1<X && maze[y][x+1] == 0)//向右
				{
					if(turn==UNKNOWNTURN)
						turn=TURNRIGHT;
					lastTurn=TURNRIGHT;
					lastXpos=x;
					lastYpos=y;
					lastIdx=idx;
				}
				if(turn==UNKNOWNTURN)//向上向右都不行
				{
					if(x-1>=0 && maze[y][x-1] == 0)//向左
						turn = TURNLEFT;
					else//向左不行回到上一个点
					{
						get_back(xpos,ypos,x,y,lastIdx);
						idx=lastIdx;
						turn=lastTurn;
						continue;
					}
				}
				break;
			case TURNUP:
			case TURNDOWN:
				if(turn==TURNUP)
					y++;
				else
					y--;
				turn=UNKNOWNTURN;
				if(x+1<X && maze[y][x+1] == 0)//向右
					turn=TURNRIGHT;
				if(y+1<Y && maze[y+1][x] == 0)//向上
				{
					if(turn==UNKNOWNTURN)
						turn=TURNUP;
					lastTurn=TURNUP;
					lastXpos=x;
					lastYpos=y;
					lastIdx=idx;
				}
				if(turn==UNKNOWNTURN)
				{
					if(y-1>=0 && maze[y-1][x] == 0)//向下
						turn = TURNDOWN;
					else
					{
						get_back(xpos,ypos,x,y,lastIdx);
						idx=lastIdx;
						turn=lastTurn;
						continue;
					}
				}
				break;
		}
		xpos.push_back(x);
		ypos.push_back(y);
		idx++;

	}
}
/*void Sudoku(vector<int> ary,vector<int> xary,vector<int> yary)
{
	for(int i=0;i<)
}*/
// template<class KEY,class VALUE>
bool paircmp(const pair<char, int>& a, const pair<char, int>& b) {
	return a.second > b.second;
}
int get_max_beauty(string name)
{
	map<char,int> cCnts;
	map<char,int>::iterator it; 
	for(int i=0;i<name.size();i++)
	{
		it = cCnts.find(name[i]);
		if(it==cCnts.end())
		{
			cCnts.insert(pair<char,int>(name[i],1));
		}
		else
		{
			it->second ++;
		}
	}
	// sort(cCnts.begin(),cCnts.end(),paircmp);
	vector<pair<int, int>> vec(cCnts.begin(),cCnts.end());
	sort(vec.begin(),vec.end(),paircmp);
	int Beauty=26;
	int MaxBeauty = 0;
	for(int i=0;i<vec.size();i++)
	{
		MaxBeauty += vec[i].second*Beauty;
		Beauty--;
	}
	// for(it=cCnts.begin();it!=cCnts.end();it++)
	// {
	// 	MaxBeauty += it->second*Beauty;
	// 	Beauty--;
	// }
	return MaxBeauty;
}
bool ifChinese(char h,char l)
{
	if((h & 0x80) == 0 || (l & 0x80) == 0)
		return false;
	return true;
}
string cutStr(string str,int len)
{
	string res;
	if(len <=0)
		return res;
	if(len >= str.size() || str.size() <=1)
		return str;
	

	if(ifChinese(str[len-1],str[len]))
		res=string(str.begin(),str.begin()+len-1);
	else 
		res=string(str.begin(),str.begin()+len);
	return res;
}
class myListNode
{
public:
	myListNode(int nkey):m_nKey(nkey),m_pNext(NULL){}
	int       m_nKey;
	myListNode* m_pNext;
};
bool list_init(myListNode** list,int nkey)
{
	*list= new myListNode(nkey);
	if(list!=NULL)
		return true;
	return false;
}
myListNode* list_search(myListNode* list,int nkey)
{
	if(list==NULL)
		return NULL;
	if(list->m_nKey==nkey)
		return list;
	else
	{
		list=list->m_pNext;
		return list_search(list,nkey);
	}
}
bool list_insert(myListNode* list,int fatherkey,int sonkey)
{
	myListNode* node=list_search(list,fatherkey);
	if(node!=NULL)
	{
		myListNode* newNode = new myListNode(sonkey);
		if(newNode)
		{
			newNode->m_pNext=node->m_pNext;
			node->m_pNext = newNode;
			return true;
		}
		else
			return false;
	}
	else 
		return false;
}
bool list_del(myListNode* list,int nkey)
{
	myListNode* node=list_search(list,nkey);

	if(node==NULL)
	{
		return false;
	}
	else
	{
		myListNode* lastNode=node;
		while(1)
		{
			if(node->m_pNext==NULL)
			{
				delete node;
				break;
			}
			else
			{
				lastNode=node;
				node->m_nKey=node->m_pNext->m_nKey;
				node=node->m_pNext;
			}
		}
		lastNode->m_pNext=NULL;
		return true;
	}

}
void list_deinit(myListNode** list)
{
	// printf("11111111\n");
	if(list==NULL || *list==NULL)
		return;
	if((*list)->m_pNext==NULL)
	{
		// cout << (*list)->m_nKey << ' ';
		delete *list;
		*list=NULL;
		return ;
	}
	else
	{
		list_deinit(&((*list)->m_pNext));
		if((*list)->m_pNext==NULL)
		{
			// cout << (*list)->m_nKey << ' ';
			delete *list;
			*list=NULL;
			return ;
		}
	}
		
}
void list_display(myListNode* list)
{
	while(list)
	{
		cout << list->m_nKey << ' ';
		list=list->m_pNext;
	}
}
int gongbei(int a,int b)
{
	int min,max;
	if(a<b)
	{
		min=a;
		max=b;
	}
	else
	{
		min=b;max=a;
	}
	if(max%min==0)
		return max;
	else
	{
		int beginIdx=max/min+1;
		int res=0;
		for(;beginIdx <= max;beginIdx++)
		{
			res=min*beginIdx;
			if(res % max == 0)
				return res;
		}
	}
}
double getCubeRoot(double input)
{
	double Int=1.0;
	double dot=0.1;

	double sum=0.0;

	while(1)
	{
		if(Int*Int*Int>input)
		{
			Int--;
			break;
		}
		Int++;
	}
	while(1)
	{
		/*只有最多10次计算，要优化也可以用二分*/
		sum = (Int+dot)*(Int+dot)*(Int+dot);
		if(sum >input)
		{
			dot=dot-0.1;
			sum = (Int+dot+0.05)*(Int+dot+0.05)*(Int+dot+0.05);
			if(sum<=input)
			{
				sum = (Int+dot+0.0999999)*(Int+dot+0.0999999)*(Int+dot+0.0999999);
				if(sum>=input)
					dot+=0.1;
			}
#if 0
			for(double dot2=0.05;dot2<=0.09;dot2+=0.01)
			{

				sum = (Int+dot+dot2)*(Int+dot+dot2)*(Int+dot+dot2);
				printf("dot2:%lf,sum:%lf\n",dot2, sum);
				if(sum>=input)
				{
					dot+=0.1;
					break;
				}
				if(dot2==0.09)
				{
					sum = (Int+dot+0.099)*(Int+dot+0.099)*(Int+dot+0.099);
					if(sum>=input)
					{
						dot+=0.1;
						break;
					}
				}
			}
#endif				
			return Int+dot;
		}
		dot=dot+0.1;
	}
}
int getMaxAndIdx(vector<int>& nums,vector<int>& idxs)
{
	auto maxIdx=max_element(nums.begin(),nums.end());

	for(int i=0;i<nums.size();i++)
	{
		if(nums[i]==(*maxIdx))
			idxs.push_back(i);
	}
	return (*maxIdx);
}
void getMaxPos(vector<int>& idxs,int idx,int &beginIdx,int &endIdx)
{
	for(int i=0;i<idxs.size();i++)
	{
		if(idx<=idxs[i])
		{
			beginIdx = i<1?0:i-1;
			endIdx = i;
			break;
		}
	}
}
int getMaxToTop(vector<int>& nums)
{
	int maxCnt=1;
	vector<int> idxs;
	int max=getMaxAndIdx(nums,idxs);
	int step=1;
	int jbegin;
	int jend=0;
	for(int i=0;i<nums.size();i++)
	{
		int singleMax=nums[i];
		int cnt=1;
		printf("iiiiiiiiiiiii:%d\n",i );
		for(int k=0;k<idxs.size();k++)
		{
			printf("kkkkkkkkkkkkk:%d\n",k );
			jbegin=i;
			
			if(i<=idxs[k])
			{
				jend=idxs[k]+1;
				step=1;
			}
			else
			{
				jend=idxs[k]-1;
				step=-1;
			}
			for(;jbegin!=jend && jbegin;jbegin+=step)
			{
				printf("jbegin:%d,jend:%d,step:%d,num:%d\n",jbegin,jend, step,nums[jbegin]);
				// if(nums[jbegin]==max)
				// {
				// 	cnt++;
				// 	// if(maxCnt<cnt)
				// 	// 	maxCnt=cnt;
				// 	// cnt=1;
				// }
				// else
				{
					if(singleMax < nums[jbegin])
					{
						cnt++;
						singleMax = nums[jbegin];
					}
				}
				
			}
			if(maxCnt<cnt)
				maxCnt=cnt;
			cnt=1;

		}
			
		
	}
	return maxCnt;
}
bool paircmp2(const pair<char, int>& a, const pair<char, int>& b) {
	if(a.second > b.second)
		return true;
	else if(a.second == b.second && a.first <= b.first)
		return true;
	return false;
}
void charCnt(string str)
{
	map<char,int> charCnts;
	map<char,int>::iterator it;
	for(int i=0;i<str.size();i++)
	{
		it = charCnts.find(str[i]);
		if(it==charCnts.end())
			charCnts.insert(pair<char,int>(str[i],1));
		else
			it->second ++;
	}
	vector<pair<char,int>> pairVec(charCnts.begin(),charCnts.end());
	sort(pairVec.begin(),pairVec.end(),paircmp2);
	for(int i=0;i<pairVec.size();i++)
	{
		cout << pairVec[i].first ;
		// cout << pairVec[i].first << ":" << pairVec[i].second<<endl ;
	}
	// cout << endl;
}
bool downcmp(int a,int b)
{
	return a>b;
}
void sortIntegerArray(vector<int >& pIntegerArray,int iSortFlag)
{
	if(iSortFlag)
		sort(pIntegerArray.begin(),pIntegerArray.end(),downcmp);
	else
		sort(pIntegerArray.begin(),pIntegerArray.end());
}
string MarkNum(string& str)
{
	string res;
	bool getNum=false;
	int i=0;
	for(;i<str.size();i++)
	{
		if(!getNum && str[i]>='0' && str[i] <= '9')
		{
			res.push_back('*');
			getNum=true;
		}
		else if(getNum && (str[i]<'0' || str[i] > '9'))
		{
			res.push_back('*');
			getNum=false;
		}
		res.push_back(str[i]);
	}
	if(str[i-1]>='0' && str[i-1] <= '9')
		res.push_back('*');
	return res;
}
#endif
void parseStr(string& str,vector<string>& args)
{
	string arg;
	bool get_long_arg = false;
	for(int i=0;i<str.size();i++)
	{	
		if(get_long_arg)
		{
			arg.push_back(str[i]);
		}
		else
		{
			if(str[i]!=' ')
				arg.push_back(str[i]);
			else
			{
				if(!arg.empty())
				{
					args.push_back(arg);
					arg.erase(arg.begin(),arg.end());
				}
			}

		}
		if(str[i]=='\"')
			get_long_arg=~get_long_arg;
	}
	if(!arg.empty())
	{
		args.push_back(arg);
	}
}
void swapStr(string& minStr,string& maxStr )
{
	if(minStr.size()>maxStr.size())
	{
		string tmp = minStr;
		minStr=maxStr;
		maxStr=tmp;
	}
}
int getMaxCommonStrLen(string& str1,string& str2)
{
	int maxLen=0;
	int len=0;
	for(int i=0;i<str1.size();i++)
	{
		for(int j=0;j<str2.size();j++)
		{
			if(str1[i]==str2[j])
			{
				len++;
				i++;
				j++;
				while(i<str1.size() && j<str2.size())
				{
					if(str1[i]==str2[j] )
					{
						len++;
						i++;
						j++;
					}
					else
					{
						i-=len;
						j--;
						break;
					}	
				}
			}
				
				
			if(maxLen < len)
				maxLen = len;
			len =0;
				
		}
	}
	return maxLen;
}
void get_divisors(int num,vector<int>& divisors)
{
	if(num<2)
		return;
	int res=0;
	vector<int> divisorsUp;
	for(int i=2;i<=num;i++)
	{
		if(res!=0 && i>=res)
			break;
		if(num%i==0)
		{
			res=num/i;
			if(i==num)
				divisorsUp.push_back(i);
			else
			{
				divisors.push_back(i);
				if(res!=i)
					divisorsUp.push_back(res);
			}
		}
	}
	for(int i=divisorsUp.size()-1;i>=0;i--)
		divisors.push_back(divisorsUp[i]);
	if(divisors[divisors.size()-1] != num)
		divisors.push_back(num);
	// divisors.insert(divisors.end(),divisorsUp.end(),divisorsUp.begin());
}
void aiji(int son,int mom,vector<int>& res)
{
	son *= 10;
	mom *= 10;
	vector<int> divisors;
	get_divisors(mom,divisors);
	for(int i=0;i<divisors.size();i++)
	{
		for(int j=i+1;j<divisors.size();j++)
		{

		}
	}
}
bool checkStrInclude(string& shortStr,string& longStr)
{
	bool existSingle=true;
	for(int i=0;i<shortStr.size();i++)
	{
		existSingle=false;
		for(int j=0;j<longStr.size();j++)
		{
			if(shortStr[i]==longStr[j])
			{
				existSingle=true;
				break;
			}
		}
		if(!existSingle)
			return false;
	}
	return true;
}
int getUpperChar(string& str)
{
	int cnt=0;
	for(int i=0;i<str.size();i++)
	{
		if(str[i] >= 'A' && str[i] <= 'Z')
			cnt++;
	}
	return cnt;
}
int checkHuiwen(string& str,int beginIdx,int endIdx)
{
	int begin = beginIdx;
	int end = endIdx;
	while(begin<end)
	{
		if(str[begin] == str[end])
		{
			begin++;
			end--;
		}
		else
			return 0;
	}
	return endIdx - beginIdx+1;
}
int maxHuiwen(string& str)
{
	int MaxLen=0;
	int singleLen=0;
	for(int i=0;i<str.size();i++)
	{
		singleLen=0;
		for(int j=str.size()-1;j>=MaxLen;j--)
		{
			if(str[i]==str[j])
			{
				singleLen= checkHuiwen(str,i,j);
				if(MaxLen < singleLen)
					MaxLen = singleLen;
			}
		}
	}
	return MaxLen;
}
int getContinualOne(int bytenum)
{
	bool getOne =false;
	int maxCnt=0;
	int cnt=0;
	while(bytenum)
	{
		if(!getOne)
		{
			if(bytenum%2==1)
			{
				getOne=true;
				cnt++;
			}
		}
		else
		{
			if(bytenum%2==1)
				cnt++;
			else
			{
				cnt=0;
				getOne=false;
			}
		}
		bytenum /= 2;
		if(maxCnt<cnt)
			maxCnt=cnt;
	}
	return maxCnt;
}
vector<string> mark={"AVERAGE","STRONG","VERY_STRONG","SECURE"};
string markPasswd(string& passwd)
{
	int Score=0;
	int alphaScore=0,numScore=0,charScore=0;
	unsigned char alphaType=0;//0:no,bit1:small,bit2:upper
	int numCnt=0,charCnt=0;
	if(passwd.size() <=4)
		Score=5;
	else if(passwd.size() >=5 && passwd.size() <=7)
		Score=10;
	else if(passwd.size() >=8)
		Score=25;
	for(int i=0;i<passwd.size();i++)
	{
		
		if((passwd[i]>='a' && passwd[i]<='z') )
		{
			alphaType = alphaType | 0x1;
		}
		else if(passwd[i]>='A' && passwd[i]<='Z')
		{
			alphaType = alphaType | 0x2;
		}
		else if(passwd[i]>='0' && passwd[i]<='9')
		{
			numCnt++;
		}
		else
		{
			charCnt++;
		}
	}
	unsigned char Extra=0;//0:no,bit1:num,bit2:char,bit3:alpha,bit4:multialpha
	cout << "Score:" << Score << endl;
	printf("alphaType:%d\n",alphaType);
	
	// cout << "alphaType:" << alphaType << endl;
	if(alphaType==0x1 ||alphaType==0x2)
	{
		Score+=10;
		Extra |= 0x3;
	}
	else if(alphaType==0x3)
	{
		Score+=20;
		Extra |= 0x8;
	}
	cout << "Score:" << Score << endl;
	cout << "numCnt:" << numCnt << endl;
	
	if(numCnt==1)
	{
		Score+=10;
		Extra |= 0x1;
	}
	else if(numCnt>1)
	{
		Score+=20;
		Extra |= 0x1;
	}
	cout << "Score:" << Score << endl;
	cout << "charCnt:" << charCnt << endl;
	
	if(charCnt==1)
	{
		Score+=10;
		Extra |= 0x2;
	}
	else if(charCnt>1)
	{
		Score+=25;
		Extra |= 0x2;
	}
	cout << "Score:" << Score << endl;
	printf("Extra:%d\n",Extra);
	
	// cout << "Extra:" << Extra << endl;
	if(Extra==0x3)
		Score+=2;
	else if(Extra==0x7)
		Score+=3;
	else if(Extra==0xB)
		Score+=5;
	cout << "Score:" << Score << endl;
	if(Score >=0 && Score<25)
		return "VERY_WEAK";
	else if(Score >=25 && Score<50)
		return "WEAK";
	else if(Score >=50 && Score<90)
		return mark[(Score-50)/10];
	else
		return "VERY_SECURE";
}
string joker(string str)
{
	int idx = str.find('-');
	// cout << "idx:" << idx <<endl;
	string str1 = string(str.begin(),str.begin()+idx);
	// cout << "str1:" << str1 <<endl;
	string str2 = string(str.begin()+idx+1,str.end());
	// cout << "str2:" << str2 <<endl;
	if(str1.size()>10 || str2.size()>10)
		return "joker JOKER";
	if(str1.size()!=str2.size())
	{
		if(str1.size() == 4)
			return str1;
		if(str2.size() == 4)
			return str2;
		return "ERROR";
	}
	else
	{
		if(str1[0] == 'A')
			return str2[0]=='2'?str2:str1;
		if(str2[0] == 'A')
			return str1[0]=='2'?str1:str2;
		if(str1[0] == '2')
			return str1;
		if(str2[0] == '2')
			return str2;
		return str1[0] < str2[0]?str2:str1;
	}

}
#if 0
pthread_t thr1,thr2,thr3,thr4;
bool upthr1=false,upthr2=false,upthr3=false,upthr4=false;
pthread_mutex_t mtx12;
pthread_mutex_t mtx23;
pthread_mutex_t mtx34;
pthread_mutex_t mtx41;

pthread_cond_t cond12;
pthread_cond_t cond23;
pthread_cond_t cond34;
pthread_cond_t cond41;
int thrN;
string thrRes;
void* thread_func1(void *pnum)
{
	upthr1=true;
	thrN=*(int*)(pnum);
	int cnt=0;
	while(cnt<thrN)
	{
		printf("1111111111111111 before %d\n", cnt);
		pthread_mutex_lock(&mtx12);
		thrRes.push_back('A');
		cnt++;
		printf("1111111111111111 after %d\n", cnt);
		pthread_cond_signal(&cond12);
		pthread_mutex_unlock(&mtx12);
		pthread_mutex_lock(&mtx41);
		pthread_cond_wait(&cond41,&mtx41);
		pthread_mutex_unlock(&mtx41);

	}
	
}
void* thread_func2(void *pnum)
{
	upthr2=true;
	int cnt=0;
	while(cnt<thrN)
	{
		printf("222222222222222 before %d\n", cnt);
		pthread_mutex_lock(&mtx12);
		pthread_cond_wait(&cond12,&mtx12);
		thrRes.push_back('B');
		cnt++;
		printf("22222222222222 after %d\n", cnt);
		pthread_mutex_unlock(&mtx12);
		pthread_mutex_lock(&mtx23);
		pthread_cond_signal(&cond23);
		
		pthread_mutex_unlock(&mtx23);

	}
}
void* thread_func3(void *pnum)
{
	upthr3=true;
	int cnt=0;
	while(cnt<thrN)
	{
		printf("333333333333333 before %d\n", cnt);
		pthread_mutex_lock(&mtx23);
		pthread_cond_wait(&cond23,&mtx23);
		thrRes.push_back('B');
		cnt++;
		printf("333333333333333 after %d\n", cnt);
		pthread_mutex_unlock(&mtx23);
		pthread_mutex_lock(&mtx34);
		pthread_cond_signal(&cond34);
		
		pthread_mutex_unlock(&mtx34);

	}
}
void* thread_func4(void *pnum)
{
	upthr4=true;
	int cnt=0;
	while(cnt<thrN)
	{
		printf("4444444444444444 before %d\n", cnt);
		pthread_mutex_lock(&mtx34);
		pthread_cond_wait(&cond34,&mtx34);
		thrRes.push_back('B');
		cnt++;
		printf("444444444444444 after %d\n", cnt);
		pthread_mutex_unlock(&mtx34);
		pthread_mutex_lock(&mtx41);
		pthread_cond_signal(&cond41);
		
		pthread_mutex_unlock(&mtx41);

	}
}
#endif
int sortAndUnique()
{
	int N;
	while(cin >> N)
	{
		std::vector<int> nums(N);
		vector<int> res;
		for(int i=0;i<N;i++)
		{
			cin >> nums[i];
		}
		sort(nums.begin(),nums.end());
		res.push_back(nums[0]);
		cout << nums[0] << endl;
		for(int i=1;i<nums.size();i++)
		{
			if(nums[i] != res[res.size()-1])
			{
				res.push_back(nums[i]);
				cout << nums[i] << endl;
			}
		}	
	}
	return 0;
}
bool pairCmpNag(const pair<char,int>& pair1,const pair<char,int>& pair2)
{
	return pair1.second < pair2.second;
}
/*string delMin(string& str)
{
	string res;
	map<char,int> charCnts;
	map<char,int>::iterator it;
	for(int i=0;i<str.size();i++)
	{
		it=charCnts.find(str[i]);
		if(it == charCnts.end())
			charCnts.insert(pair<char,int>(str[i],1));
		else
			it->second ++;
	}
	vector<pair<char,int>> vec(charCnts.begin(),charCnts.end());
	// sort(vec.begin(),vec.end(),pairCmpNag);
	
	int minCnt = charCnts[0].second;
	for(int i=1;i<charCnts.size();i++)
	{
		if(minCnt>charCnts[i].second)
			minCnt = charCnts[i].second;
	}
	for(int i=0;i<str.size();i++)
	{
		if(str[i]!=)
	}
}*/

int hechang()
{
	int N;
	while(cin>>N)
	{
		vector<int > heights(N);
		for(int i=0;i<N;i++)
		{
			cin >> heights[i];
		}
		vector<int > dp1(N,1);
		vector<int > dp2(N,1);
		for(int i=1;i<N;i++)
		{
			for(int j=i-1;j>=0;j--)
			{
				if(heights[i]>heights[j] && dp1[i] < dp1[j]+1)
					dp1[i] = dp1[j]+1;
			}
		}
		for(int i=N-2;i>=0;i--)
		{
			for(int j=i+1;j<N;j++)
			{
				if(heights[i]>heights[j] && dp2[i] < dp2[j]+1)
					dp2[i] = dp2[j]+1;
			}
		}
		// std::reverse(heights.begin(),heights.end());
		// for(int i=1;i<N;i++)
		// {
		// 	for(int j=i-1;j>=0;j++)>
		// 	{
		// 		if(heights[i]>heights[j] && dp2[i] < dp2[j]+1)
		// 			dp2[i] = dp2[j]+1;
		// 	}
		// }
		// std::reverse(dp2.begin(),dp2.end());
		int Max = 1;
		for(int i=0;i<N;i++)
		{
			if(Max < dp1[i] + dp2[i])
				Max = dp1[i] + dp2[i];
		}
		cout << N-Max+1 <<endl;
	}
}
int searchInsert(vector<int>& nums, int target) {
    int size=nums.size();
    if(size==0)
        return 0;
    int i=0;
    for(;i<size;i++)
    {
    	if(nums[i] >= target)
    		return i;
    }
    return i;
}
int maxSubArray(vector<int>& nums) {
    vector<int> dp(nums.size());
    dp.push_back(nums[0]);
    int maxSum = nums[0];
    for(int i=1;i<nums.size();i++)
    {
    	if(nums[i-1] < 0)
    	{
    		dp[i] = nums[i];
    	}
    	else
    	{
    		dp[i] = nums[i] + nums[i-1];
    	}
    	if(maxSum < dp[i])
    		maxSum = dp[i];
    }
    return maxSum;
}
int lengthOfLastWord(string s) {
	bool getChar = false;
	int cnt = 0;
	for(int i=s.size()-1;i>=0;i--)
	{
		if(getChar )
		{
			if(s[i]== ' ')
				return cnt;
			else
				cnt++;
		}
		else
		{
			if(s[i] != ' ')
			{
				cnt++;
				getChar = true;
			}
		}
	}
	return cnt;
}
vector<int> plusOne(vector<int>& digits) {
	vector<int> res;
	unsigned char up=0;
	int single = digits[digits.size()-1]+1;
	res.push_back(single%10);
	up = single/10;
	int i=digits.size()-2;
	while(up && i>=0)
	{
		single = digits[i]+up;
		res.push_back(single%10);
		up = single/10;
		i--;
	}
	if(up)
		res.push_back(up);
	for(;i>=0;i--)
	{
		res.push_back(digits[i]);
	}
	
	std::reverse(res.begin(),res.end());
	return res;
}
string addBinary(string a, string b) {
	bool up = false;
	int i=a.size()-1,j=b.size()-1;
	string res;
	while(i>=0 && j >=0)
	{
		if(a[i]=='1' && b[j]=='1')
		{
			res.push_back(up?'1':'0');
			up=true;
		}
		else if(a[i]=='0' && b[j]=='0')
		{
			res.push_back(up?'1':'0');
			up=false;
		}
		else
		{
			res.push_back(up?'0':'1');
		}
		i--;
		j--;
	}
	while(i>=0 )
	{
		if(up)
		{
			if(a[i]=='1')
			{
				res.push_back('0');
			}
			else
			{
				res.push_back('1');
				up=false;
			}
		}
		else
			res.push_back(a[i]);
		i--;
	}
	while(j >=0)
	{
		if(up)
		{
			if(b[j]=='1')
			{
				res.push_back('0');
			}
			else
			{
				res.push_back('1');
				up=false;
			}
		}
		else
			res.push_back(b[j]);
		j--;
	}
	if(up)
		res.push_back('1');
	std::reverse(res.begin(),res.end());
	return res;
}
int mySqrt(int x) {
	if(x==0)
        return 0;
    if(x < 4)
		return 1;
	bool greater = false;
	int semix = 2;
	long tmpSum = 2*2;
	int lastx=1;
	while(1)
	{
		if(semix==65536 || tmpSum > x)
		{
			while(1)
			{
                tmpSum  = lastx*lastx;
                if(tmpSum == x)
                    return lastx;
				if( tmpSum + 2*lastx +1 > x )
					return lastx;
				lastx++;
			}
		}
		else if(tmpSum == x)
		{
			return semix;
		}
		else if(tmpSum < x)
		{
			lastx=semix;
			semix = semix*2;
		}
        if(semix < 65536)
		    tmpSum = semix*semix;
	}
	return -1;
}
int climbStairs(int n) {
	if(n<=1)
		return n;
	int n1=n;
	int n2=0;
	int cntSum = 0;
	int tmp = 0;
	while(n2*2 <= n)
	{
		tmp = n2*n1;
		cntSum += tmp?tmp:1;
		n2++;
		n1=n-n2*2;
	}
	return cntSum;
}
ListNode* deleteDuplicates(ListNode* head) {
	vector<int> Duplicates;
	vector<int>::iterator it;
	ListNode* res = head;
	ListNode* lastHead = head;
	while(head)
	{
		it = find(Duplicates.begin(),Duplicates.end(),head->val);
		if(it == Duplicates.end())
		{
			Duplicates.push_back(head->val);
			lastHead = head;
			
		}
		else
		{
			lastHead->next = head->next;
		}
		head = head->next;
	}
	return res;
}
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
	int tmp = 0;
	int j = n-1;
	int i=m-1;
	int totalIdx = m-1;
	while(i>=0 && j >=0)
	{
		if(nums1[i]<nums2[j])
		{
			nums1[totalIdx--] = nums2[j];
			j--;
		}
		else
		{
			nums1[totalIdx--] = nums1[i];
			i--;
		}
	}
	// while(i>=0)
	// {
	// 	nums1[totalIdx--] = nums1[i];
	// 	i--;
	// }
	while(j>=0)
	{
		nums1[totalIdx--] = nums2[j];
		j--;
	}

}
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
bool isSameTree(TreeNode* p, TreeNode* q) {
	if(!p && !q)
        return true;
    else if(p && !q)
    	return false;
    else if(!p && q)
    	return false;
    else
    {
    	if(p->val == q->val)
    		return (isSameTree(p->left,q->left) && isSameTree(p->right,q->right));
    	else 
    		return false;
    }
}
bool isMirror(TreeNode* t1,TreeNode* t2)
{
	if(t1==NULL && t2 == NULL)
		return true;
	if(t1==NULL || t2==NULL)
		return false;
	return (t1->val == t2->val && isMirror(t1->left,t2->right) && isMirror(t2->left,t1->right));
}
bool isSymmetric(TreeNode* root) {
	return isMirror(root,root);
}
bool hasLeaf(TreeNode* t,int& n)
{
	if(t==NULL)
		return false;
	if(t->left==NULL && t->right==NULL)
		return false;
	if(t->left && t->right==NULL)
		n+=(hasLeaf(t->left,n) )?1:0;
	else if(t->left==NULL && t->right)
		n+=(hasLeaf(t->right,n) )?1:0;
	else
	{
		n+=(hasLeaf(t->left,n) || hasLeaf(t->right,n))?1:0;
	}
	return true;
}
int maxDepth(TreeNode* root) {
	int depth =1;
	depth += (hasLeaf(root,depth) )?1:0;
	return depth;
}
vector<vector<int>> generate(int numRows) {
		vector<vector<int>> res;
		if(numRows==0)
			return res;
		vector<int> begin(1);
		begin[0]=1;
		res.push_back(begin);
		for(int i=1;i<numRows;i++)
		{
			vector<int> tmp(i+1);
			tmp[0] =1;
			tmp[i] = 1;
			for(int j=1;j<i;j++)
			{
				
				tmp[j] = (res[i-1][j-1] + res[i-1][j]);
				
			}
			res.push_back(tmp);
		}
		return res;
}
int maxProfit(vector<int>& prices) {
    if(prices.size()<=1)
		return 0;
	int sub = 0;
	int maxSub = 0;
	int min = prices[0];
	for(int i=1;i<prices.size();i++)
	{
		if(min > prices[i])
			min = prices[i];
		else
		{
			sub = prices[i] - min;
			if(maxSub < sub)
				maxSub = sub;
		}
	}
	return maxSub;
}
int maxProfit2(vector<int>& prices) {
	if(prices.size()<=1)
		return 0;
	vector<int> dp(prices.size());
	dp[0] = -65536;
	int sub = 0;
	int max = 0;
    int i=1;
	for(;i<prices.size();i++)
	{
		for(int j=0;j<i;j++)
		{
			sub = prices[i] - prices[j];
			if(max < sub)
				max = sub;
		}
		sub = prices[i] - prices[i-1];
		if(sub>0)
			dp[i] = dp[i-1]>0?dp[i-1]+sub:sub;
		else
		{
			dp[i] = dp[i-1]>sub?dp[i-1]:sub;
		}
	}
	return dp[i-1];
}
int maxProfit22(vector<int>& prices)
{
	if(prices.size()<=1)
		return 0;
	int max = 0;
	int sub = 0;
	for(int i=1;i<prices.size();i++)
	{
		sub = prices[i] - prices[i-1];
		max+=sub>0?sub:0;
	}
	return max;
}
bool isSameChar(char c1,char c2)
{
	static int step = 'a'-'A';
	if(c1>='A' && c1 <='Z' && c2>='a' && c2 <='z')
		return (c1+step)==c2;
	else if(c2>='A' && c2 <='Z' && c1>='a' && c1 <='z')
		return (c2+step)==c1;
	else
		return c1==c2;
}
bool isCharValid(char c)
{
	if(c>='0' && c <='9')
		return true;
	if(c>='A' && c <='Z')
		return true;
	if(c>='a' && c <='z')
		return true;
	return false;
}
bool isPalindrome(string s) {
	int i=0,j=s.size()-1;
	while(i<=j)
	{
		printf("000000000000 i:%d,j:%d,s[i]:%c,s[j]:%c\n", i,j,s[i],s[j]);
		while(!isCharValid(s[i]) && i <=j)
			i++;
		while(!isCharValid(s[j]) && i <=j)
			j--;
		printf("111111111111 i:%d,j:%d,s[i]:%c,s[j]:%c\n", i,j,s[i],s[j]);
		if(!isSameChar(s[i],s[j]))
			return false;
		i++;
		j--;
	}
	return true;
}
int singleNumber(vector<int>& nums) {
	int res=nums[0];
	for(int i=1;i<nums.size();i++)
	{
		res = res^nums[i];
	}
	return res;
}
int missingNumber(vector<int>& nums) {
	int sum = 0;
	for(int i=0;i<nums.size();i++)
	{
		sum += nums[i];
	}
	return nums.size()*(nums.size()+1)/2 - sum;
}
int findDuplicate(vector<int>& nums) {

    sort(nums.begin(),nums.end());
    for(int i=1;i<nums.size();i++)
    {
    	if(nums[i]==nums[i-1])
    		return nums[i];
    }
    return nums[0];
}
int findDuplicate2(vector<int>& nums){
	unordered_map<int,int> numsMap;
	for(int i=0;i<nums.size();i++)
	{
		if(numsMap.find(nums[i]) != numsMap.end())
			return nums[i];
		numsMap[nums[i]]=1;
	}
	return nums[0];
}
vector<int> findErrorNums(vector<int>& nums) {
	vector<int> orderNums(nums.size(),0);
	vector<int> res(2);
	for(int i=0;i<nums.size();i++)
	{
		if(orderNums[nums[i]-1] == 0)
			orderNums[nums[i]-1] = nums[i];
		else
			res[0] = nums[i];
	}
	for(int i=0;i<nums.size();i++)
	{
		if(orderNums[i] == 0)
		{
			res[1] = i+1;
			break;
		}
	}
	return res;
}
vector<int> twoSum(vector<int>& numbers, int target) {
	vector<int> res(2);
	for(int i=0;i<numbers.size();i++)
	{
		for(int j=i+1;j<numbers.size();j++)
		{
			if(numbers[i]+numbers[j] == target)
			{
				res[0]=i+1;
				res[1]=j+1;
				return res;
			}
		}
	}
	return res;
}
vector<int> twoSum2(vector<int>& numbers, int target) {
	vector<int> res(2);
	int beginIdx = 0;
	int endIdx = numbers.size()-1; 
	while(beginIdx < endIdx)
	{
		while(numbers[endIdx] > target && beginIdx < endIdx)
			endIdx--;
		if(numbers[beginIdx] + numbers[endIdx] == target)
		{
			res[0] = beginIdx+1;
			res[1] = endIdx +1;
			return res;
		}
		else if(numbers[beginIdx] + numbers[endIdx] > target)
			endIdx --;
		else
			beginIdx++;
	}
	
	return res;
}

string convertToTitle(int n) {
    string res;
	while(n>0)
	{
        if(n<=26 && n>0)
        {
            res.push_back(n -1 + 'A');
            break;
        }
        if(n%26==0)
        {
            res.push_back('Z');
            n = n/26-1;
        }
            
        else
        {
            res.push_back(n%26 -1 + 'A');
            n = n/26;
        }
        // cout << n <<endl;
	}
	std::reverse(res.begin(),res.end());
	return res;
}

int titleToNumber(string s) {
	int res=0;
	for(int i=s.size()-1;i>=0;i--)
	{
		res +=(s[i]-'A'+1)*pow(26,i);
	}
	return res;
}
int trailingZeroes(int n) {
	int cnt = 0;
	int tmp=0;
	for(int i=5;i<n;i+=5)
	{
		tmp = i;
		while(tmp)
		{
			if(tmp%5==0)
				cnt++;
			else
				break;
			tmp/=5;
		}
	}
	return cnt;
}
int trailingZeroes2(int n) {
	int cnt = 0;
	while(n)
	{
		cnt += n/5;
		n/=5;
	}
	return cnt;
}
int majorityElement(vector<int>& nums) {
	unordered_map<int,int> numsMap;
	unordered_map<int,int>::iterator it;
	for(int i=0;i<nums.size();i++)
	{
		it = numsMap.find(nums[i]);
		if(it==numsMap.end())
		{
			numsMap.insert(pair<int,int>(nums[i],1));
		}
		else
		{
			
			if(++it->second >nums.size()/2)
				return it->first;
		}
	}
	return nums[0];
}
int maxProduct(vector<int>& nums) {
	if(nums.size()==1)
		return nums[0];
	vector<int> dp_pos(nums.size(),0);
	vector<int> dp_neg(nums.size(),0);
	if(nums[0] >= 0)
	{
		dp_pos[0] = nums[0];
	}
	else
	{
		dp_neg[0] = nums[0];
	}
	int i=1;
	for(;i<nums.size();i++)
	{
		if(nums[i] > 0)
		{
			dp_pos[i] = nums[i]*(dp_pos[i-1]==0?1:dp_pos[i-1]);
			dp_neg[i] = nums[i]*dp_neg[i-1];
		}
		else if(nums[i] < 0)
		{
			dp_pos[i] = nums[i]*dp_neg[i-1];
			dp_neg[i] = nums[i]*(dp_pos[i-1]==0?1:dp_pos[i-1]);
		}
		else
		{
			dp_pos[i] = 0;
			dp_neg[i] = 0;
		}
	}
	return *max_element(dp_pos.begin(),dp_pos.end());
}
vector<int> productExceptSelf(vector<int>& nums) {
	vector<int> res(nums.size(),0);
	
	for(int i=0;i<nums.size();i++)
	{
		for(int j=0;j<nums.size();j++)
		{
			if(j!=i)
			{
				if(res[j]==0 && nums[i]!=0)
					res[j] = nums[i];
				else
					res[j] *= nums[i];
			}
		}
	}
	return res;
}
ListNode* removeElements(ListNode* head, int val) {
	while(head && head->val == val)
	{
		head = head->next;
	}
	if(head==NULL )
        return NULL;
	ListNode* res = head;
	ListNode* lastHead = head;
	while(head)
	{
        cout << "1111111" << endl;
		if(head->val == val)
		{
            cout << "222222222" << endl;
            lastHead->next=head->next;
		}
		else
			lastHead = head;
		head = head->next;
	}
	return res;
}
bool isPrime(int n)
{
	for(int i=3;i*i<=n;i++)
	{
		if(n%i==0)
			return false;
	}
	return true;
}
int countPrimes(int n) {
	if(n<=2)
		return 0;
	int cnt=1;
	for(int i=3;i<=n;i+=2)
	{
		if(isPrime(i))
			cnt++;
	}
	return cnt;
}
bool isIsomorphic(string s, string t) {
	if(s.size() != t.size())
		return false;
	if(s.size()==1)
		return true;
	for(int i=0;i<s.size();i++)
	{
		for(int j=i+1;j<s.size();j++)
		{
			if((s[i]==s[j] && t[i]==t[j]) || (s[i]!=s[j] && t[i]!=t[j]))
				continue;
			else
				return false;
		}
	}
	return true;
}
bool isIsomorphic2(string s, string t) {
	if(s.size() != t.size())
		return false;
	if(s.size()==1)
		return true;
	unordered_map<char,char> stMap;
	unordered_map<char,char> tsMap;
	unordered_map<char,char>::iterator s_it;
	unordered_map<char,char>::iterator t_it;
	for(int i=0;i<s.size();i++)
	{
		s_it = stMap.find(s[i]);
		if(s_it == stMap.end())
		{
			stMap.insert(unordered_map<char,char>::value_type(s[i],t[i]));
		}
		else
		{
			if(s_it->second != t[i])
				return false;
		}
		t_it = tsMap.find(t[i]);
		if(t_it == tsMap.end())
		{
			tsMap.insert(unordered_map<char,char>::value_type(t[i],s[i]));
		}
		else
		{
			if(t_it->second != s[i])
				return false;
		}
	}
	return true;
}
ListNode* reverseList(ListNode* head) {
	ListNode* headNode = head;
	ListNode* nextNode = head;
	ListNode* tmpNext = NULL;
	while(head && head->next)
	{
		headNode->next = headNode;
		headNode = head->next;
		nextNode = head;
		tmpNext = headNode->next;
		headNode->next = nextNode;
		head = head->next;
		head->next = tmpNext;
	}
	nextNode->next=NULL;
	return headNode;
}

bool containsDuplicate(vector<int>& nums) {
	vector<int> tmp;
	for(int i=0;i<nums.size();i++)
	{
		if(find(tmp.begin(),tmp.end(),nums[i])==tmp.end())
		{
			tmp.push_back(nums[i]);
		}
		else
			return true;
	}
	return false;
}
bool containsDuplicate2(vector<int>& nums){
	unordered_map<int,bool> tmp;
	for(int i=0;i<nums.size();i++)
	{
		if(tmp.find(nums[i])==tmp.end())
		{
			tmp.insert(unordered_map<int,bool>::value_type(nums[i],true) );
		}
		else
			return true;
	}
	return false;
}
bool containsDuplicate3(vector<int>& nums){
	set<int> s(nums.begin(),nums.end());
	return s.size()!=nums.size();
}
bool containsNearbyDuplicate(vector<int>& nums, int k) {
	unordered_map<int,int> tmp;
    unordered_map<int,int>::iterator it;
	for(int i=0;i<nums.size();i++)
	{
        it = tmp.find(nums[i]);
		if(it==tmp.end())
		{
			tmp.insert(unordered_map<int,int>::value_type(nums[i],i) );
		}
		else
		{
            // cout << "i:" << i << ",second:" << it->second << endl;
			if(i-(it->second)  <= k)
				return true;
			it->second=i;
		}
	}
	return false;
}

void reverseString(vector<char>& s) {
	int i=0;
	int j=s.size()-1;
	char tmp = 0;
	while(i<j)
	{
		tmp = s[i];
		s[i] = s[j];
		s[j]=tmp;
		i++;
		j--;
	}
}
int lengthOfLongestSubstring(string s) {
	if(s.size()<=1)
		return s.size();
	int len = 0;
	int max = 1;

	return max;
}

void rotate(vector<int>& nums, int k) {
	k=k%nums.size();
	std::reverse(nums.begin(),nums.begin()+k+1);
	std::reverse(nums.begin()+k+1,nums.end());
	std::reverse(nums.begin(),nums.end());

}	
int rob(vector<int>& nums) {
	if(nums.size()==1)
		return nums[0];
	else if(nums.size()==2)
		return max(nums[0],nums[1]);
	vector<int> dp(nums.size(),0);
	// int maxRes = 0;
	dp[0]=nums[0];
	dp[1]=nums[1];
	for(int i=2;i<nums.size();i++)
	{
		for(int j=i-2;j>=0;j--)
		{
			dp[i] = nums[i] + dp[j] > dp[i]?nums[i] + dp[j]:dp[i];
		}
	}
	return max(dp[dp.size()-1],dp[dp.size()-2]);

}
int binaryChopSearch(vector<int>& nums,int key)
{
	int begin = 0;
	int end = nums.size()-1;
	int mid=0;
	while(begin <= end )
	{
		mid = (begin+end+1)/2;

		if(nums[mid]==key)
			return mid;
		else if(key<nums[mid])
			end = mid-1;
		else if(key>nums[mid])
			begin=mid+1;
	}
	return -1;
}
bool isHappy(int n) {
	if(n==0)
		return false;
	static vector<int> err={2,3,4,20,37,42,58,89,145};
	int newN = n;
    int tmpN = n;
	// while(find(err.begin(),err.end(),newN)==err.end())
	while(binaryChopSearch(err,newN) != -1)
	{
		newN=0;
		while(tmpN)
		{
			newN += (tmpN%10)*(tmpN%10);
			tmpN /= 10;
		}
        cout << newN << endl;
		if(newN == 1)
			return true;
        tmpN = newN;
	}
	return false;
}
bool isAnagram(string s, string t) {
	if(s.size()!=t.size()) 
		return false;
	sort(s.begin(),s.end());
	sort(t.begin(),t.end());
	return s==t;
}
bool isAnagram2(string s, string t) {
	if(s.size()!=t.size()) 
		return false;
	unordered_map<int,int> scntMap;
	for(auto c:s)
	{
		scntMap[c]++;
	}
	for(auto c:t)
	{
		if(scntMap[c]>0)
			scntMap[c]--;
		else
			return false;
	}
	return true;
}
bool isUgly(int num) {
	if(num==0)
		return false;
	if(num==1)
		return true;
	while(num)
	{
		if(num%2==0)
			num/=2;
		else if(num%3==0)
			num/=3;
		else if(num%5==0)
			num/=5;
		else
			return false;
	}
	return true;
}
bool isBadVersion(int version){
	/*API*/
	return false;
}
int firstBadVersion(int n) {
	if(n<=1)
		return n;
	int begin=1;
	int end=n;
	int mid=0;
	while(begin < end)
	{
		mid = (begin+end)/2;
		if(isBadVersion(mid ))
			end = mid;
		else
			begin = mid;
	}
	return mid;
}
void moveZeroes(vector<int>& nums) {
	for(int i=0;i<nums.size();i++)
	{
		if(nums[i]==0)
		{
			for(int j=i+1;j<nums.size();j++)
			{
				if(nums[j]!=0)
				{
					swap(nums[i],nums[j]);
					break;
				}
			}
		}
		
	}
}
vector<string> split_by_space(const string& str) {
    vector<string> ans;
    istringstream is(str);
    string s;
    while (is >> s) ans.push_back(s);
    return ans;
}
string getHint(string secret, string guess) {
	int Acnt = 0;
	int Bcnt = 0;
	vector<int> secCharCnt(10,0);
	vector<int> gueCharCnt(10,0);
	for(int i=0;i<secret.size();i++)
	{
		if(secret[i]==guess[i])
			Acnt++;
		else
		{	
			secCharCnt[secret[i]-'0'] ++;
			gueCharCnt[guess[i]-'0'] ++;
		}
	}
	for(int i=0;i<10;i++)
	{
		Bcnt += min(secCharCnt[i],gueCharCnt[i]);
	}
	string res;
	stringstream ss;
	ss << Acnt << 'A' << Bcnt << 'B';
	ss >> res;
	return res;
}    
class NumArray {
public:
    vector<int> nums;
    vector<int> numsDp;
    NumArray(vector<int>& nums) {
        this->nums = nums;
        FileNumsDp();
    }
    void FileNumsDp(){
    	if(nums.size()==0)
            return;
    	// printf("size:%d\n",nums.size() );
    	numsDp.push_back(nums[0]);
        for(int i=1;i<nums.size();i++)
        {
        	numsDp.push_back(numsDp[i-1] + nums[i]);
        	// numsDp[i]= numsDp[i-1] + nums[i];
        	printf("%d: nums:%d,numsDp:%d\n",i,nums[i],numsDp[i] );
        }
        printf("exit FileNumsDp\n");
    }
    
    int sumRange(int i, int j) {
        if(i==0)
        	return numsDp[j];
        else
        	return numsDp[j] - numsDp[i-1];
    }
};
unordered_map<int,bool> PowerOfThree;
bool isPowerOfThree(int n) {
	int tmpN=n;
	do
	{
		if(tmpN%3!=0)
			return false;
		else
		{
			tmpN /= 3;
			if(PowerOfThree.find(tmpN)!=PowerOfThree.end())
				break;
			if(tmpN==1)
				break;
		}
	}while(1);
	PowerOfThree.insert(pair<int,bool>(n,true));
	return true;
}
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
	unordered_set<int> numSet(nums1.begin(),nums1.end());
    unordered_set<int> resSet;
	
	for(auto n:nums2)
	{
		if(numSet.find(n)!=numSet.end())
			resSet.insert(n );
	}
    vector<int> res(resSet.begin(),resSet.end());
	return res;
}
bool isPerfectSquare(int num) {
	return false;
}
int set_bound_test()
{
	vector<int> nums = {-2, 0, 3, -5, 2, -1,-2, 0, 3, -5, 2};
	for(auto n:nums)
		cout << n << ',';
	cout << endl;
	set<int> numSet(nums.begin(),nums.end());
	for(auto n:numSet)
		cout << n << ',';
	cout << endl;
	cout << "size:" << numSet.size() << endl;
	unordered_set<int> numSet2(nums.begin(),nums.end());
	for(auto n:numSet2)
		cout << n << ',';
	cout << endl;
	cout << "size2:" << numSet2.size() << endl;
	int i;
	while(cin >>i)
	{
		cout << "lower_bound:" << *numSet.lower_bound(i) << endl;
		cout << "upper_bound:" << *numSet.upper_bound(i) << endl;
	}
}
ListNode* removeNthFromEnd(ListNode* head, int n) {

	if(n==0)//不删除直接返回
		return head;
	ListNode* ahead = head;
	ListNode* behind = head;
	for(int i=0;i<n;i++)
	{
		ahead = ahead->next;
	}
	if(ahead==NULL)//移到了结尾，说明是要删除头结点
		return head->next;
	while(ahead)//双指针，当移动到头指针为空时，尾指针也就是要删除的节点了
	{
		if(ahead->next==NULL)
		{
			behind->next=behind->next->next;
			break;
		}
		ahead = ahead->next;
		behind = behind->next;
	}
	return head;

}

int reinterpret_cast_test()
{
	char str[] = "glad to test something";
	char *p = str;
	p++;
	int *p1 = reinterpret_cast<int *>(p);
	p1++;
	p = reinterpret_cast<char *>(p1); 
	printf("result is %s\n", p);

}
int FindSubString( char* pch )
{
    int   count  = 0;
    char  * p1   = pch;
    while ( *p1 != '\0' )
    {   
        if ( *p1 == p1[1] - 1 )
        {
            p1++;
            count++;
        }else  {
            break;
        }
    }
    int count2 = count;
    while ( *p1 != '\0' )
    {
        if ( *p1 == p1[1] + 1 )
        {
            p1++;
            count2--;
        }else  {
            break;
        }
    }
    if ( count2 == 0 )
        return(count);
    return(0);
}
void ModifyString( char* pText )
{
    char  * p1   = pText;
    char  * p2   = p1;
    while ( *p1 != '\0' )
    {
        int count = FindSubString( p1 );
        if ( count > 0 )
        {
            *p2++ = *p1;
            sprintf( p2, "%i", count );
            while ( *p2 != '\0' )
            {
                p2++;
            }
            p1 += count + count + 1;
        }else  {
            *p2++ = *p1++;
        }
    }
}
/*int main(  )
{
    char text[32] = "XYBCDCBABABA";
    ModifyString( text );
    printf( text );
    return 0;
}  */
int sum(int a)
{
    int c = 0;
    static int b = 3;
    c += 1;
    b += 2;
    return (a + b + c);
}
void dealTimer(int delayTime)
{
	for(int i=0;i<delayTime;i++)
	{
		cout << delayTime << ":" << i << endl;
		sleep(1);
	}
	cout << "timer exit:" << delayTime << endl;
}
void thr_func1(string funcName,int N)
{
	for(int i=0;i<N;i++)
		cout << funcName << i << endl;
}
void thr_func2()
{
	cout << "thr_func2" << endl;
}
void myTimerThrFunc(std::function<void(void)> cb,queue<int> times)
{
	int i=0;
	while(!times.empty())
	{
		cout << "begin timer:" << times.front() << endl;
		
		for(;i<times.front();i++)
		{
			cout << "i:" << i << endl;
			sleep(1);
		}
			
		cout << "after " << times.front() << " s run the func:";
		cb();
		times.pop();
	}
}

typedef struct TIME_
{
	int a;
	int b;
	int c;
}TIME;

#if 0
bool wordPattern(string pattern, string str) {

	unordered_map<char,string> cs;
	unordered_map<string,char> sc;
	unordered_map<char,int> csCnt;
	stringstream ss;
	ss << str;
	string word;
	int i=0;
	while(cin >> word)
	{
		if(i>=pattern.size())
			return false;
		if(cs.find(pattern[i])==pattern.end())
		{
			if(sc.find(word)!=sc.end())
				return false;
			cs[pattern[i]]=word;
		}
		else
		{
			if()
		}
		i++;

	}

}
#endif
bool judgeCircle(string moves) {
	map<char,int> moveCnt={{'U',0},{'D',0},{'L',0},{'R',0}};
	for(auto c:moves)
	{
		moveCnt[c]++;
	}
	if(moveCnt['U']==moveCnt['D'] && moveCnt['L']==moveCnt['R'])
		return true;
	return false;
}
bool checkPossibility(vector<int>& nums) {
	int cnt=0;
	for(int i=0;i+1<nums.size();i++)
	{
		if(nums[i]>nums[i+1])
		{
			if(++cnt >= 2)
				return false;
			else
			{
				for(int j=i-1;j>=0;--j)
				{
					if(nums[j]==nums[i])
						continue;
					if(nums[j]>nums[i+1])
						return false;
					else
						break;
				}
			}
		}
		else if(nums[i]==nums[i+1])
		{
			if(cnt != 0 && i-1>=0 && nums[i-1] > nums[i])
			{
				for(int j=i-2;j>=0;--j)
				{
					if(nums[j]==nums[i-1])
						continue;
					if(nums[j]>nums[i])
						return false;
					else
						break;
				}
			}
		}	
	}
	return true;
		
}
int findLengthOfLCIS(vector<int>& nums) {
	if(nums.size()<=1)
		return nums.size();
	int maxLen = 1;
	int len=1;
	for(int i=0;i+1< nums.size();i++)
	{
		if(nums[i] < nums[i+1])
			len++;
		else
		{
			if(maxLen < len)
				maxLen = len;
			len = 1;
		}
	}
	return maxLen;
}
bool validPalindromeTmp(string s,int lIdx,int rIdx,bool getDiff)
{
	while(lIdx<rIdx)
	{
		if(s[lIdx]!=s[rIdx])
		{
			if(getDiff)
				return false;
			bool bRet1,bRet2,bRet3,bRet4;
			if(validPalindromeTmp(s,lIdx+1,rIdx,true))
				return true;
			if(validPalindromeTmp(s,lIdx,rIdx-1,true))
				return true;
			if(rIdx+1 < s.size() && validPalindromeTmp(s,lIdx,rIdx+1,true))
				return true;
			if(lIdx-1 >=0 && validPalindromeTmp(s,lIdx-1,rIdx,true))
				return true;
			return false;

		}
	}
	return true;
}
bool validPalindrome(string s)
{
	int lIdx=0,rIdx=s.size()-1;
	return validPalindromeTmp(s,lIdx,rIdx,false);
}
bool validPalindrome2(string s) {
	int lIdx=0,rIdx=s.size()-1;
	bool getDiff = false;
	while(lIdx<rIdx)
	{
		if(s[lIdx]!=s[rIdx])
		{
			if(getDiff)
				return false;
			getDiff = true;
			if(s[lIdx+1]==s[rIdx])
				lIdx++;
			else if(s[lIdx]==s[rIdx-1])
				rIdx--;
			else if(rIdx+1 < s.size() && s[lIdx]==s[rIdx+1])
				lIdx++;
			else if(lIdx-1 >=0 && s[lIdx-1]==s[rIdx])
				rIdx++;
			else
				return false;
		}
		else
		{
			lIdx++;
			rIdx--;
		}
	}
	return true;
}
int repeatedStringMatch(string A, string B) {
	bool checked = false;
	for(int i=0;i<A.size();i++)
	{
		if(A[i]==B[i])
		{
			checked = true;
			int j=0;
			for(;j<B.size();j++)
			{
				if(A[(i+j)%A.size()] != B[j])
				{
					checked = false;
					break;
				}
			}
			if(checked)
				return (i+B.size())%A.size()?(i+B.size())/A.size():(i+B.size())/A.size()-1;
		}
	}
	return -1;
}
class Z
{
public:
	virtual void printM(int n){printN(n);}
	virtual void printN(int n){cout << n << endl;}
};
class Z1:public Z{};
class Z2:public Z{
public:
	void printM(int n){printN(n);}
	virtual void printN(int n){cout << n+1 << endl;}
};
queue<int> myqueue;
void queueFunc()
{
	while(1)
	{
		if(!myqueue.empty())
		{
			cout << " get value from myqueue:" <<myqueue.front() << endl;
			myqueue.pop();
		}
		else
			usleep(200*1000);
	}
	return;
}
class FUNC
{
public:
	FUNC(int num):num_(num){}
	void printN() const {cout << num_ << endl;}
	void func1(int i) const {cout << "func1:" << i << endl;}
	void func2(int i) const {cout << "func2:" << i << endl;}
	friend void ThrFunc4(FUNC& Func);
	friend void myTimerThrFunc3(const map<int,function<void(int)>>& timerCbFuncs) ;
private:
	int num_;
};
void ThrFunc4(FUNC& Func) 
{
	cout << "ThrFunc4:";
	Func.printN();
}
void myTimerThrFunc3(const map<int,function<void(int)>>& timerCbFuncs)
{
	int i=0;
	for(auto it=timerCbFuncs.begin();it!=timerCbFuncs.end();it++)
	{
		cout << "get the timer :" << it->first << endl;
		while(i<it->first)
		{
			cout << "i:" <<i << endl;
			sleep(1);
			++i;
		}
		it->second(it->first);
		cout << "finish the timer:" << it->first <<endl;
	}
}
void myTimerThrFunc2(const map<int,function<void(const FUNC&,int)>>& timerCbFuncs,const FUNC& func)
{
	int i=0;
	for(auto it=timerCbFuncs.begin();it!=timerCbFuncs.end();it++)
	{
		cout << "get the timer :" << it->first << endl;
		while(i<it->first)
		{
			cout << "i:" <<i << endl;
			sleep(1);
			++i;
		}
		it->second(func,it->first);
		// function<void(const FUNC&,int)> tmp = it->second;
		// tmp(func,it->first);
		cout << "finish the timer:" << it->first <<endl;
	}
}
class FangFunc{
	void operator()(int i) const {
		cout << i << endl;
	}
};
void showAry(const vector<int>& ary)
{
	for(auto n : ary)
		cout << n << ' ' ;
	cout << endl;
}
void quickSort(vector<int> &ary,int l,int r)
{
	if(l<r)
	{
		int x=ary[l],i=l,j=r;
		while(i<j)
		{
			while(i<j && ary[j]>=x)
				j--;
			if(i<j)
			{
				ary[i++]=ary[j];
			}
			showAry(ary);
			while(i<j && ary[i]<x)
				i++;
			if(i<j)
			{
				ary[j--]=ary[i];
			}
			showAry(ary);
		}
		ary[i]=x;
		quickSort(ary,l,i-1);
		quickSort(ary,i+1,r);
	}
}
vector<int> topK(vector<int> &nums,int k)
{
	priority_queue<int,vector<int>,greater<int>> pq(nums.begin(),nums.begin()+k);
	for(int i=k;i<nums.size();i++)
	{
		if(nums[i]>pq.top())
		{
			pq.pop();
			pq.push(nums[i]);
		}
	}
	vector<int> res;
	while(!pq.empty())
	{
		res.push_back(pq.top());
		pq.pop();
	}
	return res;
}
void topK2(vector<int> &nums,int k)
{
	for(int i=0;i<k;i++)
	{
		for(int j=i+1;j<nums.size();j++)
		{
			if(nums[i]<nums[j])
				std::swap(nums[i],nums[j]);
		}
	}
}
ListNode* reverseList2(ListNode* head)
{
	if(head == NULL)
		return NULL;
	ListNode* pre=head;
	ListNode* cur=head->next;
	pre->next=NULL;
	ListNode* tmp=NULL;
	while(cur!=NULL)
	{
		cout << "val:" << cur->val << endl;
		tmp=cur->next;
		cur->next=pre;
		pre=cur;
		cur=tmp;
	}
	return pre;
}
ListNode* reverseListK(ListNode* head,int k)
{
	if(head == NULL)
		return NULL;
	ListNode* pre=head;
	ListNode* cur=head->next;
	ListNode* first=pre;
	ListNode* tmp=NULL;
	int cnt=0;
	while(cur!=NULL)
	{
		if(++cnt >=k)
		{
			first->next=tmp;
			break;
		}
		cout << "val:" << cur->val << endl;
		tmp=cur->next;
		cur->next=pre;
		pre=cur;
		cur=tmp;
		
	}
	return pre;
}
int main(int argc, char const *argv[])
{
	std::vector<int> nums{1,2,3,4,5,6,7};
	std::vector<int> nums2{1,3,2,4,6,5,7};
	cout << "sort nums1:::::::::" << endl;
	quickSort(nums,0,6);
	showAry(nums);
	cout << "sort nums2:::::::::" << endl;
	// quickSort(nums2,0,6);
	// showAry(nums2);
	priority_queue<int> pq1(nums2.begin(),nums2.end());
	while(!pq1.empty())
	{
		cout << pq1.top() << " ";
		pq1.pop();
	}
	cout <<endl;
	priority_queue<int,vector<int>,greater<int>> pq2(nums2.begin(),nums2.end());
	while(!pq2.empty())
	{
		cout << pq2.top() << " ";
		pq2.pop();
	}
	cout <<endl;
	vector<int> res=topK(nums2,4);
	cout << "res::::::::::::::" <<endl;
	showAry(res);
	topK2(nums2,4);
	cout << "topK2:::::::::::::" <<endl;
	showAry(nums2);
	ListNode* list=new ListNode(1);
	ListNode* head=list;
	head->next=new ListNode(2);
	head=head->next;
	head->next=new ListNode(3);
	head=head->next;
	head->next=new ListNode(4);
	head=head->next;
	head->next=new ListNode(5);
	head=head->next;
	ListNode* revList=reverseListK(list,3);
	cout << "revListK:::::::::::::::" <<endl;
	while(revList)
	{
		cout << revList->val << " ";
		ListNode* tmp=revList;
		revList=revList->next;
		delete tmp;
	}
	cout <<endl;
	#if 1
	/*queue<int> times;
	times.push(5);
	times.push(10);
	times.push(20);
	std::thread thr1(myTimerThrFunc,thr_func2,times);
    thr1.join();
    cout << "now the thread is to exit" << endl;*/
    int c=10;
    function<void(int,int)> f1=[&](int a,int b){\
    	c=a+b;
    };
    f1(3,8);
    cout << "c:" <<c << endl;
    function<void(const FUNC&)> f2=&FUNC::printN;
    FUNC myfunc(10);
    f2(myfunc);
    function<void(FUNC&)> f4=ThrFunc4;
    f4(myfunc);
    // function<void(int)> f3=FangFunc();
    // f3(6);
    /*auto f4= [](int a,int b,int c){
    	cout << a+b+c << endl;
    };
    f4(1,2,4);
    map<int,function<void(const FUNC&,int)>> timerCbFuncs;
    timerCbFuncs[5] = &FUNC::func1;
    timerCbFuncs[10] = &FUNC::func2;
    // std::thread thr2(myTimerThrFunc2,timerCbFuncs,myfunc);
    // thr2.join();
    std::thread thr3(myTimerThrFunc3,timerCbFuncs);
    thr3.join();
    cout << "now the thread is to exit" << endl;*/
    #endif
	return 0;
}
#include "te.h"
int mtest(int argc, char const *argv[])
{
	int num;
	#if 0
	while(cin>>num)
	{
		pthread_mutex_init(&mtx12,NULL);
		pthread_mutex_init(&mtx23,NULL);
		pthread_mutex_init(&mtx34,NULL);
		pthread_mutex_init(&mtx41,NULL);
		pthread_create(&thr1,NULL,thread_func1,(void*)&num);
		pthread_detach(thr1);
		
		usleep(10000);
		pthread_create(&thr2,NULL,thread_func2,NULL);
		pthread_detach(thr2);
		usleep(10000);
		// if(upthr4)
		{
			pthread_create(&thr3,NULL,thread_func3,NULL);
			pthread_detach(thr3);
		}
		
		// if(upthr3)
		// {
		// 	pthread_create(&thr2,NULL,thread_func2,NULL);
		// 	pthread_detach(thr2);
		// }
		usleep(10000);	
		// if(upthr2)
		{
			// pthread_create(&thr1,NULL,thread_func1,(void*)&num);
			// pthread_detach(thr1);
		}
		pthread_create(&thr4,NULL,thread_func4,NULL);	
		pthread_join(thr4,NULL);
		pthread_mutex_destroy(&mtx12);
		pthread_mutex_destroy(&mtx23);
		pthread_mutex_destroy(&mtx34);
		pthread_mutex_destroy(&mtx41);
		cout << thrRes << endl;
		thrRes.erase(thrRes.begin(),thrRes.end());
	}
	#endif
	/*int num;
	while(cin>>num)
	{
		cout << getContinualOne(num) <<endl;
	}*/
	/*string str;
	while(getline(cin,str))
	{
		cout << joker(str) << endl;
		// cout << markPasswd(str) << endl;
		// cout << maxHuiwen(str) <<endl;
		// cout << getUpperChar(str) <<endl;
		// printf("%d\n",checkStrInclude(str1,str2)?"true":"false" );
	}*/
	/*int num;
	while(cin>>num)
	{
		vector<int> divisors;
		get_divisors(num,divisors);
		for(int i=0;i<divisors.size();i++)
			cout << divisors[i] << ' ';
		cout << endl;
	}*/
	/*
	while(cin>>str1 && cin>>str2)
	{
		cout << getMaxCommonStrLen(str1,str2)<< endl;
	}*/
	/*while(getline(cin,str))
	{
		vector<string> args;
		parseStr(str,args);
		cout << args.size() << endl;
		for(int i=0;i<args.size();i++)
			cout << args[i] << endl;
		// cout << MarkNum(str) << endl;
	}*/
	/*int n;
	int iSortFlag;
	while(cin>>n)
	{
		vector<int > pIntegerArray(n,0);
		for(int i=0;i<n;i++)
		{
			cin>>pIntegerArray[i];
		}
		cin >>iSortFlag;
		sortIntegerArray(pIntegerArray,iSortFlag);
		for(auto i : pIntegerArray)
			cout << i << ' ';
		cout << endl;
	}*/
	/*string str;
	while(cin>>str)
	{
		charCnt(str);
	}*/
	/*int n;
	while(cin>>n)
	{
		vector<int > nums(n);
		for(int i=0;i<n;i++)
		{
			cin>>nums[i];
		}
		vector<int> ve;
		vector<int> upper;
        ve.push_back(nums[0]);
        upper.push_back(nums[0]);
		// cout << getMaxToTop(nums) << endl;
		// vector<int> idxs;
		// cout << "max:"<<getMaxAndIdx(nums,idxs) << endl;
		// for(int i=0;i<idxs.size();i++)
		// 	cout << idxs[i] << " ";
		// cout << endl;
		vector<int >::iterator itlower;
		vector<int >::iterator itupper;
		for(int i=1;i<nums.size();i++)
		{
			itlower = lower_bound(ve.begin(),ve.end(),nums[i]);
			if(itlower==ve.end())
				ve.push_back(nums[i]);
			else
			{
				printf("num:%d,itlower:%d\n",nums[i],*itlower );
				*itlower = nums[i];
			}
		}
		for(int i=0;i<ve.size();i++)
			cout << ve[i] << " ";
		cout << endl;
	}*/
	/*double num;
	while(cin>>num)
	{
		// cout << getCubeRoot(num) << endl;
		printf("%.1lf\n", getCubeRoot(num));
	}*/
	/*int a,b;
	while(cin>>a>>b)
	{
		cout << gongbei(a,b) << endl;
	}*/
	#if 0
	int nodeCnt;
	int rootKey;
	myListNode* list=NULL;
	int sonkey,fatherkey,delkey;
	while(cin >> nodeCnt)
	{
		cin>>rootKey;
		// scanf("%d\n",&rootKey);
		list_init(&list,rootKey);
		for(int i=0;i<nodeCnt-1;i++)
		{
			cin >> sonkey >> fatherkey;
			// scanf("%d%d\n",&sonkey,&fatherkey);
			list_insert(list,fatherkey,sonkey);
		}
		cin >>delkey;
		// scanf("%d\n",&delkey);
		list_del(list,delkey);
		list_display(list);
		list_deinit(&list);
		cout << endl;
		
	}
	#endif
	/*int n;
	string str;
	while(cin>>str)
	{
		// scanf("%d\n",&n);
		cin >> n;
		cout << cutStr(str,n) <<endl;
	}*/
	/*int n;
	string name;
	while(scanf("%d\n",&n)!=EOF)
	{
		for(int i=0;i<n;i++)
		{
			cin>>name;
			cout << get_max_beauty(name) << endl;
		}
	}*/
	/*int X,Y;
	while(cin >> Y && cin>>X )
	{
		vector<vector<int> > maze;
		for(int i=0;i<Y;i++)
		{
			vector<int> xary(X);
			for(int j=0;j<X;j++)
				cin>>xary[j];
			maze.push_back(xary);
		}
		vector<int> xpos;
		vector<int> ypos;
		runmaze(Y,X,maze,xpos,ypos);
		for(int i=0;i<xpos.size();i++)
		{
			cout << '(' << ypos[i] << ',' <<  xpos[i] << ')' << endl;
		}
		
	}*/
	// long num;
	// while(cin>>num)
	// {
	// 	cout << parseNum(num) << endl;
	// }
	// recordLog();
	// checkIP();
	// cout << ipvalid("10.70.44.68") << endl;
	// cout << ipvalid("123.123.123.123")<< endl;
	// cout << ipvalid("123.123..")<< endl;
	// movePos();
	// sortLine();
	// reverceLine();
	// uniqueInt();
	//combineTable();
	// cout << getNearInt() << endl;
	// zhishu();
	/*cout <<"strStr:" <<strStr("mississippi","issip") << endl;*/
	/*cout << "mulSingle:" << mulSingle("18765",'5',0) << endl;
	vector<string > nums={"9","89"};
	vector<string > nums={"9","99","999","9999","99999"};
	vector<string > nums={"045600","09120","1368"};
	cout << "addStr:" << addStr(nums) << endl;

	cout <<"multiply:" << multiply("0","456") << endl;*/
	// vector<int> nums = {4,5,6,7,0,1,2,3};
	// vector<int> nums = {3,1};
	// cout << "search:" << search(nums,7) << endl;
	/*ListNode* l1 = new ListNode(5);
	// l1->next = new ListNode(2);
	ListNode* l2 = new ListNode(5);
	// l2->next = new ListNode(3);
	displayL(l1);
	displayL(l2);
	// ListNode* l3 = mergeTwoLists(l1,l2);
	ListNode* l3 = addTwoNumbers(l1,l2);
	displayL(l3);*/
	/*map<char,char> cmap;
	cmap.insert(pair<char,char>('a','b'));
	cout << cmap['a'] << endl;
	vector<string> strs;
	strs.push_back("hello");
	strs.push_back("my");
	strs.push_back("name");
	strs.push_back("is");
	strs.push_back("lxc");
	sort(strs.begin(),strs.end());
	for(auto it=strs.begin();it!=strs.end();it++)
	{
		cout << *it << " " ;
	}
	cout << endl;
	sortStr(strs);
	for(auto it=strs.begin();it!=strs.end();it++)
	{
		cout << *it << " " ;
	}
	cout << endl;*/
	// cout << myAtoi("    -42 4")<<endl;
	// cout << "res str:" <<longestPalindrome("cccccbbccccc")<<endl;
	#if 0
	vector<int> nums={82597,-9243,62390,83030,-97960,-26521,-61011,83390,-38677,12333,75987,46091,83794,19355,-71037,-6242,-28801,324,1202,-90885,-2989,-95597,-34333,35528,5680,89093,-90606,50360,-29393,-27012,53313,65213,99818,-82405,-41661,-3333,-51952,72135,-1523,26377,74685,96992,92263,15929,5467,-99555,-43348,-41689,-60383,-3990,32165,65265,-72973,-58372,12741,-48568,-46596,72419,-1859,34153,62937,81310,-61823,-96770,-54944,8845,-91184,24208,-29078,31495,65258,14198,85395,70506,-40908,56740,-12228,-40072,32429,93001,68445,-73927,25731,-91859,-24150,10093,-60271,-81683,-18126,51055,48189,-6468,25057,81194,-58628,74042,66158,-14452,-49851,-43667,11092,39189,-17025,-79173,13606,83172,92647,-59741,19343,-26644,-57607,82908,-20655,1637,80060,98994,39331,-31274,-61523,91225,-72953,13211,-75116,-98421,-41571,-69074,99587,39345,42151,-2460,98236,15690,-52507,-95803,-48935,-46492,-45606,-79254,-99851,52533,73486,39948,-7240,71815,-585,-96252,90990,-93815,93340,-71848,58733,-14859,-83082,-75794,-82082,-24871,-15206,91207,-56469,-93618,67131,-8682,75719,87429,-98757,-7535,-24890,-94160,85003,33928,75538,97456,-66424,-60074,-8527,-28697,-22308,2246,-70134,-82319,-10184,87081,-34949,-28645,-47352,-83966,-60418,-15293,-53067,-25921,55172,75064,95859,48049,34311,-86931,-38586,33686,-36714,96922,76713,-22165,-80585,-34503,-44516,39217,-28457,47227,-94036,43457,24626,-87359,26898,-70819,30528,-32397,-69486,84912,-1187,-98986,-32958,4280,-79129,-65604,9344,58964,50584,71128,-55480,24986,15086,-62360,-42977,-49482,-77256,-36895,-74818,20,3063,-49426,28152,-97329,6086,86035,-88743,35241,44249,19927,-10660,89404,24179,-26621,-6511,57745,-28750,96340,-97160,-97822,-49979,52307,79462,94273,-24808,77104,9255,-83057,77655,21361,55956,-9096,48599,-40490,-55107,2689,29608,20497,66834,-34678,23553,-81400,-66630,-96321,-34499,-12957,-20564,25610,-4322,-58462,20801,53700,71527,24669,-54534,57879,-3221,33636,3900,97832,-27688,-98715,5992,24520,-55401,-57613,-69926,57377,-77610,20123,52174,860,60429,-91994,-62403,-6218,-90610,-37263,-15052,62069,-96465,44254,89892,-3406,19121,-41842,-87783,-64125,-56120,73904,-22797,-58118,-4866,5356,75318,46119,21276,-19246,-9241,-97425,57333,-15802,93149,25689,-5532,95716,39209,-87672,-29470,-16324,-15331,27632,-39454,56530,-16000,29853,46475,78242,-46602,83192,-73440,-15816,50964,-36601,89758,38375,-40007,-36675,-94030,67576,46811,-64919,45595,76530,40398,35845,41791,67697,-30439,-82944,63115,33447,-36046,-50122,-34789,43003,-78947,-38763,-89210,32756,-20389,-31358,-90526,-81607,88741,86643,98422,47389,-75189,13091,95993,-15501,94260,-25584,-1483,-67261,-70753,25160,89614,-90620,-48542,83889,-12388,-9642,-37043,-67663,28794,-8801,13621,12241,55379,84290,21692,-95906,-85617,-17341,-63767,80183,-4942,-51478,30997,-13658,8838,17452,-82869,-39897,68449,31964,98158,-49489,62283,-62209,-92792,-59342,55146,-38533,20496,62667,62593,36095,-12470,5453,-50451,74716,-17902,3302,-16760,-71642,-34819,96459,-72860,21638,47342,-69897,-40180,44466,76496,84659,13848,-91600,-90887,-63742,-2156,-84981,-99280,94326,-33854,92029,-50811,98711,-36459,-75555,79110,-88164,-97397,-84217,97457,64387,30513,-53190,-83215,252,2344,-27177,-92945,-89010,82662,-11670,86069,53417,42702,97082,3695,-14530,-46334,17910,77999,28009,-12374,15498,-46941,97088,-35030,95040,92095,-59469,-24761,46491,67357,-66658,37446,-65130,-50416,99197,30925,27308,54122,-44719,12582,-99525,-38446,-69050,-22352,94757,-56062,33684,-40199,-46399,96842,-50881,-22380,-65021,40582,53623,-76034,77018,-97074,-84838,-22953,-74205,79715,-33920,-35794,-91369,73421,-82492,63680,-14915,-33295,37145,76852,-69442,60125,-74166,74308,-1900,-30195,-16267,-60781,-27760,5852,38917,25742,-3765,49097,-63541,98612,-92865,-30248,9612,-8798,53262,95781,-42278,-36529,7252,-27394,-5021,59178,80934,-48480,-75131,-54439,-19145,-48140,98457,-6601,-51616,-89730,78028,32083,-48904,16822,-81153,-8832,48720,-80728,-45133,-86647,-4259,-40453,2590,28613,50523,-4105,-27790,-74579,-17223,63721,33489,-47921,97628,-97691,-14782,-65644,18008,-93651,-71266,80990,-76732,-47104,35368,28632,59818,-86269,-89753,34557,-92230,-5933,-3487,-73557,-13174,-43981,-43630,-55171,30254,-83710,-99583,-13500,71787,5017,-25117,-78586,86941,-3251,-23867,-36315,75973,86272,-45575,77462,-98836,-10859,70168,-32971,-38739,-12761,93410,14014,-30706,-77356,-85965,-62316,63918,-59914,-64088,1591,-10957,38004,15129,-83602,-51791,34381,-89382,-26056,8942,5465,71458,-73805,-87445,-19921,-80784,69150,-34168,28301,-68955,18041,6059,82342,9947,39795,44047,-57313,48569,81936,-2863,-80932,32976,-86454,-84207,33033,32867,9104,-16580,-25727,80157,-70169,53741,86522,84651,68480,84018,61932,7332,-61322,-69663,76370,41206,12326,-34689,17016,82975,-23386,39417,72793,44774,-96259,3213,79952,29265,-61492,-49337,14162,65886,3342,-41622,-62659,-90402,-24751,88511,54739,-21383,-40161,-96610,-24944,-602,-76842,-21856,69964,43994,-15121,-85530,12718,13170,-13547,69222,62417,-75305,-81446,-38786,-52075,-23110,97681,-82800,-53178,11474,35857,94197,-58148,-23689,32506,92154,-64536,-73930,-77138,97446,-83459,70963,22452,68472,-3728,-25059,-49405,95129,-6167,12808,99918,30113,-12641,-26665,86362,-33505,50661,26714,33701,89012,-91540,40517,-12716,-57185,-87230,29914,-59560,13200,-72723,58272,23913,-45586,-96593,-26265,-2141,31087,81399,92511,-34049,20577,2803,26003,8940,42117,40887,-82715,38269,40969,-50022,72088,21291,-67280,-16523,90535,18669,94342,-39568,-88080,-99486,-20716,23108,-28037,63342,36863,-29420,-44016,75135,73415,16059,-4899,86893,43136,-7041,33483,-67612,25327,40830,6184,61805,4247,81119,-22854,-26104,-63466,63093,-63685,60369,51023,51644,-16350,74438,-83514,99083,10079,-58451,-79621,48471,67131,-86940,99093,11855,-22272,-67683,-44371,9541,18123,37766,-70922,80385,-57513,-76021,-47890,36154,72935,84387,-92681,-88303,-7810,59902,-90,-64704,-28396,-66403,8860,13343,33882,85680,7228,28160,-14003,54369,-58893,92606,-63492,-10101,64714,58486,29948,-44679,-22763,10151,-56695,4031,-18242,-36232,86168,-14263,9883,47124,47271,92761,-24958,-73263,-79661,-69147,-18874,29546,-92588,-85771,26451,-86650,-43306,-59094,-47492,-34821,-91763,-47670,33537,22843,67417,-759,92159,63075,94065,-26988,55276,65903,30414,-67129,-99508,-83092,-91493,-50426,14349,-83216,-76090,32742,-5306,-93310,-60750,-60620,-45484,-21108,-58341,-28048,-52803,69735,78906,81649,32565,-86804,-83202,-65688,-1760,89707,93322,-72750,84134,71900,-37720,19450,-78018,22001,-23604,26276,-21498,65892,-72117,-89834,-23867,55817,-77963,42518,93123,-83916,63260,-2243,-97108,85442,-36775,17984,-58810,99664,-19082,93075,-69329,87061,79713,16296,70996,13483,-74582,49900,-27669,-40562,1209,-20572,34660,83193,75579,7344,64925,88361,60969,3114,44611,-27445,53049,-16085,-92851,-53306,13859,-33532,86622,-75666,-18159,-98256,51875,-42251,-27977,-18080,23772,38160,41779,9147,94175,99905,-85755,62535,-88412,-52038,-68171,93255,-44684,-11242,-104,31796,62346,-54931,-55790,-70032,46221,56541,-91947,90592,93503,4071,20646,4856,-63598,15396,-50708,32138,-85164,38528,-89959,53852,57915,-42421,-88916,-75072,67030,-29066,49542,-71591,61708,-53985,-43051,28483,46991,-83216,80991,-46254,-48716,39356,-8270,-47763,-34410,874,-1186,-7049,28846,11276,21960,-13304,-11433,-4913,55754,79616,70423,-27523,64803,49277,14906,-97401,-92390,91075,70736,21971,-3303,55333,-93996,76538,54603,-75899,98801,46887,35041,48302,-52318,55439,24574,14079,-24889,83440,14961,34312,-89260,-22293,-81271,-2586,-71059,-10640,-93095,-5453,-70041,66543,74012,-11662,-52477,-37597,-70919,92971,-17452,-67306,-80418,7225,-89296,24296,86547,37154,-10696,74436,-63959,58860,33590,-88925,-97814,-83664,85484,-8385,-50879,57729,-74728,-87852,-15524,-91120,22062,28134,80917,32026,49707,-54252,-44319,-35139,13777,44660,85274,25043,58781,-89035,-76274,6364,-63625,72855,43242,-35033,12820,-27460,77372,-47578,-61162,-70758,-1343,-4159,64935,56024,-2151,43770,19758,-30186,-86040,24666,-62332,-67542,73180,-25821,-27826,-45504,-36858,-12041,20017,-24066,-56625,-52097,-47239,-90694,8959,7712,-14258,-5860,55349,61808,-4423,-93703,64681,-98641,-25222,46999,-83831,-54714,19997,-68477,66073,51801,-66491,52061,-52866,79907,-39736,-68331,68937,91464,98892,910,93501,31295,-85873,27036,-57340,50412,21,-2445,29471,71317,82093,-94823,-54458,-97410,39560,-7628,66452,39701,54029,37906,46773,58296,60370,-61090,85501,-86874,71443,-72702,-72047,14848,34102,77975,-66294,-36576,31349,52493,-70833,-80287,94435,39745,-98291,84524,-18942,10236,93448,50846,94023,-6939,47999,14740,30165,81048,84935,-19177,-13594,32289,62628,-90612,-542,-66627,64255,71199,-83841,-82943,-73885,8623,-67214,-9474,-35249,62254,-14087,-90969,21515,-83303,94377,-91619,19956,-98810,96727,-91939,29119,-85473,-82153,-69008,44850,74299,-76459,-86464,8315,-49912,-28665,59052,-69708,76024,-92738,50098,18683,-91438,18096,-19335,35659,91826,15779,-73070,67873,-12458,-71440,-46721,54856,97212,-81875,35805,36952,68498,81627,-34231,81712,27100,-9741,-82612,18766,-36392,2759,41728,69743,26825,48355,-17790,17165,56558,3295,-24375,55669,-16109,24079,73414,48990,-11931,-78214,90745,19878,35673,-15317,-89086,94675,-92513,88410,-93248,-19475,-74041,-19165,32329,-26266,-46828,-18747,45328,8990,-78219,-25874,-74801,-44956,-54577,-29756,-99822,-35731,-18348,-68915,-83518,-53451,95471,-2954,-13706,-8763,-21642,-37210,16814,-60070,-42743,27697,-36333,-42362,11576,85742,-82536,68767,-56103,-63012,71396,-78464,-68101,-15917,-11113,-3596,77626,-60191,-30585,-73584,6214,-84303,18403,23618,-15619,-89755,-59515,-59103,-74308,-63725,-29364,-52376,-96130,70894,-12609,50845,-2314,42264,-70825,64481,55752,4460,-68603,-88701,4713,-50441,-51333,-77907,97412,-66616,-49430,60489,-85262,-97621,-18980,44727,-69321,-57730,66287,-92566,-64427,-14270,11515,-92612,-87645,61557,24197,-81923,-39831,-10301,-23640,-76219,-68025,92761,-76493,68554,-77734,-95620,-11753,-51700,98234,-68544,-61838,29467,46603,-18221,-35441,74537,40327,-58293,75755,-57301,-7532,-94163,18179,-14388,-22258,-46417,-48285,18242,-77551,82620,250,-20060,-79568,-77259,82052,-98897,-75464,48773,-79040,-11293,45941,-67876,-69204,-46477,-46107,792,60546,-34573,-12879,-94562,20356,-48004,-62429,96242,40594,2099,99494,25724,-39394,-2388,-18563,-56510,-83570,-29214,3015,74454,74197,76678,-46597,60630,-76093,37578,-82045,-24077,62082,-87787,-74936,58687,12200,-98952,70155,-77370,21710,-84625,-60556,-84128,925,65474,-15741,-94619,88377,89334,44749,22002,-45750,-93081,-14600,-83447,46691,85040,-66447,-80085,56308,44310,24979,-29694,57991,4675,-71273,-44508,13615,-54710,23552,-78253,-34637,50497,68706,81543,-88408,-21405,6001,-33834,-21570,-46692,-25344,20310,71258,-97680,11721,59977,59247,-48949,98955,-50276,-80844,-27935,-76102,55858,-33492,40680,66691,-33188,8284,64893,-7528,6019,-85523,8434,-64366,-56663,26862,30008,-7611,-12179,-70076,21426,-11261,-36864,-61937,-59677,929,-21052,3848,-20888,-16065,98995,-32293,-86121,-54564,77831,68602,74977,31658,40699,29755,98424,80358,-69337,26339,13213,-46016,-18331,64713,-46883,-58451,-70024,-92393,-4088,70628,-51185,71164,-75791,-1636,-29102,-16929,-87650,-84589,-24229,-42137,-15653,94825,13042,88499,-47100,-90358,-7180,29754,-65727,-42659,-85560,-9037,-52459,20997,-47425,17318,21122,20472,-23037,65216,-63625,-7877,-91907,24100,-72516,22903,-85247,-8938,73878,54953,87480,-31466,-99524,35369,-78376,89984,-15982,94045,-7269,23319,-80456,-37653,-76756,2909,81936,54958,-12393,60560,-84664,-82413,66941,-26573,-97532,64460,18593,-85789,-38820,-92575,-43663,-89435,83272,-50585,13616,-71541,-53156,727,-27644,16538,34049,57745,34348,35009,16634,-18791,23271,-63844,95817,21781,16590,59669,15966,-6864,48050,-36143,97427,-59390,96931,78939,-1958,50777,43338,-51149,39235,-27054,-43492,67457,-83616,37179,10390,85818,2391,73635,87579,-49127,-81264,-79023,-81590,53554,-74972,-83940,-13726,-39095,29174,78072,76104,47778,25797,-29515,-6493,-92793,22481,-36197,-65560,42342,15750,97556,99634,-56048,-35688,13501,63969,-74291,50911,39225,93702,-3490,-59461,-30105,-46761,-80113,92906,-68487,50742,36152,-90240,-83631,24597,-50566,-15477,18470,77038,40223,-80364,-98676,70957,-63647,99537,13041,31679,86631,37633,-16866,13686,-71565,21652,-46053,-80578,-61382,68487,-6417,4656,20811,67013,-30868,-11219,46,74944,14627,56965,42275,-52480,52162,-84883,-52579,-90331,92792,42184,-73422,-58440,65308,-25069,5475,-57996,59557,-17561,2826,-56939,14996,-94855,-53707,99159,43645,-67719,-1331,21412,41704,31612,32622,1919,-69333,-69828,22422,-78842,57896,-17363,27979,-76897,35008,46482,-75289,65799,20057,7170,41326,-76069,90840,-81253,-50749,3649,-42315,45238,-33924,62101,96906,58884,-7617,-28689,-66578,62458,50876,-57553,6739,41014,-64040,-34916,37940,13048,-97478,-11318,-89440,-31933,-40357,-59737,-76718,-14104,-31774,28001,4103,41702,-25120,-31654,63085,-3642,84870,-83896,-76422,-61520,12900,88678,85547,33132,-88627,52820,63915,-27472,78867,-51439,33005,-23447,-3271,-39308,39726,-74260,-31874,-36893,93656,910,-98362,60450,-88048,99308,13947,83996,-90415,-35117,70858,-55332,-31721,97528,82982,-86218,6822,25227,36946,97077,-4257,-41526,56795,89870,75860,-70802,21779,14184,-16511,-89156,-31422,71470,69600,-78498,74079,-19410,40311,28501,26397,-67574,-32518,68510,38615,19355,-6088,-97159,-29255,-92523,3023,-42536,-88681,64255,41206,44119,52208,39522,-52108,91276,-70514,83436,63289,-79741,9623,99559,12642,85950,83735,-21156,-67208,98088,-7341,-27763,-30048,-44099,-14866,-45504,-91704,19369,13700,10481,-49344,-85686,33994,19672,36028,60842,66564,-24919,33950,-93616,-47430,-35391,-28279,56806,74690,39284,-96683,-7642,-75232,37657,-14531,-86870,-9274,-26173,98640,88652,64257,46457,37814,-19370,9337,-22556,-41525,39105,-28719,51611,-93252,98044,-90996,21710,-47605,-64259,-32727,53611,-31918,-3555,33316,-66472,21274,-37731,-2919,15016,48779,-88868,1897,41728,46344,-89667,37848,68092,-44011,85354,-43776,38739,-31423,-66330,65167,-22016,59405,34328,-60042,87660,-67698,-59174,-1408,-46809,-43485,-88807,-60489,13974,22319,55836,-62995,-37375,-4185,32687,-36551,-75237,58280,26942,-73756,71756,78775,-40573,14367,-71622,-77338,24112,23414,-7679,-51721,87492,85066,-21612,57045,10673,-96836,52461,-62218,-9310,65862,-22748,89906,-96987,-98698,26956,-43428,46141,47456,28095,55952,67323,-36455,-60202,-43302,-82932,42020,77036,10142,60406,70331,63836,58850,-66752,52109,21395,-10238,-98647,-41962,27778,69060,98535,-28680,-52263,-56679,66103,-42426,27203,80021,10153,58678,36398,63112,34911,20515,62082,-15659,-40785,27054,43767,-20289,65838,-6954,-60228,-72226,52236,-35464,25209,-15462,-79617,-41668,-84083,62404,-69062,18913,46545,20757,13805,24717,-18461,-47009,-25779,68834,64824,34473,39576,31570,14861,-15114,-41233,95509,68232,67846,84902,-83060,17642,-18422,73688,77671,-26930,64484,-99637,73875,6428,21034,-73471,19664,-68031,15922,-27028,48137,54955,-82793,-41144,-10218,-24921,-28299,-2288,68518,-54452,15686,-41814,66165,-72207,-61986,80020,50544,-99500,16244,78998,40989,14525,-56061,-24692,-94790,21111,37296,-90794,72100,70550,-31757,17708,-74290,61910,78039,-78629,-25033,73172,-91953,10052,64502,99585,-1741,90324,-73723,68942,28149,30218,24422,16659,10710,-62594,94249,96588,46192,34251,73500,-65995,-81168,41412,-98724,-63710,-54696,-52407,19746,45869,27821,-94866,-76705,-13417,-61995,-71560,43450,67384,-8838,-80293,-28937,23330,-89694,-40586,46918,80429,-5475,78013,25309,-34162,37236,-77577,86744,26281,-29033,-91813,35347,13033,-13631,-24459,3325,-71078,-75359,81311,19700,47678,-74680,-84113,45192,35502,37675,19553,76522,-51098,-18211,89717,4508,-82946,27749,85995,89912,-53678,-64727,-14778,32075,-63412,-40524,86440,-2707,-36821,63850,-30883,67294,-99468,-23708,34932,34386,98899,29239,-23385,5897,54882,98660,49098,70275,17718,88533,52161,63340,50061,-89457,19491,-99156,24873,-17008,64610,-55543,50495,17056,-10400,-56678,-29073,-42960,-76418,98562,-88104,-96255,10159,-90724,54011,12052,45871,-90933,-69420,67039,37202,78051,-52197,-40278,-58425,65414,-23394,-1415,6912,-53447,7352,17307,-78147,63727,98905,55412,-57658,-32884,-44878,22755,39730,3638,35111,39777,74193,38736,-11829,-61188,-92757,55946,-71232,-63032,-83947,39147,-96684,-99233,25131,-32197,24406,-55428,-61941,25874,-69453,64483,-19644,-68441,12783,87338,-48676,66451,-447,-61590,50932,-11270,29035,65698,-63544,10029,80499,-9461,86368,91365,-81810,-71914,-52056,-13782,44240,-30093,-2437,24007,67581,-17365,-69164,-8420,-69289,-29370,48010,90439,13141,69243,50668,39328,61731,78266,-81313,17921,-38196,55261,9948,-24970,75712,-72106,28696,7461,31621,61047,51476,56512,11839,-96916,-82739,28924,-99927,58449,37280,69357,11219,-32119,-62050,-48745,-83486,-52376,42668,82659,68882,38773,46269,-96005,97630,25009,-2951,-67811,99801,81587,-79793,-18547,-83086,69512,33127,-92145,-88497,47703,59527,1909,88785,-88882,69188,-46131,-5589,-15086,36255,-53238,-33009,82664,53901,35939,-42946,-25571,33298,69291,53199,74746,-40127,-39050,91033,51717,-98048,87240,36172,65453,-94425,-63694,-30027,59004,88660,3649,-20267,-52565,-67321,34037,4320,91515,-56753,60115,27134,68617,-61395,-26503,-98929,-8849,-63318,10709,-16151,61905,-95785,5262,23670,-25277,90206,-19391,45735,37208,-31992,-92450,18516,-90452,-58870,-58602,93383,14333,17994,82411,-54126,-32576,35440,-60526,-78764,-25069,-9022,-394,92186,-38057,55328,-61569,67780,77169,19546,-92664,-94948,44484,-13439,83529,27518,-48333,72998,38342,-90553,-98578,-76906,81515,-16464,78439,92529,35225,-39968,-10130,-7845,-32245,-74955,-74996,67731,-13897,-82493,33407,93619,59560,-24404,-57553,19486,-45341,34098,-24978,-33612,79058,71847,76713,-95422,6421,-96075,-59130,-28976,-16922,-62203,69970,68331,21874,40551,89650,51908,58181,66480,-68177,34323,-3046,-49656,-59758,43564,-10960,-30796,15473,-20216,46085,-85355,41515,-30669,-87498,57711,56067,63199,-83805,62042,91213,-14606,4394,-562,74913,10406,96810,-61595,32564,31640,-9732,42058,98052,-7908,-72330,1558,-80301,34878,32900,3939,-8824,88316,20937,21566,-3218,-66080,-31620,86859,54289,90476,-42889,-15016,-18838,75456,30159,-67101,42328,-92703,85850,-5475,23470,-80806,68206,17764,88235,46421,-41578,74005,-81142,80545,20868,-1560,64017,83784,68863,-97516,-13016,-72223,79630,-55692,82255,88467,28007,-34686,-69049,-41677,88535,-8217,68060,-51280,28971,49088,49235,26905,-81117,-44888,40623,74337,-24662,97476,79542,-72082,-35093,98175,-61761,-68169,59697,-62542,-72965,59883,-64026,-37656,-92392,-12113,-73495,98258,68379,-21545,64607,-70957,-92254,-97460,-63436,-8853,-19357,-51965,-76582,12687,-49712,45413,-60043,33496,31539,-57347,41837,67280,-68813,52088,-13155,-86430,-15239,-45030,96041,18749,-23992,46048,35243,-79450,85425,-58524,88781,-39454,53073,-48864,-82289,39086,82540,-11555,25014,-5431,-39585,-89526,2705,31953,-81611,36985,-56022,68684,-27101,11422,64655,-26965,-63081,-13840,-91003,-78147,-8966,41488,1988,99021,-61575,-47060,65260,-23844,-21781,-91865,-19607,44808,2890,63692,-88663,-58272,15970,-65195,-45416,-48444,-78226,-65332,-24568,42833,-1806,-71595,80002,-52250,30952,48452,-90106,31015,-22073,62339,63318,78391,28699,77900,-4026,-76870,-45943,33665,9174,-84360,-22684,-16832,-67949,-38077,-38987,-32847,51443,-53580,-13505,9344,-92337,26585,70458,-52764,-67471,-68411,-1119,-2072,-93476,67981,40887,-89304,-12235,41488,1454,5355,-34855,-72080,24514,-58305,3340,34331,8731,77451,-64983,-57876,82874,62481,-32754,-39902,22451,-79095,-23904,78409,-7418,77916};
	#endif
	// vector<int> nums={1,2,-2,-1};
	/*vector<vector<int>> res = threeSum(nums);
	for(auto it=res.begin();it!=res.end();it++)
	{
		for(auto it2=(*it).begin();it2!=(*it).end();it2++)
		{
			cout << (*it2) << " " ;
		}
		cout << endl;
	}*/
	#if 0
	int aary[] = {1,45,5,1,33,4,667,854,324,777,888,999};
	int aary2[] = {1,45,5,1,33,4,667,854,324,777,888,999};
	sortM(aary,sizeof(aary)/sizeof(int));
	for(int i=0;i<sizeof(aary)/sizeof(int);i++)
		cout << aary[i] << " " ;
	cout << endl << "count:" << swapcount << endl;
	swapcount = 0;
	bubbleSort(aary2,0,sizeof(aary2)/sizeof(int));
	for(int i=0;i<sizeof(aary2)/sizeof(int);i++)
		cout << aary2[i] << " " ;
	cout << endl << "count:" << swapcount << endl;

	string strt = "112233445566778899123134526523653475324";
	elimDups(strt);
	cout << strt << endl;
	int sa = geta();
	int& psa = geta();
	cout << sa << psa << endl;
	int aint;
	TTYPE bTTYPE;
	checkType(aint);
	checkType(bTTYPE);
	cout << "straddx:" << straddx("idx",1) << endl;
	cout << "add(1):" << add(1) << endl;
	std::vector<int> v_int;
	v_int.push_back(1);
	std::vector<int> *pv_int = &v_int;
	cout << "size:" << pv_int->size() << "," << (*pv_int)[0]<<endl; 
	v_int.insert(v_int.begin(),2);
	cout << "size2:" << pv_int->size() << "," << (*pv_int)[0]<< "," << (*pv_int)[1]<< endl;
	deque<int> deque1;
	deque1.push_back(1);
	deque<int> *pdeque1 = &deque1;
	cout << "size:" << pdeque1->size() << "," << (*pdeque1)[0]<<endl;
	deque1.push_front(2);
	cout << "size2:" << pdeque1->size() << "," << (*pdeque1)[0]<< "," << (*pdeque1)[1]<<endl;
	testNode n1(1);
	n1.init("1");
	n1.a =2;
	n1.symbol = "2";
	// n1.a = 1;
	// n2 = n1;
	// testNode n3 = n1;
	cout << "printa:"  << endl;
	n1.printa();
	char *pa[5] ;
	char (*pb)[5];
	printf("sizeof(pa):%ld\n", sizeof(pa) );
	printf("sizeof(pb):%ld\n", sizeof(pb) );
	char ar[NUM];
	printf(" sizeof(ar):%ld\n",sizeof(ar) );
	float f_num = -10.2345;
	printf("f_num:%1.0f\n",f_num );
	char f_char[10] = {0};
	sprintf(f_char,"%2.0f",f_num);
	printf("f_char:%s\n",f_char);
	// AA a;
	AA *ap;
	BB b;
	CC c;
	CC c1(20);
	ap = &b;
	// a.print();
	b.print();
	c.print();
	c1.print();
	ap->print();
	string mtime1;
	string mtime2;
	get_fileTime("./test.cpp",mtime1);
	get_fileTime("./CStudent.cpp",mtime2);
	printf("%s\n",mtime1>=mtime2?"1>=2":"1<2" );
	int neg = -1;
	unsigned int pos = 1;
	printf("%s\n",(neg < pos)?"neg<pos":"pos<neg" );
	char char1[100]={0};
	strcpy(char1,"hello");
	get_charsize(char1);
	// get_charsize("hello");
	int N=0;
	#endif
	// mkdir("./newdir",00766);
	/*while(1)
	{
		cout << "input num to get the num of '1' in binary type:";
		cin >> N;
		cout<<"get_one:"<<get_one(N)<<endl;
		cout<<"getAddSum:"<<getAddSum(N)<<endl;
	}*/
	/*std::pair<int ,int> testpair(1,2);
	std::map<int ,int> testmap;
	// testmap.insert(testpair);
	testmap[2]=3;
	std::cout << testmap.size() << std::endl;
	std::map<int ,int>::iterator it;
	for(it =testmap.begin();it != testmap.end();it++)
	{
		std::cout << "11111111111" << std ::endl;
		std::cout << it->first << it->second <<testmap[it->first] << std::endl;
		std::cout << testmap[1] << std::endl;
		std::cout << testmap[2] << std::endl;
	}*/
#if 0
	std::vector<testNode> nodes;	
	std::vector<testNode*> pnodes;
	testNode node1;	
	testNode node2;	
	testNode node3;	
	node1.v.push_back(&node2);
	nodes.push_back(node1);
	nodes.push_back(node2);
	nodes.push_back(node3);
	pnodes.push_back(&node1);
	pnodes.push_back(&node2);
	pnodes.push_back(&node3);
	if(argc == 2)
	{
		char dirPath[256]={0};
		strcpy(dirPath,argv[1]);
		std::vector<std::string> Files;
		std::vector<std::string> EmptyDir;
		getFiles(std::string(dirPath),Files,EmptyDir);
		std::cout << "files:::::::::::::::::::" << std::endl;
		for(int i =0;i<Files.size();i++)
		{
			std::cout << Files[i] << " ";
		}
		std::cout << std::endl;
		std::cout << "emptyDir:::::::::::::::::::" << std::endl;
		for(int i =0;i<EmptyDir.size();i++)
		{
			std::cout << EmptyDir[i] << " ";
		}
		std::cout << std::endl;
	}
#endif		
	// vector<size_t> retv(testv.size());
	// retv = sort_indexes(testv);
	// vector<int>::iterator testIdx;
	// vector<size_t>::iterator retIdx;
	// for(int i = 0;i<testv.size();i++)
	// {
	// 	cout << testv[i] << " ";
	// }
	// cout << endl;
	// for(int i = 0;i<testv.size();i++)
	// {
	// 	cout << retv[i] << " ";
	// }
	// cout << endl;
#if 0
	thrflag = true;
	pthread_t thr = -1;
	pthread_create(&thr,NULL,thread_func1,NULL);
	printf("wait exit...........\n");
	pthread_join(thr,NULL);
	perror("join");
	
	return 0;

		

	pid_t  pid;
     //创建第一个子进程
     pid = fork();
    if (pid < 0)
     {
         perror("fork error:");
         exit(1);
     }
     //第一个子进程
     else if (pid == 0)
     {
         //子进程再创建子进程
         printf("I am the first child process.pid:%d\tppid:%d\n",getpid(),getppid());
         pid = fork();
        if (pid < 0)
         {
             perror("fork error:");
             exit(1);
         }
         //第一个子进程退出
         else if (pid >0)
         {
             printf("first procee is exited.\n");
             exit(0);
         }
        //第二个子进程
         //睡眠保证第一个子进程退出，这样第二个子进程的父亲就是init进程里
         sleep(3);
         printf("I am the second child process.pid: %d\tppid:%d\n",getpid(),getppid());
         exit(0);
     }
     //父进程处理第一个子进程退出
     if (waitpid(pid, NULL, 0) != pid)
     {
         perror("waitepid error:");
         exit(1);
    }
     exit(0);

	int count = 0;
	pid_t child,child_second = -1;
	child = fork();
	int status = -1;
	while(1)
	{
		if(child < 0)
		{
			perror("fork error");
			exit(1);
		}
		else if(child == 0)
		{
			printf("this is son ID:%d,count is %d(%p),pid:%d,ppid:%d\n",child ,++count,&count,getpid(),getppid() );
			if(child_second == -1)
			{
				child_second = fork();
				if(child_second < 0)
				{
					perror("fork second error");
					exit(1);
				}
			}
			if(count >= 5)
				exit(0);
		}
		else 
		{
			static pid_t ret = -1;
			if(ret == -1)
			{
				ret = wait(&status);
				printf("wait ret:%d,status:%d\n",ret ,status);
			}	

			printf("this is father ID:%d,count is %d(%p),pid:%d,ppid:%d\n",child,++count,&count,getpid(),getppid() );
		}
		if(child_second != -1)
		{
			printf("second son ID:%d,count is %d(%p),pid:%d,ppid:%d\n",child_second,++count,getpid(),getppid() );
		}
		sleep(1);
	}

	

	
	int len = strlen(srcs);
	printf("len:%d\n",len );
	unsigned char dsts[2000]={0};
	StrToHex(dsts,(unsigned char*)srcs,len);
	printf("{");
	for(int i=0;i<len/2;i++)
	{
		printf("0x%02x,",dsts[i] );
	}
	printf("}");
	printf("\ncrc:%02x\n",Crc((char*)dsts,len/2) );
	// char tmpdata[]={0x55,0xAA,0x00,0x42,0x41,0x54,0x33,0x30,0x30,0x30,0x36,0x30,0x34,0x30,0x31,0x06,0x01,0x13,0x04,0x04,0x0f,0x1f,0x19,0x07,0x04,0xc6,0x09,0x68,0x18,0x5b,0xfb,0x60,0x00,0xb1,0x06,0x18,0x00,0x05,0x75,0x08,0x00,0x13,0x2c,0x02,0x0e,0x00,0x05,0x75,0x08,0x0c,0x1a,0x90,0x0d,0x10,0x80,0x00,0x05,0x75,0x08,0x81,0x00,0x00,0x8c,0xa3,0x82,0x01};
	// printf("crc:%02x\n",Crc(tmpdata,sizeof(tmpdata)) );
	// char tmpdata2[]=
 //    {
 //    0x23,0x23,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x00,0x00,0x00,0x00,0x00,0x00,0x55,0xAA,0x00,0x2E,0x41,0x54,0x33,0x30,0x30,0x30,0x36,0x30,0x34,0x30,0x31,0x07,0x0C,0x13,0x04,0x04,0x0f,0x1f,0x19,0x07,0x04,0xc6,0x09,0x68,0x18,0x5b,0xfb,0x60,0x00,0xb1,0x06,0x18,0x00,0x50,0x05,0x50,0x00,0x50,0x05,0x50,0x05,0x50,0xb6,0xe3
 //    };
 //    char tmpdata[]=
 //    {
 //    0x55,0xAA,0x00,0x2E,0x41,0x54,0x33,0x30,0x30,0x30,0x36,0x30,0x34,0x30,0x31,0x07,0x0C,0x13,0x04,0x04,0x0f,0x1f,0x19,0x07,0x04,0xc6,0x09,0x68,0x18,0x5b,0xfb,0x60,0x00,0xb1,0x06,0x18,0x00,0x50,0x05,0x50,0x00,0x50,0x05,0x50,0x05,0x50
 //    };
 //    printf("crc:%02x\n",Crc(tmpdata,sizeof(tmpdata)) );
	// printf("Cal_BCC_CheckSum:%02x\n",Cal_BCC_CheckSum((unsigned char*)tmpdata2+2,sizeof(tmpdata2)-2) );
#endif
		return 0;

}
#if 0
int main()
{
	char a[100] = {0};
	int i,j,sz=0,dx=0,xx=0,qt=0;
	int m;
	scanf("%d",&m);
	printf("Case Digits Lowers Uppers Others\n");
	for(i=0;i<=m;i++)
	{
		gets(a);
		for(j=0;a[j] != '\0';j++)
		{
			if(a[j] >= '0' && a[j] <= '9')
				sz++;
			else if(a[j] >= 'a' && a[j] <= 'z')
				xx++;
			else if(a[j] >= 'A' && a[j] <= 'Z')
				dx++;
			else
				qt++;
		}
		printf("%-5d%-7d%-7d%-7d%-7d\n", i,sz,xx,dx,qt);
	}
	return 0;
}

#include <iostream>
using namespace std;
int main()
{
	const int w=2;
	int i,j,a[5][5];
	for(i=0;i<5;i++)
	{
		if(i>0)
		{
			cout.width(i*(w+1));
			cout.fill(' ');
			cout<<' ';
		}
		for(j=i;j<5;j++)
		{
			a[i][j]=i*5+j+1;
			cout.width(2);
			cout.fill('0');
			cout<<a[i][j]<<(4!=j ? ' ' : '\n');
		}
	}
	return 0;
}

#define Ascending true//升序
#define Decending false//降序
/**
 * 交换a和b的值
 */
void swap(int &a,int &b)//&表示引用作为参数，也可以使用指针的形式，但不能直接传形参的方式，否则无法交换
{
	int temp = a;
	a=b;
	b=temp;
}
/**
 * [sort 排序，根据type决定是升序还是降序]
 * @param ary  [传进来要排序的数组]
 * @param len  [排序数目]
 * @param type [排序类型，升序或降序]
 */
void sort(int *ary,int len,bool type)
{
	//每个数同后面的所有数都比较一次，将最值放到最前面，下次从下一个开始比较
	for(int i=0;i<len;i++)
	{
		for(int j=i+1;j<len;j++)
		{
			if(type == Ascending)//升序，小的在前面
			{
				if(ary[i] > ary[j])
					swap(ary[i],ary[j]);
			}
			else//降序，大的在前面
			{
				if(ary[i] < ary[j])
					swap(ary[i],ary[j]);
			}
				
		}
		cout << ary[i] << " ";//一轮比较下来获得最值，输出，也可以在外面对已经排序好的数组进行打印输出
	}
}
int main()
{
	int N = 0;
	cout << "请输入总数：";
	cin >> N;
	int *arry_odd = new int[N];//存放奇数
	int *arry_even = new int[N];//存放偶数
	int odd_count = 0;//奇数计数
	int even_count = 0;//偶数计数
	int temp_num = 0; //临时存放从键盘获取的值，判断奇偶之后存到相应数组
	if(arry_odd != NULL && arry_even != NULL)
	{
		for(int i=0;i<N;i++)
		{
			cout << "请输入第 " << i << " 个数：";
			cin >> temp_num;
			if(temp_num % 2 == 0)//偶数
			{
				arry_even[even_count] = temp_num;
				even_count++;
			}
			else //奇数
			{
				arry_odd[odd_count] = temp_num;
				odd_count++;
			}
		}
		cout << "奇数："<<endl;
		sort(arry_odd,odd_count,Ascending);//奇数升序传参Ascending类型
		cout << endl;
		cout << "偶数："<<endl;
		sort(arry_even,even_count,Decending);//偶数降序传参Decending类型
		cout << endl;
		delete[] arry_odd;//回收动态分配的内存
		delete[] arry_even;//回收动态分配的内存
	}
	return 0;
}

#define N 5 //可通过改变此值修改方阵行列数
int a[N][N]={0};
int main()
{
	int row = 0;
	int col = 0;
	for(row=0;row<N;row++)
	{
		for(col=0;col<N;col++)
		{
			cout << "请输入第 " << row+1 << " 行，第 " << col << " 列数：" ; 
			cin >> a[row][col];
		}
		cout << endl;//换行区分录入下一行
	}
	for(row=0;row<N;row++)
	{
		for(col=0;col<N;col++)
		{
			/*行数大于列数输出0，否则输出实际值*/
			if(row > col)
				cout << "0 ";
			else
				cout << a[row][col] << " " ;
		}
		cout << endl;//打印完一行之后换行
	}
	return 0;
}

#include <stdio.h>
int fun(int x,int y)
{ 
	int sum; 
	sum=x+y; 
	return sum; 
}
int fum(int x,int y)
{ 
	int chen; 
	chen=x*y; 
	return chen;
} 
int main()
{ 
	int a[3],i,k; 
	for(i=0;i<3;i++)
	{ 
		printf("请输入数：");
		scanf("%d",&a[i]); //原程序中此处最后少了 &
		// printf("%d",a[i]); 
	} 
	printf("\n");
	for(i=0;i<3;i++)
	{
		for(k=1;k<3;k++)
		{
			printf("%d+%d=%d\n",a[i],a[k],fun(a[i],a[k]) );//原程序中此处最后少了一个')'
			printf("%d*%d=%d\n",a[i],a[k],fum(a[i],a[k]) );//原程序中此处最后少了一个')'
		}
	}
}//原程序此处少了

int main()
{
	char c;
	do
	{
		cout << "请输入字符：(Ctrl + c 退出)";
		cin >> c;
		if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') )
		{
			cout << "输入字符是字母" << endl;
		}
		else if((c >= '0' && c <= '9'))
		{
			cout << "输入字符是数字" << endl;
		}
		else
		{
			cout << "其他字符" << endl;
		}
	}while(1);
	return 0;
}

#define N 10//可通过改变此值，决定n*n
int main()
{   
	int j,k,a[N][N];
	for(k=1;k<=N;k++)
    	for(j=1;j<=N;j++)
			a[k-1][j-1]=(k/j)*(j/k);
  	for(k=0;k<N;k++)
  	{
    	for(j=0;j<N;j++)
    	{
			printf("%d ",a[k][j]);//每个数留个空格
    	}
    	printf("\n");//增加一个换行，这样打印出来直观
  	}
  	return 0;
}

#define MAX_VEH_NUM 100
typedef struct 
{
	unsigned int year;
	unsigned int  month;
	unsigned int day;
}DATE;
typedef struct 
{
	char plate_num[10];//车牌
	char model[10];//型号
	float displacement;//排量
	DATE date;//日期
	float mileage;//里程
}VEH_MSG;

VEH_MSG veh_msg[MAX_VEH_NUM]={0};//存放车辆信息
int veh_num=0;//实际录入车辆数

int inputVeh()
{
	if(veh_num<MAX_VEH_NUM)//不能超过最大限制数
	{
		printf("请输入车牌号：");
		scanf("%s",veh_msg[veh_num].plate_num);
		printf("请输入排量：");
		scanf("%f",&veh_msg[veh_num].displacement);
		printf("请输入型号：");
		scanf("%s",veh_msg[veh_num].model);
		printf("请输入里程：");
		scanf("%f",&veh_msg[veh_num].mileage);
		printf("veh_msg[veh_num].mileage:%f\n",veh_msg[veh_num].mileage );
		printf("请按顺序输入年 月 日，空格隔开:");
		scanf("%d%d%d",&veh_msg[veh_num].date.year,&veh_msg[veh_num].date.month,&veh_msg[veh_num].date.day);
		veh_num ++ ;//车数量增加了一辆
		return 0;
	}
	else
	{
		printf("超过最大车辆数\n");
		return -1;
	}
}

float milStat()
{
	double mileage_sum = 0.0;
	for(int i=0;i<veh_num;i++)
	{
		mileage_sum += veh_msg[i].mileage;
	}
	float mileage_avg = mileage_sum / (1.0*veh_num);
	printf("平均里程数:%f\n",mileage_avg );
	return mileage_avg;
}
int inquireVeh()
{
	char temp_plate_num[10]={0};
	char flag = 1;
	do
	{
		printf("请输入要查询的车辆车牌：");
		scanf("%s",temp_plate_num);
		for(int i=0;i<veh_num;i++)
		{
			if(strcmp(temp_plate_num,veh_msg[i].plate_num) == 0)
			{
				printf("车牌号：%s\n",veh_msg[i].plate_num );
				printf("型号：%s\n",veh_msg[i].model );
				printf("排量：%f\n",veh_msg[i].displacement );
				printf("里程：%f\n",veh_msg[i].mileage );
				printf("日期：%04d-%02d-%02d \n",veh_msg[i].date.year,veh_msg[i].date.month,veh_msg[i].date.day);
				return 0;
			}
		}
		printf("没有找到相应车辆,是否 :0)退出查询 1)继续查询 2)添加车辆信息： ");
		scanf("%d",&flag);
		printf("flag:%d\n",flag );
		if(flag <0 || flag >2 )
		{
			flag = 0;
			break;
		}
		else if(flag == 1)
			continue;
		else if(flag == 2)
		{
			inputVeh();
			continue;
		}
	}while(flag);
	return 0;
}
int main()
{
	char cmd = 0;
	do
	{
		printf("请输入功能项：1)录入车辆信息 2)计算里程 3)查询：" );
		scanf("%d",&cmd);
		switch(cmd)
		{
			case 1:
				inputVeh();
				break;
			case 2:
				milStat();
				break;
			case 3:
				inquireVeh();
				break;
			default:
				cmd = 0;
				break;
		}
	}while(cmd);
	return 0;
}

int main()
{
	int num = 0;
	bool a[100] = {0};
	printf("请输入要按多少次：");
	cin >> num;
	for(int k=1;k<=num;k++)
	{
		for(int i = 0;i<100;i++)
		{
			if((i+1)%k == 0)
			{
				a[i] = (!a[i]);
			}
		}
	}
	for(int i=0;i<100;i++)
	{
		if(a[i])
		{
			printf("%d ",i+1 );
		}
	}
	printf("\n");
	return 0;
}

#define flag(a) (a%2==0?-1.0:1.0)//双数就是负数，单数就是正数
int main()
{
	int i=0;
	float sum = 0;
	printf("%f\n", 1.0/(1*2*3));
	for(i=1;i<=20;i++)
	{
		sum += flag(i) * 1.0/(1.0*i*(i+1)*(i+2));
	}
	printf("sum:%f\n",sum );
	return 0;
}
#endif
