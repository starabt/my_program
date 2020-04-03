/******************************************************************************************************************
    AppName:    RSA.cpp
    Description:    RSA encrypt and decrypt
    Auther:     Lu xican 
    Usage:      README.txt

                                                                                      
******************************************************************************************************************/
#include <iostream>  
#include <bitset>  
#include <string.h>  
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "AES.h"

using namespace std; 

unsigned char S_Box[16][16] = {  
    {0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76},  
    {0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0},  
    {0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15},  
    {0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75},  
    {0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84},  
    {0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF},  
    {0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8},  
    {0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2},  
    {0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73},  
    {0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB},  
    {0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79},  
    {0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08},  
    {0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A},  
    {0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E},  
    {0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF},  
    {0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16}  
};  
  
unsigned char Inv_S_Box[16][16] = {  
    {0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB},  
    {0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB},  
    {0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E},  
    {0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25},  
    {0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92},  
    {0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84},  
    {0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06},  
    {0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B},  
    {0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73},  
    {0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E},  
    {0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B},  
    {0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4},  
    {0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F},  
    {0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF},  
    {0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61},  
    {0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D}  
};  
  
// 轮常数，密钥扩展中用到。（AES-128只需要10轮）  
unsigned int Rcon[10] = {0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000,   
                 0x20000000, 0x40000000, 0x80000000, 0x1b000000, 0x36000000};  
  
/**********************************************************************/    
/*                                                                    */    
/*                              AES算法实现                           */    
/*                                                                    */    
/**********************************************************************/   
  
/******************************下面是加密的变换函数**********************/  
/*************************************************************************************
    Function:   SubBytes()
    Description:    do transformation with S-box ,S盒变换 - 前4位为行号，后4位为列号
    Input:      a 16 bytes array to  transform 
    Output:     transformed array 
 ************************************************************************************/  
void AES::SubBytes(unsigned char mtx[4*4])  
{  
    for(unsigned int i=0; i<16; ++i)  
    {  
        unsigned int row = (mtx[i]>>4)&0xf;  
        unsigned int col = (mtx[i])&0xf;  
        mtx[i] = S_Box[row][col];  
    }  
}  
  
/********************************************************************************
    Function:   ShiftRows()
    Description:    Shift rows 行变换 - 按字节循环移位 
    Input:      a 16 bytes array to shift
    Output:     shifted array  
 *************************************************************************************/  
void AES::ShiftRows(unsigned char mtx[4*4])  
{  
    // 第二行循环左移一字节  
    unsigned char temp = mtx[4];  
    for(unsigned int i=0; i<3; ++i)  
        mtx[i+4] = mtx[i+5];  
    mtx[7] = temp;  
    // 第三行循环左移两字节  
    for(unsigned int i=0; i<2; ++i)  
    {  
        temp = mtx[i+8];  
        mtx[i+8] = mtx[i+10];  
        mtx[i+10] = temp;  
    }  
    // 第四行循环左移三字节
    temp = mtx[15];  
    for(unsigned int i=3; i>0; --i)  
        mtx[i+12] = mtx[i+11];  
    mtx[12] = temp;  
}  
  
/*********************************************************************************
    Function:       GFMul()
    Description:        the multiple algorithm in GF(2^8) ，有限域上的乘法
    Input:      two byte to multiple
    return:     multiple result
 ********************************************************************************/  
unsigned char AES::GFMul(unsigned char a, unsigned char b) {   
    unsigned char p = 0;  
    unsigned char hi_bit_set;  
    for (unsigned int counter = 0; counter < 8; counter++) {  
        if ((b & (unsigned char)(1)) != 0) {  
            p ^= a;  
        }  
        hi_bit_set = (unsigned char) (a & (unsigned char)(0x80));  
        a <<= 1;  
        if (hi_bit_set != 0) {  
            a ^= 0x1b; /* x^8 + x^4 + x^3 + x + 1 */  
        }  
        b >>= 1;  
    }  
    return p;  
}  
  
