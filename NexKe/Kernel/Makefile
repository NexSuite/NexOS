CFLAGS?=-g -O3
LDFLAGS?=
LIBS?=

DESTDIR?=../rootdir/System
SYSROOT?=../rootdir
INCLUDEDIR?=../Include
LIBDIR?=/lib

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra -Wpedantic -Werror=implicit-function-declaration -I../Include -I../../Include -I ../../../Include $(DEFINES) -IInclude
LDFLAGS:=-Wl,--subsystem,native -Wl,--image-base,$(IMAGE_BASE) -Wl,--file-alignment,4096 -Wl,--section-alignment,4096 \
-Wl,--entry,$(ENTRY) -Wl,--dynamicbase

LIBS:=$(LIBS) -nostdlib -lgcc

KE_OBJS=\
	$(ARCH_LOAD_OBJS) \
	Kernel.o \

OBJS=\
	$(KE_OBJS) \

LINK_LIST=\
	$(OBJS) \
	$(LIBS) \

.PHONY: all clean install

.SUFFIXES: .o .c .asm

all: NexKe.exe

NexKe.exe: $(OBJS)
	$(CC) -o $@ $(CFLAGS) $(LINK_LIST) $(LDFLAGS)

.c.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS)
.asm.o:
	$(AS) -f$(AS_ARCH) -o $@ $<
clean:
	rm -f NexKe.exe
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install:
	mv NexKe.exe ../NexKe.exe

-include $(OBJS:.o=.d)
