#ifndef KDK_TOKEN
#define KDK_TOKEN

#include "lexeme.h"

/*
holds information
*/

typedef struct token{

char * raw;
lexeme type;
void * info;

} token;


typedef struct tBuffer
{

unsigned tCount;

} tBuffer;

#endif