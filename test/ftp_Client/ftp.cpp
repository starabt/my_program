#include "ftp.h"
// #include "TDmetalog.h"
#include <stdio.h>
// #include "linuxFile.h"
// 获取
static int getFirstNo(char *command) {
    int no = 0;
    for (unsigned int i = 0; i < strlen(command); i++) {
        if (command[i] >= '0' && command[i] <= '9') {
            no = no * 10 + (command[i] - '0');
        } else {
            break;
        }
    }
    return no;
}

// 判断一个字符是否是数字
static int isDigit(char ch) {
    if (ch >= '0' && ch <='9') {
        return 1;
    } else {
        return 0;
    }
}

// 在字符串指定的字符后寻找数字并求值
static void getNumbersAfter(char *str, char flag, long int *num, int count) {
    int pos = 0;
    while (str[pos] != flag) {
        pos ++;
    }
    int j;
    for (j = 0; j < count; j++) {
        while (!isDigit(str[pos])) {
            pos ++;
        }
        num[j] = 0;
        while (isDigit(str[pos])) {
            num[j] = num[j] * 10 + (str[pos] - '0');
            pos ++;
        }
    }
}

FTP::FTP():
is_transferring(false),
is_opening(false),
is_uploading(false),
FTPserver_connect_fail(false),
FTPserver_login_fail(false),
ftp_sock(-1),
passive_sock(-1),
ftp_thread(0),
ftp_code(-1),
filetag(0x00),
upgrade_status(NO_UPGRADE)
{
    memset(username,0,sizeof(username));
    memset(userpwd,0,sizeof(userpwd));
    memset(serv_ip,0,sizeof(serv_ip));
    serv_port = 0;
    memset(local_dir,0,sizeof(local_dir));
    memset(remote_dir,0,sizeof(remote_dir));
    memset(recvbuf,0,sizeof(recvbuf));

}

FTP::~FTP()
{}


// 设置FTP的IP和端口
void FTP::set_addr(const char* ip,const unsigned short port)
{
    strcpy(serv_ip,ip);
    serv_port = port;
    return ;
}

// 设置FTP用户名和密码
void FTP::set_user(const char* user,int len)
{
    memcpy(username,user,len);
    return ;
}

void FTP::set_pwd(const char* pwd,int len)
{
    memcpy(userpwd,pwd,len);
    return ;
}

// 改变本地路径
void FTP::set_localdir(const char* localdir,int len)
{
    memcpy(local_dir,localdir,len);;
    return ;
}

// 改变远程路径
void FTP::set_remotedir(const char* remotedir,int len)
{
    memcpy(remote_dir,remotedir,len);   //用strcpy会出错
}

//
void FTP::set_filetag(unsigned char tag)
{
    filetag = tag;
}

bool FTP::open_ftp()
{
    printf("into open_ftp\n");
    //避免重复打开
    if(is_opening)
        return false;
    is_opening = true;

    // init socket addr
    ftp_sock = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in servaddr;
    bzero(&(servaddr.sin_zero),8);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(serv_port);
    inet_pton(AF_INET,serv_ip,&servaddr.sin_addr);


    // 连接FTP
    int ret = connect(ftp_sock,(struct sockaddr*)&servaddr,sizeof(servaddr));
    if(ret < 0)
    {
        perror("Ftp connect 错误");
        char tmp_log[256];
        sprintf(tmp_log,"%s%s","Ftp connect 错误:",strerror(errno));
        // ERR_LOG("%s\n",tmp_log);
        close_ftp();
        is_opening = false;
        FTPserver_connect_fail=true;
        return false;
    }
    read(ftp_sock,recvbuf,sizeof(recvbuf));
    printf("%s\n", recvbuf);
    ftp_code = getFirstNo(recvbuf);
    if(ftp_code != 220)
    {
        char tmp_log[256];
        sprintf(tmp_log,"没有收到220回复，收到:%d\n",ftp_code);
        // ERR_LOG("%s\n",tmp_log);        
        printf(tmp_log);
        close_ftp();
        is_opening = false;
        return false;
    }

    //输入用户名
    char ftpcmd[32];
    sprintf(ftpcmd,"%s%s\r\n","USER ",username);
    if(!send_ftpcmd(ftpcmd,331,0))
    { 
        close_ftp();
        is_opening = false;
        FTPserver_login_fail=true;
        return false;
    }

    // 输入密码
    sprintf(ftpcmd,"%s%s\r\n","PASS ",userpwd);
    if(!send_ftpcmd(ftpcmd,230,0))
    { 
        close_ftp();
        is_opening = false;
        FTPserver_login_fail=true;
        return false;
    }
    is_opening = false;
    return true;
}

