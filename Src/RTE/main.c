#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "KNX_String.h"
#include "KNX_Console.h"

#include "KDK.h"

#include "startup.h"

Config * config;

void printHelp(){
    printf("Help\r\n");
}

void printVersion(){
    printf("Version\r\n");
}

int parseCmd(int argc, char ** argv){

    //do not start interpeter if only information is requested
    int runnableOptionSet = 0;
    int infoOptionSet = 0;

    config = getDefaultConfig();

    for (int i = 1; i < argc; ++i){
        
        char * option = argv[i];

        printf(">> %s\r\n", option);

        if (option[0] != '-'){
            printf("Options must be preceeded by one or two '-'\r\n\t%s\r\n", option);
            continue;
        }

        if (option[1] == '-'){

        } else {
            for (int j = 1; j < strlen(option); ++j){
                switch(option[j]){
                    case 'h': 
                        printHelp(); 
                        infoOptionSet = 1;
                    break;
                    case 'v': 
                        printVersion(); 
                        infoOptionSet = 1;
                    break;
                    
                    case 'w':
                        config->suppressWarning = 1;
                        runnableOptionSet = 1;
                    break;
                    case 'f':
                        config->fatalWarn = 1;
                        runnableOptionSet = 1;
                    break;
                    case 'p':
                        config->pendantic = 1;
                        runnableOptionSet = 1;
                    break;

                }
            }
        }

    }

    return  runnableOptionSet + !infoOptionSet;
}

int main(int argc, char ** argv){

    startConsoleControl();
    setEcho(0);

    if (parseCmd(argc, argv) == 0){
        return 0;
    }

    endConsoleControl();

    return 0;
}