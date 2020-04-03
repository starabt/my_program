unsigned int Nr = 10;  // AES-128需要 10 轮加密  
unsigned int Nk = 4;   // Nk 表示输入密钥的 unsigned int 个数  
class AES
{
public:
    //AES();
    //~AES();
    /******************************下面是加密和解密函数**************************/  
/****************************************************************************
    Function:   encrypt()
    Description:    encrypt 16 bytes text
                    加密16字节数据（数组*in）, *w为扩展密钥，返回加密后的数据到*in
    Input:      in:the text to encrypt      w:round key 
 *****************************************************************************/ 
    void encrypt(unsigned char *in, unsigned int *w);
/****************************************************************************
    Function:   decrypt()
    Description:    decrypt 16 bytes text
                    解密16字节数据（数组*in）, *w为扩展密钥，返回解密后的数据到*in
    Input:      in:the text to decrypt      w:round key 
 *****************************************************************************/ 
    void decrypt(unsigned char *in, unsigned int *w);
/*********************************************************************************
    Function:   encryptlong()
    Description:     encrypt a long text
    Input:      message:text to encrypt     lenM:bytes of text      w:round key     cArray:store the encrypted text
    Retrun:     the encrypted bytes
 *******************************************************************************/ 
    unsigned int encryptlong(unsigned char *message,unsigned int lenM,unsigned int *w,unsigned char *cArray);
/*********************************************************************************
    Function:   decryptlong()
    Description:     decrypt a long text
    Input:      message:text to decrypt     lenC:bytes of text      w:round key     cArray:store the decrypted text
    Retrun:     the decrypted bytes
 *******************************************************************************/ 
    unsigned int decryptlong(unsigned char *encryptedMsg,unsigned int lenC,unsigned int *w,unsigned char *mArray);
/*********************************************************************************************************************
    Function:   KeyExpansion()
    Description:    expand 4 word key(16 bytes) to 44 word ,(one key to 11 keys)  ,对4字密钥进行扩展得到 *w，
                    本程序中Nr=10，总共进行11次轮密钥加，每次需要一个4字（16字节）的轮密钥 
 ******************************************************************************************************************/ 
    unsigned int KeyExpansion(unsigned char *key, unsigned int *w);
private:
/*************************************************************************************
    Function:   SubBytes()
    Description:    do transformation with S-box ,S盒变换 - 前4位为行号，后4位为列号
    Input:      a 16 bytes array to  transform 
    Output:     transformed array 
 ************************************************************************************/ 
    void SubBytes(unsigned char mtx[4*4]) ;  
/********************************************************************************
    Function:   ShiftRows()
    Description:    Shift rows 行变换 - 按字节循环移位 
    Input:      a 16 bytes array to shift
    Output:     shifted array  
 *************************************************************************************/  
    void ShiftRows(unsigned char mtx[4*4]);
/*********************************************************************************
    Function:       GFMul()
    Description:        the multiple algorithm in GF(2^8) ，有限域上的乘法
    Input:      two byte to multiple
    return:     multiple result
 ********************************************************************************/ 
    unsigned char GFMul(unsigned char a, unsigned char b); 
/******************************************************************************
    Function:       MixColumns()
    Description:        mixture column,列混淆，与特定数组进行按位异或
    Input：      a 16 bytes array to mix
    Output:     mixed array
********************************************************************************/ 
    void MixColumns(unsigned char mtx[4*4]);
/*****************************************************************************
    Function:   AddRoundKey()
    Description:    轮密钥加变换 - 将每一列与扩展密钥进行异或  
    Input:      mtx:the initial text array      k:Round Key
    Output:     the array
 *******************************************************************************/  
    void AddRoundKey(unsigned char mtx[4*4], unsigned int k[4]);
/***************************************************************************
    Function:   InvSubBytes()
    Description:    逆S盒变换
  
*****************************************************************************/ 
    void InvSubBytes(unsigned char mtx[4*4]);
/************************************************************************* 
    Function:   InvShiftRows()
    Description:      逆行变换 - 以字节为单位循环右移    
 ************************************************************************/  
    void InvShiftRows(unsigned char mtx[4*4]);
/***********************************************************************
    Function:       InvMixColumns()
    Description:         逆列混淆，与特定数据进行按位异或

***********************************************************************/ 
    void InvMixColumns(unsigned char mtx[4*4]);
    /******************************下面是密钥扩展部分***********************/  
/***********************************************************************
    Function:       Word()
    Description:    combine 4 byte tobe one word 
    Retrun :        the word
 ***********************************************************************/ 
    unsigned int Word(unsigned char &k1, unsigned char &k2, unsigned char &k3, unsigned char &k4);
/*********************************************************************
    Function:    Rotword()
    Description:    circle shift left one byte     
    
 ******************************************************************/  
    unsigned int Rotword(unsigned int rw);
/*******************************************************************
    Function:   Subword()
    Description:      do S-box transformation with each byte of the word sw     
    
 ********************************************************************/  
    unsigned int Subword(unsigned int sw) ;
    
}; 