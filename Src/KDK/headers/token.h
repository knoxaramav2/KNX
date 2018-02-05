#ifndef KDK_TOKEN
#define KDK_TOKEN

#include "type.h"

#define RAW_DATA 0x8000000

typedef unsigned int T_TYPE;

typedef struct Token{

    T_TYPE type;
    void * data;

} Token;

#endif