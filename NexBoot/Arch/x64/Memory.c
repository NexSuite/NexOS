/*
    Memory.c - contains  memory manager
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#include <Nexboot.h>
#include <Multiboot.h>

VOID* base = (VOID*)0x0000000000001000;

void* NbAllocBlock()
{
    VOID* ret = base;
    base += 4096;
    return (VOID*)ret;
}

