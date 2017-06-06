//RTE

#include <stdio.h>
#include <stdlib.h>

#include "node.h"

node * createNode()
{
    node * ret = malloc(sizeof(node));

    ret->id_index = 0;
    ret->status = ns_active;

    return ret;
}

int destroyNode(node * n)
{


    return 0;
}