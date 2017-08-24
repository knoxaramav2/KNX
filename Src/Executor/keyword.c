#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "node.h"
#include "objUtil.h"
#include "type.h"
#include "function.h"

#include "keyword.h"

token * runKeyword(HMODULE * module, token * arg, lexeme word)
{
    node * n = module->owner;
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
        obj * data = invokeKeyword(module, arg, word);

        if (!data || isFault(data->type)){
            //printf("Failure : keyword.c\r\n");
            return NULL;
        }

        token * ret = createToken((char*)arg->info, data->type, data);

        return ret;
    }

    return NULL;
}