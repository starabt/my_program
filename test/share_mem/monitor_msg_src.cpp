#include <stdlib.h>
#include "share_mem.h"

int main()
{
	sys_infos *src_sys_infos;
	int ret = creat_shemp(&src_sys_infos);
	int age = 0;
	printf("ret :%d\n", ret);
	if( ret == 0)
	{
		while(1)
		{
			// src_sys_infos->age++;
			age++;
			share_write(SHARE_SINGLE,&src_sys_infos->age,&age,src_sys_infos);
			printf("src_sys_infos.age:%d\n", src_sys_infos->age);
			sleep(1);
		}
	}
		
	return 0;
}