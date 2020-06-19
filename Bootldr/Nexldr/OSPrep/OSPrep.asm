; OSPrep.asm - contains code to enter protected mode and load OSLoader
; Distributed with NexOS, licensed under the AGPL v3.0
; See LICENSE

bits 16                     ; We are in real mode

org 600h                    ; BootProg loads us here

jmp Start                   ; Jump to start

Start:
    mov ax, 0      ; Load segments
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 7BFFh   ; Set stack
    
    mov ah, 0       ; BIOS set video mode (can clear screen) (Should be put in subroutine. Currently feeling a little lazy...)
    mov al, 03h     ; Text mode
    int 10h         ; Call BIOS

    ; Now, we must enter protected mode

    cli             ; Disable inerrupts

    call EnableA20 ; Enbable A20 gate

    cli

    lgdt [GdtPtr]  ; Load GDT

    mov eax, cr0    ; Get CR0
    or eax, 1       ; Set PE bit
    mov cr0, eax    ; Load CR0 with PE bit enabled
    jmp 08h:PmodeEntry        ; Far jump to enter protected mode

    cli
    hlt

; Enables A20 gate

EnableA20:
	cli
	pusha

    call WaitInput
    mov al, 0xAD
    out 0x64, al		; disable keyboard
    call WaitInput

    mov al, 0xD0
    out 0x64,al		; tell controller to read output port
    call WaitOutput

    in  al,0x60
    push eax		; get output port data and store it
    call WaitInput

    mov al, 0xD1
    out 0x64, al		; tell controller to write output port
    call WaitInput

    pop eax
    or al,2		; set bit 1 (enable a20)
    out 0x60, al		; write out data back to the output port

    call WaitInput
    mov al, 0xAE		; enable keyboard
    out 0x64, al

    call WaitInput
	popa
    sti
    ret

; Wait for input buffer to be clear

WaitInput:
    in al, 0x64
    test al, 2
    jnz WaitInput
    ret

; Wait for output buffer to be clear

WaitOutput:
    in al, 0x64
    test al, 1
    jz WaitOutput
    ret

; BIOS printing routine

Puts16:
    lodsb           ; Puts char from SI in AL
    cmp al, 0       ; It it null?
    je .done        ; If so, we are done
    mov ah, 0Eh     ; BIOS print char
    int 10h         ; call BIOS
    jmp Puts16    ; Print next char
    .done:          ; Called when done
        ret         ; Return to caller

; The GDT

gdt:
    dq 0            ; Null descriptor

    ; Code descriptor

    dw 0FFFFh       ; Limit low
    dw 0            ; Base low
    db 0            ; Base middle
    db 10011010b    ; Access
    db 11001111b    ; Granularity
    db 0

    ; Data descriptor

    dw 0FFFFh       ; Limit low
    dw 0            ; Base low
    db 0            ; Base middle
    db 10010010b    ; Access
    db 11001111b    ; Granularity
    db 0
GdtEnd:
GdtPtr:            ; Pointer to GDT
    dw GdtEnd - gdt - 1
    dd gdt

bits 32             ; We are 32 bit now
ImageSig db 'PE'
BASE equ 0xA000

; Protected mode entry point

PmodeEntry:
    mov ax, 10h         ; Load segments registers
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 90000h      ; Set stack
	mov eax, endByte     ; Store base of OSLoader
	inc eax
    push di              ; Pass di as parameter. DI contains if this is a floppy or hard disk we are booting from
	CopyImage:
        mov esi, eax     ; Store source in esi
		mov edi, BASE   ; Store destination in edi
		cld             ; We want to move forward
		mov ecx, 8192   ; Copy 8192 bytes. Should be able to calculate size dynamically
		rep movsb       ; Copy it
	Execute:
		mov ebx, [BASE+60]      ; Get signature
  	    add ebx, BASE
  		mov esi, ebx
  		mov edi, ImageSig
  		cmpsw                   ; Compare it
  	    jne Done                ; If not equal, halt system
	EXECUTE:
		add	ebx, 24             ; Find entry point by parsing headers
		mov	eax, [ebx]
		add	ebx, 16
		mov	ebp, dword [ebx]
		add	ebx, 12
		mov	eax, dword [ebx]
		add	ebp, eax
		cli
		call ebp                ; Start OSLoader!
	Done:
		cli
    	hlt

endByte db 0
