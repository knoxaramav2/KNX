#compiles entire KNX project

SUBDIRS = Src/KDK/ Src/ModuleManager/ Src/DataManager/ Src/Executor/ Src/Parser/ Src/RTE/
BITVRS=64
BINPATH=$(shell pwd)/bin
DEBUG=false
COMMON= -DNULL=0 -Dtrue=1 -Dfalse=0

KLIB=-I ../../../KNX_Libraries/headers -L ../../../KNX_Libraries/_bin/$(BITVRS) -lKNX_Library

export BITVRS
export BINPATH
export KLIB
export DBG
export COMMON

subdirs:
	for dir in $(SUBDIRS); do \
	 $(MAKE) -C $$dir; \
	done

.PHONY: run
run:
	bin/KNX

.PHONY: dbg
dbg:
	bin/KNX -d -v --nolog --test=hello

build: subdirs run

.PHONY: clean
clean:
	for dir in $(SUBDIRS); do \
	 $(MAKE) clean -C $$dir; \
	done
	 rm -f $@ bin/KNX
	 rm -f $@ bin/*.so
