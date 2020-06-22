/*
    NexBoot.c - contains C entry point for NexBoot
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#include <Nexboot.h>
#include "Include/Multiboot.h"

// C entry point

VOID NbEntry(DWORD magic, MULTIBOOT_INFO* bootinfo)
{
    NbSerialInit();
    NbDebug("Serial test\r\n");
    for(;;);
}
