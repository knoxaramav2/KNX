#include <stdlib.h>
#include <stdio.h>

#include "config.h"

#include "datamanager.h"

//reference: http://www.programmingsimplified.com/c/source-code/c-program-for-prime-number

unsigned long * primeCipher(int range)
{
    Config * config = getConfig();

    unsigned long * ret = malloc(sizeof(unsigned long *) * config->maxNodes);

    //ret[0] = 1;//for root node master permission
    //ret[1] = 2;
 
    /*int n, i = 3, count, c;
 
    n = 10;

    if ( n >= 1 )
    {
        printf("First %d prime numbers are :\n",n);
        printf("2\n");
    }

    for ( count = 2 ; count <= n ;  )
    {
        for ( c = 2 ; c <= i - 1 ; c++ )
        {
            if ( i%c == 0 )
            break;
        }
        if ( c == i )
        {
            printf("%d\n",i);
            count++;
        }
        i++;
    }*/

    return ret;
}