/*
    Runtime.c - contains NexBoot basic runtime
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#include <nexdef.h>

INT NbStrLen(PSTR str)
{
    INT len = 0;
    while(str[len])
        len++;
    return len;
}

CHAR buf[32];
CHAR bchars[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

// This function converts an integer into a string
VOID NbIntToStr(UINT i, PSTR str, INT base)
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

VOID NbLongToStr(ULONGLONG i, PSTR str, INT base)
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

VOID NbLongToStrSigned(LONGLONG i, PSTR str, INT base)
{
    if(base > 16)
        return;
    if(i < 0)
    {
        *str++ = '-';
        i *= -1;
    }
    NbIntToStr(i, str, base);
}

VOID NbIntToStrSigned(INT i, PSTR str, INT base)
{
    if(base > 16)
        return;
    if(i < 0)
    {
        *str++ = '-';
        i *= -1;
    }
    NbIntToStr(i, str, base);
}

VOID* NbCopyMemory(VOID* dest, VOID* src, DWORD count)
{
	const char* sp = (const char*)src;
	char* dp = (char*)dest;
	for (; count != 0; count--) *dp++ = *sp++;
	return dest;
}

VOID NbZeroMemory(VOID* block, DWORD count)
{
    unsigned char* temp = (unsigned char*)block;
	for (; count != 0; count--, temp[count] = 0);
}

INT NbCmpStr(PSTR str1, PSTR str2)
{
    INT res = 0;
    while (!(res = *(UCHAR*)str1 - *(UCHAR*)str2) && *str2)
        ++str1, ++str2;

    if (res < 0)
        res = -1;
    if (res > 0)
        res = 1;

    return res;
}
