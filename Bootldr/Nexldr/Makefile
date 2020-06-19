.PHONY: all clean install

PROJECTS = OSPrep OSLoader

all:
	for dir in $(PROJECTS); do \
		(cd $$dir; ${MAKE}) \
	done
	cat OSPrep/OSPrep.bin OSLoader/OSLoader.exe > nexldr

clean:
	for dir in $(PROJECTS); do \
		(cd $$dir; ${MAKE} clean) \
	done;

install:
	for dir in $(PROJECTS); do \
		(cd $$dir; ${MAKE} install) \
	done
	cp nexldr ../../rootdir/nexldr
