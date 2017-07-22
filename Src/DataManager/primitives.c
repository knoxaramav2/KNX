/*
defines and registers built in data types and structures
*/

/*
NOTES:

In case of exception, return c_execption("exception messege", exception_id)

*/

#include <stdio.h>
#include <stdlib.h>

#include "type.h"

#include "registry.h"

type_reg * type_registry;

t_exception * createException(char * name, char * msg){
    //t_exception * ret = malloc(sizeof(t_exception));

    return NULL;
}

//INTEGER

/*overloads:
    name (def value 0)
    name value
*/
obj * c_int(token * data){

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
                name = castTo(getTokenValue(data), data->type, lx_STRING);
                if (name == NULL)
                    ;//return createException("Invalid Overload Exception");
            break;
            case 1:
                value = castTo(getTokenValue(data), data->type, lx_INT);
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

void * sum_math_int (void * lv, void * rv, lexeme rt, lexeme word){


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

//LONG INTEGER

//UNSIGNED LONG INTEGER

//SHORT INTEGER

//UNSIGNED SHORT INTEGER

//FLOAT

//DOUBLE

//CHAR


//UCHAR


//WCHAR


//STRING


//WSTRING


//ARRAY


//LIST


//CLASS


//BYTE


//FUNCTION


//VOID


//EXCEPTION

/*overloads:
    none
    extra message
*/
obj * c_exception(token * except){
    char * val = castTo(except->info, except->type, lx_STRING);
    return createObject(val, lx_EXCEPTION, NULL);
}

int d_excepection(obj * self){

    if (self->data)
        free(self->data);
    free(self);
    return 0;
}



int loadPrimitives(){

printf("Loading primitives\r\n");

int fail = 0;

//signed integer
fail += registerType("int", c_int, d_int, cc_int);
fail += addCaster(&type_registry->slots[type_registry->registered_types-1], lx_DOUBLE, c_int2double);
fail += assignMath(&type_registry->slots[type_registry->registered_types-1], sum_math_int);

//unsigned integer
fail += registerType("uint", c_uint, d_uint, cc_uint);
fail += assignMath(&type_registry->slots[type_registry->registered_types-1], sum_math_uint);

return fail;

}