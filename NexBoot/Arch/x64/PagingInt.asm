; PagingInt.asm - contains internal paging routines for 64 bit
; Distributed with NexOS, licensed under the AGPL v3.0
; See LICENSE

global SwitchDir

extern pdbr

SwitchDir:
    mov rax, [pdbr]
    mov cr3, rax
    ret
