#include <pthread.h>
#include <stdio.h>

#include "config.h"
#include "startup.h"
#include "node.h"

Config * config;

int start(){

    //initializers
    _initNodeReg();

    //start root node
    int destNodes = 0;

    Node * root = spawnNode(0, 0);
    registerNode(root);
    beginNode(root);
    pthread_join(root->_handle_t, 0);
    deregisterNode(root);
    destNodes = destroyNode(root);

    if (destNodes < 0){
        printf("ERROR KILL ROOT : %d\r\n", destNodes * -1);
        return -1;
    } else {
        printf("Collapsed nodes : %d\r\n", destNodes);
    }

    return 0;
}