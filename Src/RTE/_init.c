#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "globals.h"

NodeRegistry * _nodeReg;
Config * _config;

void _initNodeReg(){
    
    _nodeReg = malloc(sizeof(NodeRegistry));
    _nodeReg->registry = malloc(sizeof(Node *) * _config->maxNodes);
    _nodeReg->size = 0;
}