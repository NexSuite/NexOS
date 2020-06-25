/*
    Idt.h - contains IDT structures
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#ifndef _IDT_H
#define _IDT_H

#include <nexdef.h>

typedef struct tagIDTPTR
{
    WORD limit;
    QWORD base;
}__attribute__((packed)) IDTPTR;

typedef struct tagIDTGATE
{
    WORD baseLow;
    WORD sel;
    BYTE ist;
    BYTE flags;
    WORD baseMid;
    DWORD baseHigh;
    DWORD always0;
}__attribute__((packed)) IDTGATE;

VOID HalIdtSetGate(BYTE num, QWORD base, WORD sel, BYTE flags, BYTE ist);

#endif
