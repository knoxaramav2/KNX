#compiles std module set
BINPATH=
PREFIX = Src/StdModules/Std/
SUBDIRS = 

P_BINPATH=$(BINPATH)/std

#placeholder for exported variables
export BITVRS
export P_BINPATH
export KLIB
export KLIB_MOD
export DEBUG
export COMMON

subdirs:
	for dir in $(SUBDIRS); do \
	 $(MAKE) -C Std$$dir; \
	 echo Std$$dir; \
	done

.PHONY: clean
clean:
	for dir in $(SUBDIRS); do \
	 $(MAKE) clean -C $$dir; \
	done
	 rm -f $@ bin/KNX
	 rm -f $@ bin/*.so