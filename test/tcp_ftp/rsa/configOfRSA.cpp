#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <string.h>

using namespace std;

const int MAX_NUM=63001;
//store random num e;
struct eKeySet
{
	unsigned int set[MAX_NUM];
	unsigned int size;
}eSet;

//store public and privary key pair
struct PairKey
{
	unsigned int d;
	unsigned int e;
	unsigned int n;
}pairKey;

//judge a num prime or not
int judge_prime(unsigned int n)
{
	unsigned int i;
	unsigned int k=(int) sqrt(n);
	for (i=2;i<=k;i++)
	{
		if(0==(n%2))
		{
			break;
		}
	}
	return (i>k)?1:0;//1 for prime ;0 for not
}

int judge_prime_two(unsigned int m,unsigned int n)
{
	unsigned int r1=m;
	unsigned int r2=n;
	unsigned int r;
	while(r2>0)
	{
		r=r1%r2;
		r1=r2;
		r2=r;
	}
	return r1;//if prime to eath other,return 1
}

//random num eSet.set[]
//1<e<z=(p-1)*(q-1),e and z prime to eath other
int get_eKey(unsigned int uiP,unsigned int uiQ)
{
	unsigned int z=(uiP-1)*(uiQ-1);
	unsigned int i;
	eSet.size=0;
	memset(eSet.set,0,sizeof(eSet.size));
	for (i=2;i<z;i++)
	{
		//printf("i:%d,judge:%d\n",i,judge_prime_two(i,z) );
		if(1==judge_prime_two(i,z))
		{
			eSet.set[eSet.size]=i;
			eSet.size++;
		}
		else
		{

			cout<<"get_eKey error"<<endl;
		}
	} 
	//printf("size:%d\n",eSet.size );
	for(i=0;i<eSet.size;i++)
	{
		printf("eSet.set[%u]%u\n",i,eSet.set[i] );
	}
	return eSet.size;
}


//get PairKey(e,d,n)
int GetPairKey(unsigned int uiP,unsigned int uiQ,unsigned int uiE)
{
	
	unsigned int i=0,d;
	unsigned int z=(uiP-1)*(uiQ-1);
	unsigned int e=eSet.set[uiE];

	if(1==judge_prime_two(e,z))
	{
		for (i=2;i<z;i++)
		{
			if((e*i)%z==1)
			{
				d=i;
			}
		}
	}
	else 
	{	cout<<"e,z not prime to each other "<<endl;
		return -1;
	}
	pairKey.d=d;
	pairKey.e=e;
	pairKey.n=uiP*uiQ;
	return 0;
}

//rsa_encrypt()
void rsa_encrypt(unsigned int n,unsigned int e, const char *mw,unsigned int mlength,char *cw)
{
	unsigned int i=0,j=0;
	unsigned int temInt=0;
	for (i=0;i<mlength;i++)
	{
		temInt=mw[i];
		if(e!=0)
		{
			for(j=0;j<e;j++)
			{
				temInt =(temInt*mw[i])%n;
			}
		}
		else
		{
			temInt =1;
		}
		cw[i]=(int)temInt;
	}
	
}

//judge whether is number array
bool judge_Num(const char *strNum)
{
	unsigned int i;
	for (i=0;i<strlen(strNum);i++)
	{
		if(strNum[i]<'0'||strNum[i]>'9')
			return false;
		else 
			return true; 
	}
}


int main()
{
	unsigned int p,q;
	unsigned int i;
	bool aFlag=true;
	bool bFlag=true;
	const char *message="1234567890";
	char codemesg[MAX_NUM];
		
	
	while(aFlag)
	{
		cout<<"input the first prime p:"<<endl;
		scanf("%u",&p);
		if(1==judge_prime(p))
		{
			aFlag=false;

		}
		else
		{
			aFlag=true;
		}
	}
	
	while(bFlag)
	{
		cout<<"input the second prime q:"<<endl;
		scanf("%u",&q);
		if(1==judge_prime(q))
		{
			bFlag=false;

		}
		else
		{
			bFlag=true;
		}
	}
	
	#if 0
	unsigned int s=get_eKey(p,q);
	for(i=0;i<s;i++)
	{
		cout<<"num:e"<<endl;
		printf("eSet.set[%u]:%u\n",i,eSet.set[i] );	
	}
	#endif
	//cout<<"input the num of e you choose "<<endl;
	unsigned int E=65539;

	scanf("%u",&E);
	GetPairKey(p,q,E);
	printf("the public key is (%u,%u)\n",pairKey.n,pairKey.e );
	printf("the privary key is (%u,%u)\n",pairKey.n,pairKey.d  );
	
	#if 0
	if(judge_Num(message)==true)
	{
		rsa_encrypt(pairKey.n,pairKey.e,message,strlen(message),codemesg);
		for (i=0;i<strlen(codemesg);i++)
		{
			printf("%d ",codemesg[i] );
		}
	}
	else
		printf("oh no\n");
	#endif


	return 0;


}

