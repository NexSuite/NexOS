/*
    Isr.c - contains C ISR handlers
    Distributed with NexOS, licensed under the AGPL v3.0
    See LICENSE
*/

#include <Kernel/Kernel.h>
#include <Kernel/BootDrv.h>
#include <Kernel/Runtime.h>
#include <Kernel/System.h>
#include <Hal.h>
#include "Include/Idt.h"

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

VOID HalIsrInstall()
{
    HalIdtSetGate(0, (DWORD)isr0, 0x08, 0x8E);
    HalIdtSetGate(1, (DWORD)isr1, 0x08, 0x8E);
    HalIdtSetGate(2, (DWORD)isr2, 0x08, 0x8E);
    HalIdtSetGate(3, (DWORD)isr3, 0x08, 0x8E);
    HalIdtSetGate(4, (DWORD)isr4, 0x08, 0x8E);
    HalIdtSetGate(5, (DWORD)isr5, 0x08, 0x8E);
    HalIdtSetGate(6, (DWORD)isr6, 0x08, 0x8E);
    HalIdtSetGate(7, (DWORD)isr7, 0x08, 0x8E);
    HalIdtSetGate(8, (DWORD)isr8, 0x08, 0x8E);
    HalIdtSetGate(9, (DWORD)isr9, 0x08, 0x8E);
    HalIdtSetGate(10, (DWORD)isr10, 0x08, 0x8E);
    HalIdtSetGate(11, (DWORD)isr11, 0x08, 0x8E);
    HalIdtSetGate(12, (DWORD)isr12, 0x08, 0x8E);
    HalIdtSetGate(13, (DWORD)isr13, 0x08, 0x8E);
    HalIdtSetGate(14, (DWORD)isr14, 0x08, 0x8E);
    HalIdtSetGate(15, (DWORD)isr15, 0x08, 0x8E);
    HalIdtSetGate(16, (DWORD)isr16, 0x08, 0x8E);
    HalIdtSetGate(17, (DWORD)isr17, 0x08, 0x8E);
    HalIdtSetGate(18, (DWORD)isr18, 0x08, 0x8E);
    HalIdtSetGate(19, (DWORD)isr19, 0x08, 0x8E);
    HalIdtSetGate(20, (DWORD)isr20, 0x08, 0x8E);
    HalIdtSetGate(21, (DWORD)isr21, 0x08, 0x8E);
    HalIdtSetGate(22, (DWORD)isr22, 0x08, 0x8E);
    HalIdtSetGate(23, (DWORD)isr23, 0x08, 0x8E);
    HalIdtSetGate(24, (DWORD)isr24, 0x08, 0x8E);
    HalIdtSetGate(25, (DWORD)isr25, 0x08, 0x8E);
    HalIdtSetGate(26, (DWORD)isr26, 0x08, 0x8E);
    HalIdtSetGate(27, (DWORD)isr27, 0x08, 0x8E);
    HalIdtSetGate(28, (DWORD)isr28, 0x08, 0x8E);
    HalIdtSetGate(29, (DWORD)isr29, 0x08, 0x8E);
    HalIdtSetGate(30, (DWORD)isr30, 0x08, 0x8E);
    HalIdtSetGate(31, (DWORD)isr31, 0x08, 0x8E);
}

PSTR messages[] = {
  "Division by zero",
  "Debug",
  "Non maskable interrupt",
  "Breakpoint",
  "Overflow",
  "Out of bounds",
  "Invalid Opcode",
  "No Coprocesser",
  "Double Fault",
  "Coprocesser Segment overrun",
  "Bad TSS",
  "Segment not present",
  "Stack Fault",
  "General Protection Fault",
  "Page Fault",
  "Unknown Interrupt",
  "Coprocesser Fault",
  "Alignment Check",
  "Machine Check",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved"
};

VOID HalIsrHandler(REGS* regs)
{
    if(regs->intNo < 32)
    {
        PSTR msg = messages[regs->intNo];
        KePanic(msg);
        asm("cli; hlt");
    }
}
