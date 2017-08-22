#include <stdlib.h>

#include "TypeDecl.h"
#include "script.h"

//args: [script name] [token stream]
static obj * __constructor(token * data){

    script * ret = malloc(sizeof(script));

    return ret;
}

static void * __copy_constructor(void * v){

    return NULL;
}

static int __destructor(obj * self){

    return 0;
}

int registerScript(type_reg * type_registery){

    int fail = 0;

    fail += registerType("script", __constructor, __destructor, __copy_constructor);

    return fail;
}