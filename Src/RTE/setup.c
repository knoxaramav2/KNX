#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>

#include "KNX_Hash.h"

#include "node_reg.h"
#include "../ModuleManager/headers/modmanage.h"

#include "dat_tables.h"
#include "config.h"
#include "node.h"
#include "globals.h"

#include "startup.h"

Config * _config = 0;

int initComponents()
{
    //core components
    register_module("libMDM.so");
    register_module("libDTM.so");
    register_module("libPRS.so");
    register_module("libEXC.so");

    //required modules
    register_module("required/libTYP.so");
    register_module("required/libKW.so");

    return 0;
}

int parseMulti(char * arg)
{
    size_t len = strlen(arg);

    for (size_t i = 1; i < len; ++i)
    {
        switch(arg[i])
        {
            case 'd': _config->debug=true;break;
            case 'v': _config->verbose=true;break;
            case 'w': _config->suppresswarn=true;break;
            case 'e': _config->werr=true;break;
            case 'f': _config->force=true;break;

            default:
            printf("Unrecognized option -%c\r\n", arg[i]);
            return 2;
        }
    }

    return 0;
}

char ** getKeyPair(char * arg)
{
    size_t len = strlen(arg);
    char key [64] = {0};
    char val [128] = {0};

    size_t ldx = 0;

    for(;ldx < len; ++ldx)
    {
        if(arg[ldx] == '=')
        {
            strncpy(val, arg+ldx+1, len-ldx+1);
            break;
        }
        
        key[ldx] = arg[ldx];
    }

    char ** ret = malloc(sizeof(char*) * 2);
    
    ret[0] = malloc(strlen(key));
    ret[1] = malloc(strlen(val));

    strncpy(ret[0], key+2, 64);
    strncpy(ret[1], val, 128);

    return ret;
}

int parseStr(char * arg)
{
    char ** keyval = getKeyPair(arg);

    unsigned long hash = FNV_1a_32(keyval[0]);

    switch(hash)
    {
        case 14210939209047507578ULL: //nolog
        _config->nolog = true;
        break;
        case 14829159093148863043ULL://maxmem
        _config->maxMem = strcmp(keyval[1], "true") == 0;
        break;
        case 4021330360095635380ULL://maxnodes
        _config->maxNodes = strcmp(keyval[1], "true") == 0;
        break;
        case 3303218281958467797ULL://maxthreads
        _config->maxThreads = strcmp(keyval[1], "true") == 0;
        break;
        case 805471052263418954ULL://maxcores
        _config->maxCores = strcmp(keyval[1], "true") == 0;
        break;
        default:
        printf("Unrecognized option %s\r\n", arg);
        return 2;
    }

    free(keyval[0]);
    free(keyval[1]);
    free(keyval);

    return 0;
}

int parseCmd(int argc, char ** argv, nodeArg * nArg)
{
    _config = getConfig();

    nArg->script = NULL;

    int ret = 0;

    for (int i = 1; i < argc; ++i)
    {
        char * arg = argv[i];
        
        printf("%s\r\n", arg);

        if (arg[0] != '-'){
            nArg->script = malloc(strlen(arg) + 1);
            strncpy(nArg->script, arg, strlen(arg) + 1);

            for (char * itr = nArg->script; *itr; ++itr){
                if (*itr=='\\' && *(itr+1) != '\\'){
                    *itr = '/';
                }
            }
        }
        else if (arg[1]=='-')
            ret |= parseStr(arg);
        else
            ret |= parseMulti(arg);
    }

    return ret;
}

int startRoot(nodeArg * arg)
{
    node * root = createNode();
    registerNode(root, NULL);

    arg->n = root;

    pthread_create(&root->_handle, NULL, _nodeProc, arg);
    pthread_join(root->_handle, NULL);

    return 0;
}

int shutdown()
{

    

    return 0;
}