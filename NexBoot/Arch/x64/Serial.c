/*
    Serial.c - contains Serial port driver
    Distributed with NexOS, licensed uner the GPL v3.0
    See LICENSE
*/

#include <Nexboot.h>

#define SERIAL_BASE 0x3F8

BYTE NbInByte(WORD port)
{
    BYTE ret;
    asm volatile ( "inb %1, %0"
         : "=a"(ret)
         : "Nd"(port) );
    return ret;
}
VOID NbOutByte(WORD port, BYTE val)
{
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

VOID NbSerialInit()
{
    NbOutByte(SERIAL_BASE + 1, 0x00);
    NbOutByte(SERIAL_BASE + 3, 0x80);
    NbOutByte(SERIAL_BASE + 0, 0x03);
    NbOutByte(SERIAL_BASE + 1, 0x00);
    NbOutByte(SERIAL_BASE + 3, 0x03);
    NbOutByte(SERIAL_BASE + 2, 0xC7);
    NbOutByte(SERIAL_BASE + 4, 0x0B);
    NbOutByte(SERIAL_BASE + 1, 0x80);
}

VOID NbSerialWriteChar(CHAR c)
{
    while(!(NbInByte(SERIAL_BASE + 5) & 0x20));
    NbOutByte(SERIAL_BASE, (BYTE)c);
}

VOID NbSerialWriteString(PSTR s)
{
    for(int i = 0; i < NbStrLen(s); i++)
        NbSerialWriteChar(s[i]);
}

VOID NbDebug(PSTR s)
{
    NbSerialWriteString(s);
}
