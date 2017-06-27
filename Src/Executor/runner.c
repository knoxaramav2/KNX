#include <stdbool.h>
#include <stdio.h>

#include "executor.h"

token * nextCom(token * crawler){

    while(crawler != NULL && !isCommand(CHKTYPE(crawler->type))){
        crawler = crawler->right;
    }

    return crawler;
}

token * executeBinary(node * n, token * arg, lexeme com)
{
    token * ret = NULL;

    if (isMath(com))
        ret = math(arg, arg->right, com);
    if (isKeyword(com))
        ret = runKeyword(n, com, arg);

    return ret;
}

token * executeUnary(node * n, token * arg, lexeme com)
{
    token * ret = NULL;
    if (isKeyword(com))
        ret = runKeyword(n, com, arg);
    return ret;
}

token * extract(token * l, token * r){

    token * save = l->left;

    if (l->left)
        l->left->right = NULL;
    if (r->right)
        r->right->left = NULL;
    
    l->left = NULL;
    r->right = NULL;

    return save;
}

token * splice(token * crawler, token * lval, token * rval)
{



    return NULL;
}

token * execute(node * nd){
    
    token * c = nd->buffer.tokens;

    while (1){
        //find first command
        c = nextCom(c);

        if (c==NULL)
            return NULL;/*
        if (c->left==NULL){
            //TODO missing argument
            return NULL;
        }*/

        lexeme type = CHKTYPE(c->type);
        token
            *i = NULL,
            *b = NULL,
            *r = NULL,
            *n = c->right;
        
        if (isUnary(type)){
            if (c->left){
                i = c->left->left;
                b = c->left;
                b->right = NULL;
            }
        } else {
            if (c->left->left == NULL){
                //TODO throw error
            }

            i = c->left->left->left;
            b = c->left->left;
            if (b)
                c->left->right = NULL;
        }

        if (i) 
            i->right = NULL;
        if (b)
            b->left = NULL;
        
        if (b == c->left){
            r = executeUnary(nd, b, type);
        } else {
            r = executeBinary(nd, b, type);
        }
        
        destroyToken(c);
        if (i || r || n) coupleTokens(i, r, n);

        c = r ?: n;
    }

    return c;
}