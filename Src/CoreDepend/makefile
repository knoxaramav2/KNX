#compiles required (core) module set
#BINPATH=
SUBDIRS = \
	RqTypes

P_BINPATH=$(BINPATH)/std

#placeholder for exported variables
export BITVRS
export P_BINPATH
export BINPATH
export KLIB_MOD
export DEBUG
export COMMON

subdirs:
	for dir in $(SUBDIRS); do \
	 $(MAKE) -C $$dir; \
	 echo $$dir; \
	done

.PHONY: clean
clean:
	for dir in $(SUBDIRS); do \
	 $(MAKE) clean -C $$dir; \
	done
	 rm -f $@ bin/KNX
	 rm -f $@ bin/*.so