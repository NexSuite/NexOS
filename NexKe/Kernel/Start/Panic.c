/*
    Panic.c - contains kernel panicing routine
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#include <Kernel/Kernel.h>
#include <Kernel/BootDrv.h>
#include <Kernel/Runtime.h>

VOID KePanic(PSTR s)
{
    BootDrvSerialWriteString("KERNEL PANIC: ");
    BootDrvSerialWriteString(s);
    asm("cli; hlt");
}
