#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "node.h"

#include "keyword.h"

token * kw_quit(node * n, token * t)
{

    printf("Quiting node %d\r\n", n->id_index);
    fflush(stdout);

    n->status = ns_terminated;

    return NULL;
}

token * runKeyword(node * n, lexeme word, token * arg)
{

    switch(word){
        case lx_KW_QUIT: return kw_quit(n, arg);

        default:

        break;
    }

    return NULL;
}