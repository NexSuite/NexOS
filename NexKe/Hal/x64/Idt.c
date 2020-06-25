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
    iptr.base = (QWORD)&idt;
    RtlZeroMemory(&idt, 256 * sizeof(IDTGATE));
    for(int i = 0; i < 256; i++)
    {
        HalIdtSetGate(i, (QWORD)HalDefHandler, 0x08, 0x8E, 0);
    }
    HalIdtFlush();
}

VOID HalIdtSetGate(BYTE num, QWORD base, WORD sel, BYTE flags, BYTE ist)
{
    idt[num].baseHigh = (base >> 32);
    idt[num].baseMid = (base >> 16) & 0xFFFF;
    idt[num].baseLow = base & 0xFFFF;
    idt[num].sel = sel;
    idt[num].ist = ist & 0x7;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

