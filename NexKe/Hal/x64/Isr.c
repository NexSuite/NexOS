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
    HalIdtSetGate(0, (QWORD)isr0, 0x08, 0x8E, 0);
    HalIdtSetGate(1, (QWORD)isr1, 0x08, 0x8E, 0);
    HalIdtSetGate(2, (QWORD)isr2, 0x08, 0x8E, 0);
    HalIdtSetGate(3, (QWORD)isr3, 0x08, 0x8E, 0);
    HalIdtSetGate(4, (QWORD)isr4, 0x08, 0x8E, 0);
    HalIdtSetGate(5, (QWORD)isr5, 0x08, 0x8E, 0);
    HalIdtSetGate(6, (QWORD)isr6, 0x08, 0x8E, 0);
    HalIdtSetGate(7, (QWORD)isr7, 0x08, 0x8E, 0);
    HalIdtSetGate(8, (QWORD)isr8, 0x08, 0x8E, 0);
    HalIdtSetGate(9, (QWORD)isr9, 0x08, 0x8E, 0);
    HalIdtSetGate(10, (QWORD)isr10, 0x08, 0x8E, 0);
    HalIdtSetGate(11, (QWORD)isr11, 0x08, 0x8E, 0);
    HalIdtSetGate(12, (QWORD)isr12, 0x08, 0x8E, 0);
    HalIdtSetGate(13, (QWORD)isr13, 0x08, 0x8E, 0);
    HalIdtSetGate(14, (QWORD)isr14, 0x08, 0x8E, 0);
    HalIdtSetGate(15, (QWORD)isr15, 0x08, 0x8E, 0);
    HalIdtSetGate(16, (QWORD)isr16, 0x08, 0x8E, 0);
    HalIdtSetGate(17, (QWORD)isr17, 0x08, 0x8E, 0);
    HalIdtSetGate(18, (QWORD)isr18, 0x08, 0x8E, 0);
    HalIdtSetGate(19, (QWORD)isr19, 0x08, 0x8E, 0);
    HalIdtSetGate(20, (QWORD)isr20, 0x08, 0x8E, 0);
    HalIdtSetGate(21, (QWORD)isr21, 0x08, 0x8E, 0);
    HalIdtSetGate(22, (QWORD)isr22, 0x08, 0x8E, 0);
    HalIdtSetGate(23, (QWORD)isr23, 0x08, 0x8E, 0);
    HalIdtSetGate(24, (QWORD)isr24, 0x08, 0x8E, 0);
    HalIdtSetGate(25, (QWORD)isr25, 0x08, 0x8E, 0);
    HalIdtSetGate(26, (QWORD)isr26, 0x08, 0x8E, 0);
    HalIdtSetGate(27, (QWORD)isr27, 0x08, 0x8E, 0);
    HalIdtSetGate(28, (QWORD)isr28, 0x08, 0x8E, 0);
    HalIdtSetGate(29, (QWORD)isr29, 0x08, 0x8E, 0);
    HalIdtSetGate(30, (QWORD)isr30, 0x08, 0x8E, 0);
    HalIdtSetGate(31, (QWORD)isr31, 0x08, 0x8E, 0);
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
