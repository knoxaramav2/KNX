#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "token.h"

token * createToken(char * raw, lexeme type, void * data)
{
    token * ret = malloc(sizeof(token));

    if (raw){
        ret->raw = malloc(strlen(raw)+1);
        ret->raw = strncpy(ret->raw, raw, strlen(raw)+1);
    }
    
    ret->type = type;
    ret->info = data;

    ret->left = NULL;
    ret->right = NULL;

    return ret;
}

void destroyToken(token * target)
{
    free(target->raw);
    //if (freeData)
    //    free(target->info);
    
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

void coupleTokens(token * left, token * center, token * right)
{
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