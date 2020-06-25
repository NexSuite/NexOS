/*
    Cpu.c - contains basic CPU functions
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#include <Hal.h>
#include <Kernel/Kernel.h>
#include <Kernel/BootDrv.h>
#include <Kernel/Runtime.h>
#include <Kernel/System.h>

INT HalCpuInit()
{
    HalGdtInit();
    HalIdtInit();
    HalInitApic();
    return 1;
}

QWORD HalReadMsr(DWORD msr)
{
    QWORD msrValue;
    asm volatile("rdmsr" : "=A" (msrValue) : "c" (msr));
    return msrValue;
}

VOID HalWriteMsr(DWORD msr, QWORD val)
{
    asm volatile("wrmsr" : : "c" (msr), "A" (val));
}

VOID HalCpuid(INT code, DWORD* a, DWORD* d)
{
    asm volatile("cpuid" : "=a"(*a), "=d"(*d) : "0"(code) : "ebx", "ecx");
}

VOID HalOutByte(WORD port, BYTE val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

BYTE HalInByte(WORD port)
{
    BYTE ret;
    asm volatile ( "inb %1, %0"
                 : "=a"(ret)
                 : "Nd"(port) );
    return ret;
}

VOID HalOutWord(WORD port, WORD val)
{
    asm volatile ( "outw %0, %1" : : "a"(val), "Nd"(port) );
}

WORD HalInWord(WORD port)
{
    WORD ret;
    asm volatile ( "inw %1, %0"
                 : "=a"(ret)
                 : "Nd"(port) );
    return ret;
}
