#ifndef KDK_NODE
#define KDK_NODE

#include <pthread.h>

#include "token.h"
#include "mem.h"
//#include "module.h"

/*
implemented in RTE/node.c
*/

typedef struct HMODULE HMODULE;

typedef enum node_status{
ns_active,
ns_disabled,
ns_sleep,
ns_terminated
} node_status;

typedef struct node{

HMODULE * hModule;

struct node * parent;
struct node ** children;

int numChild;

memTree * global, * local;

tBuffer buffer;

//meta
pthread_t _handle;
int id_index;
int exit_code;

node_status status;

} node;

node * createNode();
int destroyNode(node *);
node * getRootNode();

void * _nodeProc(void *);

#endif