// 断开连接
bool FTP::close_ftp()
{
    if (passive_sock>0)
    {
        close(passive_sock);
        passive_sock = -1;
    }
    if(ftp_sock>0)
    {
        close(ftp_sock);
        ftp_sock = -1;
    }
    return true;
}


// 进入被动模式
bool FTP::into_passive()
{
    printf("into passive \n");
    // 进入二进制模式传递信息
    char type[] = "TYPE I\r\n";
    if(!send_ftpcmd(type,200,0))
    { 
        close_ftp();
        return false;
    }

    // 进入被动模式
    char passcmd[] = "PASV\r\n";
    if(!send_ftpcmd(passcmd,227,0))
    { 
        close_ftp();
        return false;
    }
    
    long int temp[6]; // 解析服务器消息
    getNumbersAfter(recvbuf, '(', temp, 6);
    int portNo = temp[4] * 256 + temp[5]; // 获取端口号

    char serverIP[32]; // 获取ip
    memset(serverIP,0,sizeof(serverIP));
    sprintf(serverIP,"%d.%d.%d.%d",(int)temp[0],(int)temp[1],(int)temp[2],(int)temp[3]);
    // sprintf(serverIP,"%d.%d.%d.%d",temp[0],temp[1],temp[2],temp[3]);
    printf("被动模式IP端口：%s:%d\n",serverIP,portNo);

    struct sockaddr_in data_addr;
    data_addr.sin_family = AF_INET;
    inet_pton(AF_INET, serverIP, &data_addr.sin_addr);
    data_addr.sin_port = htons(portNo);
    passive_sock = socket(AF_INET,SOCK_STREAM,0);
    if(passive_sock < 0)
    {
        printf("FTP 创建被动模式socket失败\n");
        close_ftp();
        return false;
    }

    //连接数据传输socket
    int ret = connect(passive_sock,(struct sockaddr*)&data_addr,sizeof(data_addr));
    if(ret < 0)
    {
        perror("Ftp-被动模式connect失败");
        char tmp_log[256];
        sprintf(tmp_log,"%s%s","Ftp-被动模式connect失败:",strerror(errno));
        // ERR_LOG("%s\n",tmp_log);
        close_ftp();
        return false;
    }
    return true;
}

// 下载文件
bool FTP::download()
{
    if(is_transferring)
    {
        return false;
    }
    is_transferring = true;
    pthread_create(&ftp_thread,NULL,download_thre,this);
    pthread_detach(ftp_thread);
    return true;
}

