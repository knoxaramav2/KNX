#ifndef KDK_MEM
#define KDK_MEM

typedef enum treeMode{
    tm_binary,
    tm_splay
} treeMode;

typedef struct obj
{
    unsigned long hash;
    void * data;
    unsigned type;

    //mem tree associations
    struct obj * parent;
    struct obj * left;
    struct obj * right;
} obj;

typedef struct memTree{
    treeMode mode;
    obj * root;
} memTree;

memTree * createMemTree();
int destroyMemTree(memTree *);

obj * createObject(char *, unsigned);
int destroyObject(obj*);

#endif