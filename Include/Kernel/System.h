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

#if defined(ARCH_X86)
typedef struct tagREGS
{
    DWORD edi, esi, ebp, unused, ebx, edx, ecx, eax;
    DWORD intNo, errCode;
    DWORD eip, cs, eflags, esp, ss;
}REGS;
#else
typedef struct tagREGS
{
    QWORD r15, r14, r13, r12, r11, r10, r9, r8;
    QWORD rbp, rdi, rsi, rdx, rcx, rbx, rax;
    DWORD errCode, intNo;
    QWORD rip, cs, rflags, rsp, ss;
}REGS;
#endif

#endif
