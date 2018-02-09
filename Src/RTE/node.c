#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "node.h"
#include "config.h"

#include "../Parser/headers/parser.h"

#include "KNX_Console.h"

NodeRegistry    * _nodeReg;
Config          * _config;

void * _nodeProc(void * arg){

    Node * node = (Node *) arg;
    node->alive = 1;

    char history [32][256] = {0};
    int historyIndex = 0;
    char usin [256] = {0};
    int usinIndex = 0;

    do{
        char c = getKeyPress();

        switch(c){
            case 10://enter
                if (usinIndex == 0){
                    continue;
                }

                printf("\r\n");

                tokenize(usin, node->stack, node->module);
                
                usin[usinIndex] = 0;
                strncpy(history[historyIndex++], usin, 256);
                //printf("> %s\r\n", usin);
                memset(usin, '\0', 256);
                usinIndex = 0;

                if (historyIndex == 255){
                    historyIndex = 0;
                }

                

            break;

            //ARROW KEYS TODO: replace with KNX_LIB functionality
            case -126://left

            break;
            case -125://right
            break;
            case -128://up
                {
   
                }
            break;
            case -127://down

            break;

            //MISC
            case 127:
                if (usinIndex == 0)
                    continue;
                usin[--usinIndex] = 0;
                printf("%c[2K", 27);
                printf("\r%s", usin);
            break;

            default:
                usin[usinIndex++] = c;
                printf("%c", c);
        }

        if (c=='!') return 0;

    } while(node->alive);



    return 0;
}

Node * spawnNode(Node * parent, char * arg){

    //TODO module/stack mallocs with factories
    Node * n = malloc(sizeof(Node));
    n->module = createModule(0);
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