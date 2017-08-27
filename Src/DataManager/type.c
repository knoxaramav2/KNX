#include <stdlib.h>

#include "type.h"

//TODO remove casts: casting to be done in local type files
//or remove type casting from local files

type_reg * type_registry;

type_slot * getTypeSlot(lexeme type){
    for(int i = 0; i < type_registry->registered_types; ++i){
        if (type != type_registry->slots[i].type)
            continue;

        return &type_registry->slots[i];
    }

    return NULL;
}

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
    
    type_slot * slot = getTypeSlot(order);
    if (slot == NULL)
        return NULL;

    token * res = slot->math(upg, r, rt, word);
    if (order != lt){
        free(upg);//TODO destroy if non-primitive
    }

    return res;
}

token * setValue(token * args, lexeme op){

    args = getTokenList(args);

    if (!args || !args->right){
        //TODO throw exception
        return NULL;
    } else if (!args->isStored){
        //TODO throw exception
        return NULL;
    }
    
    type_slot * slot = getTypeSlot(args->type);

    if (slot->setter == NULL){
        //TODO throw exception
        return NULL;
    }

    void * lval = getTokenValue(args);
    void * rval = getTokenValue(args->right);

    if (args->type != args->right->type)
        rval = castTo(rval, args->right->type, args->type);

    token * ret = slot->setter(lval, rval, op);

    if (args->type != args->right->type)
        free(rval);

    return ret;
}