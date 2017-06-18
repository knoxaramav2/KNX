#include <stdlib.h>
#include <string.h>

#include "token.h"

tBuffer createTBuffer()
{
    tBuffer ret;

    //memset(ret.opStack, 0, sizeof ret.opStack);
    ret.oCount = 0;
    ret.tCount = 0;
    ret.qState = 0;

    ret.head = NULL;
    ret.tokens = NULL;

    return ret;
}

void clearTBuffer(tBuffer * bf)
{
    bf->oCount = 0;
    bf->tCount = 0;
    bf->qState = 0;

    token * tmp = bf->tokens;
    while (tmp != NULL){
        token * t = tmp->right;
        destroyToken(tmp);
        tmp = t;
    }

    bf->head = NULL;
    bf->tokens = NULL;
}

void appendTBuffer(tBuffer * bf, token * tk, bool link)
{
    if (bf->head == NULL){

        bf->head = tk;
        bf->tokens = tk;

        return;
    }

    bf->head->right = tk;
    tk->left = bf->head;
    bf->head = tk;
}