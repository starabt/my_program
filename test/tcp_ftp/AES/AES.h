const unsigned int Nr = 10;  // AES-128需要 10 轮加密  
const unsigned int Nk = 4;   // Nk 表示输入密钥的 int 个数  
class AES
{
public:
    //AES();
    //~AES();
    /******************************下面是加密和解密函数**************************/  
    /** 
    *  加密16字节数据（数组in[4*4]）, w[4*(Nr+1)]为扩展密钥，返回加密后的数据到in[4*4] 
    */  
    void encrypt(unsigned char in[4*4], unsigned int w[4*(Nr+1)]);
    /** 
    *  解密16字节数据（数组in[4*4]）, w[4*(Nr+1)]为扩展密钥，返回解密后的数据到in[4*4] 
    */  
    void decrypt(unsigned char in[4*4], unsigned int w[4*(Nr+1)]);
    /** 
 	*  加密长串数据（数组message[]）, w[4*(Nr+1)]为扩展密钥，加密后的数据存到数组 cArray[]，返回加密的字节数
 	*/
    unsigned int encryptlong(unsigned char *message,unsigned int lenM,unsigned int w[4*(Nr+1)],unsigned char *cArray);
    /** 
 	*  解密长串数据（数组encryptedMsg[]）, w[4*(Nr+1)]为扩展密钥，解密后的数据存到全局数组 mArray[]，返回解密的字节数
	*/
    unsigned int decryptlong(char unsigned *encryptedMsg, unsigned int lenEN,unsigned int w[4*(Nr+1)],unsigned char *mArray);
    /** 
    *  密钥扩展函数 - 对128位密钥进行扩展得到 w[4*(Nr+1)]，
    *  本程序中Nr=10，总共进行11次轮密钥加，每次需要一个4字（16字节）的轮密钥 
    */   
    unsigned int KeyExpansion(unsigned char key[4*Nk],unsigned int w[4*(Nr+1)]);
private:
	    /** 
    *  S盒变换 - 前4位为行号，后4位为列号 
    */  
    void SubBytes(unsigned char mtx[4*4]) ;  
    /** 
    *  行变换 - 按字节循环移位 
    */  
    void ShiftRows(unsigned char mtx[4*4]);
    /** 
    *  有限域上的乘法 GF(2^8) 
    */  
    unsigned char GFMul(unsigned char a, unsigned char b); 
    /** 
    *  列混淆，与特定数组进行按位异或
     */  
    void MixColumns(unsigned char mtx[4*4]);
    /** 
    *  轮密钥加变换 - 将每一列与扩展密钥进行异或 
    */  
    void AddRoundKey(unsigned char mtx[4*4],unsigned  int k[4]);
    /**************************下面是解密的逆变换函数***********************/  
    /** 
    *  逆S盒变换 
    */  
    void InvSubBytes(unsigned char mtx[4*4]);
    /** 
    *  逆行变换 - 以字节为单位循环右移 
    */  
    void InvShiftRows(unsigned char mtx[4*4]);
    /** 
    *  逆列混淆，与特定数据进行按位异或
    */ 
    void InvMixColumns(unsigned char mtx[4*4]);
    /******************************下面是密钥扩展部分***********************/  
    /** 
    * 将4个 char 转换为一个 int. 
    */  
    unsigned int Word(unsigned char &k1,unsigned char &k2, unsigned char &k3, unsigned char &k4);
    /** 
    *  按字节 循环左移一位 
    *  即把[a0, a1, a2, a3]变成[a1, a2, a3, a0] 
    */  
    unsigned int Rotword(unsigned int rw);
    /** 
    *  对输入int中的每一个字节进行S-盒变换 
    */  
    unsigned int Subword(unsigned int sw) ;
    
}; 