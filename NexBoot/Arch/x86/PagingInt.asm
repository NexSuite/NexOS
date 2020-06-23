; Contains internal paging routines
; Distributed with NexOS, licensed under the AGPL v3.0
; See LICENSE

extern pdbr
global SwitchDir
global EnablePaging

SwitchDir:
    mov eax, [pdbr]
    mov cr3, eax
    ret

EnablePaging:
    mov eax, cr0
    or eax, 1 << 17
    mov cr0, eax

    mov eax, cr4
    or eax, 1 << 4
    mov cr4, eax

    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax
    ret
