/*
    Hal.c - contains Hal intialization
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#include <Hal.h>
#include <Kernel/Kernel.h>
#include <Kernel/BootDrv.h>
#include <Kernel/Runtime.h>

INT HalInit(NEXBOOTINFO* bootinfo)
{
    if(!HalCpuInit())
        return 0;
    return 1;
}
