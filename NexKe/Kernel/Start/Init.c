/*
    Init.c - contains kernel initialization functions
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#include <Kernel/Kernel.h>
#include <Kernel/BootDrv.h>
#include <Kernel/BootDrv.h>
#include <Kernel/System.h>

INT KeInit(NEXBOOTINFO* bootinfo)
{
    if(!HalInit(bootinfo))
        return 0;
    return 1;
}
