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
    gdtptr.base = (DWORD)&gdt;
    HalGdtSetEntry(0, 0, 0, 0, 0);
    HalGdtSetEntry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    HalGdtSetEntry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    HalGdtFlush();
}

VOID HalGdtSetEntry(INT num, DWORD base, DWORD limit, BYTE access, BYTE gran)
{
    gdt[num].baseLow = (base & 0xFFFF);
    gdt[num].baseMid = (base >> 16) & 0xFF;
    gdt[num].baseHigh = (base >> 24) & 0xFF;
    gdt[num].limitLow = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}


