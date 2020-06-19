CFLAGS?=-O2 -g
LDFLAGS?=
LIBS?=
ASFLAGS?=-fwin32

BASEDIR?=../../..
ROOTDIR?=$(BASEDIR)/rootdir
INCLUDEDIR?=$(BASEDIR)/include

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra -I$(INCLUDEDIR) $(DEFINES)
LIBS:=$(LIBS) -nostdlib -lgcc
LDFLAGS:=-Wl,--subsystem,native -Wl,--image-base,0xA000 -Wl,--file-alignment,4096 -Wl,--section-alignment,4096 \
-Wl,--entry,_NexldrStart

OBJS=\
	NexStart.o \

LINK_LIST=\
	$(OBJS) \
	$(LIBS) \

.PHONY: all clean install

.SUFFIXES: .o .c .asm

all: OSLoader.exe

OSLoader.exe:	$(OBJS)
	$(BOOT_CC) -o $@ $(CFLAGS) $(LINK_LIST) $(LDFLAGS)

.c.o:
	$(BOOT_CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS)

.asm.o:
	$(AS) $(ASFLAGS) -o $@ $<

clean:
	rm -f *.exe
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install:

-include $(OBJS:.o=.d)
