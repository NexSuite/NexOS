.PHONY: all clean install

PROJECTS = Runtime BootDrivers Kernel

all:
	for dir in $(PROJECTS); do \
		(cd $$dir; ${MAKE}) \
	done

clean:
	for dir in $(PROJECTS); do \
		(cd $$dir; ${MAKE} clean) \
	done;
	rm -f NexKe.exe

install:
	for dir in $(PROJECTS); do \
		(cd $$dir; ${MAKE} install) \
	done
	cp NexKe.exe ../rootdir/System/NexKe.exe
