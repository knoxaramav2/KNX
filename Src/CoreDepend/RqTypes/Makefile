#compiles required types module

CC = gcc
BITVRS=64
DEBUG=false
CFLAGS = -std=c11 -Iheaders -I../../KDK/headers -Wall $(COMMON) -g
LFLAGS = -lm -L$(BINPATH) -l:libKDK.so -l:libDTM.so
DFLAGS = -DDEBUG=$(DEBUG)#build debug arg
VERSION = -DKDKVersion=\"0.0.1\"
OUT = libTYP.so
CLEANEXT = o a
DBGFLAGS= -d#command line debug arg
SRC=RqTypes.c int.c uint.c lint.c ulint.c sint.c usint.c \
	char.c uchar.c wchar.c string.c wstring.c \
	array.c list.c class.c byte.c function.c void.c \
	exception.c
EXPORT_PTH=../../../bin/required/

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
	$(CC) $(CFLAGS) $(DFLAGS) $(LFLAGS) $(VERSION) $(SRC) -shared -o $(EXPORT_PTH)$(OUT) $(OSMODE) $(PLATFORM) $(KLIB_MOD)

.PHONY: clean
clean:
	rm -f $@ *.o

.PHONY: dbg
dbg: $(OUT)
	$(RUNPATH) $(DBGFLAGS)
