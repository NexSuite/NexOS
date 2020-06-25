; IdtInt.asm - contains IDT backend ASM
; Distributed with NexOS, licensed under the AGPL v3.0
; See LICENSE

section .text

extern _iptr
global _HalIdtFlush

_HalIdtFlush:
    lidt[_iptr]
    ret
