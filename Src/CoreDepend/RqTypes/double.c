#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "TypeDecl.h"

static obj * __constructor(token * data){

    if (data == NULL){

    }

    data = getTokenList(data);

    char * name = NULL;
    double * value = malloc(sizeof(double));
    *value = 0;

    for (int indx = 0; data; ++indx){
        switch (indx){
            case 0:
                name = castTo(data->info, data->type, lx_STRING);
                if (name == NULL)
                    ;//return createException("Invalid Overload Exception");
            break;
            case 1:
                value = castTo(data->info, data->type, lx_DOUBLE);
                if (value == NULL)
                    ;//return createException("Invalid Overload Exception");
            break;
            default:
                ;//return createException("Invalid Overload Exception");
        }
        
        data = data->right;
    }

    return createObject(name , lx_DOUBLE, value);
}

static void * __copy_constructor(void * v){
    double * val = malloc(sizeof(double));
    *val = *(double *) v;
    return val;
}

static int __destructor(obj * self){

    free(self->data);

    return 0;
}
//TODO allow adjustment
void * c_double2string(void * orig){
    char * data = malloc(11);
    sprintf(data, "%lf", *(double *) orig);
    return data;
}

token * math_double (void * lv, void * rv, lexeme rt, lexeme op){


    double * ret = malloc(sizeof(double));
    void * tmp = NULL;
    *ret = 0;

    tmp = castTo(rv, rt, lx_DOUBLE);

    switch(op){
        case lx_ADD:
            *ret = *(double*)lv + *(double*)tmp;
        break;
        case lx_SUB:
            *ret = *(double*)lv - *(double*)tmp;
        break;
        case lx_DIV:
            *ret = *(double*)lv / *(double*)tmp;
        break;
        case lx_MULT:
            *ret = *(double*)lv * *(double*)tmp;
        break;
        case lx_MOD:
            *ret = fmod(*(double*)lv, *(double*)tmp);
        break;
        case lx_POW:
            *ret = pow(*(double*)lv, *(double*)tmp);
        break;
        /*case lx_ROOT:
            *ret = *(int*)lv + *(int*)rv;
        break;*/
        default:

        break;
    }

    if (tmp != rv)
        free(tmp);

    return createToken(false, lx_DOUBLE, ret);
}

int registerDouble(type_reg * type_registry){

    int fail = 0;

    fail += registerType("double", __constructor, __destructor, __copy_constructor);

    fail += addCaster(&type_registry->slots[type_registry->registered_types-1], lx_STRING, c_double2string);

    fail += assignMath(&type_registry->slots[type_registry->registered_types-1], math_double);


    return fail;
}