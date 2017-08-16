#ifndef DATMAN_REG
#define DATMAN_REG

#include "type.h"
#include "function.h"

extern type_reg * type_registry;

void initTypeRegistry();
void initKwRegistry();

#endif