#compiles RTE component

CC = gcc
CFLAGS = $(COMMON) 
LFLAGS = -lm -ldl -lpthread -L$(BINPATH) \
-l:libKDK.so -l:libMDM.so -l:libDTM.so -l:libPRS.so -l:libEXC.so\
-Wl,-rpath=$(BINPATH)
VERSION=-DRTEVERSION=\"0.0.1\"
OUT = KNX
CLEANEXT = o a
BITVRS=64
DBGFLAG=
SRC=main.c
O_SRC = $(SRC:.c=.o)

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

#all:
#	$(CC) $(SRC) $(OSMODE) $(CFLAGS) $(VERSION) $(PLATFORM) $(LFLAGS) $(KLIB) -o $(RUNPATH)

all: $(RUNPATH)
	echo $(OUT) Done

.c.o:
	$(CC) $(OSMODE) $(CFLAGS) $(VERSION) $(PLATFORM) $(LFLAGS) -c -o $@ $< $(KLIB)

$(RUNPATH) : $(O_SRC)
	$(CC) $(OSMODE) $(CFLAGS) $(VERSION) $(PLATFORM) $(LFLAGS) -o $@ $(O_SRC) $(KLIB)

.PHONY: clean
clean:
	rm -f $@ *.o

.PHONY: dbg
dbg: $(OUT)
	$(RUNPATH) $(DBGFLAGS)
