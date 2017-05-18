#Compiles KNX Development Kit

FILES = $(shell ls ../../../KNX_Libraries/_bin/64)
$(info [${FILES}])

CC = gcc
BITVRS=64
CFLAGS = -std=c11 -Wall -Iheaders
LFLAGS = -lm -Iheaders
VERSION = -DKDKVersion=\"0.0.1\"
OUT = libKDK.so
CLEANEXT = o a
DBGFLAGS=
SRC=compinfo.c
EXPORT_PTH=../../bin/

ifeq ($(shell uname), Linux)
	FixPath = $1
	PLATFORM = -D__LINUX
	OSMODE = -DBITMODE=$(BITVRS)
	CFLAGS += -fPIC
else
#Windows
	FixPath = $(subst /,\,$1)
	PLATFORM = -D__WINDOWS
	OSMODE = -DBITMODE=$(BITVRS)
endif

all:
	$(CC) $(CFLAGS) $(LFLAGS) $(KLIB) $(VERSION) $(SRC) -shared -o $(EXPORT_PTH)$(OUT) $(OSMODE) $(DBGFLAGS)

.PHONY: clean
clean:
	rm -f $@ *.o

.PHONY: dbg
dbg: $(OUT)
	$(RUNPATH) $(DBGFLAGS)
