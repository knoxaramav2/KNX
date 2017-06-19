#include <stdlib.h>
#include <string.h>

#include "token.h"

tBuffer createTBuffer()
{
    tBuffer ret;

    ret.oCount = 0;
    ret.tCount = 0;
    ret.qState = 0;
    ret.yieldLine = 0;
    ret.commentMode = 0;
    ret.index = 0;

    ret.head = NULL;
    ret.tokens = NULL;

    return ret;
}

void clearTBuffer(tBuffer * bf)
{
    bf->oCount = 0;
    bf->tCount = 0;
    bf->qState = 0;
    bf->yieldLine = 0;
    bf->commentMode = bf->commentMode == CB_COMMENT? CB_COMMENT : CNO_COMMENT;
    bf->index = 0;

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