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

    printf("{%d %d}\r\n", *(int*)l, *(int*)r);

    l = castTo(l, lval->type, lx_DOUBLE);
    r = castTo(r, rval->type, lx_DOUBLE);
    
    double lv = *(double*)l;
    double rv = *(double*)r;

    double * ret = malloc(sizeof(double));

    switch(op){
        case lx_ADD: *ret = lv + rv; break;
        case lx_SUB: *ret = lv - rv; break;
        case lx_MULT:*ret = lv * rv; break;
        case lx_DIV: *ret = lv / rv; break;
        case lx_MOD: *ret = (int)lv % (int) rv; break;
        case lx_POW: *ret = pow(lv, rv); break;

        default:
        *ret = 0;
        break;
    }

    //destroy temp cast
    if (lval->type != lx_DOUBLE)
        free(l);
    if (rval->type != lx_DOUBLE)
        free(r);

    printf("RESULT (%lf %lf %u) %lf\r\n", lv, rv, CHKTYPE(op), *ret);

    return createToken(NULL, lx_DOUBLE, ret);
}