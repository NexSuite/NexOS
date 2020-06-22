; NexOS i686 bootstrap file
; Distributed with NexOS, licensed under the AGPL v3.0
; See LICENSE

global entry                        ; Needed for linker
extern NbEntry

MOD_ALIGN equ 1<<0                  ; Page align modules
MEMINFO equ 1<<1                    ; Obtain memory map
VIDINFO equ 1<<2                    ; Have GRUB give us video info
FLAGS equ MOD_ALIGN | MEMINFO | VIDINFO
MAGIC equ 0x1BADB002                ; Required by mutliboot
CHECKSUM equ -(MAGIC + FLAGS)       ; Checksum of the above

section .multiboot                  ; Put mutliboot in its own section
align 4                             ; Header must be 4 byte aligned
Header:                             ; Tell grub about our image
    dd MAGIC
    dd FLAGS
    dd CHECKSUM
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 800
    dd 600
    dd 32

section .bss
align 16
stackBottom:
    resb 16384                      ; Reserve 16K for our stack
stackTop:                          ; x86 architecture stack grows downward

section .text                       ; Executable code
entry:                              ; OS entry point
    mov esp, stackTop               ; Load stack into esp
    push ebx
    push eax
    call NbEntry
s:  cli                             ; Halt system
    hlt
    jmp s
