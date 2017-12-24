#compiles testing application
GFLAGS= -O3 -I../../KNX_Libraries/src/headers
LIBS= -lm -L../../KNX_Libraries/_bin/64 -lKNX_Library
SRC=Dev.c

all:
	$(CC) $(SRC) $(COMMON) $(GFLAGS) $(LIBS) -o dev.exe

clean:
	rm -f *.o
