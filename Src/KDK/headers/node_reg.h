#ifndef KDK_NODEREG
#define KDK_NODEREG

#include "stdbool.h"

#include "config.h"
#include "node.h"

typedef struct nodereg
{
    unsigned long * idTable;
    bool * usedIdIndices;//TODO remove
    node ** nodeTable;
} nodereg;

extern nodereg * node_reg;

nodereg * getNodeReg();
void resizeNodeRegTable();
int registerNode(node*, node*);



#endif