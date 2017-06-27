#include <stdbool.h>
#include <stdio.h>

#include "executor.h"

token * nextCom(token * crawler){

    while(crawler != NULL && !isCommand(CHKTYPE(crawler->type))){
        crawler = crawler->right;
    }

    return crawler;
}

token * executeBinary(token * arg, lexeme com)
{
    token * ret = NULL;

    if (isMath(com))
        ret = math(arg, arg->right, com);

    return ret;
}

token * executeUnary(token * arg, lexeme com)
{

    


    return NULL;
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

token * execute(node * n){
    
    token * c = n->buffer.tokens;

    while (1){
        //find first command
        c = nextCom(c);

        if (c==NULL)
            return NULL;
        if (c->left==NULL){
            //TODO missing argument
            return NULL;
        }

        lexeme type = CHKTYPE(c->type);
        token
            *i = NULL,
            *b = NULL,
            *r = NULL,
            *n = c->right;
        
        if (isUnary(type)){
            i = c->left->left;
            b = c->left;
            b->right = NULL;
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
        b->left = NULL;
        
        if (b == c->left){
            r = executeUnary(b, type);
        } else {
            r = executeBinary(b, type);
        }
        
        destroyToken(c);
        coupleTokens(i, r, n);

        c = r;
    }

    return c;
}