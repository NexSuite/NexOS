/*
    String.c - contains kernel string routines
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#include <Kernel/Runtime.h>

INT RtlStrLen(PSTR str)
{
    INT len = 0;
    while(str[len])
        len++;
    return len;
}

CHAR buf[32];
CHAR bchars[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

// This function converts an integer into a string
VOID RtlIntToStr(UINT i, PSTR str, INT base)
{
    int pos = 0;
    int opos = 0;
    int top = 0;
    if(i == 0 || base > 16)
    {
        str[0] = '0';
        str[1] = '\0';
        return;
    }
    while (i != 0)
    {
        buf[pos] = bchars[i % base];
        pos++;
        i /= base;
    }
    top = pos--;

    for (opos = 0; opos < top; pos--, opos++) 
    {
        str[opos] = buf[pos];
    }
    str[opos] = 0;
}

VOID RtlLongToStr(ULONGLONG i, PSTR str, INT base)
{
    int pos = 0;
    int opos = 0;
    int top = 0;
    if(i == 0 || base > 16)
    {
        str[0] = '0';
        str[1] = '\0';
        return;
    }
    while (i != 0)
    {
        buf[pos] = bchars[i % base];
        pos++;
        i /= base;
    }
    top = pos--;

    for (opos = 0; opos < top; pos--, opos++) 
    {
        str[opos] = buf[pos];
    }
    str[opos] = 0;
}

VOID RtlLongToStrSigned(LONGLONG i, PSTR str, INT base)
{
    if(base > 16)
        return;
    if(i < 0)
    {
        *str++ = '-';
        i *= -1;
    }
    RtlIntToStr(i, str, base);
}

VOID RtlIntToStrSigned(INT i, PSTR str, INT base)
{
    if(base > 16)
        return;
    if(i < 0)
    {
        *str++ = '-';
        i *= -1;
    }
    RtlIntToStr(i, str, base);
}

INT RtlCmpStr(PSTR str1, PSTR str2)
{
    INT i = 0;
    while(str1[i] != '\0' || str2[i] != '\0')
    {
        if(str1[i] != str2[i])
            return 0;
    }
    return 1;
}

PSTR RtlStrCpy(PSTR dest, PSTR src)
{
    char* temp = dest;
    while(*dest++ = *src++);
    return temp;
}

PSTR RtlStrCat(PSTR dest, PSTR src)
{
	 char* ptr = dest + RtlStrLen(dest);
	 while (*src != '\0')
		*ptr++ = *src++;

	*ptr = '\0';
	return dest;
}
