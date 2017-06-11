#compiles RTE component

CC = gcc
CFLAGS = -std=c11 -Wall -I../KDK/headers -Iheaders -I../../../KNX_Libraries/headers -DNULL=0 -Dtrue=1 -Dfalse=0 -g
LFLAGS = -lm -ldl -lpthread -L$(BINPATH) \
-l:libKDK.so -l:libMDM.so -l:libDTM.so -l:libPRS.so \
-Wl,-rpath=$(BINPATH)
VERSION=-DRTEVERSION=\"0.0.1\"
OUT = KNX
CLEANEXT = o a
BITVRS=64
DBGFLAG=
SRC=main.c setup.c node.c

ifeq ($(shell uname), Linux)
	FixPath = $1
	PLATFORM = -D__LINUX
	OSMODE = -DBITMODE=$(BITVRS)
	EXPORT_PTH=../../bin/
	EXT=
	RUNPATH=./$(EXPORT_PTH)$(OUT)$(EXT)
else
#Windows
	FixPath = $(subst /,\,$1)
	PLATFORM = -D__WINDOWS
	OSMODE = -DBITMODE=$(BITVRS)
	EXPORT_PTH=../../bin/
	EXT=.exe
	RUNPATH=$(EXPORT_PTH)$(OUT)$(EXT)
endif

all:
	$(CC) $(SRC) $(OSMODE) $(CFLAGS) $(VERSION) $(PLATFORM) $(LFLAGS) $(KLIB) -o $(RUNPATH)

.PHONY: clean
clean:
	rm -f $@ *.o

.PHONY: dbg
dbg: $(OUT)
	$(RUNPATH) $(DBGFLAGS)
