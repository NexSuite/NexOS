/*
    Hal.h - contains HAL internal functions
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#ifndef _HAL_H
#define _HAL_H

#include <nexdef.h>

INT HalCpuInit();
VOID HalGdtInit();
VOID HalIdtInit();

#endif
