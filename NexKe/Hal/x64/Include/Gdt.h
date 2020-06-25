/*
    Gdt.h - contains GDT structures
    Distributed with NexOS, licensed uder the AGPL v3.0
    See LICENSE
*/

#ifndef _GDT_H
#define _GDT_H

#include <nexdef.h>

typedef struct tagGDTENTRY
{
    WORD limit_low;
    WORD base_low;
    BYTE base_mid;
    BYTE access;
    BYTE granularity;
    BYTE base_high;
}__attribute__((packed)) GDTENTRY;

typedef struct tagGDTPTR
{
    WORD limit;
    QWORD base;
}__attribute__((packed)) GDTPTR;

#define MAX_DESCRIPTORS 3

VOID HalGdtSetEntry(INT num, DWORD base, DWORD limit, BYTE access, BYTE gran);

#endif
