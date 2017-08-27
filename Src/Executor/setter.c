#include <stdlib.h>

#include "token.h"
#include "type.h"

#include "setter.h"

token * runSetter(token * arg, lexeme word){

    if (!arg || !arg->right){
        //TODO return throw exception
        return NULL;
    }

    return setValue(arg, word);
}