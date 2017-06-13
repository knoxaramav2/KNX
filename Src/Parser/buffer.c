#include <stdlib.h>
#include <string.h>

#include "token.h"

tBuffer createTBuffer()
{
    tBuffer ret;

    memset(ret.opStack, 0, sizeof ret.opStack);
    ret.oCount = 0;

    ret.head = NULL;
    ret.tokens = NULL;
    ret.tCount = 0;

    return ret;
}

void clearTBuffer(tBuffer * bf)
{
    for (int i = bf->oCount; i>= i; --i)
    {
        bf->opStack[i] = 0;
    }

    token * tmp = bf->head;
    while (tmp != NULL){
        token * t = tmp->right;
        destroyToken(t, tmp);
        tmp = t;
    }

    bf->head = NULL;
}

void appendTBuffer(tBuffer * bf, token * tk, bool link)
{
    
}