#include <stdio.h>
#include <stdlib.h>

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

    char * name = NULL;
    int * value = malloc(sizeof (int));
    *value = 0;

    if (data->type == lx_STRING || data->type == lx_CHAR) {
        name = data->info;
    } else {
        return c_exception("Invalid Overload Exception", lx_LANG_EXCEPTION);
    }

    if (data->right){
        if (data->right->type == lx_INT)
            value = data->right->info;
    }

    createObject(name , lx_INT, value);

    return NULL;
}

int d_int(obj * self){
    
    free(self->data);

    return 0;
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

registerType("int", c_int, d_int);



return fail;

}