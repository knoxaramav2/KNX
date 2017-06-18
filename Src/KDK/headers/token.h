#ifndef KDK_TOKEN
#define KDK_TOKEN

#include <stdbool.h>

#include "lexeme.h"

typedef struct token token;

#define QBIT_S  1
#define QBIT_D  2

typedef struct tBuffer
{
    
unsigned char qState;

//operator stack
lexeme opStack [128];
unsigned oCount;

//output stack
token * tokens;
token * head;
unsigned tCount;

bool yieldLine;

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
void destroyToken(token *);

tBuffer createTBuffer();
void clearTBuffer(tBuffer *);
void appendTBuffer(tBuffer *, token *, bool);


#endif