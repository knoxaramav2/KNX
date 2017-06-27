#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "token.h"

#include "mathx.h"

token * math(token*lval, token*rval, lexeme op){

    double lv, rv;

    sscanf(lval->raw, "%lf", &lv);
    sscanf(rval->raw, "%lf", &rv);

    double * ret = malloc(sizeof(double));

    switch(op){

        case lx_ADD: *ret = lv + rv; break;
        case lx_SUB: *ret = lv + rv; break;
        case lx_MULT: *ret = lv * rv; break;
        case lx_DIV: *ret = lv / rv; break;
        case lx_MOD: *ret = (int)lv % (int) rv; break;
        case lx_POW: *ret = pow(lv, rv); break;

        default:
        return NULL;
        break;
    }

    char * rstr = malloc(128);
    snprintf(rstr, 128, "%lf", *ret);

    printf("RESULT %lf\r\n", *ret);

    return createToken(rstr, lx_DOUBLE, ret);
}