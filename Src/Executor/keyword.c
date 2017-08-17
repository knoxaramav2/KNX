#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "node.h"
#include "objUtil.h"
#include "type.h"
#include "function.h"

#include "keyword.h"


int throwException(t_exception * ex){
    printf("TODO: %s", ex->msg);
    return 0;
}

token * kw_quit(node * n, token * t)
{
    int * val = NULL;
    bool casted = false;
    if (t){
        casted = t->type != lx_INT;
        val = castTo(getTokenValue(t), t->type, lx_INT);
    }
    n->exit_code = val ? *val : 0;
    printf("Quiting node %d (%d)\r\n", n->id_index, n->exit_code);

    n->status = ns_terminated;

    if (casted)
        free(val);

    return createToken(NULL, lx_VOID, NULL);
}

token * kw_throw(node *n, token *t){



    return NULL;
}

token * runKeyword(node * n, token * arg, lexeme word)
{

    //declare variable
    //TODO differ on scope
    if (isDecl(word)){
        obj * data = spawnType(word, arg);

        if (!data || isFault(data->type)){
            //printf("Failure : keyword.c\r\n");
            return NULL;
        }

        appendObject(n->local, data);
        token * ret = createToken((char*)arg->info, data->type, data);
        ret->isStored = true;
        return ret;
    } else if (isFKeyword(word)){
        obj * data = invokeKeyword(n, arg, word);

        if (!data || isFault(data->type)){
            //printf("Failure : keyword.c\r\n");
            return NULL;
        }

        token * ret = createToken((char*)arg->info, data->type, data);

        return ret;
    }

    /*switch(word){
        case lx_KW_QUIT: return kw_quit(n, arg);
        case lx_KW_THROW: return kw_throw(n, arg);

        default:

        break;
    }*/

    return NULL;
}