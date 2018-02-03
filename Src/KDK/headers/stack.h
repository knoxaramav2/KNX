#ifndef KDK_STACK
#define KDK_STACK

//holds arguments, meta info of/for function 
//determined after token decomposition
typedef struct Instruction{

    unsigned meta;
    //pointer to instruction
    void * argument;

    struct Instruction * next;

} Instruction;

//Holds function scope instructions and memory
typedef struct Frame{

    char * SOURCE;//for stack traces; name of script/node; pointed to, not copied during frame creation
    void * LAST_RESULT;

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
Instruction     * createInstruction();

int destroyStack(Stack * stack);
int destroyFrame(Frame * frame);
int destroyInstruction(Instruction * inst);

/*
    Frame calling and restoration: recursive call convention?
*/

#endif