#ifndef KDK_STACK
#define KDK_STACK

#include "type.h"
#include "module.h"

//holds arguments, meta info of/for function 
//determined after token decomposition
typedef struct Instruction{

    unsigned meta;
    //pointer to instruction
    void * argument [2];
    unsigned argType [2];

    struct Instruction * next;

} Instruction;

//Holds function scope instructions and memory
typedef struct Frame{

    Module * SOURCE;//for stack traces; name of script/node; pointed to, not copied during frame creation
    void * LAST_RESULT;
    T_TYPE LR_TYPE;//last result type

    Instruction * _instructions;
    Instruction * _instructionPointer;

    //object * array - local memory
} Frame;

/*
    Master stack
    One per node

*/
typedef struct Stack{

    Frame * _frames;

    int frameAlloc; //total number of frames currently allocated for
    int frameCount; //current number of used framesD

} Stack;

//Factories
Stack           * createStack();
Frame           * createFrame();
Instruction     * createInstruction(unsigned, void *, T_TYPE, void *, T_TYPE);

int destroyStack(Stack * stack);
int destroyFrame(Frame * frame);
int destroyInstruction(Instruction * inst);

/*
    Frame calling and restoration: recursive call convention?
*/

#endif