const unsigned int const_e= 257;//实现确定公钥为257
const unsigned int P_QPAIR[5][2]={{257,223},{221,277},{257,211},{229,277},{283,331}};//第一个数组为12位密钥素数对，最后一个为16位密钥素数对
struct PAIRKEY//存放最后的密钥对
{
	unsigned int e;
	unsigned int d;
	unsigned int n;
}pairkey;
enum bits//用于索引素数对
{
	bit_12=0,//索引12位密钥所用素数对
	bit_13,//索引13位密钥所用素数对
	bit_14,//索引14位密钥所用素数对
	bit_15,//索引15位密钥所用素数对
	bit_16,//索引16位密钥所用素数对
	p=0,//索引p
	q=1,//索引q

};


class RSA
{
public:
	//RSA();
	//~RSA();
/**
*加密函数，输入明文 mArray,公钥（ee,nn），输出密文到 cArray,函数返回加密的字节数
*存放密文的 cArray要自己定义好	
*/
	unsigned int encrypt(unsigned char *mArray,unsigned int lenM ,unsigned int ee,unsigned int nn,unsigned int *cArray);
/**
*加密函数，输入密文 cArray,私钥（dd,nn），输出明文到 mArray,函数返回解密的字节数；
*存放明文的 mArray要自己定义好	
*/
	unsigned int decrypt(unsigned int *cArray,unsigned int lenC,unsigned int dd,unsigned int nn,unsigned char *mArray);
/**
*获取最终的密钥对，uiP和uiQ分别指素数p和q，最后保存在ARS.h中定义的struct PAIRKEY pairkey， pairkey.d， pairkey.e,pairkey.n
*/
	unsigned int GetPairKey(unsigned int uiP,unsigned int uiQ);
/**
*判断一个整数是不是素数，是的话返回1，不是的话返回大于一的整数
*/
	bool is_prime(unsigned int n);
/**
*在（homeNum, endNum）范围内获取素数对p和q，存于二维指针数组P_Q中，每一对为一个小数组，实际存放的二维数组须事先定义好
*/
	unsigned int getPrime(unsigned int homeNum,unsigned int endNum,unsigned int **P_Q);
/**
*判断两个整数是不是互为素数，是的话返回1，不是的话返回大于一的整数
*/
	unsigned int judge_prime_two(unsigned int m,unsigned int n);
/**
*快乘法，基于快速幂的二分思想，在 pow_mod, Miller_Rabbin中引用
*/
	unsigned int add_mod(unsigned int a,unsigned int b,unsigned int mod);
/**
*快速幂，递归版,在 Miller_Rabbin中引用 
*/
	unsigned int pow_mod(unsigned int a,unsigned int n,unsigned int mod);
/**
*米勒拉宾素数判断函数主体,在is_prime中引用
*/
	bool Miller_Rabbin(unsigned int n,unsigned int a);
/**
*由公钥ee,n的欧拉数O_n=(p-1)(q-1)，获取私钥dd，根据关系ee*dd=1mod(p-1)(q-1)
*/
	unsigned int get_d(unsigned int ee,unsigned int uiP,unsigned int uiQ);//e is 257 ,n=(p-1)*(q-1)
/**
*加解密的关键算法m^e=c(mod n),c^d=m(mod n),此算法的处理利用了模运算的相关特性，避免了超大数的出现，但仍无可避免大量的运算次数
*函数输入单个明文或密文m_c，密钥e_d指加密时输入公钥e，解密时输入私钥d,n为素数对p和q的乘积n=p*q，返回加解密的结果
*/
	unsigned int mod(unsigned int m_c,unsigned int e_d,unsigned int n);

	
};