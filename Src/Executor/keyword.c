#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "node.h"
#include "objUtil.h"
#include "type.h"

#include "keyword.h"

token * kw_quit(node * n, token * t)
{
    n->exit_code = *(int*) getTokenValue(t);
    printf("Quiting node %d (%d)\r\n", n->id_index, n->exit_code);

    n->status = ns_terminated;

    return createToken(NULL, lx_VOID, NULL);
}

token * runKeyword(node * n, token * arg, lexeme word)
{

    //declare variable
    //TODO differ on scope
    if (isDecl(word)){
        obj * data = spawnType(word, arg);

        if (!data || isFault(data->type)){
            printf("Failure : keyword.c\r\n");
        }

        appendObject(n->local, data);
        token * ret = createToken((char*)arg->info, data->type, data);
        return ret;
    }

    switch(word){
        case lx_KW_QUIT: return kw_quit(n, arg);

        default:

        break;
    }

    return NULL;
}