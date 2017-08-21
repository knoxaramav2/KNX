#ifndef KDK_MODULE
#define KDK_MODULE

#include "token.h"
#include "mem.h"

/*
Contains information about the scope owner of statement issuing bodies

Modules include:
    node
    loaded/imported scripts
    binary modules

memory provided through common interface
search/edit methods selected by memTree mode

allows for modular scopes

scripts/ext libraries stored in owner node memory tree
symbol lookup continues 
*/

//module handle
typedef struct HMODULE{
    memTree * memory;
    node * owner;

    char * id;

    tBuffer buffer;
} HMODULE;

HMODULE * createHModule(char *, node *, treeMode);

HMODULE * getRootHandle();

//setup procedures
void setRootHandle(HMODULE *);

#endif