/******************************************************************************
    Function:       MixColumns()
    Description:        mixture column,列混淆，与特定数组进行按位异或
    Input：      a 16 bytes array to mix
    Output:     mixed array
********************************************************************************/  
void AES::MixColumns(unsigned char mtx[4*4])  
{  
    unsigned char arr[4];  
    for(unsigned int i=0; i<4; ++i)  
    {  
        for(unsigned int j=0; j<4; ++j)  
            arr[j] = mtx[i+j*4];  
  
        mtx[i] = GFMul(0x02, arr[0]) ^ GFMul(0x03, arr[1]) ^ arr[2] ^ arr[3];  
        mtx[i+4] = arr[0] ^ GFMul(0x02, arr[1]) ^ GFMul(0x03, arr[2]) ^ arr[3];  
        mtx[i+8] = arr[0] ^ arr[1] ^ GFMul(0x02, arr[2]) ^ GFMul(0x03, arr[3]);  
        mtx[i+12] = GFMul(0x03, arr[0]) ^ arr[1] ^ arr[2] ^ GFMul(0x02, arr[3]);  
    }  
}  
  
/*****************************************************************************
    Function:   AddRoundKey()
    Description:    轮密钥加变换 - 将每一列与扩展密钥进行异或  
    Input:      mtx:the initial text array      k:Round Key
    Output:     the array
 *******************************************************************************/  
void AES::AddRoundKey(unsigned char mtx[4*4], unsigned int k[4])  
{  
    for(unsigned int i=0; i<4; ++i)  
    {  
        unsigned int k1 = k[i] >> 24;  
        unsigned int k2 = (k[i] << 8) >> 24;  
        unsigned int k3 = (k[i] << 16) >> 24;  
        unsigned int k4 = (k[i] << 24) >> 24;  
          
        mtx[i] = mtx[i] ^ (unsigned char)k1;  
        mtx[i+4] = mtx[i+4] ^ (unsigned char)k2;  
        mtx[i+8] = mtx[i+8] ^ (unsigned char)k3;  
        mtx[i+12] = mtx[i+12] ^ (unsigned char)k4;  
    }  
}  
  
/**************************下面是解密的逆变换函数***********************/  
/***************************************************************************
    Function:   InvSubBytes()
    Description:    逆S盒变换
  
*****************************************************************************/  
void AES::InvSubBytes(unsigned char mtx[4*4])  
{  
    for(unsigned int i=0; i<16; ++i)  
    {  
        unsigned int row = (mtx[i]>>4)&0xf;  
        unsigned int col = (mtx[i])&0xf;   
        mtx[i] = Inv_S_Box[row][col];  
    }  
}  
  
/************************************************************************* 
    Function:   InvShiftRows()
    Description:      逆行变换 - 以字节为单位循环右移    
 ************************************************************************/  
void AES::InvShiftRows(unsigned char mtx[4*4])  
{  
    // 第二行循环右移一字节  
    unsigned char temp = mtx[7];  
    for(unsigned int i=3; i>0; --i)  
        mtx[i+4] = mtx[i+3];  
    mtx[4] = temp;  
    // 第三行循环右移两字节 
    for(unsigned int i=0; i<2; ++i)  
    {  
        temp = mtx[i+8];  
        mtx[i+8] = mtx[i+10];  
        mtx[i+10] = temp;  
    }  
    // 第四行循环右移三字节 
    temp = mtx[12];  
    for(unsigned int i=0; i<3; ++i)  
        mtx[i+12] = mtx[i+13];  
    mtx[15] = temp;  
}  
/***********************************************************************
    Function:       InvMixColumns()
    Description:         逆列混淆，与特定数据进行按位异或

***********************************************************************/ 
void AES::InvMixColumns(unsigned char mtx[4*4])  
{  
    unsigned char arr[4];  
    for(unsigned int i=0; i<4; ++i)  
    {  
        for(unsigned int j=0; j<4; ++j)  
            arr[j] = mtx[i+j*4];  
  
        mtx[i] = GFMul(0x0e, arr[0]) ^ GFMul(0x0b, arr[1]) ^ GFMul(0x0d, arr[2]) ^ GFMul(0x09, arr[3]);  
        mtx[i+4] = GFMul(0x09, arr[0]) ^ GFMul(0x0e, arr[1]) ^ GFMul(0x0b, arr[2]) ^ GFMul(0x0d, arr[3]);  
        mtx[i+8] = GFMul(0x0d, arr[0]) ^ GFMul(0x09, arr[1]) ^ GFMul(0x0e, arr[2]) ^ GFMul(0x0b, arr[3]);  
        mtx[i+12] = GFMul(0x0b, arr[0]) ^ GFMul(0x0d, arr[1]) ^ GFMul(0x09, arr[2]) ^ GFMul(0x0e, arr[3]);  
    }  
}  
  
