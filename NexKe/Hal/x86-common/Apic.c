/*
    Apic.c - contains APIC funcions
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#include <Kernel/Kernel.h>
#include <Kernel/Runtime.h>
#include <Kernel/System.h>
#include <Kernel/BootDrv.h>
#include <Hal.h>
#include "Include/Apic.h"

volatile IOAPIC* ioapic;

INT HalCheckApic()
{
    DWORD eax, edx;
    HalCpuid(CPUID_GETFEATURES, &eax, &edx);
    return edx & CPUID_FEAT_EDX_APIC;
}

VOID HalIoapicWrite(DWORD reg, DWORD val)
{
    ioapic->reg = reg;
    ioapic->val = val;
}

DWORD HalIoapicRead(DWORD reg)
{
    ioapic->reg = reg;
    return ioapic->val;
}

INT HalInitApic()
{
    HalOutByte(0x20, 0x11);
    HalOutByte(0xA0, 0x11);
    HalOutByte(0x21, 0x20);
    HalOutByte(0xA1, 0x28);
    HalOutByte(0x21, 0x04);
    HalOutByte(0xA1, 0x02);
    HalOutByte(0x21, 0x01);
    HalOutByte(0xA1, 0x01);
    HalOutByte(0x21, 0x0);
    HalOutByte(0xA1, 0x0);
}
