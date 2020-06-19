.PHONY: all clean install

PROJECTS = Bootstrap Nexldr

all:
	for dir in $(PROJECTS); do \
		(cd $$dir; ${MAKE}) \
	done

clean:
	for dir in $(PROJECTS); do \
		(cd $$dir; ${MAKE} clean) \
	done;

install:
	for dir in $(PROJECTS); do \
		(cd $$dir; ${MAKE} install) \
	done
