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
    DWORD base;
}__attribute__((packed)) IDTPTR;

typedef struct tagIDTGATE
{
    WORD baseLow;
    WORD sel;
    BYTE always0;
    BYTE flags;
    WORD baseHigh;
}__attribute__((packed)) IDTGATE;

VOID HalIdtSetGate(BYTE num, DWORD base, WORD sel, BYTE flags);

#endif
