#include <stdlib.h>
#include <stdio.h>

#include "KwDecl.h"
#include "type.h"

obj * kw_quit(HMODULE * module, token * arg){

    token * stream = getTokenList(arg);

    module->owner->exit_code = 0;

    if (stream){

        void * info = getTokenValue(stream);
        int * pExitCode = castTo(info, stream->type, lx_INT);

        if (pExitCode){
            
            module->owner->exit_code = *pExitCode;
            free(pExitCode);
        } else {
            module->owner->exit_code = -1;
        }
    }

    module->owner->status = ns_terminated;

    printf("Quiting node %d with code (%d)\r\n", 
        module->owner->id_index, 
        module->owner->exit_code);
    fflush(stdout);

    return NULL;
}