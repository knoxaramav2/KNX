#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "node.h"
#include "config.h"

#include "KNX_Console.h"

NodeRegistry    * _nodeReg;
Config          * _config;

void * _nodeProc(void * arg){

    Node * node = (Node *) arg;
    char usin [256] = {0};

    int i = 0;

    do{
        char c = getKeyPress();
        printf("%d %c\r\n", ++i, c);
        if (i==5) break;
    } while(1);



    return 0;
}

Node * spawnNode(Node * parent, char * arg){

    //TODO module/stack mallocs with factories
    Node * n = malloc(sizeof(Node));
    n->module = createModule();
    n->stack = createStack();
    n->children = malloc(0);
    n->childCount = 0;
    n->id = -1;
    n->_handle_t = 0;
    n->module->name = 0;

    return n;
}

int destroyNode(Node * n){

    if (n == 0){
        return 1;
    }

    //destroy all children
    int nodesDestroyed = 0;
    int children = n->childCount;
    int i = 0;
    for (; i < children; ++i){
        if (deregisterNode(n->children[i])){
            return nodesDestroyed * -1;
        }

        int recDestroyed = destroyNode(n->children[i]);
        nodesDestroyed += abs(recDestroyed);

        if (recDestroyed < 0){
            return nodesDestroyed * -1;
        }
    }

    //TODO replace with destroyers
    destroyModule(n->module);
    destroyStack(n->stack);
    free(n->children);
    free(n);

    return nodesDestroyed + 1;
}

int beginNode(Node * n){

    if (n == 0){
        return 1;
    }

    if (pthread_create(&n->_handle_t, 0, _nodeProc, n)){
        return 2;
    }

    return 0;
}

int registerNode(Node * n){

    if (_nodeReg->size >= _config->maxNodes){
        return 1;
    }

    //find available node slot
    int i = 0;
    for (; i < _config->maxNodes; ++i){
        if (_nodeReg->registry[i] == 0){
            break;
        }
    }

    //allocate id, register
    n->id = i;
    _nodeReg->registry[i] = n;

    //assign name
    n->module->name = malloc(11);
    sprintf(n->module->name, "__node_%d", i);

    return 0;
}

int deregisterNode(Node * n){

    if (n->id < 0){
        return 1;
    }

    if (n->id >= _config->maxNodes){
        return 2;
    }

    //deregister node
    _nodeReg->registry[n->id] = 0;
    --_nodeReg->size;
    n->id = -1;

    return 0;
}