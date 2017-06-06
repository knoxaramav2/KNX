#include <stdlib.h>
#include <stdio.h>

#include "config.h"

#include "datamanager.h"

//reference: http://www.programmingsimplified.com/c/source-code/c-program-for-prime-number

unsigned long * primeCipher(int range)
{
    unsigned long * ret = malloc(sizeof(unsigned long *) * range);

    ret[0] = 1;
    ret[1] = 2;

    if (range <= 2)
        return ret;
 
    int n, i = 3, count, c;
 
    n = range;

    for ( count = 2 ; count <= n ;  )
    {
        for ( c = 2 ; c <= i - 1 ; c++ )
        {
            if ( i%c == 0 )
            break;
        }
        if ( c == i )
        {
            ret[count] = c;
            count++;
        }
        i++;
    }

    return ret;
}