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
    lexeme type;
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

obj * memSearch(memTree *, char *);
obj * memLookup(memTree *, unsigned long, char*);
obj * memUpdate(obj *);
bool memDelete(obj *);


int appendObject(memTree*, obj *);
obj * createObject(char *, lexeme, void *);
int destroyObject(memTree*, char *);


//interfaces

obj * (*_declare_type)();

#endif