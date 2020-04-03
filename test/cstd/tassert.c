/*test assert macro*/
#define NDEBUG
#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int val = 0;
static void field_abort(int sig)
{
	if(val == 1)
	{
		puts("success testing <assert.h>");
		exit(EXIT_SUCCESS);
	}
	else
	{
		puts("failure testing <assert.h>");
		exit(EXIT_FAILURE);
	}
}
/*test func*/
static void dummy()
{
	int i = 0;
	assert(i == 0);
	assert(i == 1);
}
#undef NDEBUG
#include <assert.h>
int main()
{
	assert(signal(SIGABRT,&field_abort) != SIG_ERR);
	dummy();
	assert(val == 0);
	++ val;
	fputs("Sample asertion failure message --\n",stderr);
	assert(val == 0);
	puts("fail to test <assert.h>");
	return (EXIT_FAILURE);
}