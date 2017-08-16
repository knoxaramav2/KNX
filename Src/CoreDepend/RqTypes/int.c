#include <stdlib.h>

#include "KNX_Hash.h"

#include "TypeDecl.h"

static obj * __constructor(token * data){

    if (data == NULL){
        //return c_exception("Invalid Overload Exception", lx_LANG_EXCEPTION);
    }

    //convert list item token to argument string
    if (data->type == lx_LIST)
        data = getTokenValue(data);

    char * name = NULL;
    int * value = malloc(sizeof (int));
    *value = 0;

    for (int cdx = 0; data; ++cdx){
        switch (cdx){
            case 0:
                name = castTo(data->info, data->type, lx_STRING);
                if (name == NULL)
                    ;//return createException("Invalid Overload Exception");
            break;
            case 1:
                value = castTo(data->info, data->type, lx_INT);
                if (value == NULL)
                    ;//return createException("Invalid Overload Exception");
            break;
            default:
                ;//return createException("Invalid Overload Exception");
        }
        
        data = data->right;
    }

    return createObject(name , lx_INT, value);
}

static void * __copy_constructor(void * v){
    int * val = malloc(sizeof(int));
    *val = *(int*) v;
    return val;
}

static int __destructor(obj * self){
    
    free(self->data);

    return 0;
}

void * c_int2double(void * orig){
    double * data = malloc(sizeof(double));
    *data = (double) *(int *) orig;
    return data;
}

void * sum_math_int (void * lv, void * rv, lexeme rt, lexeme word){


    int * ret = malloc(sizeof(int));
    void * tmp = NULL;
    *ret = 0;

    tmp = castTo(rv, rt, lx_INT);

    switch(word){
        case lx_ADD:
            *ret = *(int*)lv + *(int*)rv;
        break;
        case lx_SUB:
            *ret = *(int*)lv - *(int*)rv;
        break;
        case lx_DIV:
            *ret = *(int*)lv / *(int*)rv;
        break;
        case lx_MULT:
            *ret = *(int*)lv * *(int*)rv;
        break;
        case lx_MOD:
            *ret = *(int*)lv % *(int*)rv;
        break;
        case lx_POW:
            *ret = *(int*)lv ^ *(int*)rv;
        break;
        /*case lx_ROOT:
            *ret = *(int*)lv + *(int*)rv;
        break;*/
        default:

        break;
    }

    if (tmp != rv)
        free(tmp);

    return ret;
}

int registerInt(type_reg * type_registry){

    int fail = 0;

    fail += registerType("int", __constructor, __destructor, __copy_constructor);
    fail += addCaster(&type_registry->slots[type_registry->registered_types-1], lx_DOUBLE, c_int2double);
    fail += assignMath(&type_registry->slots[type_registry->registered_types-1], sum_math_int);

    return fail;
};