#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_BUF 128

#include "../KDK/headers/dat_tables.h"

#include "config.h"

Config * _config = 0;
char * defTarget = "\\default\\def_config.txt";

//hardcoded config -- overwritten by loadDefaultConfig
Config * generateConfig()
{
_config = malloc(sizeof(Config));

_config->debug = false;
_config->verbose = false;
_config->suppresswarn = false;
_config->werr = false;
_config->nolog = false;

_config->maxMem = 1024;
_config->maxNodes = 100;
_config->maxThreads = 100;
_config->maxCores=0;

return _config;
}

Config * loadDefaultConfig()
{
    printf("Read config\r\n");

    if (!_config)
        generateConfig();

    DatTable dat = getDatTable();

    char * defstr = malloc(strlen(dat.exeLocation) + strlen(defTarget) + 1);
    strncpy(defstr, dat.exeLocation, strlen(dat.exeLocation));
    strncpy(defstr+strlen(dat.exeLocation), defTarget, strlen(defTarget));

    FILE * defcon = fopen(defstr, "r");
    char * buf = 0;
    size_t size = 0;
    ssize_t read = 0;

    

    if (!defcon) return _config;

    while((read = getline(&buf, &size, defcon)) != -1){
        long unsigned hash;
        char key [64];
        char val [64];
        size_t val_offset=0;

        //TODO add split
    }

    fclose(defcon);

    return _config;
}

Config * getConfig()
{
    return _config;
}