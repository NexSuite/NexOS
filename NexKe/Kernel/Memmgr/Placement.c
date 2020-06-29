/*
    Placement.c - contains Initial placement allocator
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#include <Kernel/Kernel.h>
#include <Kernel/Runtime.h>
#include <Kernel/System.h>

VIRTUALADDR start = (VIRTUALADDR)PLACEMENT_START;

VOID* KePlacementAlloc(DWORD size)
{
    VOID* ret = (VOID*)start;
    start += size;
    return ret;
}
