#ifndef KDK_NODE
#define KDK_NODE

#include <pthread.h>

/*
implemented in RTE/node.c
*/

typedef enum node_status{
ns_active,
ns_disabled,
ns_sleep,
ns_terminated
} node_status;

typedef struct node{

//meta
pthread_t _handle;
int id_index;

node_status status;

} node;

node * createNode();
int destroyNode(node *);

#endif