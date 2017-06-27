#Compiles KNX Development Kit

CC = gcc
BITVRS=64
DEBUG=false
CFLAGS = -std=c11 -Wall -Iheaders $(COMMON) -g
LFLAGS = -lm -Iheaders
DFLAGS = -DDEBUG=$(DEBUG)#build debug arg
VERSION = -DKDKVersion=\"0.0.1\"
OUT = libKDK.so
CLEANEXT = o a
DBGFLAGS= -d#command line debug arg
SRC=kdk.c token.c compinfo.c config.c data.c debug.c error.c registry.c
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
	$(CC) $(CFLAGS) $(DFLAGS) $(LFLAGS) $(VERSION) $(SRC) -shared -o $(EXPORT_PTH)$(OUT) $(OSMODE) $(PLATFORM) $(KLIB)

.PHONY: clean
clean:
	rm -f $@ *.o

.PHONY: dbg
dbg: $(OUT)
	$(RUNPATH) $(DBGFLAGS)
