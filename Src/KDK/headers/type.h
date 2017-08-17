#ifndef KDK_TYPE
#define KDK_TYPE

#define TYPE_FAIL_REDEF
#define TYPE_FAIL_INVALID
#define TYPE_FAIL_GENERAL

#include "mem.h"
#include "token.h"
#include "core_structs.h"

//required definitions for compiled data types
typedef obj * (*type_constructor)(token *);
typedef int (*type_destructor)(obj *);
typedef void * (*copy_constructor)(void *);
typedef void * (*type_set)(void *, lexeme);

//additional/optional
typedef void * (*type_cast)(void *);
typedef token * (*type_math)(void *, void*, lexeme, lexeme);

lexeme getPriorityType(lexeme, lexeme);

//TODO Make cast tables dynamic to save memory
//("Wont somebody think of the kilobytes?")
typedef struct type_slot{
    char * name;
    unsigned long hash;
    lexeme type;

    type_constructor constructor;
    copy_constructor copyConstructor;
    type_destructor destructor;
    lexeme cast_map[MAX_TYPE_COUNT];
    type_cast cast_table[MAX_TYPE_COUNT];

    type_math math;

    unsigned cast_count;
} type_slot;

typedef struct type_reg{
    unsigned registered_types;
    type_slot slots [MAX_TYPE_COUNT];
    
} type_reg;

//extern type_reg * type_registry;

void _setTypeRegistry(type_reg *);
type_reg * getTypeRegistry();
int registerType (char *, type_constructor, type_destructor, copy_constructor);
int addCaster(type_slot*, lexeme, type_cast);
int assignMath(type_slot*, type_math);

obj * spawnType(lexeme, token *);
void * castTo(void*, lexeme, lexeme);
void * copyValue(void*, lexeme);
token * typeMath(void *, void *, lexeme, lexeme, lexeme);

char * getTypeName(lexeme);

//exposed exception constructor
t_exception * createException(char * name, char * msg);
int throwException(t_exception *);

#endif