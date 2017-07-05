#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "token.h"

#include "mathx.h"

token * math(token*lval, token*rval, lexeme op){

    double lv, rv;

    lv = *((double *)lval->info);
    rv = *((double *)rval->info);

    //sscanf(lval->raw, "%lf", &lv);
    //sscanf(rval->raw, "%lf", &rv);

    double * ret = malloc(sizeof(double));

    switch(op){

        case lx_ADD: *ret = lv + rv; break;
        case lx_SUB: *ret = lv - rv; break;
        case lx_MULT: *ret = lv * rv; break;
        case lx_DIV: *ret = lv / rv; break;
        case lx_MOD: *ret = (int)lv % (int) rv; break;
        case lx_POW: *ret = pow(lv, rv); break;

        default:
        return NULL;
        break;
    }

    printf("RESULT (%lf %lf %u) %lf\r\n", *((double *)lval->info), *((double *)rval->info), CHKTYPE(op), *ret);

    return createToken(NULL, lx_DOUBLE, ret);
}