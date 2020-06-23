CFLAGS?=-O2 -g

INCLUDEDIR?=../../Include
LIBDIR?=../../Libs

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra -Wpedantic -Werror=implicit-function-declaration -Werror=array-bounds -I$(INCLUDEDIR) $(DEFINES)

OBJS=\
	Serial/Serial.o \

LINK_LIST=\
	$(OBJS) \
	$(LIBS) \

.PHONY: all clean install

.SUFFIXES: .o .c

all: BootDrivers.lib

BootDrivers.lib:	$(OBJS)
	$(AR) rcs $@ $(OBJS)
	cp BootDrivers.lib $(LIBDIR)/BootDrivers.lib

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS)
clean:
	rm -f BootDrivers.lib
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install:

-include $(OBJS:.o=.d)
