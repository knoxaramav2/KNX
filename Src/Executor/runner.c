#include <stdbool.h>
#include <stdio.h>

#include "executor.h"

token * nextCom(token * crawler){

    while(crawler != NULL && !isCommand(CHKTYPE(crawler->type))){
        crawler = crawler->right;
    }

    return crawler;
}

token * executeBinary(token * crawler)
{

    token * l, * r;
    r = crawler->left;
    l = r->left;
    int operands = 0;
    lexeme type = CHKTYPE(crawler->type);

    while (l->left && operands < 2){
        operands += isOperand(type);
        l = l->left;
    }
    
    token * arg = l;

    arg->left = NULL;
    l->left = NULL;
    r->right = NULL;
    token * ret = NULL;

    if (isMath(type)){
        ret = math(l, r, type);
    }

    return NULL;
}

token * executeUnary(token * crawler)
{

    


    return NULL;
}

token * splice(token * crawler, token * lval, token * rval)
{

    return NULL;
}

token * execute(node * n){

    token * opCrawler = n->buffer.tokens;

    opCrawler = nextCom(opCrawler);

    if (opCrawler == NULL)
        return NULL;

    lexeme type = CHKTYPE(opCrawler->type);

    printf("##%u %d %d\r\n", type, isUnary(type), (isKeyword(type) || type==lx_GEN_LAMBDA || type==lx_LOG_NOT));
    
    int un = isUnary(type);

    token * ret = un ?
        executeUnary(opCrawler) :
        executeBinary(opCrawler);

    

    return 0;
}