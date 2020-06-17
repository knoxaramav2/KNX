#ifndef KDK_MODULE
#define KDK_MODULE

typedef struct Module{
    char * name;
} Module;

Module * createModule(char *);
int destroyModule (Module *);

#endif