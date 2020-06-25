/*
    Apic.h - contains defintiond for the APIC controller
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/


#ifndef _APIC_H
#define _APIC_H

#define IOBASE 0xFEC00000
#define REGID 0x00
#define REGVER 0x01
#define REGTABLE 0x10

#define INTDISABLED 0x00010000
#define INTLEVELTRIGGER 0x00008000
#define INTACTIVELOW 0x00002000
#define INTLOGICAL 0x00000800

typedef struct tagIOAPIC
{
    DWORD reg;
    DWORD pad[2];
    DWORD val;
}IOAPIC;

VOID HalIoapicWrite(DWORD reg, DWORD val);
DWORD HalIoapicRead(DWORD reg);
VOID HalIoapicEnableInt(INT intNo, INT cpu);
VOID HalIoapicDisableInt(INT intNo);


#endif
