#ifndef KDK_TOKEN
#define KDK_TOKEN

#include <stdbool.h>
#include <string.h>

#include "lexeme.h"

typedef struct token token;

#define QBIT_S      1
#define QBIT_D      2

#define CNO_COMMENT 0
#define CS_COMMENT  1
#define CB_COMMENT  2

/*
typedef union tkn_id{

    struct{
        unsigned short context;
        unsigned short type;
    };

    unsigned x;
}tkn_id;*/

typedef struct tBuffer
{
    
unsigned char qState;

    //operator stack
    lexeme opStack [128];
    unsigned oCount;
    int eCount;//encapsulation level

    //output stack
    token * tokens;
    token * head;
    unsigned tCount;

    //lexer buffer
    char buffer[1024];
    size_t index;

    bool yieldLine;
    short commentMode;

} tBuffer;

typedef struct token{
    lexeme type;
    bool isStored;
    void * info;

    tBuffer buffer;

    struct token * left;
    struct token * right;

} token;

//TODO change bool to storage location id
token * createToken(bool , lexeme, void *);
void coupleTokens(token *, token *, token *);
void destroyToken(token *);
void destroyTokenStrand(token *);

tBuffer createTBuffer();
void clearTBuffer(tBuffer *);
void appendTBuffer(tBuffer *, token *, bool);


#endif