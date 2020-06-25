/*
    Gdt.c - contains GDT implementation
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#include <Kernel/Kernel.h>
#include <Kernel/Runtime.h>
#include <Hal.h>
#include <Kernel/System.h>
#include "Include/Gdt.h"

GDTENTRY gdt[MAX_DESCRIPTORS];
GDTPTR gdtptr;
extern VOID HalGdtFlush();

VOID HalGdtInit()
{
    gdtptr.limit = (sizeof(GDTENTRY) * MAX_DESCRIPTORS) - 1;
    gdtptr.base = (QWORD)&gdt;
    HalGdtSetEntry(0, 0, 0, 0, 0);
    HalGdtSetEntry(1, 0, 0xFFFFFFFF, 0x9A, 0x20);
    HalGdtSetEntry(2, 0, 0xFFFFFFFF, 0x92, 0x00);
    HalGdtFlush();
}

VOID HalGdtSetEntry(INT num, DWORD base, DWORD limit, BYTE access, BYTE gran)
{
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_mid = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}


