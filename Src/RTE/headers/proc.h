#ifndef RTE_PROC
#define RTE_PROC

#include "module.h"
#include "stack.h"

//recursively execute instruction stream
int executeFrame(Module *, Stack *);

#endif