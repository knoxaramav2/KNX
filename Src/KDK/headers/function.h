#ifndef KDK_FUNCTION
#define KDK_FUNCTION

#include "node.h"
#include "mem.h"

typedef obj * (*function)(node *, token *);

typedef struct func_slot{
    unsigned hash;
    function func;
} func_slot;

typedef struct func_reg{
    unsigned registered_functions;
    unsigned slotCount;
    func_slot * slots;
} func_reg;

int registerFunction(func_reg *, function, char *);
obj * invokeFunction(func_reg *, node*, token *, unsigned long);
obj * invokeKeyword(node*, token *, lexeme);//slightly more efficient

#endif