#include <stdlib.h>

#include "stack.h"

//Factories

Stack * createStack(){
    Stack * stack = malloc(sizeof(Stack));
    
    stack->_frames = 0;
    stack->frameAlloc = 0;
    stack->frameCount = 0;

    return stack;
}

Frame * createFrame(Module * module){
    Frame * frame = malloc(sizeof(Frame));
    
    frame->SOURCE = module;
    frame->LAST_RESULT = 0;
    frame->LR_TYPE = 0;
    frame->_instructions = 0;
    frame->_instructionPointer = 0;

    return frame;
}

Instruction * createInstruction(){
    Instruction * instruction = malloc(sizeof(Instruction));
    
    instruction->meta = 0;
    instruction->argument = 0;
    instruction->next = 0;

    return instruction;
}


//Destroyers

int destroyStack(Stack * stack){

    return 0;
}

int destroyFrame(Frame * frame){

    return 0;
}

int destroyInstruction(Instruction * inst){

    return 0;
}
