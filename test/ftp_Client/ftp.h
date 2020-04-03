/*---------------------------------------
*名称：ftp
*作用：连接ftp，上传，下载文件。读取目录。
*使用方法：上传：设置IP端口，用户密码->连接->进入被动模式->设置本地和远程路径->上传->关闭连接
            下载：设置IP端口，用户密码->连接->进入被动模式->设置本地和远程路径->下载->关闭连接
            改变路径：设置IP端口，用户密码->连接->改变路径->关闭连接
            读取路径文件目录：设置IP端口，用户密码->连接->进入被动模式->读取文件目录->关闭连接
*日期：2014-08-29
*Author：fzp
*Version:1.0
*---------------------------------------*/
#ifndef _FTP_H_
#define _FTP_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdarg.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include "mutex.h"

#define MAX_BUF_LEN 1024
static ClMutexLock g_upgradestatuLock;

//登录服务器状态
typedef enum FTP_UPGRADE_STATUS
{
    NO_UPGRADE=0,
    UPGRADE_FAIL,             //fail
    UPGRADEING,
    UPGRADE_SUCCESS,           //success 
}FTP_UPGRADE_STATUS;

class FTP
{
public:
    FTP();
    ~FTP();
    
    // 设置FTP的IP和端口
    void set_addr(const char* ip,const unsigned short port);
    // 设置FTP用户名和密码
    void set_user(const char* user,int len);
    void set_pwd(const char* pwd,int len);
    // 改变本地路径
    void set_localdir(const char* localdir,int len);
    // 改变远程路径
    void set_remotedir(const char* remotedir,int len);
    //
    void set_filetag(unsigned char tag);
    // 建立连接
    bool open_ftp();
    // 断开连接
    bool close_ftp();
    // 进入被动模式
    bool into_passive();
    // 下载文件
    bool download();
    static void* download_thre(void* pdata);
    // 上传文件
    bool upload();
    // static void* upload_thre(void* data);
    bool upload_func(void);
    //获得一个文件的大小
    long int get_file_size(const char* filename);

    //send ftp command to the server
    bool send_ftpcmd(const char* ftpcmd,int expect_code1,int expect_code2);

    void set_upgrade_status(FTP_UPGRADE_STATUS n); 
    int get_upgrade_status(); 

     //lxc
    bool FTPserver_connect_fail;
    bool FTPserver_login_fail;
	
	//add by lxc,解析标准ftp地址
    void analyze_ftp_protocol(char* ftp_url,int url_len,char* user_name,\
        char* passwd,char* ftp_ip,unsigned short &ftp_port,char *ftp_path,char* file_name);

private:

    bool is_transferring;
    bool is_opening;
    bool is_uploading;
    
    
    int ftp_sock;
    int passive_sock;
    pthread_t ftp_thread;
    int ftp_code;

    char username[64];
    char userpwd[64];
    char serv_ip[16];
    unsigned short serv_port;
    char local_dir[256];
    char remote_dir[256];
    char recvbuf[MAX_BUF_LEN];
    unsigned char filetag;
    FTP_UPGRADE_STATUS upgrade_status;
    char *Findchar(char *p1, char t,int n);
    int getcharcount(char *p1, char t);
};

#endif
