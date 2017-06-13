#ifndef KDK_TOKEN
#define KDK_TOKEN

#include <stdbool.h>

#include "lexeme.h"

/*
holds information
*/

typedef struct token{

char * raw;
lexeme type;
void * info;

struct token * left;
struct token * right;

} token;

typedef struct tBuffer
{

//operator stack
lexeme opStack [128];
unsigned oCount;

//output stack
token * head;
token * tokens;
unsigned tCount;

} tBuffer;

token * createToken(char *, lexeme, void *);
void coupleTokens(token *, token *, token *);
void destroyToken(token *, bool);

tBuffer createTBuffer();
void clearTBuffer(tBuffer *);
void appendTBuffer(tBuffer *, token *);


#endif