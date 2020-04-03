
#ifndef _CODE_FORMAT_CONVERT_H_
#define  _CODE_FORMAT_CONVERT_H_
#include "const.h"

int convert(unsigned char *dst, const unsigned char *src, int length);
unsigned long HextoDec(const unsigned char *hex, int length);
int DectoHex(int dec, unsigned char *hex, int length);
unsigned long power(int base, int times);
unsigned long  BCDtoDec(const unsigned char *bcd, int length);
int DectoBCD(int Dec, unsigned char *Bcd, int length);
char BCD2Hex(char a);
void HexToStr(UINT8 *pbDest, UINT8 *pbSrc, int nLen);
void StrToHex(UINT8 *pbDest, UINT8 *pbSrc, int nLen);
char ConvertHexChar(char ch);

#endif // _CODE_FORMAT_CONVERT_H_