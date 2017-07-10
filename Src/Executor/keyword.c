#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "node.h"
#include "type.h"

#include "keyword.h"

token * kw_quit(node * n, token * t)
{
    n->exit_code =  t ? *(int *) t->info : 0;
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
        appendObject(n->local, data);
        token * ret = createToken(arg->raw, data->type, data);
        return ret;
    }

    switch(word){
        case lx_KW_QUIT: return kw_quit(n, arg);

        default:

        break;
    }

    return NULL;
}