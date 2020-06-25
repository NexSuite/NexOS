; GdtInt.asm - contains backend GDT routines
; Distributed with NexOS, licensed under the AGPL v3.0
; See LICENSE

section .text

extern _gdtptr
global _HalGdtFlush

_HalGdtFlush:
    lgdt [_gdtptr]
    mov ax, 10h
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:Flush
Flush:
    ret
