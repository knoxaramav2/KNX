#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "TypeDecl.h"

static obj * __constructor(token * data){

    if (data == NULL){

    }

    data = getTokenList(data);

    char * name = NULL;
    char * value = NULL;

    for (int indx = 0; data; ++indx){
        switch(indx){
            case 0:
                name = castTo(data->info, data->type, lx_STRING);
            break;
            case 1:
                value = castTo(data->info, data->type, lx_STRING);
            break;
            default:;
        }

        data = data->right;
    }

    //default value
    if (value == NULL){
        value = malloc(1);
        value[0]=0;
    }

    return createObject(name, lx_STRING, value);
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

token * math_string(void * lv, void * rv, lexeme rt, lexeme op){
    void * tmp = rv;
    char * result = NULL;

    bool delCast = (rt != lx_STRING && rt != lx_CHAR);

    if (delCast)
        tmp = castTo(rv, rt, lx_STRING);

    if (tmp == NULL){
        //TODO throw exception
        return lv;
    }

    size_t lLen = strlen((char *) lv);
    size_t rLen = strlen((char *) tmp);

    switch(op){
        case lx_ADD:
            result = malloc(lLen + rLen + 1);
            if (result == NULL){
                //throw exception
                return lv;
            }

            strncpy(result, lv, lLen);
            strncpy(result+lLen, tmp, rLen);
            result[lLen + rLen] = 0;
        break;
        case lx_SUB:

        break;
        case lx_DIV:

        break;
        case lx_MULT:

        break;
        case lx_MOD:

        break;
        case lx_POW:

        break;
        default:break;
    }

    if (delCast)
        free(tmp);

    return createToken(false, lx_STRING, result);
}

int registerString(type_reg * type_registry){

    int fail = 0;

    fail += registerType("string", __constructor, __destructor, __copy_constructor);

    fail += assignMath(&type_registry->slots[type_registry->registered_types-1], math_string);

    return fail;
}