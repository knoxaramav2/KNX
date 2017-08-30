#include <stdlib.h>
#include <stdio.h>

#include "KwDecl.h"
#include "type.h"

obj * kw_print(HMODULE * module, token * arg){

    token * stream = getTokenList(arg);

    while (stream){

        void * info = getTokenValue(stream);
        void * data = isPrintable(arg->type) ?
            copyValue(info, lx_STRING) :
            castTo(info, stream->type, lx_STRING);

        if (data){
            printf("%s", (char *) data);
        } else {
            if (stream->info){
                char * name = getTypeName(arg->type);
                printf("%s", name);
                free(name);

            } else {
                printf("VOID ");
            }
        }

        free(data);

        stream = stream->right;
    }

    printf("\r\n");
    fflush(stdout);

    return NULL;
}