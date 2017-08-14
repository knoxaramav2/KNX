#include <stdlib.h>

#include "TypeDecl.h"

obj * __constructor(token * data){

    return NULL;
}

static void * __copy_constructor(void * v){

    return NULL;
}

static int __destructor(obj * self){

    return 0;
}

int registerList(type_reg * type_registery){

    int fail = 0;

    fail += registerType("", __constructor, __destructor, __copy_constructor);

    return fail;
}