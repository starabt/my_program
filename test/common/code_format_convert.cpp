/*******************************************************************************
**  (C) COPYRIGHT 2016 Haitu Tech CO.LTD
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.01.17
**  description  :在做嵌入式软件的设计中，经常会遇到十六进制、BCD码与十进制之间的转换
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "code_format_convert.h"

/*************************************************
    Function:       convert()
    Description:    二进制取反
    输入：const unsigned char *src  二进制数据
         int length                待转换的二进制数据长度
    输出：unsigned char *dst        取反后的二进制数据
    返回：0    success
*************************************************/
int convert(unsigned char *dst, const unsigned char *src, int length)
{
  int i;
  for(i=0;i<length;i++)
  {
    dst[i] = src[i]^0xFF;
  }
  return 0;
}

/*************************************************
    Function:       HextoDec()
    Description:    十六进制转为十进制
    输入：const unsigned char *hex         待转换的十六进制数据
         int length                       十六进制数据长度
    返回：int  rslt                        转换后的十进制数据
    思路：十六进制每个字符位所表示的十进制数的范围是0 ~255，进制为256
         左移8位(<<8)等价乘以256
*************************************************/
unsigned long HextoDec(const unsigned char *hex, int length)
{
  int i;
  unsigned long rslt = 0;
  for(i=0; i<length;i++)
  {
      rslt += (unsigned long)(hex[i])<<(8*(length-1-i));
  }
  return rslt;
}

/*************************************************
    Function:       DectoHex()
    Description:    十进制转十六进制
    输入：int dec                     待转换的十进制数据
         int length                  转换后的十六进制数据长度
    输出：unsigned char *hex          转换后的十六进制数据
    返回：0    success
    思路：原理同十六进制转十进制
*************************************************/
int DectoHex(int dec, unsigned char *hex, int length)
{
  int i;
  for(i=length-1; i>=0; i--)
  {
    hex[i] = (dec%256)&0xFF;
    dec /= 256;
  }
  return 0;
}

/*************************************************
    Function:      power()
    Description:    求权
    输入：int base                    进制基数
         int times                   权级数
    输出：
    返回：unsigned long               当前数据位的权
    思路：原理同十六进制转十进制
*************************************************/
unsigned long power(int base, int times)
{
  int i;
  unsigned long rslt = 1;
  for(i=0;i<times;i++)
    rslt *= base;
  return rslt;
}

/*************************************************
    Function:      BCDtoDec()
    Description:    BCD转10进制
    输入：const unsigned char *bcd     待转换的BCD码
         int length                   BCD码数据长度
    输出：
    返回：unsigned long   dec            十进制值
    思路：压缩BCD码一个字符所表示的十进制数据范围为0 ~ 99,进制为100
         先求每个字符所表示的十进制值，然后乘以权
*************************************************/
unsigned long  BCDtoDec(const unsigned char *bcd, int length)
{
  int i, tmp;
  unsigned long dec = 0;
  for(i=0; i<length;i++)
  {
    tmp = ((bcd[i]>>4)&0x0F)*10 + (bcd[i]&0x0F);  
    dec += tmp * power(100, length-1-i);         
  }
  return dec;
}


// //BCD转十进制 
// unsigned char BCD2Dec(unsigned char bcd)
// {
//     return bcd-(bcd >> 4)*6;
// }

/*************************************************
    Function:      DectoBCD()
    Description:    十进制转BCD码
    输入：int Dec                      待转换的十进制数据
         int length                   BCD码数据长度
    输出：unsigned char *Bcd           转换后的BCD码
    返回：0  success
    思路：原理同BCD码转十进制
*************************************************/
int DectoBCD(int Dec, unsigned char *Bcd, int length)
{
  int i;
  int temp;
  for(i=length-1; i>=0; i--)
  {
    temp = Dec%100;
    Bcd[i] = ((temp/10)<<4) + ((temp%10) & 0x0F);
    Dec /= 100;
  }
  return 0;
}

//BCD转十六进制    
char BCD2Hex(char a)   
{   
    unsigned char t_h,t_l;   
       
    t_h = (a&0xf0)>>4;   
    t_l = a&0x0f;   
       
    a = t_h*10 + t_l;   
       
    return(a);   
} 

/*************************************************
    Function:      HexToStr
    Description:   十六进制转字符串 
*************************************************/
void HexToStr(UINT8 *pbDest, UINT8 *pbSrc, int nLen)
{
    char ddl,ddh;
    int i=0;
    for(i=0;i<nLen;i++)
    {
        ddh = 48+pbSrc[i]/16;
        ddl = 48+pbSrc[i]%16;
        if(ddh>57)
            ddh =ddh+7;
        if(ddl>57)
            ddl=ddl+7;
        pbDest[i*2]=ddh;
        pbDest[i*2+1]=ddl;
    }
    pbDest[nLen*2]='\0';
    return;
}

/**************************************************************************** 
函数名称: hex_to_str 
函数功能: 十六进制转字符串 
输入参数: ptr 字符串 buf 十六进制 len 十六进制字符串的长度。 
输出参数: 无 
*****************************************************************************/   
// void hex_to_str(char *ptr,char *buf,int len)  
// {  
//     int i = 0;
//     for(i = 0; i < len; i++)  
//     {  
//         sprintf(ptr, "%02x",buf[i]);  
//         ptr += 2;  
//     }  
// } 

/*************************************************
    Function:      StrToHex()
    Description:    将字符串转化为16进制数
    输入：pbSrc - 字符串
         nLen - 16进制数的字节数(字符串的长度/2)
    输出：pbDest - 输出缓冲区
    返回：
    思路：
*************************************************/
void StrToHex(UINT8 *pbDest, UINT8 *pbSrc, int nLen)
{
    char h1,h2;
    UINT8 s1,s2;
    int i;
    for (i=0; i<nLen; i++)
    {
      h1 = pbSrc[2*i];
      h2 = pbSrc[2*i+1];
      s1 = toupper(h1) - 0x30;
      if (s1 > 9) 
      s1 -= 7;
      s2 = toupper(h2) - 0x30;
      if (s2 > 9) 
      s2 -= 7;
      pbDest[i] = s1*16 + s2;
    }
}
  
/*************************************************
    Function:      ConvertHexChar()
    Description:   这是一个将字符转换为相应的十六进制值的函数
    若是在0-F之间的字符，则转换为相应的十六进制字符，否则返回-1 
*************************************************/
char ConvertHexChar(char   ch)     
{   
  if((ch>='0')&&(ch<='9'))   
    return   ch-0x30;   
  else   if((ch>='A')&&(ch<='F'))   
    return   ch-'A'+10;   
  else   if((ch>='a')&&(ch<='f'))   
    return   ch-'a'+10;   
  else   
    return   (-1);   
}