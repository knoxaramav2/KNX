#ifndef KDK_NODEREG
#define KDK_NODEREG

#include "config.h"

typedef struct nodereg
{
    unsigned long * idTable;
} nodereg;

void initNodeReg();
void resizeNodeRegTable();

#endif