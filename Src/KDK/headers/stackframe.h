#ifndef KDK_STACKFRAME
#define KDK_STACKFRAME

#include "mem.h"

typedef struct obj obj;
typedef struct memTree memTree;

typedef struct stackFrame{
    obj * funcRef;      //refers to executable function definition
    memTree * local;    //stores arguments, vars declared within function

    struct stackFrame * next;
} stackFrame;



#endif