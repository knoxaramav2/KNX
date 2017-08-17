#include <stdlib.h>

#include "type.h"

type_reg * type_registry;

obj * spawnType(lexeme target, token * args){

    if (isDKeyword(target)){
        return type_registry->slots[getKwDeclIndex(target)].constructor(args);
    }

    for(int i = getDeclIndex(lx_EXCEPTION) + 1; i < type_registry->registered_types; ++i){
        if (target != type_registry->slots[i].type)
            continue;
        return type_registry->slots[i].constructor(args);
    }
    
    return NULL;
}

void * castTo(void * src, lexeme from, lexeme to){
    if (!src || (from == to))
        return copyValue(src, from);

    for(int i = 0; i < type_registry->registered_types; ++i){
        if (from != type_registry->slots[i].type)
            continue;
        
        for (int j = 0; j < type_registry->slots[i].cast_count; ++j){
            if (to == type_registry->slots[i].cast_map[j]){
                return type_registry->slots[i].cast_table[j](src);
            }
        }

        break;
    }

    return NULL;
}

void * copyValue(void * src, lexeme type){

    if (!src) return NULL;

    for(int i = 0; i < type_registry->registered_types; ++i){
        if (type != type_registry->slots[i].type)
            continue;

        return type_registry->slots[i].copyConstructor(src);
    }

    return NULL;
}

token * typeMath(void * l, void * r, lexeme lt, lexeme rt, lexeme word){
    if (!l || !r)
        return NULL;

    //determine priority type and upgrade
    lexeme order = selPriorityOp(lt, rt);
    void * upg = l;
    if (order != lt){
        upg = castTo(l, lt, order);
    }
    
    for(int i = 0; i < type_registry->registered_types; ++i){
        if (order != type_registry->slots[i].type)
            continue;
        token * res = type_registry->slots[i].math(upg, r, rt, word);
        if (order != lt){
            free(upg);//TODO destroy if non-primitive
        }
        return res;
    }

    return NULL;
}