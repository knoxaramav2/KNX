#ifndef KDK_DEBUG
#define KDK_DEBUG

#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>

#include "token.h"

/*

provides methods that only run while the compiler is in debug mode,
or have had 

*/

//#define dprint(...) printf(__VA_ARGS__)

void initDbgGlb();
void dlog(char *);

//flush log buffer
void dflush();

//lexical tools
//struct tBuffer tBuffer;
void printBufferStream(tBuffer *);

void dprint(char *, ...);

#endif