#include <stdio.h>
#include <stdlib.h>


//judge a num prime or not
int judge_prime(int n)
{
	int i;
	int k=(int) sqrt(n);
	for (i=2;i<=k;i++)
	{
		if(0==(n%2))
		{
			break;
		}
	}
	return (i>k)?1:0;//1 for prime ;0 for not
}

int judge_prime_two(int m,int n)
{
	int r1=m;
	int r2=n;
	int r;
	while(r2>0)
	{
		r=r1%r2;
		r1=r2;
		r2=r;
	}
	return r1;//if prime to eath other,return 1
}

//random num eArray[]
//1<e<z=(p-1)*(q-1),e and z prime to eath other
int get_e(int p,int q)
{
	int z=(p-1)*(q-1);
	int i;
	int j=0;
	for (i=1;i<z;i++)
	{
		if(1==judge_prime_two(i,z))
		{

		}
	} 
}