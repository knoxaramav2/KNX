#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "module.h"
#include "function.h"

#include "executor.h"

/*
command execution procedure: 12 step program addition

1)  move ITR to first command token
2)  copy command instruction
3)  set CONT to RIGHT of command token
4)  move ARG to
        FIRST lval if unary
        Second lval if binary\
5)  move LSAV to ARG->LEFT
6)  detach ARG
7)  destroy command token
8)  pass ARG and command instruction to runner
9)  if return value is not void:
10a)     attach return value to LSAV and CONT
    else
10b) attach LSAV to CONT
11) attach ITR to LSAV
12) GOTO 1
*/

token * run(HMODULE * module, token * arg, token * command){

    if (isKeyword(command->type)){
        return runKeyword(module, arg, ((function)((obj *) command->info)->data));
        //return ((function) arg->info)(module, arg);
    } else {
        return runOperator(arg, command->type);
    }
}

token * execute(HMODULE * module){
    
    node * nd = module->owner;

    token * itr = nd->buffer.tokens;
    token * cont = NULL,
    * arg = NULL,
    * lsav = NULL;

    while(itr){

        //move to command token
        while (itr && !isCommand(itr->type))
            itr = itr->right;
        if (!itr){
            break;
        } 

        lexeme com = itr->type;
        bool unary = isUnary (com);
        cont = itr->right;
        arg = unary ?
            itr->left :
            itr->left ?
                itr->left->left :
                itr->left;

        if(arg)
            lsav = arg->left;

        //detach ARG
        if (arg && arg->left)
            arg->left->right = NULL;
        if (itr->left)
            itr->left->right = NULL;

        itr = run(module, arg, itr);
        
        if (itr && itr->type != lx_LIST)
            destroyTokenStrand(arg);

        coupleTokens(lsav, itr, cont);
    }   

    nd->buffer.tokens = itr; 

    return itr;
}