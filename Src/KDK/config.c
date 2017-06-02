#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_BUF 128

#include "../KDK/headers/dat_tables.h"

#include "config.h"

Config * _config;
char * defTarget = "\\default\\def_config.txt";

Config * loadDefaultConfig()
{
    printf("Read config\r\n");
    _config = malloc(sizeof(Config));
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