/******************************下面是密钥扩展部分***********************/  
/***********************************************************************
    Function:       Word()
    Description:    combine 4 byte tobe one word 
    Retrun :        the word
 ***********************************************************************/  
unsigned int AES::Word(unsigned char &k1, unsigned char &k2, unsigned char &k3, unsigned char &k4)  
{  
    return (unsigned int)k1<<24|(unsigned int )k2<<16|(unsigned int)k3<<8|(unsigned int)k4;  
}  
  
/*********************************************************************
    Function:    Rotword()
    Description:    circle shift left one byte     
    
 ******************************************************************/  
unsigned int AES::Rotword(unsigned int rw)  
{  
    unsigned int high = rw << 8;  
    unsigned int low = rw >> 24;  
    return high | low;  
}  
  
/*******************************************************************
    Function:   Subword()
    Description:      do S-box transformation with each byte of the word sw     
    
 ********************************************************************/  
unsigned int AES::Subword(unsigned int sw)  
{  
    unsigned int row,col;
    unsigned char temp[4];
    col=(sw)&0xf;
    row=(sw>>4)&0xf;  
    temp[0] = S_Box[row][col];
    for(unsigned int i=1; i<4; i++)  
    {  
        row = (sw>>(i*8))&0xf;  
        col = (sw>>(i*8+4))&0xf;  
        temp[i] = S_Box[row][col];   
    }  
    return Word(temp[3],temp[2],temp[1],temp[0]);  
}  
  
/*********************************************************************************************************************
    Function:   KeyExpansion()
    Description:    expand 4 word key(16 bytes) to 44 word ,(one key to 11 keys)  ,对4字密钥进行扩展得到 *w，
                    本程序中Nr=10，总共进行11次轮密钥加，每次需要一个4字（16字节）的轮密钥 
 ******************************************************************************************************************/   
unsigned int AES::KeyExpansion(unsigned char *key, unsigned int *w)  
{  
    unsigned int temp;  
    unsigned int i = 0;  
    // w[]的前4个就是输入的key  
    while(i < Nk)   
    {  
        w[i] = AES::Word(key[4*i], key[4*i+1], key[4*i+2], key[4*i+3]);  
        ++i;  
    }  
  
    i = Nk;  
  
    while(i < 4*(Nr+1))  
    {  
        temp = w[i-1]; // 记录前一个unsigned int  
        if(i % Nk == 0)  
            w[i] = w[i-Nk] ^ AES::Subword(AES::Rotword(temp)) ^ Rcon[i/Nk-1];  
        else   
            w[i] = w[i-Nk] ^ temp;  
        ++i;  
    } 
    return 0; 
}  
void AES::SetAESkey(unsigned char *key)
{
    unsigned char temp[16]= {0x2b, 0x7e, 0x15, 0x16,0x28, 0xae, 0xd2, 0xa6,0xab, 0xf7, 0x15, 0x88,0x09, 0xcf, 0x4f, 0x3c};
    // printf("3333333333333333\n");
    // memset(AESkey,0,sizeof(AESkey));
    memcpy(key,temp,sizeof(temp));
    // printf("444444444444444444\n");

}
// void AES::GetAESkey(char *key)
// {
//     key=AESkey;
// }
// void AES::SetNrNk()
// {
//     Nr=10;
//     Nk=4;
// }



/******************************下面是加密和解密函数**************************/  
/****************************************************************************
    Function:   encrypt()
    Description:    encrypt 16 bytes text
                    加密16字节数据（数组*in）, *w为扩展密钥，返回加密后的数据到*in
    Input:      in:the text to encrypt      w:round key 
 *****************************************************************************/   
