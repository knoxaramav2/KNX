#include <string.h>
#include <stdio.h>

#include "_dbg.h"

void printToken(void * info, T_TYPE t, char prc){

    //data, 
    T_TYPE rt = t & ~RAW_DATA;
    T_TYPE r = t & RAW_DATA;

    switch(rt){
        case C_T_INT:  printf("_dbg : [%x %x %d %d]\r\n", rt, r, prc, *(int *)info); break;
        case C_T_DBL:  printf("_dbg : [%x %x %d %lf]\r\n", rt, r, prc, *(double *)info); break;
        case C_T_STR:  printf("_dbg : [%x %x %d %s]\r\n", rt, r, prc, (char *)info); break;
        case C_T_CHAR: printf("_dbg : [%x %x %d %c]\r\n", rt, r, prc, *(char *)info); break;
        default:
        printf("_dbg : [%x %d INFO]\r\n", t, prc); break;
    }

}