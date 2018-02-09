#compiles RTE component

CC = gcc
CFLAGS = $(COMMON) 
LFLAGS = -lm -ldl -lpthread -L$(BINPATH) \
-Wl,-rpath=$(BINPATH) \
-l:libKDK.so -l:libMDM.so -l:libDTM.so -l:libPRS.so -l:libEXC.so \
-I../Parser/headers/

VERSION=-DRTEVERSION=\"0.0.1\"
OUT = KNX
CLEANEXT = o a
BITVRS=64
DBGFLAG=
SRC=main.c node.c launch.c _init.c
O_SRC = $(SRC:.c=.o)

ifeq ($(shell uname), Linux)
	FixPath = $1
	OSMODE = -DBITMODE=$(BITVRS)
	EXPORT_PTH=../../bin/
	EXT=
	RUNPATH=./$(EXPORT_PTH)$(OUT)$(EXT)
else
#Windows
	FixPath = $(subst /,\,$1)
	OSMODE = -DBITMODE=$(BITVRS)
	EXPORT_PTH=../../bin/
	EXT=.exe
	RUNPATH=$(EXPORT_PTH)$(OUT)$(EXT)
endif 

#all:
#	$(CC) $(SRC) $(OSMODE) $(CFLAGS) $(VERSION) $(PLATFORM) $(LFLAGS) $(KLIB) -o $(RUNPATH)

all: $(RUNPATH)
	echo $(OUT) Done

#TODO Re-add $(LFLAGS) $(OSMODE) 
.c.o:
	$(CC) $(CFLAGS) $(KLIBINC) -c -o $@ $<

$(RUNPATH) : $(O_SRC)
	$(CC) $(CFLAGS) $(KLIBINC) -o $@ $(O_SRC) $(KLIBBIN) $(LFLAGS)

.PHONY: clean
clean:
	rm -f $@ *.o

.PHONY: dbg
dbg: $(OUT)
	exec gdb -x $(RUNPATH) $(DBGFLAGS)
