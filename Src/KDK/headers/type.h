#ifndef KDK_TYPE
#define KDK_TYPE

#define TYPE_FAIL_REDEF
#define TYPE_FAIL_INVALID
#define TYPE_FAIL_GENERAL

#include "mem.h"
#include "token.h"

typedef obj * (*type_constructor)(token *);
typedef int (*type_destructor)(obj *);
typedef void * (*type_cast)(void *);

//TODO Make cast tables dynamic to save memory
//("Wont somebody think of the kilobytes?")
typedef struct type_slot{
    unsigned long hash;
    lexeme type;

    type_constructor constructor;
    type_destructor destructor;
    lexeme cast_map[MAX_TYPE_COUNT];
    type_cast cast_table[MAX_TYPE_COUNT];

    unsigned cast_count;
} type_slot;

typedef struct type_reg{
    unsigned registered_types;
    type_slot slots [MAX_TYPE_COUNT];
    
} type_reg;

extern type_reg * type_registry;

void _setTypeRegistry(type_reg *);
type_reg * getTypeRegistry();
int registerType (char *, type_constructor, type_destructor);
int addCaster(type_slot*, lexeme, type_cast);

obj * spawnType(lexeme, token *);
void * castTo(void*, lexeme, lexeme);


#endif