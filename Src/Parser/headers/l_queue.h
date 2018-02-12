#ifndef PRS_L_QUEUE
#define PRS_L_QUEUE

#include "type.h"

typedef struct Token{

    T_TYPE type;
    char precedence;
    void * data;

} Token;

/*
    Stores tokens for sorting before
    being added to current stack frame

    If tokenize() returns before outIdx
    is 0 or cntInput is 1, it is assumed 
    that the input stream is not complete; 
    user input is accepted again without execution
*/
typedef struct L_QUEUE{
    
    Token operators  [128];
    Token output    [256];

    int opIdx, outIdx;
    int encapLevel;//number of open enclosures
    int cntInput;

    T_TYPE _lastPushed;

} L_QUEUE;

extern L_QUEUE _L_QUEUE;

#endif