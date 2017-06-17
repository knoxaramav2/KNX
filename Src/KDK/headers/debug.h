#ifndef KDK_DEBUG
#define KDK_DEBUG

#include <stdbool.h>

/*

provides methods that only run while the compiler is in debug mode,
or have had 

*/

void initDbgGlb();
void dlog(char *);

//flush log buffer
void dflush();

//lexical tools
//struct tBuffer tBuffer;
void printBufferStream(tBuffer *);

#endif