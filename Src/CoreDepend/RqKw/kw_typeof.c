#include <stdlib.h>
#include <stdio.h>

#include "KwDecl.h"
#include "type.h"

obj * kw_typeof(HMODULE * module, token * arg){
    
    if (arg){
        return createObject(NULL, lx_STRING, getTypeName(arg->type));
    }

    return NULL;
}