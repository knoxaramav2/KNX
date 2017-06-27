#Compiles Executor

CC = gcc
BITVRS=64
CFLAGS = -std=c11 -Wall -Iheaders -I../KDK/headers $(COMMON) -g
LFLAGS = -lm -Iheaders -L$(BINPATH) -l:libKDK.so -l:libMDM.so -l:libDTM.so
VERSION = -DEXCVersion=\"0.0.1\"
OUT = libEXC.so
CLEANEXT = o a
DBGFLAGS=
SRC= exec.c runner.c keyword.c math.c operator.c
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
