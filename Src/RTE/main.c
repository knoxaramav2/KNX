/*
starting point for KNX interpreter
*/

#include <stdio.h>

#include "KDK.h"
#include "globals.h"
#include "startup.h"
#include "lexeme.h"

#include "type.h"

comp_handle _info;

#define SYS_DEBUG

typedef int (*testfunc)();

obj * dev_cons(char * name, token * data){

    printf("Constructor called (btw %s %u)\r\n", data->raw, data->type);
    return NULL;
}

int dev_dest(){
    printf("Destructor called \r\n");
    return 0;
}

int main(int argc, char ** argv)
{

type_constructor cons = &dev_cons;
type_destructor dest = &dev_dest;

registerType(NULL, cons, dest);

//hostfunc(&print);

return 0;
init_sdk();

int rCode = 0;

if ((rCode = initComponents()))
    return rCode |= 0xA;
if ((rCode = parseCmd(argc, argv)))
    return rCode |= 0xB;
if ((rCode = startRoot()))
    return rCode |= 0xC;
if ((rCode = shutdown()))
    return rCode |= 0xD;


return rCode;
}