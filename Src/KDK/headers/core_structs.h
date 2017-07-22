//defines complex structures for core types

#ifndef KDK_CORE_STRUCT
#define KDK_CORE_STRUCT

#include "lexeme.h"

//holds array of a single type of element
typedef struct t_array{
    unsigned size;
    obj * info;
} t_array;

//differed from comma list by isStored flag,
//similar to liter vs. symbolic ints, strings, ect.
//holds array of different 
typedef struct t_list{
    unsigned size;
    obj * info;
} t_list;

//similar to a list, able to 
//inherit other classes
typedef struct t_class{
    struct t_class * super;

    unsigned elements;
    obj * info;
} t_class;

//TODO specialized interface struct?

//accepts a list of arguments to check against a callers submitted list
//while, due to name-hash searches, same-name overloads for differing
//argument lists is not possible, implied argument overloads are
//ig. int(STRING) and int(STRING, NUMERIC) are valid
//in the former example, the 'int' function decides to use a default
//value if one is not explicitly provided
//other functions may behave differently based on individual implementation
typedef struct t_function{
    lexeme args [32];
    unsigned short argCount;

    lexeme retType;

    token ** method;

} t_function;

//generic type, flagged by isStored
//non isStored have only NULL value
//value assumed NULL when 'type' is lx_VOID
typedef struct t_void{
    lexeme type;
    void * info;
} t_void;

//for special error reporting
//may invoked by setting as value of 'throw' token
typedef struct t_exception{
    //ERRCODE err;
    char * msg;
} t_exception;

#endif