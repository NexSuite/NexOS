ENTRY(entry)
OUTPUT_FORMAT(elf32-i386)

SECTIONS {
   . = 0x00100000;
   .multiboot : {
       *(.multiboot)
   }

   .text ALIGN(4096) : AT(ADDR(.text)) {
       *(.text)
   }

   .data ALIGN (4096) : AT(ADDR(.data)) {
       *(.data)
       *(.rodata*)
   }

   .bss ALIGN (4096) : AT(ADDR(.bss)) {
       _sbss = .;
       *(COMMON)
       *(.bss)
       _ebss = .;
   }
	end = .; _end = .; __end = .;
}
