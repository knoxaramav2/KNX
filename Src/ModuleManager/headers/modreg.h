#ifndef MODMAN_REG
#define MODMAN_REG

#include "../../KDK/headers/compinfo.h"

#include "compinfo.h"

typedef struct mod_reg
{

int count;
comp_handle * handles;

} mod_reg;


extern mod_reg _modreg;
void register_module (char *);
void release_module (char *);

#endif