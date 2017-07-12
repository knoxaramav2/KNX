/*
defines and registers built in data types and structures
*/

#include <stdio.h>
#include <stdlib.h>

#include "type.h"

#include "registry.h"

type_reg * type_registry;

//INTEGER

obj * c_exception(char * msg, lexeme lx){
    return createObject(msg, lx, NULL);
}

int d_excepection(obj * self){
    //if (self->msg)
        //free(self->msg);
    free(self);
    return 0;
}

/*overloads:
    name (def value 0)
    name value
*/
obj * c_int(token * data){

    if (data == NULL){
        return c_exception("Invalid Overload Exception", lx_LANG_EXCEPTION);
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
                name = castTo(getTokenValue(data), data->type, lx_STRING);
                if (name == NULL)
                    return c_exception("Invalid Overload Exception", lx_LANG_EXCEPTION);
            break;
            case 1:
                value = castTo(getTokenValue(data), data->type, lx_INT);
                if (value == NULL)
                    return c_exception("Invalid Overload Exception", lx_LANG_EXCEPTION);
            break;
            default:
                return c_exception("Invalid Overload Exception", lx_LANG_EXCEPTION);
        }
        
        data = data->right;
    }

    return createObject(name , lx_INT, value);
}

void * cc_int(void * v){
    int * val = malloc(sizeof(int));
    *val = *(int*) v;
    return val;
}

int d_int(obj * self){
    
    free(self->data);

    return 0;
}

void * c_int2double(void * orig){
    double * data = malloc(sizeof(double));
    *data = (double) *(int *) orig;
    return data;
}

void * sum_math (void * lv, void * rv, lexeme rt, lexeme word){


    int * ret = malloc(sizeof(int));
    void * tmp = NULL;
    *ret = 0;

    tmp = castTo(rv, rt, lx_INT);

    switch(word){
        case lx_ADD:
            *ret = *(int*)lv + *(int*)rv;
        break;
        default:

        break;
    }

    if (tmp != rv)
        free(tmp);

    return ret;
}

//UNSIGNED INTEGER

//LONG INTEGER

//UNSIGNED LONG INTEGER

//SHORT INTEGER

//UNSIGNED SHORT INTEGER

//FLOAT

//DOUBLE

int loadPrimitives(){

printf("Loading primitives\r\n");

int fail = 0;

fail += registerType("int", c_int, d_int, cc_int);
fail += addCaster(&type_registry->slots[type_registry->registered_types-1], lx_DOUBLE, c_int2double);
fail += assignMath(&type_registry->slots[type_registry->registered_types-1], sum_math);

return fail;

}