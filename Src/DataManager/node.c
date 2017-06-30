//Datamanager

#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "node_reg.h"
#include "mem.h"
#include "type.h"

#include "datamanager.h"

nodereg * node_reg;

nodereg * getNodeReg()
{
    return node_reg;
}

node * getRootNode()
{
    return node_reg->nodeTable[0];
}

void resizeNodeRegTable()
{
//TODO
}

int registerNode(node * regnode, node * parent)
{
    //search for valid id slot
    for (unsigned i = 0; i < config->maxNodes; ++i)
    {
        if (node_reg->nodeTable[i] == NULL){
            node_reg->nodeTable[i] = regnode;
            regnode->id_index = i;

            //couple to parent
            regnode->parent = parent;
            if (parent != NULL){
                parent->children = realloc(parent->children, parent->numChild+1);
                parent->children[parent->numChild] = regnode;
                ++parent->numChild;
            }

            return 0;
        }
    }

    printf("Failed to register node\r\n");
    return -1;
}

int unregisterNode(node* unreg){
    node_reg->nodeTable[unreg->id_index] = NULL;
    return 0;
}