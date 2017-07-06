#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "type.h"
#include "token.h"

#include "mathx.h"

token * math(token*lval, token*rval, lexeme op){

    double * lv, * rv;

    lv = lval->type == lx_DOUBLE ?
        (double *) lval->info :
        (double *) castTo(lval->info, lval->type, lx_DOUBLE);

    rv = rval->type == lx_DOUBLE ?
        (double *) rval->info :
        (double *) castTo(rval->info, rval->type, lx_DOUBLE);

    //sscanf(lval->raw, "%lf", &lv);
    //sscanf(rval->raw, "%lf", &rv);

    double * ret = malloc(sizeof(double));

    switch(op){

        case lx_ADD: *ret = *lv + *rv; break;
        case lx_SUB: *ret = *lv - *rv; break;
        case lx_MULT: *ret = *lv * *rv; break;
        case lx_DIV: *ret = *lv / *rv; break;
        case lx_MOD: *ret = (int)*lv % (int) *rv; break;
        case lx_POW: *ret = pow(*lv, *rv); break;

        default:
        return NULL;
        break;
    }

    printf("RESULT (%lf %lf %u) %lf\r\n", *lv, *lv, CHKTYPE(op), *ret);

    //clean cast data
    if (lval->info != lv)
        free(lv);
    if(rval->info != rv)
        free(rv);

    return createToken(NULL, lx_DOUBLE, ret);
}