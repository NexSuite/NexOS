/*
    Nexboot.h - contains functions for Nexboot
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#ifndef _NEXBOOT_H
#define _NEXBOOT_H

#include <nexdef.h>
#include <Multiboot.h>

INT NbStrLen(PSTR str);
VOID NbIntToStr(UINT i, PSTR str, INT base);
VOID NbIntToStrSigned(INT i, PSTR str, INT base);
VOID* NbCopyMemory(VOID* dest, VOID* src, DWORD count);
INT NbCmpStr(PSTR str1, PSTR str2);
VOID NbSerialInit();
VOID NbSerialWriteChar(CHAR c);
VOID NbSerialWriteString(PSTR s);
VOID NbDebug(PSTR s);
BYTE NbInByte(WORD port);
VOID NbOutByte(WORD port, BYTE val);
void NbInitAllocator(MULTIBOOT_INFO* bootinfo);
void NbFreeBlocks(void* p, int num);
void* NbAllocBlocks(int num);
void* NbAllocBlock();
void NbFreeBlock(void* p);

#endif
