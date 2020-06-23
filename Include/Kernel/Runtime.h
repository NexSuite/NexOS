/*
    Runtime.h - contains kernel runtime definitions
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#ifndef _RUNTIME_H
#define _RUNTIME_H

#include <nexdef.h>

INT RtlStrLen(PSTR str);
VOID RtlIntToStr(UINT i, PSTR str, INT base);
VOID RtlLongToStr(ULONGLONG i, PSTR str, INT base);
VOID RtlLongToStrSigned(LONGLONG i, PSTR str, INT base);
VOID RtlIntToStrSigned(INT i, PSTR str, INT base);
VOID* RtlCopyMemory(VOID* dest, VOID* src, DWORD count);
VOID RtlZeroMemory(VOID* block, DWORD count);
INT RtlCmpStr(PSTR str1, PSTR str2);
VOID RtlDebug(PSTR s);

#endif
