#include <stdlib.h>

#include "token.h"
#include "mem.h"

#include "objUtil.h"

void * getTokenValue(token * tk){
    if (!tk) return NULL;

    if (tk->isStored)
        return ((obj *)tk->info)->data;
    if (tk->type == lx_LIST){
        token * info = tk->info;
        free(tk);
        return info;
    }
    return tk->info;
}

token * getTokenList(token * list){

    if (list == NULL)
        return NULL;

    if (list->type != lx_LIST)
        return list;

    return list->info;
}