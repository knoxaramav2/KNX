#ifndef KDK_NODE
#define KDK_NODE

#include "module.h"
#include "stack.h"

typedef struct Node{

    Module * module;
    Stack * stack;

} Node;

#endif