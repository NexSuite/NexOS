/*
    Serial.c - contains Serial port driver
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#include <Kernel/Kernel.h>
#include <Kernel/Runtime.h>
#include <Kernel/System.h>

#define SERIAL_BASE 0x3F8

VOID BootDrvSerialWriteChar(CHAR c)
{
    while(!(HalInByte(SERIAL_BASE + 5) & 0x20));
    HalOutByte(SERIAL_BASE, (BYTE)c);
}

VOID BootDrvSerialWriteString(PSTR s)
{
    for(int i = 0; i < RtlStrLen(s); i++)
        BootDrvSerialWriteChar(s[i]);
}

VOID RtlDebug(PSTR s)
{
    BootDrvSerialWriteString(s);
}
