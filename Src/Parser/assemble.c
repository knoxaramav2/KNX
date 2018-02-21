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

    /*
    int idx = 0;
    while(_L_QUEUE.outIdx > 0){
        //scan for next instruction
        for (int j = idx; j < _L_QUEUE.outIdx; ++j){
            T_TYPE type = _L_QUEUE.output[j].type &~ RAW_DATA;
            if (IS_CORE_EXEC(type)){
                if (IS_CORE_OP(type)){
                    //TODO check if unary
                    Instruction * inst = createInstruction(
                        0,
                        _L_QUEUE.output[j-2].data,
                        _L_QUEUE.output[j-2].type,
                        _L_QUEUE.output[j-1].data,
                        _L_QUEUE.output[j-1].type
                    );
                }
            } else {
                continue;
            }
        }
    }*/

    printf("\r\n");
    _L_QUEUE.outIdx = 0;

    return 0;
}