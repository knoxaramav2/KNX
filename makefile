#compiles entire KNX project

SUBDIRS = Src/KDK/ Src/StdModules/ Src/ModuleManager/ Src/DataManager/ Src/Parser/ Src/Executor/ Src/RTE/
BITVRS=64
BINPATH=$(shell pwd)/bin
DEBUG=false
COMMON= -std=c11 -Wall -g -Iheaders -I../KDK/headers

KLIB=-I$(shell pwd)/../KNX_Libraries/src/headers -L../../../KNX_Libraries/_bin/$(BITVRS) -lKNX_Library

export BITVRS
export BINPATH
export KLIB
export KLIB_MOD
export DEBUG
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

.PHONY: clean
clean:
	for dir in $(SUBDIRS); do \
	 $(MAKE) clean -C $$dir; \
	done
	 rm -f $@ bin/KNX
	 rm -f $@ bin/*.so

build: clean subdirs run