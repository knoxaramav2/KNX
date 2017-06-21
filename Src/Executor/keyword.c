#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "node.h"

#include "executor.h"

int kw_quit(node * n, token * t)
{

    printf("Quiting node %d\r\n", n->id_index);
    fflush(stdout);

    n->status = ns_terminated;

    return 0;
}

int runKeyword(node * n, lexeme word, token * arg)
{

    /*switch(word){
        case lx_KW_QUIT: return kw_quit(n, arg);
    }*/

    return 0;
}