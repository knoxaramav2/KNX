//KDK

#include <stdio.h>

#include "type.h"

type_reg * type_registry = NULL;

void _setTypeRegistry(type_reg * reg)
{
    type_registry = reg;
    printf("Set Type Registry :%p\r\n", reg);
}

type_reg * getTypeRegistry(){
    return type_registry;
}