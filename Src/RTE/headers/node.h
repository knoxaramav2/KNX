#ifndef RTE_NODE
#define RTE_NODE

#include "pthread.h"

#include "module.h"
#include "stack.h"

typedef struct Node{

    Module * module;
    Stack * stack;

    struct Node ** children;
    size_t childCount;

    int id;
    int alive;

    pthread_t _handle_t;

} Node;

Node * spawnNode(Node * parent, char * arg);
int destroyNode(Node * n);
void * _nodeProc(void * arg);
int beginNode(Node * n);

typedef struct NodeRegistry{

    Node ** registry;

    int size;

} NodeRegistry;

extern NodeRegistry * _nodeReg;

void _initNodeReg();

int registerNode(Node * n);
int deregisterNode(Node * n);

#endif