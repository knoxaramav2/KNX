#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "KwDecl.h"
#include "type.h"
#include "file.h"

int parseToTStack(char * path, tBuffer * buf){

    char * localPath = localizePath(path);

    FILE * file = fopen(localPath, "r");
    free(localPath);

    char line [256];

    if (!file)
        return 1;

    while(fgets(line, sizeof(line), file)){

        size_t len = strlen(line);
        size_t nullPlace = len;
        bool isEnd = false;

        #ifdef __WINDOWS
            isEnd = line[nullPlace - 1] != '\n';
            nullPlace -= 2;
        #else
            isEnd = line[nullPlace] != '\r';
            nullPlace -= 1;
        #endif

        if (!isEnd)
            line[nullPlace] = 0;
        
            char * raw = malloc(len + 1);
        strncpy(raw, line, len);

        if (buf->stackBuffer == NULL){
            buf->stackBuffer = malloc(sizeof(tStackItem));
            buf->stackBuffer->line = raw;
            buf->stackIndex = buf->stackBuffer;
        } else {
            buf->stackIndex->next = malloc(sizeof(tStackItem));
            buf->stackIndex = buf->stackIndex->next;
            buf->stackIndex->line = raw;
        }

        printf(">> %s\r\n", buf->stackIndex->line);
        fflush(stdout);

        if (ferror(file)){
            fclose(file);
            return 2;
        }
    }
    

    fclose(file);
    return 0;
}

obj * kw_run(HMODULE * module, token * arg){

    token * stream = getTokenList(arg);

    while (stream){
        void * info = getTokenValue(stream);
        void * data = isPrintable(arg->type) ?
            copyValue(info, lx_STRING) :
            castTo(info, stream->type, lx_STRING);

        if (data){
            parseToTStack((char*) data, module->buffer);
        } else {
            
        }

        free(data);

        stream = stream->right;
    }

    return NULL;

}