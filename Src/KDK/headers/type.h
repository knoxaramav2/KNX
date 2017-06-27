#ifndef KDK_TYPE
#define KDK_TYPE

#include "mem.h"

typedef struct type_reg{
    unsigned registered_types;
} type_reg;


extern type_reg * type_registry;

void _setTypeRegistry(type_reg *);
type_reg * getTypeRegistry();


#endif