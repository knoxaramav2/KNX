#Compiles StdExcept Core Library

CORE_LB = true

CC = gcc
BITVRS=64
CFLAGS = -std=c11 -Wall -Iheaders -I../../KDK/headers $(COMMON) -g
LFLAGS = -lm -Iheaders -L$(BINPATH) -l:libKDK.so
VERSION = -DEXCVersion=\"0.0.1\"
OUT = libEXC.so
CLEANEXT = o a
DBGFLAGS=
SRC= 
EXPORT_PTH=P_BINPATH

all: $(CC)
	$(CC) $(CFLAGS) $(LFLAGS) $(VERSION) $(SRC) -shared -o $(EXPORT_PTH)$(OUT) $(OSMODE) $(DBGFLAGS)