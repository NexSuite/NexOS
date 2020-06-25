; GdtInt.asm - contains backend GDT routines
; Distributed with NexOS, licensed under the AGPL v3.0
; See LICENSE

section .text

extern gdtptr
global HalGdtFlush

HalGdtFlush:
    lgdt [gdtptr]
    mov ax, 10h
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    push 0x08
    push Flush
    retfq
Flush:
    ret
