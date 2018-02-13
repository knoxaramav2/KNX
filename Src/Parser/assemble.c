#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "KNX_String.h"

#include "parser.h"
#include "l_queue.h"

#include "_dbg.h"

L_QUEUE _L_QUEUE;

int assemble(){

    if (_L_QUEUE.cntInput)
        return 1;

    int i = 0;
    for (; i < _L_QUEUE.outIdx; ++i){
        Token * t = &_L_QUEUE.output[i];
        printToken(t->data, t->type, t->precedence);
    }

    printf("\r\n");
    _L_QUEUE.outIdx = 0;

    return 0;
}