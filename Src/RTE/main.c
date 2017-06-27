/*
starting point for KNX interpreter
*/

#include <stdio.h>

#include "KDK.h"
#include "globals.h"
#include "startup.h"

#include "lexeme.h"

comp_handle _info;

#define SYS_DEBUG

int main(int argc, char ** argv)
{
/*
unsigned i = LEVEL_ONE | lx_ADD;
unsigned j = LEVEL_TWO | lx_BIT_AND;
unsigned k = LEVEL_THREE;

printf("%u %u %u\r\n", i, j, k);
printf("%u %u %u\r\n", 
CHKLVL(i), 
CHKLVL(j), 
CHKLVL(k));

return 0;
*/
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