#ifndef KDK_FUNCTION
#define KDK_FUNCTION

#include "module.h"

#include "node.h"
#include "module.h"
#include "mem.h"

typedef obj * (*function)(HMODULE *, token *);

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
obj * invokeFunction(func_reg *, HMODULE *, token *, unsigned long);
obj * invokeKeyword(HMODULE *, token *, lexeme);//slightly more efficient

func_reg * getKeywordRegistry();
void _setKeywordRegistry(func_reg *);

#endif