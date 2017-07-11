#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "token.h"

token * createToken(bool stored, lexeme type, void * data)
{
    token * ret = malloc(sizeof(token));

    ret->isStored = stored;
    ret->type = type;
    ret->info = data;

    ret->left = NULL;
    ret->right = NULL;

    return ret;
}

void destroyToken(token * target)
{
    //is stored memory
    if (!target->isStored && target->info){
        free(target->info);
    }
    
    if (target->left && target->right)
    {
        target->left->right = target->right;
        target->right->left = target->left;
    } else
    {
        if (target->left)
            target->left->right = NULL;
        if (target->right)
            target->right->left = NULL;
    }

    free(target);
}

void destroyTokenStrand(token * t){
    while (t != NULL){
        token * r = t->right;
        destroyToken(t);
        t=r;
    }
}

void coupleTokens(token * left, token * center, token * right)
{
    if (!left && !center && !right)
        return;

    if (!center)
        return coupleTokens(NULL, left, right);

    if (left)
    {
        left->right = center;
        center->left = left;
    }

    if (right)
    {
        right->left = center;
        center->right = right;
    }
}