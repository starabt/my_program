#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/mount.h>
#include <stdlib.h>
#include <sys/statfs.h>
#include <stdio.h>
#include <errno.h>
int WriteFile(char *FILENAME,void *pBuf, int len)
{
    int ret = -1; 
    FILE *fp = fopen(FILENAME,"wb+");
    if(fp == NULL)
    {
        fprintf(stderr, "Open single param file %s for write failed ", FILENAME);
        perror(":");
        return -1;
    }
    ret=fwrite(pBuf,1,len,fp);
    fflush(fp);
    int fd=fileno(fp);
    fsync(fd); 
    // ret = ret > 0 ? 0 : -1;
    ret = ret > 0 ? ret : -1;
    if(fp != NULL)
    {
        fclose(fp);
        fp=NULL;
    }
    return ret; 
}
int ReadFile(char *FILENAME,void *pBuf, int len)
{
    int ret=-1; 
    FILE *fp = fopen(FILENAME,"rb");

    if(fp == NULL)
    {
        fprintf(stderr, "Open single param file %s for read failed ", FILENAME);
        perror(":");
        return -1;
    }
    ret=fread(pBuf,1,len,fp);
    // ret = ret > 0 ? 0 : -1;
    ret = ret > 0 ? ret : -1;
    if(fp != NULL)
    {
        fclose(fp);
        fp=NULL;
    }
    return ret;   
}

int main()
{
	printf("输入初始里程 （十进制，公里） :");
	int carid = 0;
	int carid2 = 0;
	scanf("%d",&carid);

	// FILE* fp = fopen("./carid","wb+");
	// if(fp != NULL)
	// {
	// 	fwrite(&carid,1,sizeof(carid),fp);
	// }

	// memcpy(caridBuf,&carid,sizeof(carid));
	WriteFile("./begin_mileage",&carid,sizeof(carid));
	perror("");
	// sleep(1);
	// ReadFile("./carid",&carid2,sizeof(carid2));
	// perror("");
	// printf("carid2:%x\n", carid2);
	return 0;

}