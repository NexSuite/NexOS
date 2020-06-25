# Details

Date : 2020-06-25 10:41:05

Directory /home/nexware/NexOS

Total : 60 files,  2471 codes, 224 comments, 496 blanks, all 3191 lines

[summary](results.md)

## Files
| filename | language | code | comment | blank | total |
| :--- | :--- | ---: | ---: | ---: | ---: |
| [.editorconfig](/.editorconfig) | EditorConfig | 10 | 0 | 4 | 14 |
| [.gitattributes](/.gitattributes) | Properties | 1 | 1 | 0 | 2 |
| [Include/Kernel/BootDrv.h](/Include/Kernel/BootDrv.h) | C++ | 6 | 5 | 5 | 16 |
| [Include/Kernel/Kernel.h](/Include/Kernel/Kernel.h) | C++ | 42 | 6 | 11 | 59 |
| [Include/Kernel/Runtime.h](/Include/Kernel/Runtime.h) | C++ | 15 | 5 | 9 | 29 |
| [Include/Kernel/System.h](/Include/Kernel/System.h) | C++ | 27 | 5 | 5 | 37 |
| [Include/nexdef.h](/Include/nexdef.h) | C++ | 22 | 8 | 10 | 40 |
| [Makefile](/Makefile) | Makefile | 45 | 0 | 6 | 51 |
| [NexBoot/Arch/x64/Memory.c](/NexBoot/Arch/x64/Memory.c) | C | 141 | 6 | 18 | 165 |
| [NexBoot/Arch/x64/Paging.c](/NexBoot/Arch/x64/Paging.c) | C | 120 | 5 | 24 | 149 |
| [NexBoot/Arch/x64/PagingInt.asm](/NexBoot/Arch/x64/PagingInt.asm) | x86 and x86_64 Assembly | 6 | 3 | 4 | 13 |
| [NexBoot/Arch/x64/Serial.c](/NexBoot/Arch/x64/Serial.c) | C | 39 | 5 | 8 | 52 |
| [NexBoot/Arch/x64/boot-x64.asm](/NexBoot/Arch/x64/boot-x64.asm) | x86 and x86_64 Assembly | 119 | 6 | 28 | 153 |
| [NexBoot/Arch/x64/link.ld](/NexBoot/Arch/x64/link.ld) | LinkerScript | 21 | 0 | 5 | 26 |
| [NexBoot/Arch/x86/Memory.c](/NexBoot/Arch/x86/Memory.c) | C | 141 | 6 | 18 | 165 |
| [NexBoot/Arch/x86/Paging.c](/NexBoot/Arch/x86/Paging.c) | C | 53 | 5 | 7 | 65 |
| [NexBoot/Arch/x86/PagingInt.asm](/NexBoot/Arch/x86/PagingInt.asm) | x86 and x86_64 Assembly | 18 | 3 | 6 | 27 |
| [NexBoot/Arch/x86/Serial.c](/NexBoot/Arch/x86/Serial.c) | C | 39 | 5 | 8 | 52 |
| [NexBoot/Arch/x86/boot-x86.asm](/NexBoot/Arch/x86/boot-x86.asm) | x86 and x86_64 Assembly | 37 | 3 | 6 | 46 |
| [NexBoot/Arch/x86/link.ld](/NexBoot/Arch/x86/link.ld) | LinkerScript | 22 | 0 | 5 | 27 |
| [NexBoot/Include/Multiboot.h](/NexBoot/Include/Multiboot.h) | C++ | 74 | 5 | 13 | 92 |
| [NexBoot/Include/Nexboot.h](/NexBoot/Include/Nexboot.h) | C++ | 181 | 6 | 27 | 214 |
| [NexBoot/Loader.c](/NexBoot/Loader.c) | C | 64 | 5 | 12 | 81 |
| [NexBoot/Makefile](/NexBoot/Makefile) | Makefile | 37 | 0 | 14 | 51 |
| [NexBoot/NexBoot.c](/NexBoot/NexBoot.c) | C | 20 | 6 | 4 | 30 |
| [NexBoot/Runtime.c](/NexBoot/Runtime.c) | C | 103 | 6 | 15 | 124 |
| [NexKe/BootDrivers/Makefile](/NexKe/BootDrivers/Makefile) | Makefile | 23 | 0 | 12 | 35 |
| [NexKe/BootDrivers/Serial/Serial.c](/NexKe/BootDrivers/Serial/Serial.c) | C | 18 | 5 | 6 | 29 |
| [NexKe/Hal/Makefile](/NexKe/Hal/Makefile) | Makefile | 29 | 0 | 15 | 44 |
| [NexKe/Hal/x64/Cpu.c](/NexKe/Hal/x64/Cpu.c) | C | 60 | 5 | 10 | 75 |
| [NexKe/Hal/x64/Gdt.c](/NexKe/Hal/x64/Gdt.c) | C | 27 | 5 | 7 | 39 |
| [NexKe/Hal/x64/GdtInt.asm](/NexKe/Hal/x64/GdtInt.asm) | x86 and x86_64 Assembly | 16 | 3 | 4 | 23 |
| [NexKe/Hal/x64/Idt.c](/NexKe/Hal/x64/Idt.c) | C | 35 | 5 | 7 | 47 |
| [NexKe/Hal/x64/IdtInt.asm](/NexKe/Hal/x64/IdtInt.asm) | x86 and x86_64 Assembly | 6 | 3 | 4 | 13 |
| [NexKe/Hal/x64/Include/Gdt.h](/NexKe/Hal/x64/Include/Gdt.h) | C++ | 20 | 5 | 8 | 33 |
| [NexKe/Hal/x64/Include/Idt.h](/NexKe/Hal/x64/Include/Idt.h) | C++ | 20 | 5 | 7 | 32 |
| [NexKe/Hal/x64/Isr.c](/NexKe/Hal/x64/Isr.c) | C | 116 | 5 | 6 | 127 |
| [NexKe/Hal/x64/IsrStub.asm](/NexKe/Hal/x64/IsrStub.asm) | x86 and x86_64 Assembly | 82 | 3 | 9 | 94 |
| [NexKe/Hal/x86-common/Hal.c](/NexKe/Hal/x86-common/Hal.c) | C | 10 | 5 | 3 | 18 |
| [NexKe/Hal/x86-common/Include/Hal.h](/NexKe/Hal/x86-common/Include/Hal.h) | C++ | 8 | 5 | 5 | 18 |
| [NexKe/Hal/x86/Cpu.c](/NexKe/Hal/x86/Cpu.c) | C | 50 | 5 | 10 | 65 |
| [NexKe/Hal/x86/Gdt.c](/NexKe/Hal/x86/Gdt.c) | C | 27 | 5 | 7 | 39 |
| [NexKe/Hal/x86/GdtInt.asm](/NexKe/Hal/x86/GdtInt.asm) | x86 and x86_64 Assembly | 14 | 3 | 4 | 21 |
| [NexKe/Hal/x86/Idt.c](/NexKe/Hal/x86/Idt.c) | C | 33 | 5 | 7 | 45 |
| [NexKe/Hal/x86/IdtInt.asm](/NexKe/Hal/x86/IdtInt.asm) | x86 and x86_64 Assembly | 6 | 3 | 4 | 13 |
| [NexKe/Hal/x86/Include/Gdt.h](/NexKe/Hal/x86/Include/Gdt.h) | C++ | 20 | 5 | 8 | 33 |
| [NexKe/Hal/x86/Include/Idt.h](/NexKe/Hal/x86/Include/Idt.h) | C++ | 18 | 5 | 7 | 30 |
| [NexKe/Hal/x86/Isr.c](/NexKe/Hal/x86/Isr.c) | C | 116 | 5 | 6 | 127 |
| [NexKe/Hal/x86/IsrStub.asm](/NexKe/Hal/x86/IsrStub.asm) | x86 and x86_64 Assembly | 73 | 3 | 7 | 83 |
| [NexKe/Kernel/Makefile](/NexKe/Kernel/Makefile) | Makefile | 37 | 0 | 14 | 51 |
| [NexKe/Kernel/Start/Entry.c](/NexKe/Kernel/Start/Entry.c) | C | 14 | 5 | 4 | 23 |
| [NexKe/Kernel/Start/Init.c](/NexKe/Kernel/Start/Init.c) | C | 10 | 5 | 3 | 18 |
| [NexKe/Kernel/Start/Panic.c](/NexKe/Kernel/Start/Panic.c) | C | 9 | 5 | 3 | 17 |
| [NexKe/Makefile](/NexKe/Makefile) | Makefile | 16 | 0 | 5 | 21 |
| [NexKe/Runtime/Makefile](/NexKe/Runtime/Makefile) | Makefile | 24 | 0 | 12 | 36 |
| [NexKe/Runtime/Memory/Memory.c](/NexKe/Runtime/Memory/Memory.c) | C | 13 | 5 | 4 | 22 |
| [NexKe/Runtime/String/String.c](/NexKe/Runtime/String/String.c) | C | 104 | 6 | 14 | 124 |
| [NexOS.code-workspace](/NexOS.code-workspace) | JSON with Comments | 8 | 0 | 0 | 8 |
| [README.md](/README.md) | Markdown | 2 | 0 | 1 | 3 |
| [grub/grub.cfg](/grub/grub.cfg) | Properties | 4 | 0 | 1 | 5 |

[summary](results.md)