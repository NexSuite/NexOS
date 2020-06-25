/*
    Idt.c - contains IDT functions
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#include <Kernel/Kernel.h>
#include <Kernel/Runtime.h>
#include <Hal.h>
#include <Kernel/System.h>
#include "Include/Idt.h"

IDTGATE idt[256];
IDTPTR iptr;
extern VOID HalIdtFlush();

__attribute__((naked)) VOID HalDefHandler()
{
    KePanic("Unhandled Interrupt");
    asm("cli; hlt");
}

VOID HalIdtInit()
{
    iptr.limit = (sizeof(IDTGATE) * 256) - 1;
    iptr.base = (DWORD)&idt;
    RtlZeroMemory(&idt, 256 * sizeof(IDTGATE));
    for(int i = 0; i < 256; i++)
    {
        HalIdtSetGate(i, (DWORD)HalDefHandler, 0x08, 0x8E);
    }
    HalIsrInstall();
    HalIdtFlush();
}

VOID HalIdtSetGate(BYTE num, DWORD base, WORD sel, BYTE flags)
{
    idt[num].baseLow = (base & 0xFFFF);
    idt[num].baseHigh = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

