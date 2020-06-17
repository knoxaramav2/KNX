#ifndef KDK_CONFIG
#define KDK_CONFIG

/*
Specifies options that may be set during invocation
*/

typedef struct Config{
    
    //Error/Warning
    char suppressWarning;
    char pendantic;
    char fatalWarn;

    //System
    int maxNodes;
    int maxThreads;

} Config;

Config * getDefaultConfig();

#endif