ASFLAGS?=-fbin

BASEDIR?=../..
ROOTDIR=$(BASEDIR)/rootdir

FLPY_OBJS=\
	boot12.o \

DISK_OBJS=\
	boot32.o \

.PHONY: all clean install

.SUFFIXES: .asm .o

all: floppy_boot.mbr disk_boot.mbr

floppy_boot.mbr: $(FLPY_OBJS)
	mv boot12.o floppy_boot.mbr

disk_boot.mbr:	$(DISK_OBJS)
	mv boot32.o disk_boot.mbr

.asm.o:
	$(AS) $(ASFLAGS) -o $@ $<

clean:
	rm -f *.mbr
	rm -f *.pbr

install:
	dd if=/dev/zero of=$(BASEDIR)/floppy.img bs=1K count=1440
	dd if=floppy_boot.mbr of=$(BASEDIR)/floppy.img bs=512 count=1 conv=notrunc
	dd if=/dev/zero of=$(BASEDIR)/disk.img bs=100M count=1
	sudo losetup /dev/loop19 $(BASEDIR)/disk.img
	sudo mkdosfs -F 32 /dev/loop19
	sudo losetup -d /dev/loop19
	dd if=disk_boot.mbr of=$(BASEDIR)/disk.img bs=1 count=512 seek=79 skip=79
