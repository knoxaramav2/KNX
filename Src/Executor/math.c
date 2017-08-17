#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "type.h"
#include "token.h"
#include "objUtil.h"

#include "mathx.h"

token * math(token*lval, token*rval, lexeme op){

    void * l, * r;

    l = getTokenValue(lval);
    r = getTokenValue(rval);
    
    token * ret = typeMath(l, r, lval->type, rval->type, op);

    //printf("RESULT %d\r\n", *(int*) ret);

    return ret;
}
