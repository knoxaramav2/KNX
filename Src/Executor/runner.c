#include "executor.h"


token * interpretLevel(node *n, token * t, lexeme enCap){

    token * i = n;

    //scan for opcodes
    /*
    while (i!=NULL){
        switch(i->type){
            
        }
    }*/

    return NULL;
}

int execute(node * n){

    token * c = n->buffer.tokens;

    token * ret = interpretLevel(n, c, lx_NA);

    return 0;
}