/*************************************************************************************
*此版本中，与产生密钥密切相关公钥e和素数对p和q，已在RSA.h中定义。使用此程序时，
*调用 GetPairKey()函数，根据RSA.h中的enum bits相关参数索引 P_QPAIR中相应的产生指定位数密钥的素数对，
*索引到的素数对，p和q分别作为GetPairKey()函数的参数输入，最终获得密钥存放在struct PAIRKEY pairkey中,
*pairkey.e， pairkey.d, pairkey.n，就能作为加解密函数 encrypt()和 decrypt() 的参数进行加解密
*
*如果要选用其他的密钥，只需用 getPrime()产生素数对集合，从中选取素数对进行产生密钥即可
*******************************************************************************************/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <time.h>
#include <sys/time.h>
#include "RSA.h"
#include <string.h>
using namespace std;

/**
*快乘法，基于快速幂的二分思想，在 pow_mod, Miller_Rabbin中引用
*/
unsigned int RSA::add_mod(unsigned int a,unsigned int b,unsigned int mod)
{     
    unsigned int ans=0;                     
    while(b){                    
        if(b&1)                     
            ans=(ans+a)%mod;
        a=a*2%mod;
        b>>=1;
    }
    return ans;
}
/**
*快速幂，递归版,在 Miller_Rabbin中引用 
*/
unsigned int RSA::pow_mod(unsigned int a,unsigned int n,unsigned int mod)
{             
    if(n>1){                            
        unsigned int tmp=RSA::pow_mod(a,n>>1,mod)%mod;
        tmp=RSA::add_mod(tmp,tmp,mod);
        if(n&1) tmp=RSA::add_mod(tmp,a,mod);
        return tmp;
    }
    return a;
}
/**
*米勒拉宾素数判断函数主体,在is_prime中引用
*/
bool RSA::Miller_Rabbin(unsigned int n,unsigned int a)
{
    unsigned int d=n-1,s=0,i;    
    while(!(d&1)){            // 先把(2^s)*d 算出来 
        d>>=1;
        s++;
    }
    unsigned int t=RSA::pow_mod(a,d,n);	//a^d取一次余判断 
    if(t==1 || t==-1)	//一或负一则可以声明这可能是质数 
        return 1;
    for(i=0;i<s;i++){	//不是的话继续乘上s个2 
        if(t==n-1)	//(n-1)*(n-1)%n=1 这一步是优化 
            return 1;
        t=RSA::add_mod(t,t,n);	// 快乘 
    }
    return 0;
}
/**
*判断一个整数是不是素数，是的话返回1，不是的话返回大于一的整数
*/
bool RSA::is_prime(unsigned int n)
{
    unsigned int i,tab[4]={3,4,7,11};//本来应该取[1,n]内任意整数 
    for(i=0;i<4;i++){                //但一般这几个数足以,不需要太多组测试 
        if(n==tab[i])
            return 1;        
        if(!n%tab[i])
            return 0;
        if(n>tab[i] && !RSA::Miller_Rabbin(n,tab[i]))
            return 0;
    }
    return 1;
}
/**
*判断两个整数是不是互为素数，是的话返回1，不是的话返回大于一的整数
*/
unsigned int RSA::judge_prime_two(unsigned int m,unsigned int n)
{
	unsigned int r1=m;
	unsigned int r2=n;
	unsigned int temp;
	if(r1==r2)
	{
		return 0;
	}
	else
	{
		while(r2>0)
		{
			temp=r2;
			r2=r1%r2;
			r1=temp;
		}
		return r1;
	}
}
/**
*在（homeNum, endNum）范围内获取素数对p和q，存于二维指针数组P_Q中，每一对为一个小数组，实际存放的二维数组须事先定义好
*/
unsigned int RSA::getPrime(unsigned int homeNum,unsigned int endNum,unsigned int **P_Q)
{
    unsigned int primeNum,i,num=0;
    unsigned int primeBuf[endNum-homeNum];
    //unsigned int P_Q[endNum-homeNum+1]={0};
    srand((unsigned) time(NULL)); //用时间做种，每次产生随机数不一样
    for(i=0;i<(endNum-homeNum+1);i++)
    {
		
		primeNum=rand()%(endNum-homeNum+1)+homeNum;
		if(RSA::is_prime(primeNum))
		{
			primeBuf[num]=primeNum;
			num++;
		}
	}
	for(int i=0;i<num/2+1;i++)
    {
        for(int j=1;j<num;j++)
        {

            if(1==RSA::judge_prime_two(primeBuf[i],primeBuf[j])&& 1==RSA::judge_prime_two((primeBuf[i]-1)*(primeBuf[j]-1),const_e))
            {
                P_Q[i][0]=primeBuf[i];
                P_Q[i][1] =primeBuf[j];
                
            }
        }
        
    }
	return i;

}
/**
*由公钥ee,n的欧拉数O_n=(p-1)(q-1)，获取私钥dd，根据关系ee*dd=1mod(p-1)(q-1)
*/
// unsigned int RSA::get_d(unsigned int ee,unsigned int O_n)//e is 65537 ,n=(p-1)*(q-1)
// {
// 	unsigned int k;
// 	unsigned int dd;
// 	for(k=1;;k++)
// 	{
// 		if((O_n*k+1)%ee==0)
// 		{
// 			dd=(O_n*k+1)/ee;
// 			break;
// 		}
// 	}
// 	return dd;
// }
/**
*获取最终的密钥对，uiP和uiQ分别指素数p和q，最后保存在ARS.h中定义的struct PAIRKEY pairkey， pairkey.d， pairkey.e,pairkey.n
*/
unsigned int RSA::GetPairKey(unsigned int uiP,unsigned int uiQ)
{
    unsigned int i=0,dd;
    unsigned int z=(uiP-1)*(uiQ-1);
    
    if(1==judge_prime_two(const_e,z))
    {
        for(int k=1;;k++)
        {
            if((z*k+1)%const_e==0)
            {
                dd=(z*k+1)/const_e;
                break;
            }
        }
    }
    else 
    {   cout<<"e,z not prime to each other "<<endl;
        return -1;
    }
    pairkey.d=dd;
    pairkey.e=const_e;
    pairkey.n=uiP*uiQ;
    return 0;
}
/**
*加解密的关键算法m^e=c(mod n),c^d=m(mod n),此算法的处理利用了模运算的相关特性，避免了超大数的出现，但仍无可避免大量的运算次数
*函数输入单个明文或密文m_c，密钥e_d指加密时输入公钥e，解密时输入私钥d,n为素数对p和q的乘积n=p*q，返回加解密的结果
*/
unsigned int RSA::mod(unsigned int m_c,unsigned int e_d,unsigned int n)
{
	unsigned int result=((m_c%n)*(m_c%n))%n;
	unsigned int i;
	for(i=2;i<e_d;i++)
	{
		result=(result*(m_c%n))%n;
	}
	return result;
}