void* FTP::download_thre(void* pdata)
{

    // unsigned long download_thre_tid=gettid();
	unsigned long download_thre_tid=1;
	printf("ftp_download_thread id: %ld is create\n",download_thre_tid);
    FTP* parent = (FTP*)pdata;
    char ftpcmd[128];
    memset(ftpcmd,0,sizeof(ftpcmd));
    parent->set_upgrade_status(UPGRADEING);
    sprintf(ftpcmd, "%s %s\r\n", "SIZE", parent->remote_dir);
    if(!parent->send_ftpcmd(ftpcmd,213,0))
    { 
        parent->close_ftp();
        parent->is_transferring = false;
        parent->set_upgrade_status(UPGRADE_FAIL);
        // if (parent)
        // {
        //     delete parent;
        //     parent = NULL;
        // }
        printf("ftp_download_thread %ld is exit \n",download_thre_tid);
        return NULL;
    }

    long int remotefile_size=0;
    getNumbersAfter(parent->recvbuf,' ',&remotefile_size,1);

    sprintf(ftpcmd,"%s%s\r\n","RETR ",parent->remote_dir);
    if(!parent->send_ftpcmd(ftpcmd,125,150))    //FileZilla:150,Microsoft:125
    { 
        parent->close_ftp();
        parent->is_transferring = false;
        parent->set_upgrade_status(UPGRADE_FAIL);
        // if (parent)
        // {
        //     delete parent;
        //     parent = NULL;
        // }
        printf("ftp_download_thread %ld is exit \n",download_thre_tid);
        return NULL;
    }

    int savefd = open(parent->local_dir,O_WRONLY|O_CREAT,0777);
    if(savefd < 0)
    {
        perror("Ftp- Cannot open local file");
        char tmp_log[256];
        sprintf(tmp_log,"%s%s","Ftp- Cannot open local file:",strerror(errno));
        // ERR_LOG("%s\n",tmp_log);
        close(parent->passive_sock);
        parent->close_ftp();
        parent->is_transferring = false;
        parent->set_upgrade_status(UPGRADE_FAIL);
        // if (parent)
        // {
        //     delete parent;
        //     parent = NULL;
        // }
        printf("ftp_download_thread %ld is exit \n",download_thre_tid);     
        return NULL;
    }

    long int recv_count = 0;
    //只有传输数据时候用passive socket 询问状态用ftp socket
    while(1)
    {
        int ret = recv(parent->passive_sock,parent->recvbuf,sizeof(parent->recvbuf),0);
        if(ret <= 0)
        {
            perror("recv file");
            char tmp_log[256];
            sprintf(tmp_log,"%s%s","Ftp- Recv remote file:",strerror(errno));
            // ERR_LOG("%s\n",tmp_log);
            break;
        }
        write(savefd,parent->recvbuf,ret);
        recv_count += ret;
    }

    close(savefd);
    sprintf(ftpcmd,"%s\r\n","QUIT ");
    if( !parent->send_ftpcmd(ftpcmd,226,0) || remotefile_size != recv_count)
    {
        printf("\n文件下载终止，文件大小 %ld bytes，共接收 %ld bytes .\n", remotefile_size, recv_count);
        char tmp_log[256];
        sprintf(tmp_log,"文件下载终止，文件大小 %ld bytes，共接收 %ld bytes .",remotefile_size,recv_count);
        // ERR_LOG("%s\n",tmp_log);
        char tmp[128];
        memset(tmp,0,sizeof(tmp));
        sprintf(tmp,"rm %s",parent->local_dir);
        system(tmp);
        parent->close_ftp();
        parent->is_transferring = false;
        parent->set_upgrade_status(UPGRADE_FAIL);
        printf("ftp_download_thread %ld is exit \n",download_thre_tid);
        return NULL;
    }

    else if (remotefile_size == recv_count) 
    {
        parent->set_upgrade_status(UPGRADE_SUCCESS);
        printf("\n文件下载完成，文件大小 %ld bytes，共接收 %ld bytes .\n", remotefile_size, recv_count);
        char tmp_log[256];
        memset(tmp_log,0,sizeof(tmp_log));
        sprintf(tmp_log,"file download success，filesize %ld bytes，total receive %ld bytes .",remotefile_size,recv_count);
        // ERR_LOG("%s\n",tmp_log);
        printf("tmp_log:%s\n", tmp_log);
        parent->close_ftp();
        parent->is_transferring = false;
        printf("ftp_download_thread %ld is exit \n",download_thre_tid);
        return NULL;
    }
    printf("ftp_download_thread %ld is exit \n",download_thre_tid);
    return NULL;
}

// 上传文件
bool FTP::upload()
{
    if(is_uploading)
    {
        return false;
    }
    is_uploading = true;
    
    bool ret = upload_func();
    if(!ret)
    {
        printf("upload log fail\n");
        // ERR_LOG("upload log fail\n");
        return false;
    }
    else
        return true;
    // pthread_create(&ftp_thread,NULL,upload_thre,this);
    // pthread_detach(ftp_thread);
    // return true;
}