void AES::encrypt(unsigned char *in, unsigned int *w)  
{  
    unsigned int key[4];  
    for(unsigned int i=0; i<4; ++i)  
        key[i] = w[i];  
    AES::AddRoundKey(in, key);  
  
    for(unsigned int round=1; round<Nr; ++round)  
    {  
        AES::SubBytes(in);  
        AES::ShiftRows(in);  
        AES::MixColumns(in);  
        for(unsigned int i=0; i<4; ++i)  
            key[i] = w[4*round+i];  
        AES::AddRoundKey(in, key);  
    }  
  
    AES::SubBytes(in);  
    AES::ShiftRows(in);  
    for(unsigned int i=0; i<4; ++i)  
        key[i] = w[4*Nr+i];  
    AES::AddRoundKey(in, key);  
}  
/****************************************************************************
    Function:   decrypt()
    Description:    decrypt 16 bytes text
                    解密16字节数据（数组*in）, *w为扩展密钥，返回解密后的数据到*in
    Input:      in:the text to decrypt      w:round key 
 *****************************************************************************/   
void AES::decrypt(unsigned char *in, unsigned int *w)  
{  
    unsigned int key[4];  
    for(unsigned int i=0; i<4; ++i)  
        key[i] = w[4*Nr+i];  
    AES::AddRoundKey(in, key);  
  
    for(unsigned int round=Nr-1; round>0; --round)  
    {  
        AES::InvShiftRows(in);  
        AES::InvSubBytes(in);  
        for(unsigned int i=0; i<4; ++i)  
            key[i] = w[4*round+i];  
        AES::AddRoundKey(in, key);  
        AES::InvMixColumns(in);  
    }  
  
    AES::InvShiftRows(in);  
    AES::InvSubBytes(in);  
    for(unsigned int i=0; i<4; ++i)  
        key[i] = w[i];  
    AES::AddRoundKey(in, key);  
}
/*********************************************************************************
    Function:   encryptlong()
    Description:     encrypt a long text
    Input:      message:text to encrypt     lenM:bytes of text      w:round key     cArray:store the encrypted text
    Retrun:     the encrypted bytes
 *******************************************************************************/ 
unsigned int AES::encryptlong(unsigned char *message,unsigned int lenM,unsigned int *w,unsigned char *cArray)
{
    unsigned char plain[16]={'\0'};
    unsigned int size,numPlain,i,j;
    unsigned int offset=lenM%16;
    if (0!=offset)
    {

        numPlain=lenM/16 ;
        for(i=0;i<numPlain;i++)
        {
                memset(plain,0,sizeof(plain));
                for(j=0;j<16;j++)
                {
                        plain[j]=message[i*16+j];
                }
                AES::encrypt(plain, w);
                for(j=0;j<16;j++)
                {
                        cArray[i*16+j]=plain[j];
                }
                memset(plain,'\0',sizeof(plain));

        }
        for(j=0;j<15;j++)
        {
            if(j<offset)
                plain[j]=message[i*16+j];
            else
                plain[j]=0x00;

        }
        plain[j]=lenM;
        AES::encrypt(plain, w);
        for(j=0;j<16;j++)
        {
                cArray[i*16+j]=plain[j];
        }
        memset(plain,'\0',sizeof(plain));
        
        size=(numPlain+1)*16;


    }
    else
    {
        numPlain=lenM/16;
        for(i=0;i<numPlain;i++)
        {
                memset(plain,0,sizeof(plain));
                for(j=0;j<16;j++)
                {
                        plain[j]=message[i*16+j];
                }
                AES::encrypt(plain, w);
                for(j=0;j<16;j++)
                {
                        cArray[i*16+j]=plain[j];
                }

        }
        size=numPlain*16;
    }
    return size;
} 
/*********************************************************************************
    Function:   decryptlong()
    Description:     decrypt a long text
    Input:      message:text to decrypt     lenC:bytes of text      w:round key     cArray:store the decrypted text
    Retrun:     the decrypted bytes
 *******************************************************************************/ 
