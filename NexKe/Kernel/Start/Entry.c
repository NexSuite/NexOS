/*
    Entry.c - contains kernel entry point
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#include <Kernel/Runtime.h>
#include <Kernel/Kernel.h>
#include <Kernel/BootDrv.h>

VOID KeEntry(NEXBOOTINFO* bootinfo)
{
    RtlDebug("Kernel starting...\r\n");

    if(!KeInit(bootinfo))
    {
        RtlDebug("System initialization failed!\r\n");
        asm("int $0x19");
    }
    RtlDebug("Kernel started.\r\n");
    for(;;);
}
