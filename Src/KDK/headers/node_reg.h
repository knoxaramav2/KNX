#ifndef KDK_NODEREG
#define KDK_NODEREG

#include "config.h"

typedef struct nodereg
{
    unsigned long * idTable;
    int * usedIdIndices;
} nodereg;

nodereg * getNodeReg();
void resizeNodeRegTable();

#endif