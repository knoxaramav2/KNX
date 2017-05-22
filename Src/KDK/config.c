#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../KDK/headers/dat_tables.h"

#include "config.h"

Config * _config;
char * defTarget = "\\default\\def_config.txt";

Config * loadDefaultConfig()
{
    _config = malloc(sizeof(Config));
    DatTable dat = getDatTable();

    char * defstr = malloc(strlen(dat.exeLocation) + strlen(defTarget) + 1);
    strncpy(defstr, dat.exeLocation, strlen(dat.exeLocation));
    printf(">> %s | %s\r\n", dat.exeLocation, defTarget);
    strncpy(defstr+strlen(dat.exeLocation), defTarget, strlen(dat.exeLocation));

    printf(">> %s\r\n", defstr);

    FILE * defcon = fopen("", "r");
    char buf[64];
    size_t size;

    if (!defcon) return _config;

    while((size = fread(buf, 1, sizeof buf, defcon)) > 0){
        printf("%s\r\n", buf);
    }

    fclose(defcon);

    return _config;
}

Config * getConfig()
{
    return _config;
}