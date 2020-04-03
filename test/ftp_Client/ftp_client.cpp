#include<stdio.h>
#include"ftp.h"

int main(int argc, char const *argv[])
{
    if(argc <2)
    {
        printf("Usage: exe <filename to upload>\n");
        return -1;
    }
    char tempIP[16] = "120.77.212.71";
    unsigned short port = 21;
    char usrname[] = "xny";
    char pwd[] = "busonline";
    char remote_path[256] = {0};
    char local_path[256] = {0};
    FTP* ftp=new FTP;
    ftp->set_addr(tempIP,port);
    ftp->set_user(usrname,strlen(usrname));
    ftp->set_pwd(pwd,strlen(pwd));



    

    if(!ftp->open_ftp())
    {
        printf("ftp open_ftp failed\n");
        return -1;
    }


    for(int i=1;i<argc;i++)
    {
        char *p1 = NULL;
        char localFile[128]={0};
        memset(local_path,0,sizeof(local_path));
        memset(remote_path,0,sizeof(remote_path));
        strcpy(local_path,argv[i]);
        p1 = strrchr(local_path,'/');
        memset(localFile,0,sizeof(localFile));
        if(p1!=NULL )
        {
            strcpy(localFile,p1+1);
        }
        else
            strcpy(localFile,local_path);

        sprintf(remote_path,"test/%s",localFile);
        ftp->set_remotedir(remote_path,strlen(remote_path));
        ftp->set_localdir(local_path,strlen(local_path));
        if(!ftp->into_passive())
        {
            printf("ftp into passive mode failed\n");
            continue;
        }
        if(ftp->upload())
        {
            printf("upload success\n");
            unlink(local_path);
        }
        else
        {
            printf("upload failed\n");
        }
    }
    ftp->close_ftp();
    if(ftp)
    {
        delete ftp;
        ftp = NULL;
    } 
    return 0;
}
#if 0
int main()
{
    char tempIP[16] = "200.200.4.216";
    unsigned short port = 21;
    char usrname[] = "tzw";
    char pwd[] = "123456";
    char remote_path[256] = "/newtest/cool.zip";
    char local_path[256] = "./testfile/cool.zip";
    FTP* ftp=new FTP;
    ftp->set_addr(tempIP,port);
    ftp->set_user(usrname,strlen(usrname));
    ftp->set_pwd(pwd,strlen(pwd));
    ftp->set_remotedir(remote_path,strlen(remote_path));
    ftp->set_localdir(local_path,strlen(local_path));
    bool Stop_upgrade=false;
    //上传
    #if 1
    if(ftp->open_ftp())
    {
        if(ftp-> into_passive())
        {
            printf("into PASV success\n");
            if(!ftp->upload())
            {
              //  reply_server_func(msg,msglen,0x04);//0x04 upload fail
                ftp->close_ftp();
                if(ftp)
                {
                    delete ftp;
                    ftp = NULL;
                }   
                return 0;
            }
            else
            {
                printf("upload success\n");
            }
        }
    }
    else
    {
        ftp->close_ftp();
    }
    if(ftp)
    {
        delete ftp;
        ftp = NULL;
    } 
    #endif 

    //下载

    
    return 0;
}
#endif