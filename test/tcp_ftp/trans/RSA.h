const unsigned int const_e= 257;//实现确定公钥为257
const unsigned int P_QPAIR[5][2]={{257,223},{221,277},{257,211},{229,277},{283,331}};//第一个数组为12位密钥素数对，最后一个为16位密钥素数对
#if 0
struct PAIRKEY//存放最后的密钥对
{
	unsigned int e;
	unsigned int d;
	unsigned int n;
};
#endif
enum bits//用于索引素数对
{
	bit_12=0,//索引12位密钥所用素数对
	bit_13,//索引13位密钥所用素数对
	bit_14,//索引14位密钥所用素数对
	bit_15,//索引15位密钥所用素数对
	bit_16,//索引16位密钥所用素数对
	pp=0,//索引p
	qq=1,//索引q

};


class RSA
{
public:
	//RSA();
	//~RSA();
/***********************************************************************************************************************
	Function: 	encrypt()
	Description:	encrypt public test mArray,the cipher text saved in cArray
	Input:		mArray:public text to be encrypted 		lenM:the bytes of pubulic text 		ee&nn:the public key pair(e,n)		cArray:to store the cipher text
	Return:		the encrypted bytes	
***********************************************************************************************************************/
	unsigned int encrypt(unsigned char *mArray,unsigned int lenM ,unsigned int ee,unsigned int nn,unsigned int *cArray);
/************************************************************************************************************************************
	Function:		decrypt()
	Description:		decrypt cipher text cArray,the decrypted result stored in mArray
	Input:		cArray:teh cipher text		lenC:the bytes of cipher text 	 dd&nn:the pravate key pair(d,n)	mArray:store the decrypted text
	Return:		the decrypted bytes
***********************************************************************************************************************************/
	unsigned int decrypt(unsigned int *cArray,unsigned int lenC,unsigned int dd,unsigned int nn,unsigned char *mArray);
/***********************************************************************************************************************************
	Function:	get_d()
	Description:	to get the pravite key with pubulic key(e,n),e has been defined in RSA.h named const_e;uiP and uiQ is the prime pair 	
	Return:		private key d

************************************************************************************************************************************/
	unsigned int get_d(unsigned int ee,unsigned int uiP,unsigned int uiQ);//e is 257 ,n=(p-1)*(q-1)
/****************************************************************************************************************************
	Function:	mod()
	Description:	encrypt one byte or decrypt one byte,public key(e,n) for encrypt,private key(d,n) for decrypt
	Attention:		used in encrypt() and decrypt()
	Return:			the encrypted or decrypted result 
***************************************************************************************************************************/
	unsigned int mod(unsigned int m_c,unsigned int e_d,unsigned int n);
/*********************************************************************************************
	Function:	getPrime()
	Description:	randomly get prime pair(p and q) within (homeNum, endNum),saved in P_Q
	
********************************************************************************************/
	unsigned int getPrime(unsigned int homeNum,unsigned int endNum,unsigned int **P_Q);
#if 0
/**
*获取最终的密钥对，uiP和uiQ分别指素数p和q，最后保存在ARS.h中定义的struct PAIRKEY pairkey， pairkey.d， pairkey.e,pairkey.n
*/
	unsigned int GetPairKey(unsigned int uiP,unsigned int uiQ);
#endif
/*********************************************************************************
	Function:	is_prime()
	Description: 	judge whether a interger is prime or not
	Return:		1:prime  		>1:not prime
*********************************************************************************/
	bool is_prime(unsigned int n);
/******************************************************************************
	Function:	judge_prime_two()
	Description:	判断两个整数是不是互为素数
	Return:			1:互为素数 		>1:不是互为素数
*******************************************************************************/
	unsigned int judge_prime_two(unsigned int m,unsigned int n);



private:
/***************************************************************************************
	Function:	add_mod()
	Description:	快乘法，基于快速幂的二分思想，used in pow_mod(), Miller_Rabbin()

***************************************************************************************/
	unsigned int add_mod(unsigned int a,unsigned int b,unsigned int mod);
/**************************************************************************************
	Function:	pow_mod()
	Description:	快速幂，递归版,used in Miller_Rabbin()
**************************************************************************************/
	unsigned int pow_mod(unsigned int a,unsigned int n,unsigned int mod);
/************************************************************************************
	Function:	Miller_Rabbin()
	Description: 	judge whether is Miller_Rabbin prime,used in is_prime()
************************************************************************************/
	bool Miller_Rabbin(unsigned int n,unsigned int a);


	
};