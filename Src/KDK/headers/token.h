#ifndef KDK_TOKEN
#define KDK_TOKEN

#include <stdbool.h>

#include "lexeme.h"

typedef struct token token;

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

typedef struct token{

char * raw;
lexeme type;
void * info;

tBuffer buffer;

struct token * left;
struct token * right;

} token;

token * createToken(char *, lexeme, void *);
void coupleTokens(token *, token *, token *);
void destroyToken(token *, bool);

tBuffer createTBuffer();
void clearTBuffer(tBuffer *);
void appendTBuffer(tBuffer *, token *, bool);


#endif