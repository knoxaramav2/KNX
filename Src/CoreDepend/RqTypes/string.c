#include <stdlib.h>
#include <string.h>

#include "TypeDecl.h"

static obj * __constructor(token * data){



    return NULL;
}

static void * __copy_constructor(void * v){

    size_t len = strlen((char *) v) + 1;
    char * ret = malloc(len);
    strncpy(ret, (char *) v, len);

    return ret;
}

static int __destructor(obj * self){

    return 0;
}

int registerString(type_reg * type_registery){

    int fail = 0;

    fail += registerType("string", __constructor, __destructor, __copy_constructor);

    return fail;
}