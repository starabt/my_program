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
#include "RSA.h"
#include <string.h>
using namespace std;

/***************************************************************************************
	Function:	add_mod()
	Description:	快乘法，基于快速幂的二分思想，used in pow_mod(), Miller_Rabbin()

***************************************************************************************/
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
/**************************************************************************************
	Function:	pow_mod()
	Description:	快速幂，递归版,used in Miller_Rabbin()
**************************************************************************************/
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
/************************************************************************************
	Function:	Miller_Rabbin()
	Description: 	judge whether is Miller_Rabbin prime,used in is_prime()
************************************************************************************/
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
/*********************************************************************************
	Function:	is_prime()
	Description: 	judge whether a interger is prime or not
	Return:		1:prime  		>1:not prime
*********************************************************************************/
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
/*********************************************************************************************
	Function:	getPrime()
	Description:	randomly get prime pair(p and q) within (homeNum, endNum),saved in P_Q
	
********************************************************************************************/
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
/***********************************************************************************************************************************
	Function:	get_d()
	Description:	to get the pravite key with pubulic key(e,n),e has been defined in RSA.h named const_e;uiP and uiQ is the prime pair 	
	Return:		private key d

************************************************************************************************************************************/
unsigned int RSA::get_d(unsigned int ee,unsigned int uiP,unsigned int uiQ)//e is 65537 ,n=(p-1)*(q-1)
{
	unsigned int k;
	unsigned int dd;
	unsigned int O_n=(uiP-1)*(uiQ-1);
	for(k=1;;k++)
	{
		if((O_n*k+1)%ee==0)
		{
			dd=(O_n*k+1)/ee;
			break;
		}
	}
	return dd;
}
#if 0
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
#endif
/****************************************************************************************************************************
	Function:	mod()
	Description:	encrypt one byte or decrypt one byte,public key(e,n) for encrypt,private key(d,n) for decrypt
	Attention:		used in encrypt() and decrypt()
	Return:			the encrypted or decrypted result 
***************************************************************************************************************************/
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

/***********************************************************************************************************************
	Function: 	encrypt()
	Description:	encrypt public test mArray,the cipher text saved in cArray
	Input:		mArray:public text to be encrypted 		lenM:the bytes of pubulic text 		ee&nn:the public key pair(e,n)		cArray:to store the cipher text
	Return:		the encrypted bytes	
***********************************************************************************************************************/
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
/************************************************************************************************************************************
	Function:		decrypt()
	Description:		decrypt cipher text cArray,the decrypted result stored in mArray
	Input:		cArray:teh cipher text		lenC:the bytes of cipher text 	 dd&nn:the pravate key pair(d,n)	mArray:store the decrypted text
	Return:		the decrypted bytes
***********************************************************************************************************************************/
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

/******************************************************************************
	Description:	get 100 random Number between 0~255 as message to eb encrypted
	Attention:		used for test
*********************************************************************************/
unsigned char ranMsg(unsigned char *buf)
{
	unsigned int num=0;
	srand((unsigned) time(NULL));
	for(int i=0;i<100;i++)
	{
		buf[i]=rand()%255;
		num++;
	}
	return num;
}
/********************************************************************************
	Description:	compare two Array
	Return:		1:the same 		0:not the same
	Attention:		used for test
*******************************************************************************/
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
	clock_t enstart, enfinish;//计算加密时间，单位us
	clock_t destart, definish;//计算解密时间，单位us
	
	unsigned int i,j;
	RSA rsa;//定义一个RSA 对象，用于引用RSA.h中定义的RSA类
	unsigned char message[2048]={0};
	unsigned int ranNUm=ranMsg(message);//get 100 random num between 0~5 saved in message,return 100 to ranNUm
	unsigned int codeMsg[4096]={0};//存放密文
	unsigned char initMsg[4096]={0};//存放解密后的明文（原数据）
	//打印待加密明文
	for(i=0;i<ranNUm;i++)
	{
		printf("%x ",message[i] );
	}
	unsigned int p=P_QPAIR[bit_12][pp];
	unsigned int q=P_QPAIR[bit_12][qq];
	printf("p:%d, q:%d\n", p,q);
	unsigned int n=p*q;
	unsigned int d=rsa.get_d(const_e,p,q);
	//for(int i=0;i<100;i++)//test 100 times
	//{
		enstart=clock();//记录加密开始时间
		rsa.encrypt(message,ranNUm,const_e,n,codeMsg);//开始加密，最后密文存于 codeMsg[]
		enfinish=clock();//记录加密结束时间
		printf("entime:%ld\n",enfinish-enstart );//加密时间
		#if 0
		for(i=0;i<strlen(message);i++)
		{
			printf("%u ",codeMsg[i] );
		}
		printf("\n");
		#endif
		//unsigned int d=rsa.get_d(e,(p-1)*(q-1));
		printf("d(x):%x\n",d );
		printf("d(d):%d\n",d );//打印看一下私钥
		destart=clock();//解密开始时间
		unsigned int nbytes=rsa.decrypt(codeMsg,ranNUm,d,n,initMsg);//解密，返回解密字节数到 nbytes
		definish=clock();//解密结束时间
		printf("detime:%ld\n",definish-destart );
		printf("nbytes:%d\n",nbytes );
		printf("cmp:%u\n",cmp(message,initMsg,ranNUm)) ;
	
		for(int i=0;i<ranNUm;i++)
		{
			printf("%x ",initMsg[i] );
			
		}
		
		

	//}
	
}


