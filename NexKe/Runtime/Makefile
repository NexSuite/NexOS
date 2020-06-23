CFLAGS?=-O2 -g

INCLUDEDIR?=../../Include
LIBDIR?=../../Libs

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra -Wpedantic -Werror=implicit-function-declaration -Werror=array-bounds -I$(INCLUDEDIR) $(DEFINES)

OBJS=\
	String/String.o \
	Memory/Memory.o \

LINK_LIST=\
	$(OBJS) \
	$(LIBS) \

.PHONY: all clean install

.SUFFIXES: .o .c

all: Krt.lib

Krt.lib:	$(OBJS)
	$(AR) rcs $@ $(OBJS)
	cp Krt.lib $(LIBDIR)/Krt.lib

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS)
clean:
	rm -f Krt.lib
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install:

-include $(OBJS:.o=.d)
