#include <stdlib.h>

#include "token.h"
#include "type.h"

#include "setter.h"

token * runSetter(token * arg, lexeme word){

    if (!arg || !arg->right){
        //TODO return throw exception
        return NULL;
    }

    lexeme ltype, rtype;
    ltype = arg->type;
    rtype = arg->right->type;

    void * dat = castTo(arg->right->info, rtype, ltype);
    if (!dat){
        //TODO return throw exception
        return NULL;
    }

    switch(word){
        case lx_SET:

        break;
        case lx_SET_ADD:

        break;
        case lx_SET_SUB:

        break;
        case lx_SET_MULT:

        break;
        case lx_SET_DIV:

        break;
        case lx_SET_AND:

        break;
        case lx_SET_OR:

        break;
        case lx_SET_NOT:

        break;
        case lx_SET_POST_INC:

        break;
        case lx_SET_POST_DEC:

        break;
        case lx_SET_PRE_INC:

        break;
        case lx_SET_PRE_DEC:

        break;
        case lx_SET_TERN:

        break;
        default:

        break;
    }

    arg->info = dat;

    if (rtype != ltype)
        free(dat);

    return arg;
}