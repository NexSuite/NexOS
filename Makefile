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
	mkdir fs
	sudo losetup /dev/loop19 disk.img
	sudo mount /dev/loop19 fs
	sudo cp rootdir/* fs/
	sudo umount fs
	sudo losetup -d /dev/loop19
	rm -r fs
	qemu-system-$(QEMU_TYPE) -hda disk.img
