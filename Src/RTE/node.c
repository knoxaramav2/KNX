//RTE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>

#include "KNX_Hash.h"

#include "node.h"
#include "globals.h"
#include "token.h"
#include "../Executor/headers/executor.h"

#include "../Parser/headers/parser.h"

static volatile int interrupt = 1;

void intrFlag(int d)
{
    interrupt = 0;
}

node * createNode()
{
    node * ret = malloc(sizeof(node));

    ret->parent = NULL;
    ret->children = malloc(0);
    ret->numChild = 0;

    ret->id_index = 0;
    ret->status = ns_active;

    ret->local = createMemTree();
    ret->global = NULL;//TODO look up root node

    ret->buffer = createTBuffer();

    return ret;
}

int destroyNode(node * n)
{
    

    return 0;
}


void * _nodeProc(void * _self)
{

signal(SIGINT, intrFlag);

node * self = (node*) _self;
printf("Starting node %d\r\n", self->id_index);

char buffer[256];
int bindex = 0;
bool startline = true;

fflush(stdout);

do
{
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

        if (strcmp(buffer, "quit") == 0) 
            return NULL;

        //printf("%llu\r\n", FNV_1a_32(buffer));
        //continue;

        tokenize(self, buffer);

        execute(self);
        
        clearTBuffer(&self->buffer);
    }

    if (c==0xa) continue;
    buffer[bindex++] = c;
} while(self->status != ns_terminated && interrupt);

return NULL;
}