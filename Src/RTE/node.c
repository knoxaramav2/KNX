//RTE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "node.h"

node * createNode()
{
    node * ret = malloc(sizeof(node));

    ret->parent = NULL;
    ret->children = malloc(0);
    ret->numChild = 0;

    ret->id_index = 0;
    ret->status = ns_active;

    return ret;
}

int destroyNode(node * n)
{


    return 0;
}


void * _nodeProc(void * _self)
{

node * self = (node*) _self;
printf("Starting node %d\r\n", self->id_index);

char buffer[256];
int bindex = 0;
bool startline = true;

fflush(stdout);

while(self->status != ns_terminated){
    if (startline){
        printf("|%d|\t", self->id_index);
        startline=false;
        fflush(stdout);
    }

    int c = getchar();
    if (c == '\r' || c == '\n'){
        startline=true;
        buffer[bindex] = 0;
        bindex=0;

        printf("%s\r\n", buffer);
        fflush(stdout);

        //TODO
    }

    buffer[bindex++] = c;
}

return NULL;
}