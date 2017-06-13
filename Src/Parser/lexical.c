#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "parser.h"

#define isOperator(x) (!(x>='a' &&x<='z') && !(x>='A' || x<='Z') && x!='.')

static void pushOp(char * str, size_t * pos)
{


} 

static void pushVal(char * str, size_t * pos)
{

}

//TODO implement modified shunting yard as in docs
int tokenize(node * node, char * raw)
{

    printf("Input: %s from node %d\r\n", raw, node->id_index);

    size_t len = strlen(raw);

    for (size_t x=0; x<len; ++x)
    {
        char c = raw[x];

        if (isOperator(c))
            pushOp(raw+x, &x);
        else
            pushVal(raw+x, &x);
    }

    return node->buffer.tCount == 0 ?
        TK_COMPLETE :
        TK_PENDING;
}