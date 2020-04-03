#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//judge a num prime or not
int judge_prime(int64_t n)
{
	unsigned int i;
	int64_t k=sqrt(n);
	for (i=2;i<=k;i++)
	{
		if(0==(n%2))
		{
			break;
		}
	}
	return (i>k)?1:0;
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



int main()
{
	printf("%d\n",judge_prime(2147483647) );
	printf("%d\n",judge_prime(4294967297) );

	/*int p,q,n,On,e,d,min_wen;
	printf("input the first prime num:\n");
	scanf("%d",&p);
	printf("input the second prime num:");
	scanf("%d",&q);
	int testd=15;
	int testh=0x10;
	printf("d:%d\n",testh*testd );
	printf("x%x\n",testd*testh );

	n=p*q;
	On=(p-1)*(q-1);

	printf("input the index 'e': \n");
	scanf("%d",&e);

	printf("%d\n",judge_prime_two(p,q) );
*/

	return 0;
}