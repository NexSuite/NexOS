; IdtInt.asm - contains IDT backend ASM
; Distributed with NexOS, licensed under the AGPL v3.0
; See LICENSE

section .text

extern iptr
global HalIdtFlush

HalIdtFlush:
    lidt [iptr]
    ret
