/*
    BootDrv.h - contains Boot Driver functions
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#ifndef _BOOTDRV_H
#define _BOOTDRV_H

#include <nexdef.h>

VOID BootDrvSerialWriteChar(CHAR c);
VOID BootDrvSerialWriteString(PSTR s);

#endif
