#include <stdlib.h>

#include "stack.h"

//Factories

Stack * createStack(Module * module){
    Stack * stack = malloc(sizeof(Stack));
    
    stack->owner = module;
    
    stack->baseFrame = createFrame(stack, module, 0);
    stack->framePointer = stack->baseFrame;
    stack->frameHeight = 1;

    return stack;
}

//Used during execution when a new frame is declared with {}
Frame * createFrame(Stack * stack, Module * module, Frame * parent){
    Frame * frame = malloc(sizeof(Frame));
    
    frame->SOURCE = module;
    frame->LAST_RESULT = 0;
    frame->LR_TYPE = 0;
    frame->_instructions = 0;
    frame->_instructionPointer = 0;

    frame->callee = 0;
    frame->caller = 0;

    if (parent){
        frame->caller = parent;
        parent->callee = frame;
    }

    stack->framePointer = frame;
    ++stack->frameHeight;

    return frame;
}

Instruction * createInstruction(unsigned meta, void * a0, T_TYPE t0, void * a1, T_TYPE t1){
    Instruction * instruction = malloc(sizeof(Instruction));
    
    instruction->meta = meta;
    instruction->argument[0]=a0;
    instruction->argument[1]=a1;
    instruction->argType[0]=t0;
    instruction->argType[1]=t1;
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


//Other

void addInstruction(Stack * stack, Instruction * inst){

    Frame * frame = stack->framePointer;

    if (frame == 0){
        return;
    }

    if (frame->_instructions == 0){
        frame->_instructions = inst;
        frame->_instructionPointer = inst;
        return;
    }

    frame->_instructionPointer->next = inst;
    frame->_instructionPointer = inst;
}

void startNewFrame(Stack * stack, Module * module){
    //Frame * frame = createFrame(stack, module);

}