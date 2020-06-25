; NexOS x86_64 bootstrap file
; Distributed with NexOS, licensed under the GPL v3.0
; See LICENSE
; Partialy taken from the LemonOS project. Portions from LemonOS are copyright JJ Roberts-White, licensed under the BSD 2 clause license

bits 32

global entry                        ; Needed for linker
extern NbEntry

MOD_ALIGN equ 1<<0                  ; Page align modules
MEMINFO equ 1<<1                    ; Obtain memory map
VIDINFO equ 1<<2                    ; Have GRUB gives us video info
FLAGS equ MOD_ALIGN | MEMINFO | VIDINFO
MAGIC equ 0x1BADB002                ; Required by mutliboot
CHECKSUM equ -(MAGIC + FLAGS)       ; Checksum of the above

KERNEL_VIRTUAL_BASE equ 0xFFFFFFFF80000000      ; Base address
KERNEL_BASE_PML4_INDEX equ (((KERNEL_VIRTUAL_BASE) >> 39) & 0x1FF)
KERNEL_BASE_PDPT_INDEX equ  (((KERNEL_VIRTUAL_BASE) >> 30) & 0x1FF)

section .multiboot.data             ; Put mutliboot in its own section
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

align 4096
kernel_pml4:
times 512 dq 0

align 4096
kernel_pdpt:
dq 0x83 
times 511 dq 0

align 4096
kernel_pdpt2:
times KERNEL_BASE_PDPT_INDEX dq 0
dq 0x83

align 16
GDT64:                              ; 64 bit GDT
    dq 0                            ; Null Descriptor

    dw 0FFFFh                       ; Code descriptor
    dw 0
    db 0
    db 10011010b
    db 00100000b
    db 0

    dw 0FFFFh                      ; Data descriptor
    dw 0
    db 0
    db 10010010b
    db 00000000b
    db 0

GDT64Ptr32:                          ; 32 bit GDT pointer
    dw $ - GDT64 - 1
    dq GDT64

GDT64Ptr64:                          ; 64 bit GDT pointer
    dw GDT64Ptr32 - GDT64 - 1
    dq GDT64 + KERNEL_VIRTUAL_BASE

section .text                       ; Executable code
entry:                              ; OS entry point
    mov esi, ebx                    ; Store mutliboot stuff so we don't touch it
    mov edi, eax

    mov eax, 0x80000001             ; Check if long mode is available
    cpuid
    test edx, 1 << 29
    jz s                            ; If not, halt system.

    mov eax, cr0
    and ax, 0xFFFB		            ; Clear coprocessor emulation CR0.EM
    or ax, 0x2			            ; Set coprocessor monitoring  CR0.MP
    mov cr0, eax
    mov eax, cr4
    or ax, 3 << 9		            ; Set CR4.OSFXSR and CR4.OSXMMEXCPT at the same time
    mov cr4, eax

    mov eax, cr4                    ; Get CR4 in EAX
    or eax, 1 << 5                  ; Set PAE bit
    mov cr4, eax                    ; Restore CR4

    mov eax, kernel_pdpt            ; Get first PDPT
    or eax, 3                       ; Set present, writeable
    mov dword [kernel_pml4], eax    ; Store PDPT in PML4

    mov eax, kernel_pdpt2           ; Get second PDPT
    or eax, 3                       ; Set present, writeable
    mov dword [kernel_pml4 + KERNEL_BASE_PML4_INDEX * 8], eax    ; Store PDPT in PML4

    mov eax, kernel_pml4            ; Get PML4
    mov cr3, eax                    ; Load PML4

    mov eax, cr0                    ; Get CR0
    or eax, 1 << 17                 ; Set WP bit
    mov cr0, eax

    mov ecx, 0xC0000080            ; Select EFER MSR
    rdmsr
    or eax, 1 << 8                  ; Set long mode bit
    ;or eax, 1 << 11                 ; Set NX bit
    wrmsr                           ; Enable long mode
    
    mov eax, cr0                    ; Get CR0
    or eax, 1 << 31                 ; Set bit 31 (PG)
    mov cr0, eax                    ; Enable paging
    lgdt [GDT64Ptr32]               ; Load 64 bit GDT
    jmp 0x08:entry64                ; Far jump to 64 bit code

s:
    int 19h
    cli
    hlt

bits 64                             ; We are in Long Mode

entry64:                            ; 64 bit entry
    ;lgdt [GDT64Ptr64]               ; Load 64 bit GDT pointer
    mov ax, 10h                     ; Load segments registers with 64 bit segments
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov rsp, stack_top              ; Load Stack into RSP
    push rsi                        ; Pass multiboot info
    push rdi
    call NbEntry
    cli                             ; Halt system
    hlt

section .bss
stack_bottom:                       ; The start of the stack
    resb 16384                      ; Make a 16K stack
stack_top:                          ; x86 architecture stack grows downwards
