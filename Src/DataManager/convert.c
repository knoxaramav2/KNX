#include "token.h"
#include "mem.h"

#include "objUtil.h"

void * getTokenValue(token * tk){

    if (tk->isStored)
        return ((obj *)tk->info)->data;
    return tk->info;
}