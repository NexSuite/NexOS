.PHONY: all clean run

PROJECTS = NexBoot NexKe

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
	mkdir -p rootdir/System
	mkdir -p rootdir/boot/grub
	cp grub/grub-$(ARCH).cfg rootdir/boot/grub/grub.cfg
	for dir in $(PROJECTS); do \
		(cd $$dir; ${MAKE} install) \
	done
	mkdir fs
	sudo kpartx -av nexos.img
	sudo mount /dev/mapper/loop16p1 fs
	sudo cp -r rootdir/* fs/
	sleep 1
	sudo umount fs
	sudo kpartx -d nexos.img
	rm -r fs
	bochs -f bochs.txt

grub_disk:
	echo "Creating GRUB disk image..."
	dd if=/dev/zero of=nexos.img bs=200M count=2
	sudo parted --script nexos.img mklabel msdos mkpart p fat32 1 20 set 1 boot on
	sudo kpartx -av nexos.img
	sleep 1
	sudo mkdosfs -F 32 /dev/mapper/loop16p1
	mkdir fs
	sudo mount /dev/mapper/loop16p1 fs
	sudo grub-install --no-floppy --modules="biosdisk part_msdos configfile normal multiboot"  --root-directory=$(HOME)/NexOS/fs /dev/loop16 --target=i386-pc
	sudo umount fs
	sudo kpartx -d nexos.img
	LOGNAME=`logname`
	LOGGROUP=`groups $(LOGNAME)` | awk '{print $(3)}'
	sudo chown $(LOGNAME):$(LOGGROUP) -R fs nexos.img
	rm -r fs
	echo "GRUB image created. Run with make run."
