#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "type.h"
#include "token.h"

#include "mathx.h"

token * math(token*lval, token*rval, lexeme op){

    if (lval->type != lx_DOUBLE){
        double * tmp = castTo(lval->info, lval->type, lx_DOUBLE);
        free(lval->info);
        lval->info = tmp;
        lval->type = lx_DOUBLE;
    }

    if (rval->type != lx_DOUBLE){
        double * tmp = castTo(rval->info, rval->type, lx_DOUBLE);
        free(rval->info);
        rval->info = tmp;
        rval->type = lx_DOUBLE;
    }

    double lv = *(double*)lval->info;
    double rv = *(double*)rval->info;

    double * ret = malloc(sizeof(double));

    switch(op){
        case lx_ADD: *ret = lv + rv; break;
        case lx_SUB: *ret = lv - rv; break;
        case lx_MULT: *ret = lv * rv; break;
        case lx_DIV: *ret = lv / rv; break;
        case lx_MOD: *ret = (int)lv % (int) rv; break;
        case lx_POW: *ret = pow(lv, rv); break;

        default:
        *ret = 0;
        break;
    }

    printf("RESULT (%lf %lf %u) %lf\r\n", lv, rv, CHKTYPE(op), *ret);

    return createToken(NULL, lx_DOUBLE, ret);
}