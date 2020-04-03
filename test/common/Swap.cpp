/*
Ìí¼ÓÈÕÆÚ£º2017-02-28
¹¦ÄÜËµÃ÷£º´óÐ¡¶Ë×ª»»º¯Êý
*/
#include <stdio.h>
#include "Swap.h"
ushort Swap16(unsigned short n)
{
    unsigned short m = ((n&0xff)<<8)|((n&0xff00)>>8);
    return m;
}

uint Swap32(uint n)
{
    uint m = ((n&0xff)<<24)| ((n&0xff00)<<8)|((n&0xff0000)>>8) |((n&0xff000000)>>24);
    return m;
}
