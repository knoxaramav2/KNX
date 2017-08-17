//KDK

#include <stdio.h>

#include "type.h"
#include "function.h"

type_reg * type_registry = NULL;
func_reg * kw_registry = NULL;


void _setKeywordRegistry(func_reg * reg){
    kw_registry = reg;
    printf("Set Func Registry :%p\r\n", reg);
}

func_reg * getKeywordRegistry(){
    return kw_registry;
}

void _setTypeRegistry(type_reg * reg)
{
    type_registry = reg;
    printf("Set Type Registry :%p\r\n", reg);
}

type_reg * getTypeRegistry(){
    return type_registry;
}