bool FTP::upload_func(void)
{
    char ftpcmd[128];
    memset(ftpcmd,0,sizeof(ftpcmd));

    long int remotefile_size = 0;
    long int localfile_size = get_file_size(local_dir);
    printf("local_dir: %s\n", local_dir );
    printf("local file size:%ld\n", localfile_size);

    // FILE* sendfd = fopen(local_dir,"rb");
    // int savefd = open(local_dir,O_RDONLY);
    FILE* savefd = fopen(local_dir,"rb");
    if(savefd == NULL)
    {
        perror("Ftp- Cannot open local file");
        char tmp_log[256];
        sprintf(tmp_log,"%s%s","Ftp- Cannot open local file:",strerror(errno));
        // ERR_LOG("%s\n",tmp_log);
        close_ftp();
        is_uploading = false;

        return false;
    }

    sprintf(ftpcmd, "%s %s\r\n", "SIZE", remote_dir);
    if(send_ftpcmd(ftpcmd,213,550))
    {
        if(ftp_code == 550)
        {
            remotefile_size = 0;
        }
        else if(ftp_code == 213)
        {
            #if 0
            sprintf(ftpcmd, "%s %ld\r\n", "REST", remotefile_size);
            if(!send_ftpcmd(ftpcmd,350,0))
            {
                close_ftp();
                is_uploading = false;

                fclose(savefd);
                return NULL;
            }
            if(localfile_size >= remotefile_size)
            {
                fseek(savefd, remotefile_size,SEEK_SET);
            }
            #endif
            /*sprintf(ftpcmd, "%s%s \r\n","DELE ",remote_dir);
            if(!send_ftpcmd(ftpcmd,550,250))
            {
                close_ftp();
                is_uploading = false;

                fclose(savefd);
                return NULL;
            }*/

        }
    }
    else
    {
        close_ftp();
        is_uploading = false;
  
        fclose(savefd);
        return false;
    }

    sprintf(ftpcmd,"%s%s\r\n","STOR ",remote_dir);
    if(send_ftpcmd(ftpcmd,550,150))////FileZilla:150,Microsoft:125,550:文件被其它进程占用，会引起程序崩溃
    {
        if(ftp_code == 550)
        {
            close_ftp();
            is_uploading = false;
            fclose(savefd);
            // fclose(sendfd);
            return false;
        }
        
    }

    //只有传输数据时候用passive socket 询问状态用ftp socket
    

    long int send_count = 0;
    while(1)
    {
        // int ret = read(savefd,recvbuf,sizeof(recvbuf));
        int ret = fread(recvbuf,1,sizeof(recvbuf),savefd);
        
        if(ret <= 0)
        {
            perror("Read local file");
            char tmp_log[256];
            sprintf(tmp_log,"%s%s","Ftp- read local log file:",strerror(errno));
            // ERR_LOG("%s\n",tmp_log);
            break;
        }
        send(passive_sock,recvbuf,ret,0);
        send_count += ret;
    }
    remotefile_size += send_count;

    if(passive_sock>0)
    {
        close(passive_sock);    //这句移到read后面上传会出错，无知点解
    }

    sprintf(ftpcmd,"%s\r\n","QUIT ");
    if(!send_ftpcmd(ftpcmd,226,0))
    {
        printf("\n文件上传终止，文件大小 %ld bytes，共上传 %ld bytes .\n", localfile_size, send_count);
        
    }
    else if (localfile_size == remotefile_size) 
    {
        printf("\n文件上传完成，文件大小 %ld bytes，共上传 %ld bytes .\n", localfile_size, send_count);
    } 

    fclose(savefd);
    close_ftp();
    is_uploading = false;

    return true;
}

