/*
    Serial.c - contains Serial port driver
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#include <Kernel/Runtime.h>

#define SERIAL_BASE 0x3F8

// Will be moved to HAL

BYTE HalInByte(WORD port)
{
    BYTE ret;
    asm volatile ( "inb %1, %0"
         : "=a"(ret)
         : "Nd"(port) );
    return ret;
}
VOID HalOutByte(WORD port, BYTE val)
{
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

VOID BootDrvSerialInit()
{
    HalOutByte(SERIAL_BASE + 1, 0x00);
    HalOutByte(SERIAL_BASE + 3, 0x80);
    HalOutByte(SERIAL_BASE + 0, 0x03);
    HalOutByte(SERIAL_BASE + 1, 0x00);
    HalOutByte(SERIAL_BASE + 3, 0x03);
    HalOutByte(SERIAL_BASE + 2, 0xC7);
    HalOutByte(SERIAL_BASE + 4, 0x0B);
    HalOutByte(SERIAL_BASE + 1, 0x80);
}

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
