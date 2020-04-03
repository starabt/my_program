#include <stdlib.h>
#include "share_mem.h"


int main()
{
	sys_infos *my_sys_infos;
	int ret = -1;
	ret = get_infos_address(&my_sys_infos);
	printf("ret :%d\n", ret);
	while(1)
	{
		printf("age:%d\n",my_sys_infos->age );
		sleep(1);
	}
	return 0;
}