#if 0
void* FTP::upload_thre(void* data)
{
    FTP* parent = (FTP*)data;
    char ftpcmd[128];
    memset(ftpcmd,0,sizeof(ftpcmd));

    long int remotefile_size = 0;
    long int localfile_size = parent->get_file_size(parent->local_dir);
    printf("local_dir: %s\n", parent->local_dir );
    printf("local file size:%ld\n", localfile_size);

    // FILE* sendfd = fopen(parent->local_dir,"rb");
    // int savefd = open(parent->local_dir,O_RDONLY);
    FILE* savefd = fopen(parent->local_dir,"rb");
    if(savefd < 0)
    {
        perror("Ftp- Cannot open local file");
        char tmp_log[256];
        sprintf(tmp_log,"%s%s","Ftp- Cannot open local file:",strerror(errno));
        ERR_LOG("%s\n",tmp_log);
        parent->close_ftp();
        parent->is_uploading = false;

        return NULL;
    }

    sprintf(ftpcmd, "%s %s\r\n", "SIZE", parent->remote_dir);
    if(parent->send_ftpcmd(ftpcmd,213,550))
    {
        if(parent->ftp_code == 550)
        {
            remotefile_size = 0;
        }
        else if(parent->ftp_code == 213)
        {           
		 #if 0
            sprintf(ftpcmd, "%s %ld\r\n", "REST", remotefile_size);
            if(!parent->send_ftpcmd(ftpcmd,350,0))
            {
                parent->close_ftp();
                parent->is_uploading = false;

                fclose(savefd);
                return NULL;
            }
            if(localfile_size >= remotefile_size)
            {
                fseek(savefd, remotefile_size,SEEK_SET);
            }
            #endif
            /*sprintf(ftpcmd, "%s%s \r\n","DELE ",parent->remote_dir);
            if(!parent->send_ftpcmd(ftpcmd,550,250))
            {
                parent->close_ftp();
                parent->is_uploading = false;

                fclose(savefd);
                return NULL;
            }*/

        }
    }
    else
    {
        parent->close_ftp();
        parent->is_uploading = false;
  
        fclose(savefd);
        return NULL;
    }

    sprintf(ftpcmd,"%s%s\r\n","STOR ",parent->remote_dir);
    if(!parent->send_ftpcmd(ftpcmd,125,150))////FileZilla:150,Microsoft:125,550:文件被其它进程占用，会引起程序崩溃
    {
        printf("===============++++++++++++++================\n");
        parent->close_ftp();
        parent->is_uploading = false;
        fclose(savefd);
        // fclose(sendfd);
        return NULL;
    }

    //只有传输数据时候用passive socket 询问状态用ftp socket
    

    long int send_count = 0;
    while(1)
    {
        // int ret = read(savefd,parent->recvbuf,sizeof(parent->recvbuf));
        int ret = fread(parent->recvbuf,1,sizeof(parent->recvbuf),savefd);
        
        if(ret <= 0)
        {
            perror("Read local file");
            char tmp_log[256];
            sprintf(tmp_log,"%s%s","Ftp- read local log file:",strerror(errno));
            ERR_LOG("%s\n",tmp_log);
            break;
        }
        send(parent->passive_sock,parent->recvbuf,ret,0);
        send_count += ret;
    }
    remotefile_size += send_count;

    if(parent->passive_sock>0)
    {
        close(parent->passive_sock);    //这句移到read后面上传会出错，无知点解
    }

    sprintf(ftpcmd,"%s\r\n","QUIT ");
    if(!parent->send_ftpcmd(ftpcmd,226,0))
    {
        printf("\n文件上传终止，文件大小 %ld bytes，共上传 %ld bytes .\n", localfile_size, send_count);
    }
    else if (localfile_size == remotefile_size) 
    {
        printf("\n文件上传完成，文件大小 %ld bytes，共上传 %ld bytes .\n", localfile_size, send_count);
    } 

    fclose(savefd);
    parent->close_ftp();
    parent->is_uploading = false;

    return NULL;
}
#endif

//获得一个文件的大小
long int FTP::get_file_size(const char *filename) {
    struct stat tbuf;
    if(stat(filename, &tbuf) == -1)
    {
        return 0;
    }
    else
    {
        return tbuf.st_size;
    }
}

