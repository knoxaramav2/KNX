#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "KNX_String.h"

#include "parser.h"
#include "l_queue.h"

L_QUEUE _L_QUEUE;

#define _NRM  0   //Normal
#define _SQT  1   //Single quote
#define _DQT  2   //Double quote
#define _SCM  3   //Single line comment
#define _MCM  4   //Multi line comment
#define _BRK  5   //exit parsing

void addToQueue(){

}

char getPrecedence(T_TYPE type){

    if (type >= C_ASGN_OFFSET && type < C_COMP_OFFSET){
        return 0;
    }

    if (type >= C_BOOL_OFFSET && type < C_CTL_OFFSET){
        return 1;
    }

    if (type >= C_COMP_OFFSET && type < C_BOOL_OFFSET){
        return 2;
    }

    if (type >= C_MATH_OFFSET && type < C_MULT){
        return 3;
    }

    if (type >= C_MULT && type < C_POW){
        return 4;
    }

    if (type >= C_POW && type < C_ASGN_OFFSET){
        return 5;
    }

    if (type == C_LIST) return 7;
    if (type == C_FLAG) return 8;

    if (type >= C_O_PARAN && type <= C_C_BRACK) return 9;

    return 6;
}

T_TYPE getKeyWord(unsigned long val){

    switch (val){
        case 0x95e97e5e: return C_D_INT;

        case 0x16378a88: return C_PRINT;
    }

    return C_T_NA;
}

T_TYPE getType(char * raw){

    {
        int tp = isNumber(raw);
        if (tp == 1)
            return C_T_INT | RAW_DATA;
        if (tp == 2)
            return C_T_DBL | RAW_DATA;
    }

    unsigned long hash = fnv1a_32(raw);

    T_TYPE type;

    type = getKeyWord(hash);
    

    return type;
}

int addToken(char * l, char * r, T_TYPE type){

    char * str = 0;

    if (l!=0 && r!=0){
        int len = (r-l);
        str = malloc(len + 1);
        strncpy(str, l, len);
        str[len + 1] = 0;
    }
    
    if (type == C_T_NA){
        type = getType(str);
    }

    int prc = getPrecedence(type);

    printf("[%s %d %x]\r\n", str, prc, type);

    return 0;
}

//check for special characters, update state and current character pointer
T_TYPE checkSpecialChar(char ** curr, int * state){

    char c = **curr;

    //Check current state
    if (*state == _SQT){
        if (c == '\''){
            *state = _NRM;
            return _SQT;
        }
    } else if (*state == _DQT){
        if (c == '\"'){
            *state = _NRM;
            return _DQT;
        }
    } else if (*state == _SCM){
        
    } else if (*state == _MCM){
        
    }

    //Check for operators/variants
    switch(c){
        case '\'': *state = _SQT; break;
        case '\"': *state = _DQT; break;
        case '\0':
            *state = _BRK;
        break;
    }


    return 0;
}

int tokenize(char * raw, Stack * stk, Module * mod){

    printf("::%s\r\n", raw);

    char * prev = raw;
    char * curr = raw;

    int state = _NRM;
    int nscLen = 0;
    T_TYPE type = C_T_NA;

    while (state != _BRK){

        T_TYPE op = checkSpecialChar(&curr, &state);

        if (op == 0 && state == _NRM) {
            ++nscLen;
        } else {
            if (nscLen > 0){                
                addToken(prev, prev+nscLen, C_T_NA);
                nscLen = 0;
                prev += nscLen;
            }

            if (state == _NRM) {
                if (op == _SQT || op == _DQT){
                    addToken(prev+1, curr, op == _SQT ? C_T_CHAR : C_T_STR);
                } else if (op != _SCM && op != _MCM) {
                    addToken(0, 0, op);
                }
                prev = curr + 1;
            }
        }

        ++curr;
    }

    
    return 0;
}