/*
    NexBoot.c - contains C entry point for NexBoot
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#include <Nexboot.h>
#include <Multiboot.h>

// C entry point

VOID NbEntry(DWORD magic, MULTIBOOT_INFO* bootinfo)
{
    if(magic != MULTIBOOT_BOOTLOADER_MAGIC)
        asm("int $0x19");                   // Restart computer by triple faulting
    NbSerialInit();
    NbInitAllocator(bootinfo);
    if(!NbPagingInit())
    {
        NbDebug("Not enough memory!\r\n");
        asm("int $0x19");
    }
    if(!NbKernelExec(bootinfo))
    {
        NbDebug("Not enough memory!\r\n");
        asm("int $0x19");
    }
    for(;;);
}