//
bool FTP::send_ftpcmd(const char* ftpcmd,int expect_code1,int expect_code2)
{

    char temp_log[512];
    for(int i = 0;i<3;i++)
    {
        int ret = send(ftp_sock,ftpcmd,strlen(ftpcmd),0);
        if(ret < 0)
        {
            sprintf(temp_log,"FTP发送命令失败:%s",ftpcmd);
            // printf(temp_log);
            return false;
        }
        usleep(500*1000);

        memset(recvbuf,0,sizeof(recvbuf));
        ret = read(ftp_sock,recvbuf,sizeof(recvbuf));
        if (ret<0)
        {
            sprintf(temp_log,"FTP接收消息失败:%s",ftpcmd);
            // INFO_LOG("%s",temp_log);
            // printf(temp_log);
            return false;
        }
        ftp_code = getFirstNo(recvbuf);

        printf("\n*****  start  **********\n%s:%s\n********  end  ********\n", ftpcmd,recvbuf);
        if(ftp_code == expect_code1 || ftp_code == expect_code2)
        {
            printf("%d %d %d\n",ftp_code, expect_code1,expect_code2);
            return true;
        }
        else
        {
            usleep(500*1000);
        }
    }
    memset(temp_log,0,sizeof(temp_log));
    sprintf(temp_log,"%s,没有收到%dor%d回复，收到:%d\n",ftpcmd,expect_code1,expect_code2,ftp_code);
    // INFO_LOG("%s",temp_log);
    // printf(temp_log);

    return false;

    //fflush(stdout);
    //send_resultcode((unsigned char)ftp_code,(unsigned char)(ftp_code>>8));
    //return(ftp_code);
}


void FTP::set_upgrade_status(FTP_UPGRADE_STATUS n)
{
    g_upgradestatuLock.Lock();
    upgrade_status = n;
    g_upgradestatuLock.Unlock();
    return;
}
int FTP::get_upgrade_status()
{
    int n =0;
    // g_upgradestatuLock.Lock();
    
    n = upgrade_status;
    // g_upgradestatuLock.Unlock();

    return n;
}
void FTP::analyze_ftp_protocol(char* ftp_url,int url_len,char* user_name,\
    char* passwd,char* ftp_ip,unsigned short &ftp_port,char *ftp_path,char* file_name)
{
    char* begin = NULL;
    char* end = NULL;
    char tempPort[6];
    memset(tempPort,0,sizeof(tempPort));

    /*
    ftp_path 包括文件夹和文件名，没有"/" 开头
    file_name 只有文件名，没有"/" 开头
     */
    begin = Findchar(ftp_url,'/',3);
    if(begin != NULL)
        memcpy(ftp_path,begin+1,strlen(begin)-1);
    int ret_count=getcharcount(ftp_path,'/');
    if(ret_count > 0)
    {
        begin = Findchar(ftp_path,'/',ret_count);
        if(begin != NULL)
            memcpy(file_name,begin+1,strlen(begin)-1);
    }
    else if(ret_count == 0)
    {
        memcpy(file_name,ftp_path,strlen(ftp_path));
    }
    //ip and port
    begin=Findchar(ftp_url,'@',1);
    end=Findchar(ftp_url,':',3);
    if(end!=NULL)
    {
        if(begin!=NULL)
            memcpy(ftp_ip,begin+1,strlen(begin)-strlen(end)-1);
        begin=Findchar(ftp_url,':',3);
        end=Findchar(ftp_url,'/',3);
        if(begin!=NULL && (end!=NULL))
            memcpy(tempPort,begin+1,strlen(begin)-strlen(end)-1);
        ftp_port = atoi(tempPort);
    }
    else
    {
        end=Findchar(ftp_url,'/',3);
        if(end!=NULL)
            memcpy(ftp_ip,begin+1,strlen(begin)-strlen(end)-1);
        ftp_port=21;
    }
    //username
    begin=Findchar(ftp_url,'/',2);
    end=Findchar(ftp_url,':',2);
    if(begin!=NULL && (end!=NULL))
        memcpy(user_name,begin+1,strlen(begin)-strlen(end)-1);
    //password
    begin=Findchar(ftp_url,':',2);
    end=Findchar(ftp_url,'@',1);
    if(begin!=NULL && (end!=NULL))
        memcpy(passwd,begin+1,strlen(begin)-strlen(end)-1);
    return;
}

char *FTP::Findchar(char *p1, char t,int n)
{
    int ret=0; 
    char *p2=NULL;
    p2=p1;
    while(*p2)
    {
        if((*p2)==t)
        {
            ret++;
            if(ret==n)
                return p2;
        }
        p2++;
    }
    return NULL;
}

int FTP::getcharcount(char *p1, char t)
{
    int ret=0;  
    char *p2=NULL;
    p2=p1;
    while(*p2)
    {
        if((*p2)==t)
        {
            ret++;
        }
        p2++;
    }
    return ret;
}