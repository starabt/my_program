#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <time.h>

#define ll long long

using namespace std;

ll add_mod(ll a,ll b,ll mod){    //快乘法 基于快速幂的二分思想 
    ll ans=0;                    //由于考虑到取模数很大 快速幂会溢出 
    while(b){                    //必须使用该方法 
        if(b&1)                    //我这里写的是非递归版 
            ans=(ans+a)%mod;
        a=a*2%mod;
        b>>=1;
    }
    return ans;
}

ll pow_mod(ll a,ll n,ll mod){            //快速幂 递归版 
    if(n>1){                            
        ll tmp=pow_mod(a,n>>1,mod)%mod;
        tmp=add_mod(tmp,tmp,mod);
        if(n&1) tmp=add_mod(tmp,a,mod);
        return tmp;
    }
    return a;
}

bool Miller_Rabbin(ll n,ll a){//米勒拉宾素数判断函数主体
    ll d=n-1,s=0,i;    
    while(!(d&1)){            // 先把(2^s)*d 算出来 
        d>>=1;
        s++;
    }
    ll t=pow_mod(a,d,n);    //a^d取一次余判断 
    if(t==1 || t==-1)        //一或负一则可以声明这可能是质数 
        return 1;
    for(i=0;i<s;i++){                //不是的话继续乘上s个2 
        if(t==n-1)            //(n-1)*(n-1)%n=1 这一步是优化 
            return 1;
        t=add_mod(t,t,n);    // 快乘 
    }
    return 0;
}

bool is_prime(ll n){
    ll i,tab[4]={3,4,7,11};//本来应该取[1,n]内任意整数 
    for(i=0;i<4;i++){                //但一般这几个数足以,不需要太多组测试 
        if(n==tab[i])
            return 1;        //小判断小优化~ 
        if(!n%tab[i])
            return 0;
        if(n>tab[i] && !Miller_Rabbin(n,tab[i]))
            return 0;
    }
    return 1;
}


ll judge_prime_two(ll m,ll n)
{
    ll r1=m;
    ll r2=n;
    ll temp;
    while(r2>0)
    {
        temp=r2;
        r2=r1%r2;
        r1=temp;
    }
    return r1;//if prime to eath other,return 1
}

ll ranNum(ll homeNum,ll endNum)
{
    ll primeNum;
    srand((unsigned) time(NULL)); //用时间做种，每次产生随机数不一样
    while(1)
    {
        primeNum=rand()%(endNum-homeNum+1)+homeNum;
        if(is_prime(primeNum))
            break;
    }
    return primeNum;

}
    
int main(){
    ll n;
    n=ranNum(4294967290,4294967299);
    printf("ranNum:%lld\n",n );
    printf("%lld\n",judge_prime_two(4294967291,2147483647) );
    printf("prime_two:%lld\n",judge_prime_two(4294967290*2147483646,257) );
    //scanf("%lld",&n);
    if(n<2) printf("No");
    else if(n==2) printf("Yes");
    else{
        if(!n%2) printf("No");
        else if(is_prime(n))
            printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}

