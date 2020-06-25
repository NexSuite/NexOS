/*
    System.h - contains HAL functions
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#ifndef _SYSTEM_H
#define _SYSTEM_H

INT HalInit(NEXBOOTINFO* bootinfo);
VOID HalOutWord(WORD port, WORD val);
WORD HalInWord(WORD port);
BYTE HalInByte(WORD port);
VOID HalOutByte(WORD port, BYTE val);
VOID HalCpuid(INT code, DWORD* a, DWORD* d);
VOID HalWriteMsr(DWORD msr, QWORD val);
QWORD HalReadMsr(DWORD msr);

#endif
