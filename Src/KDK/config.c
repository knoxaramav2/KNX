#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_BUF 128

#include "KNX_Hash.h"
#include "KNX_String.h"

#include "../KDK/headers/dat_tables.h"

#include "config.h"

Config * _config = 0;
char * defTarget = "\\default\\def_config.txt";

int kwtoi(char*);

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
        char * key, * val;
        key = strtok(buf, " ");
        val = strtok(NULL, " ");

        if (key == NULL || val == NULL)
            continue;

        size_t vlen = val == NULL ? 0 : strlen(val);

        //remove ending characters
        if (vlen > 0){
            #ifdef __WINDOWS
            val[vlen-2] = 0;
            #else
            val[vlen-1] = 0;
            #endif
        }

        key = toLowerc(key);
        unsigned long long hash = FNV_1a_32(key);

        switch(hash)
        {
            case 7391100764467111004ULL://debug
            _config->debug = kwtoi(val);
            break;
            case 14240799945583472663ULL://verbose
            _config->verbose = kwtoi(val);
            break;
            case 3703768262614815098ULL://suppresswarn
            _config->suppresswarn = kwtoi(val);
            break;
            case 338348135679073710ULL://werr
            _config->werr = kwtoi(val);
            break;
            case 9508952674701482718ULL://force
            _config->force = kwtoi(val);
            break;
            case 14210939209047507578ULL://nolog
            _config->nolog = kwtoi(val);
            break;

            case 14395617016193075435ULL://maxmem
            _config->maxMem = atoi(val);
            break;
            case 168781108370588788ULL://maxmodes
            _config->maxNodes = atoi(val);
            break;
            case 1964334753117364437ULL://maxthreads
            _config->maxThreads = atoi(val);
            break;
            case 10909174432916404858ULL://maxcores
            _config->maxCores = atoi(val);
            break;
            default:
            printf("Unrecognized config (%s)\r\n", key);
            break;
        }
    }

    fclose(defcon);

    return _config;
}

Config * getConfig()
{
    return _config;
}



//UTIL

int kwtoi(char*str){
    str = toLowerc(str);

    unsigned long long hash = FNV_1a_32(str);

    switch(hash)
    {
        case 338497781026018834LL: return 1;
        case 8437673119161304082: return 0;
        default: return 0;
    }

    return 0;
}