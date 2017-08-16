#include <stdlib.h>

#include "KNX_Hash.h"

#include "TypeDecl.h"

static obj * __constructor(token * data){

    return NULL;
}

static void * __copy_constructor(void * v){

    return NULL;
}

static int __destructor(obj * self){

    return 0;
}

static void * c_char2string(void * orig){
    char * data = malloc(2 * sizeof(char));
    data[0] = ((char *) orig)[0];
    data[1] = 0;
    return data;
}

int registerChar(type_reg * type_registry){

    int fail = 0;

    fail += registerType("char", __constructor, __destructor, __copy_constructor);
    fail += addCaster(&type_registry->slots[type_registry->registered_types-1], lx_STRING, c_char2string);

    return fail;
}