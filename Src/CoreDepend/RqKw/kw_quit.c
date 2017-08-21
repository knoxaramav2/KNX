#include <stdlib.h>
#include <stdio.h>

#include "KwDecl.h"
#include "type.h"

obj * kw_quit(node * n, token * arg){

    token * stream = getTokenList(arg);

    n->exit_code = 0;

    if (stream){

        void * info = getTokenValue(stream);
        int * pExitCode = castTo(info, stream->type, lx_INT);

        if (pExitCode){
            
            n->exit_code = *pExitCode;
            free(pExitCode);
        } else {
            n->exit_code = -1;
        }
    }

    n->status = ns_terminated;

    printf("Quiting node %d with code (%d)\r\n", n->id_index, n->exit_code);
    fflush(stdout);

    return NULL;
}