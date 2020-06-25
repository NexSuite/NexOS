CFLAGS?=-O2 -g

INCLUDEDIR?=../../Include
LIBDIR?=../../Libs

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra -Wpedantic -Werror=implicit-function-declaration -Werror=array-bounds \
-I$(INCLUDEDIR) -I$(ARCH)/Include -I$(ARCH_COMMON)-common/Include $(DEFINES)

include $(ARCH)/make.config
include $(ARCH_COMMON)-common/make.config

OBJS=\
	$(HAL_ARCH_OBJS) \
	$(HAL_COMMON_OBJS) \

LINK_LIST=\
	$(OBJS) \
	$(LIBS) \

.PHONY: all clean install

.SUFFIXES: .o .c .asm

all: Hal.lib

Hal.lib:	$(OBJS)
	$(AR) rcs $@ $(OBJS)
	cp Hal.lib $(LIBDIR)/Hal.lib

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS)

.asm.o:
	$(AS) -f$(AS_ARCH) -o $@ $<

clean:
	rm -f Hal.lib
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install:

-include $(OBJS:.o=.d)
