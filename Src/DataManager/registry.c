//DTM

#include <stdlib.h>

#include "registry.h"

type_reg * type_registry;

void initTypeRegistry(){
    type_registry = malloc(sizeof(type_reg));
    
    type_registry->registered_types = 0;
}