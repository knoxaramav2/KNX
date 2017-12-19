/*
starting point for KNX interpreter
*/

#include <stdio.h>

#include "KNX_String.h"

#include "KDK.h"

#define SYS_DEBUG

int main(int argc, char ** argv)
{
    char msg[] = "help/Test.a";
    printf("%s %s\r\n", getFileName(msg, 0), getFileName(msg, 1));

    return 0;
}