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
    asm("div %0" : : "r"(0));
    return 1;
}

QWORD HalReadMsr(DWORD msr)
{
    DWORD low, high;
	asm volatile (
		"rdmsr"
		: "=a"(low), "=d"(high)
		: "c"(msr)
	);
	return ((QWORD)high << 32) | low;
}

VOID HalWriteMsr(DWORD msr, QWORD val)
{
    DWORD low = val & 0xFFFFFFFF;
	DWORD high = val >> 32;
	asm volatile (
		"wrmsr"
		:
		: "c"(msr), "a"(low), "d"(high)
	);
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
