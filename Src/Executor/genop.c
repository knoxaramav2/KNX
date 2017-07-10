#include "token.h"
#include "lexeme.h"
#include "genop.h"


token * listItem(token * arg){

    //append
    if (arg->type == lx_LIST){
        token * l = (token *) arg->info;

        while(l->right)
            l = l->right;

        coupleTokens(NULL, l, arg->right);

        return arg;
    }

    //new list
    return createToken(NULL, lx_LIST, arg);
}

token * runGenOp(token * arg, lexeme word){

    token * ret = NULL;

    switch(word){
        case lx_GEN_LISTITEM: return listItem(arg); break;
        default: return NULL;
    }

    return ret;
}