unsigned int AES::decryptlong(unsigned char *encryptedMsg,unsigned int lenC,unsigned int *w,unsigned char *mArray)
{
    unsigned char plain[16];
    unsigned int size,numPlain,i,j;
    if (0!=lenC%16)
    {
        numPlain=lenC/16 + 1;
        for(i=0;i<numPlain;i++)
        {
                memset(plain,0,sizeof(plain));
                for(j=0;j<16;j++)
                {
                        plain[j]=encryptedMsg[i*16+j];
                }
                AES::decrypt(plain, w);
                for(j=0;j<16;j++)
                {
                        mArray[i*16+j]=plain[j];
                }

        }
        size=numPlain*16-lenC%16;

    }
    else
    {
        numPlain=lenC/16;
        for(i=0;i<numPlain;i++)
        {
                memset(plain,0,sizeof(plain));
                for(j=0;j<16;j++)
                {
                        plain[j]=encryptedMsg[i*16+j];
                }
                AES::decrypt(plain, w);
                for(j=0;j<16;j++)
                {
                        mArray[i*16+j]=plain[j];
                }

        }
        size=numPlain*16;
    }
    return size;
}
  
/******************************************************************************
    Description:    get 100 random Number between 0~255 as message to eb encrypted
    Attention:      used for test
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
    Description:    compare two Array
    Return:     1:the same      0:not the same
    Attention:      used for test
*******************************************************************************/
unsigned int cmp(unsigned char *buf1,unsigned char *buf2,unsigned int len)
{
    for(unsigned int i=0;i<len;i++)
    {
        if(buf1[i]!=buf2[i])
        {
            return 0;
            break;
        }
    }
    return 1;
}

/**********************************************************************/    
/*                                                                    */    
/*                              测试                                  */    
/*                                                                    */    
/**********************************************************************/
#if 0
int main()  
{  
    AES aes;
    unsigned int j,i;
    clock_t enstart, enfinish;
    clock_t destart, definish;
    unsigned char key[16] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};//cipher key  
    unsigned char codeMsg[8096]={0};//存放加密后的数据 
    unsigned char initMsg[8096]={0};// 存放解密后的数据
     
    //unsigned char message[]="0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789";
    unsigned char message[2048]={0};
    unsigned int MsgNum=ranMsg(message);
    // 输出密钥  
    cout << "the cipher key is:";  
    for(unsigned int i=0; i<16; ++i)  
        printf("%x ",key[i] );  
    cout << endl;  
  
    unsigned int w[4*Nr+1];  
    aes.KeyExpansion(key, w);  
  
    // 输出待加密的明文  
    cout << endl << "the word to be encrypted :"<<endl;  
    for(unsigned int i=0; i<MsgNum; ++i)  
    {  
        printf("%x ",message[i] ); 
        //if((i+1)%4 == 0)  
            //cout << endl;  
    }  
    cout << endl;  
    //for(int i=0;i<100;i++)//test 100 times
    //{
    // 加密，输出密文
    enstart=clock();
    aes.encryptlong(message,MsgNum,w,codeMsg);
    enfinish=clock();
    cout<<"encryptT:"<<dec<<enfinish - enstart<<endl;
    #if 0
    cout << "the encrypted word:"<<endl;  
    for(unsigned int i=0; i<lenM; ++i)  
    {  
        printf("%02x",codeMsg[i] );  
        //if((i+1)%4 == 0)  
            //cout << endl;  
    }  
    cout << endl;  
    #endif
    // 解密，输出明文
    destart=clock();
    aes.decryptlong(codeMsg,MsgNum,w,initMsg);
    definish=clock();
    cout<<"decryptT:"<<dec<<definish- destart<<endl;
    cout << "the decrypted word:"<<endl;  
    for(unsigned int i=0; i<MsgNum; ++i)  
    {  
        printf("%x ",initMsg[i]);
        //cout << initMsg[i].to_string();   
    }  
    cout << endl; 
    printf("cmp:%u\n",cmp(message,initMsg,MsgNum) ); 
    //}
    return 0;  
}
#endif