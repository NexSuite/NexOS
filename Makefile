.PHONY: all clean run

PROJECTS = Bootldr

all:
	for dir in $(PROJECTS); do \
		(cd $$dir; ${MAKE}) \
	done

clean:
	for dir in $(PROJECTS); do \
		(cd $$dir; ${MAKE} clean) \
	done;
	rm -rf rootdir

run:
	mkdir rootdir
	for dir in $(PROJECTS); do \
		(cd $$dir; ${MAKE} install) \
	done
	qemu-system-$(QEMU_TYPE) -hda disk.img
