#include <stdlib.h>
#include <stdio.h>

#include "KwDecl.h"
#include "type.h"

obj * kw_print(node * n, token * arg){

    token * stream = getTokenList(arg);

    while (stream){


        void * data = isPrintable(arg->type) ?
            copyValue(arg->info, lx_STRING) :
            castTo(stream->info, stream->type, lx_STRING);

        if (data){
            printf("%s", (char *) data); fflush(stdout);
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

    return NULL;
}