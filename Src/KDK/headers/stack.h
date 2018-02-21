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

    struct Frame * caller, * callee;

    //object * array - local memory
} Frame;

/*
    Master stack
    One per node

*/
typedef struct Stack{

    Frame * framePointer;
    Frame * baseFrame;

    Module * owner;

    int frameHeight;

} Stack;

//Factories
Stack           * createStack(Module *);
Frame           * createFrame(Stack * stack, Module *, Frame *);
Instruction     * createInstruction(unsigned, void *, T_TYPE, void *, T_TYPE);

//Deconstructors
int destroyStack(Stack * stack);
int destroyFrame(Frame * frame);
int destroyInstruction(Instruction * inst);

//Calls
void addInstruction(Stack *, Instruction *);
void startNewFrame(Stack *, Module *);

/*
    Frame calling and restoration: recursive call convention?
*/

#endif