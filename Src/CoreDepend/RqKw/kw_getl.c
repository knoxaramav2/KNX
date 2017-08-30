#include <stdlib.h>
#include <stdio.h>

#include "KwDecl.h"

obj * kw_getl(HMODULE * module, token * arg){

    char * str = malloc(1024);

    scanf("%[^\n]", str);

    return createObject(NULL, lx_STRING, str);

}