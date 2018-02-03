#include <stdlib.h>

#include "stack.h"

//Factories

Stack * createStack(){
    Stack * stack = malloc(sizeof(Stack));

    return stack;
}

Frame * createFrame(){
    Frame * frame = malloc(sizeof(Frame));

    return frame;
}

Instruction * createInstruction(){
    Instruction * instruction = malloc(sizeof(Instruction));

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
