ENTRY(entry)

SECTIONS {
   . = 0x100000;
   .multiboot.data : {
       *(.multiboot.data)
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
