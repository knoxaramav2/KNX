#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "token.h"
#include "dat_tables.h"
#include "config.h"
#include "debug.h"

#define BUFFER_SIZE 54

Config * _config;

char ** log_buffer;
int log_bindex;

const char * dlog_path = "/";

void initDbgGlb()
{
    _config = getConfig();

    log_bindex=0;

    log_buffer = malloc(sizeof(char*)*BUFFER_SIZE);
}

void dlog(char * msg){
    if (!_config->nolog){
        size_t dlen = strlen(msg);
        log_buffer[log_bindex] = malloc(dlen + 2);
        strncpy(log_buffer[log_bindex], msg, dlen);

        log_buffer[log_bindex][dlen]='\r';
        log_buffer[log_bindex][dlen+1]='\n';

        log_bindex++;

        if (log_bindex == log_bindex-1)
            dflush();
    }

    if (_config->debug)
        printf("@ %s\r\n", msg);
}

//TODO
void dflush()
{
    //DatTable = getDatTable();
    
    //FILE * dlog = fopen("", "a");
}


//lexical


void printBufferStream(tBuffer * buf)
{
    printf(">>%d\r\n", _config->debug);
    //if (!_config->debug)
    //    return;

    printf("eCount :%3d\r\n", buf->eCount);
    printf("oCount :%3d\r\n", buf->oCount);
    printf("tCount :%3d\r\n", buf->tCount);
    
    token * top = buf->tokens;

    while (top){
        printf("{%s|%u}", top->raw, top->type);

        token * sib = top->sibling;

        while(sib){
            printf("<%s|%u>", sib->raw, sib->type);
            sib = sib->sibling;
        }

        top = top->right;

        printf("\r\n");
    }


    printf("\r\n");
    fflush(stdout);
}