/**
*加密函数，输入明文 mArray,公钥（ee,nn），输出密文到 cArray,函数返回加密的字节数
*存放密文的 cArray要自己定义好	
*/
unsigned int RSA::encrypt(unsigned char *mArray,unsigned int lenM ,unsigned int ee,unsigned int nn,unsigned int *cArray)
{
	unsigned int i;
	unsigned int r;//r is remainder
	for (i=0;i<lenM;i++)
	{
		r=RSA::mod(mArray[i],ee,nn);
		//printf("r:%d ", r);
		cArray[i]=(nn+r);
		//printf("n+r:%d ",nn+r );
		//printf("cA:%d ", cArray[i]);
	}
	cArray[i]='\0';
	printf("len_cA:%d\n",i );
	//printf("sizeof:%d",sizeof(cArray) );
	return i;
	
}
/**
*加密函数，输入密文 cArray,私钥（dd,nn），输出明文到 mArray,函数返回解密的字节数；
*存放明文的 mArray要自己定义好	
*/
unsigned int RSA::decrypt(unsigned int *cArray,unsigned int lenC,unsigned int dd,unsigned int nn,unsigned char *mArray)
{
	unsigned int i=0;

	unsigned int r;//r is remainder
	//printf("size2:%d\n",(cArray) );
	for(i=0;i<lenC;i++)
	{
		r=RSA::mod(cArray[i],dd,nn);
		mArray[i]=r;
		//printf("mA:%d ",mArray[i] );
	}
	return i;

}
unsigned int ranMsg(unsigned char *buf,int count)
{
	unsigned int num=0;
	srand((unsigned) time(NULL));
	for(int i=0;i<count;i++)
	{
		buf[i]=rand()%255;
		num++;
	}
	return num;
}
unsigned int cmp(unsigned char *buf1,unsigned char *buf2,unsigned int len)
{
	for(int i=0;i<len;i++)
	{
		if(buf1[i]!=buf2[i])
		{
			return 0;
			break;
		}
	}
	return 1;
}
/*************************************************测试********************************************************************/
int main()
{
	// clock_t enstart, enfinish;//计算加密时间，单位us
	// clock_t destart, definish;//计算解密时间，单位us
	struct timeval start;//计算加密时间，单位us
	struct timeval finish;
	long int time_diff=0;

	
	unsigned int i,j;
	RSA rsa;//定义一个RSA 对象，用于引用RSA.h中定义的RSA类
	//unsigned char message[]="0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef";//待加密数据
	//unsigned char message[]={0xaa,0xbb,0xdd,0xcc,0xff};
	unsigned char message[2048]={0};
	unsigned int ranNUm=0;
	// unsigned int ranNUm=ranMsg(message,1024);
	//unsigned int lenMsg=sizeof(message);
	unsigned int codeMsg[4096]={0};//存放密文
	unsigned char initMsg[4096]={0};//存放解密后的明文（原数据）
	#if 0
	unsigned int numOfP_Q=rsa.getPrime(240,280,P_Qbuf);
	printf("num:%d\n",numOfP_Q );
	for(i=0;i<numOfP_Q;i++)
	{
		for(j=1;j<numOfP_Q;j++)
		{

			if(1==rsa.judge_prime_two(P_Qbuf[i],P_Qbuf[j])&& 1==rsa.judge_prime_two((P_Qbuf[i]-1)*(P_Qbuf[j]-1),e))
			{
				p=P_Qbuf[i];
				printf("p:%d\n",p );
				q=P_Qbuf[j];
				printf("q:%d\n",q );
				break;
			}
		}
		break;
	}
	
	printf("%d,%d\n",rsa.judge_prime_two(p,q) ,rsa.judge_prime_two((p-1)*(q-1),e));
	#endif
	//打印待加密明文
	int cipher=0;
	int msglen=0 ;
	while(1)
	{
		printf("input the cmd to choose the cipher length:(0>12,1>13,2>14,3>15,4>16)\n");
		scanf("%d",&cipher);
		rsa.GetPairKey(P_QPAIR[cipher][p],P_QPAIR[cipher][q]);//获得最终的密钥对，P_QPAIR定义在RSA.h中，存放事先定义好的素数对，cipher指最终产生12位私密
		printf("\np:%d, q:%d, d:%d\n", P_QPAIR[cipher][p],P_QPAIR[cipher][q],pairkey.d);
		
		printf("choose the msg len:(0>1024,1>512,2>256,3>128,4>64)\n");
		scanf("%d",&msglen);
		switch(msglen)
		{
			case 0:
				memset(message,0,sizeof(message));
				ranNUm=ranMsg(message,1024);
				break;
			case 1:
				memset(message,0,sizeof(message));
				ranNUm=ranMsg(message,512);
				break;
			case 2:
				memset(message,0,sizeof(message));
				ranNUm=ranMsg(message,256);
				break;
			case 3:
				memset(message,0,sizeof(message));
				ranNUm=ranMsg(message,128);
				break;
			case 4:
				memset(message,0,sizeof(message));
				ranNUm=ranMsg(message,64);
				break;
			default:
				break;
		}
		// printf("the message to be encrypted:\n");
		// for(i=0;i<ranNUm;i++)
		// {
		// 	printf("%d ",message[i] );
		// }
		// printf("\n");
		
		

		gettimeofday(&start,NULL);//记录加密开始时间
		rsa.encrypt(message,ranNUm,pairkey.e,pairkey.n,codeMsg);//开始加密，最后密文存于 codeMsg[]
		gettimeofday(&finish,NULL);//记录加密结束时间
		time_diff=(finish.tv_sec-start.tv_sec)*1000*1000 + (finish.tv_usec-start.tv_usec);
		printf("entime:%ldus\n",time_diff);//加密时间
		#if 0
		printf("encrypted message:\n");
		for(i=0;i<ranNUm;i++)
		{
			printf("%d ",codeMsg[i] );
		}
		printf("\n");
		#endif
		//unsigned int d=rsa.get_d(e,(p-1)*(q-1));
		// printf("d(x):%x\n",pairkey.d );
		// printf("d(d):%d\n",pairkey.d );//打印看一下私钥
		gettimeofday(&start,NULL);//记录加密开始时间
		unsigned int nbytes=rsa.decrypt(codeMsg,ranNUm,pairkey.d,pairkey.n,initMsg);//解密，返回解密字节数到 nbytes
		gettimeofday(&finish,NULL);//记录加密结束时间
		time_diff=(finish.tv_sec-start.tv_sec)*1000*1000 + (finish.tv_usec-start.tv_usec);
		printf("detime:%ldus\n",time_diff);//加密时间
		printf("nbytes:%d\n",nbytes );
		// printf("cmp:%u\n",cmp(message,initMsg,ranNUm)) ;
		// printf("decrypted message:\n");
	
		// for(int i=0;i<ranNUm;i++)
		// {
		// 	printf("%d ",initMsg[i] );
			
		// }
		// printf("\n");
	}
		
		
	return 0;	
	
}


