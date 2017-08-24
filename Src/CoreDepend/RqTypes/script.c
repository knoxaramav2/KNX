#include <stdlib.h>

#include "TypeDecl.h"
#include "script.h"

//args: [script name] [token stream]
static obj * __constructor(token * data){

    if (data == NULL){
        //return c_exception("Invalid Overload Exception", lx_LANG_EXCEPTION);
    }
    
    data = getTokenList(data);

    char * name = NULL;
    script * value = malloc(sizeof(script));

    for (int indx = 0; data; ++indx){
        switch (indx){
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

    return createObject(name, lx_SCRIPT, value);
}

static void * __copy_constructor(void * v){

    return NULL;
}

static int __destructor(obj * self){

    return 0;
}

int registerScript(type_reg * type_registery){

    int fail = 0;

    fail += registerType("script", __constructor, __destructor, __copy_constructor);

    return fail;
}