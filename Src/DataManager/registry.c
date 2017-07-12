//DTM

#include <stdlib.h>
#include <stdio.h>

#include "KNX_Hash.h"

#include "node_reg.h"
#include "type.h"

#include "registry.h"

type_reg * type_registry;

void initTypeRegistry(){
    type_registry = malloc(sizeof(type_reg));
    
    type_registry->registered_types = 0;
}

int registerType(char * name, type_constructor cons, type_destructor dest, copy_constructor copy){

    unsigned long hash = FNV_1a_32(name);
    unsigned regCount = type_registry->registered_types;

    if (regCount + 1 == MAX_TYPE_COUNT)
        return 2;

    //check for type name collisions
    for (unsigned i = 0; i < regCount; ++i){
        if (hash == type_registry->slots[i].hash)
            return 1;
    }

    //setup next available type slot
    type_slot * slot = &type_registry->slots[regCount];
    slot->constructor = cons;
    slot->copyConstructor = copy;
    slot->destructor = dest;
    slot->hash = hash;
    slot->cast_count = 0;
    slot->type = lx_TYPE_OFFSET + regCount + 1;

    //optional
    slot->math = NULL;

    printf("Registered %s (%u)\r\n", name, regCount);

    ++type_registry->registered_types;

    return 0;
}

int addCaster(type_slot * slot, lexeme from, type_cast cast){

    slot->cast_table[slot->cast_count] = cast;
    slot->cast_map[slot->cast_count] = from;

    ++slot->cast_count;

    return 0;
}

int assignMath(type_slot * slot, type_math math){
    if (slot->math)
        return 1;
    slot->math = math;
    return 0;
}