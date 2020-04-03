#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int Swap32(int &n)
{
    int m = ((n&0xff)<<24)| ((n&0xff00)<<8)|((n&0xff0000)>>8) |((n&0xff000000)>>24);
    n=m;
    return m;
}
int main(int argc, char const *argv[])
{
	int mileage;
	printf("input the value of mileage:");
	scanf("%d",&mileage);
	printf("mileage:%d\n",mileage );
	FILE *fp = fopen("./canrawdata","wb+");
	if(fp == NULL)
	{
		perror("open file error");
		exit(1);
	}
	// Swap32(mileage);
	char tmp[4];
	tmp[0] = (mileage>>24) && 0xff;
	tmp[1] = (mileage>>16) && 0xff;
	tmp[2] = (mileage>>8) && 0xff;
	tmp[3] = (mileage) && 0xff;
	int ret = fwrite(tmp,1,4,fp);
	printf("write ret:%d\n",ret );
	fclose(fp);

	return 0;
}