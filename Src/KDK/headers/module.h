#ifndef KDK_MODULE
#define KDK_MODULE

typedef struct Module{
    char * name;
} Module;

Module * createModule();
int destroyModule (Module *);

#endif