//DTM

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "KNX_Hash.h"

#include "debug.h"
#include "node_reg.h"
#include "type.h"
#include "module.h"

#include "registry.h"

type_reg * type_registry;
func_reg * keyword_registry;

#define DEFAULT_FUNC_SLOTS  32

//KEYWORD REGISTRY

void initKwRegistry(){

    keyword_registry = malloc(sizeof(func_reg));

    keyword_registry->registered_functions = 0;
    keyword_registry->slotCount = DEFAULT_FUNC_SLOTS;
    keyword_registry->slots = malloc(sizeof(func_slot) * DEFAULT_FUNC_SLOTS);

    _setKeywordRegistry(keyword_registry);
}

int registerFunction(func_reg * reg, function func, char * name){

    //allow dynamic shrinking
    if (reg->registered_functions == reg->slotCount){
        func_slot * tmp = reg->slots;
        tmp = realloc(reg->slots, sizeof(func_slot) * reg->slotCount * 2);
        
        if (!tmp) return 0;

        reg->slots = tmp;
        reg->slotCount *= 2;
    }

    //TODO check for symbol collision
    func_slot * slot = &reg->slots[reg->registered_functions];
    slot->func = func;
    slot->hash = FNV_1a_32(name);
    
    ++reg->registered_functions;

    dprint("Registered function %s\r\n", name);

    return 0;
}

obj * invokeFunction(func_reg * reg, HMODULE * module, token * arg, unsigned long hash){

    for (unsigned x = 0; x < reg->registered_functions; ++x){
        if (hash == reg->slots[x].hash){
            return reg->slots[x].func(module, arg);
        }
    }

    return NULL;
}

obj * invokeKeyword(HMODULE * module, token * arg, lexeme word){
    int select = word-(lx_CNT+1);
    return keyword_registry->slots[select].func(module, arg);
}

func_reg * getKeywordRegistry(){
    return keyword_registry;
}

//TYPE REGISTRY

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
    //optional fields
    slot->math=NULL;
    slot->setter=NULL;

    size_t nmLen = strlen(name) + 1;
    slot->name = malloc(nmLen);
    strncpy(slot->name, name, nmLen);

    //optional
    slot->math = NULL;

    dprint("Registered %s (%u)\r\n", name, regCount);

    ++type_registry->registered_types;

    return 0;
}

int addCaster(type_slot * slot, lexeme to, type_cast cast){

    slot->cast_table[slot->cast_count] = cast;
    slot->cast_map[slot->cast_count] = to;

    ++slot->cast_count;

    return 0;
}

int assignMath(type_slot * slot, type_math math){
    if (slot->math)
        return 1;
    slot->math = math;
    return 0;
}

int assignSetter(type_slot* slot, type_set setter){
    
    if (slot->setter)
        return 1;
    
    slot->setter = setter;
    
    return 0;
}

char * getTypeName(lexeme type){
    for (unsigned x = 0; x < type_registry->registered_types; ++x){
        if (type_registry->slots[x].type == type){
            char * typeName = type_registry->slots[x].name;
            size_t len = strlen(typeName) +1;
            char * ret = malloc(len);
            strncpy(ret, typeName, len);
            return ret;
        }
    }

    return 0;
}