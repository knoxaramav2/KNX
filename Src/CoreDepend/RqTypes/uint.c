#include <stdlib.h>

#include "TypeDecl.h"

obj * c_uint(token * data){

    return NULL;
}

void * cc_uint(void * v){

    return NULL;
}

int d_uint(obj * self){

    return 0;
}

void * sum_math_uint(void * lv, void * rv, lexeme rt, lexeme word){

    return NULL;
}

int registerUInt(type_reg * type_registry){

    int fail = 0;

    fail += registerType("uint", c_uint, d_uint, cc_uint);
    fail += assignMath(&type_registry->slots[type_registry->registered_types-1], sum_math_uint);

    return fail;
}