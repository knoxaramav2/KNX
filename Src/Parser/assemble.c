#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "KNX_String.h"

#include "parser.h"
#include "l_queue.h"

#include "_dbg.h"

L_QUEUE _L_QUEUE;

/*
Generate instructions by a given token set

If a new frame is declared with the {} operators,
this function will generate a new frame on the stack and
modify the stack frame pointers accordingly.

Execution will be signaled by returning by non-zero when
all nesting is completed and the stack frame pointer is 
at the origin frame

Note: Pointers to 'literals' are no longer under management
by tokens, which will be destroyed. Instruction instances
will track these pointers after this point
*/

int assemble(Stack * stack){

    if (_L_QUEUE.cntInput)
        return 1;

    int i = 0;
    for (; i < _L_QUEUE.outIdx; ++i){
        Token * t = &_L_QUEUE.output[i];
        printToken(t->data, t->type, t->precedence);
    }

    Instruction * instr = 0;
    
    int idx = 0;
    while(_L_QUEUE.outIdx > 0){
        //scan for next instruction

        for (int j = idx; j < _L_QUEUE.outIdx; ++j){
            T_TYPE type = _L_QUEUE.output[j].type &~ RAW_DATA;
            if (IS_CORE_EXEC(type)){
                if (IS_CORE_OP(type)){
                    //TODO check if unary
                    instr = createInstruction(
                        type,
                        _L_QUEUE.output[j-2].data,
                        _L_QUEUE.output[j-2].type,
                        _L_QUEUE.output[j-1].data,
                        _L_QUEUE.output[j-1].type
                    );
                }
            } else {
                continue;
            }

            if (instr){
                addInstruction(stack, instr);
                instr = 0;
            }

        }
    }

    printf("\r\n");
    _L_QUEUE.outIdx = 0;

    return 1;
}