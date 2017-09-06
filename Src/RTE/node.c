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

#include "../CoreDepend/RqKw/headers/KwDecl.h"
#include "../Executor/headers/executor.h"
#include "../Parser/headers/parser.h"

static volatile int interrupt = 1;

nodeArg * createNodeArg(){
    nodeArg * ret = malloc(sizeof(nodeArg));
    
    ret->n=NULL;
    ret->script=NULL;

    return ret;
}

void destroyNodeArg(nodeArg * arg){
    free(arg);
}

void intrFlag(int d)
{
    interrupt = 0;
}

node * createNode()
{
    node * ret = malloc(sizeof(node));
    node * root = getRootNode();

    ret->parent = NULL;
    ret->children = malloc(0);
    ret->numChild = 0;

    ret->id_index = 0;
    ret->exit_code = 0;
    ret->status = ns_active;

    ret->local = createMemTree();
    ret->buffer = createTBuffer();

    ret->hModule = NULL;

    if (root==NULL){
        ret->global = ret->local;
    } else {
        ret->global = root->global;
    }

    return ret;
}

int destroyNode(node * n)
{
    if (n->id_index == 0)
        destroyMemTree(n->global);
    else
        destroyMemTree(n->local);

    return 0;
}

int sanitize(int c){

    //get arrow
    if (c == 27){
        getchar();//eat 91
        char arr = getchar();

        switch(arr){
            case 65: break;//up
            case 66: break;//down
            case 67: break;//right
            case 68: break;//left
        }
    }

    return c;
}

void * _nodeProc(void * _self)
{

nodeArg * arg = _self;

signal(SIGINT, intrFlag);

node * self = arg->n;
printf("Starting node %d\r\n", self->id_index);

char buffer[256];
int bindex = 0;
bool startline = true;
bool startStack = true;

fflush(stdout);

if (arg->script){
    char * com = malloc(7 + strlen(arg->script));
    sprintf(com, "run '%s'", arg->script);

    self->buffer.stackBuffer = malloc(sizeof(tStackItem));
    self->buffer.stackBuffer->line = com;
    self->buffer.stackBuffer->next = NULL;
}

do
{
    if (self->buffer.stackBuffer){

        if (startStack){
            startStack = false;
            self->buffer.stackIndex = self->buffer.stackBuffer;
        }

        if (self->buffer.stackIndex == NULL){
            self->buffer.stackBuffer = NULL;
            self->buffer.stackIndex = NULL;
            startStack = true;
            continue;
        }

        tokenize(self->hModule, self->buffer.stackIndex->line);
        execute(self->hModule);
        clearTBuffer(&self->buffer);
        
        tStackItem * tmp = self->buffer.stackIndex->next;
        free(self->buffer.stackIndex->line);
        free(self->buffer.stackIndex);

        self->buffer.stackIndex = tmp;
        continue;
    }

    if (startline){
        printf("|%d|\t", self->id_index);
        startline=false;
        fflush(stdout);
    }

    int c = getchar();
    c = sanitize(c);
    if (c == '\r' || c == '\n'){
        if (bindex == 0)
            continue;

        startline=true;
        buffer[bindex] = 0;
        bindex=0;

        if (strcmp(buffer, "quitx") == 0) 
            return NULL;

        tokenize(self->hModule, buffer);
        execute(self->hModule);
        clearTBuffer(&self->buffer);
    }

    if (c==0xa) continue;
    buffer[bindex++] = c;
} while(self->status != ns_terminated && interrupt);

destroyNodeArg(arg);
destroyNode(self);

return NULL;
}