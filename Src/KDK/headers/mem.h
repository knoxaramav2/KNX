#ifndef KDK_MEM
#define KDK_MEM

#include <stdbool.h>

#include "lexeme.h"

typedef enum treeMode{
    tm_binary,
    tm_splay
} treeMode;

typedef struct obj
{
    unsigned long hash;
    void * data;
    unsigned type;
} obj;

typedef struct leaf{
    obj * data;

//mem tree associations
    struct leaf * parent;
    struct leaf * left;
    struct leaf * right;
} leaf;

typedef struct memTree{
    treeMode mode;
    leaf * root;
} memTree;

memTree * createMemTree();
int destroyMemTree(memTree *);

obj * memSearch(char *);
obj * memLookup(unsigned long);
obj * memUpdate(obj *);
bool memDelete(obj *);


obj * createObject(memTree*, char *, unsigned, void *);
int destroyObject(memTree*, char *);


//interfaces

obj * (*_declare_type)();

#endif