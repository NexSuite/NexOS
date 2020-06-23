CFLAGS?=-g -O3
LDFLAGS?=
LIBS?=

DESTDIR?=../rootdir/System
SYSROOT?=../rootdir
INCLUDEDIR?=../Include
LIBDIR?=/lib

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra -Wpedantic -Werror=implicit-function-declaration -I../Include -I../../Include -I ../../../Include $(DEFINES) -IInclude
LIBS:=$(LIBS) -nostdlib -lgcc

include $(BOOTARCHDIR)/make.config

LOAD_OBJS=\
	$(ARCH_LOAD_OBJS) \
	NexBoot.o \
	Runtime.o \

OBJS=\
	$(LOAD_OBJS) \

LINK_LIST=\
	$(OBJS) \
	$(LIBS) \

.PHONY: all clean install

.SUFFIXES: .o .c .asm

all: nexboot

nexboot: $(OBJS)
	$(BCC) -T$(BOOTARCHDIR)/link.ld  -o $@ -z max-page-size=4096 $(CFLAGS) $(LINK_LIST)
	grub-file --is-x86-multiboot nexboot

.c.o:
	$(BCC) -MD -c $< -o $@ $(CFLAGS)
.asm.o:
	$(AS) -f$(BAS_ARCH) -o $@ $<
clean:
	rm -f nexload
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install:
	cp nexboot $(DESTDIR)/nexboot

-include $(OBJS:.o=.d)
