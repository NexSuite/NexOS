ASFLAGS?=-fbin

BASEDIR?=../..
ROOTDIR=$(BASEDIR)/rootdir

.PHONY: all clean install

all:
	$(AS) $(ASFLAGS) -o OSPrep.bin OSPrep.asm
	
clean:
	rm -f *.bin

install:
