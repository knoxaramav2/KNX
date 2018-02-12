#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "KNX_String.h"

#include "parser.h"
#include "l_queue.h"

L_QUEUE _L_QUEUE;

#define _NRM    0   //Normal
#define _SCM    1   //Comment     
#define _MCM    2   //Comment multi line
#define _BRK    3   //Break
#define _WSB    4   //Whitespace

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

//Check for special character and set indexes accordingly
T_TYPE checkSpecialChar(char ** curr, char ** prev, int * state){

    char c = **curr;

    //Check for non-special characters
    if ((c >= 'A' && c <= 'Z') ||
        (c >= 'a' && c <= 'z') ||
        (c >= '0' && c <= '9') ||
        (c == '.' || c== '_')){
        return C_T_NA;
    }

    switch (c){

        //Ignored
        case ' ':
        case '\t':
            *state = _WSB;
        break;

        //String
        case '\'':
        case '\"':{
            char * idx = *curr + 1;
            for (; *idx != 0; ++idx){
                if (*idx == c){
                    *curr = idx;
                    return c == '\'' ? C_T_CHAR : C_T_STR;
                }
            }
            return -1;
        } break;

        //End
        case '\0':
            *state = _BRK;
        break;

    }

    return C_T_NA;
}

int tokenize(char * raw, Stack * stk, Module * mod){

    printf("::%s\r\n", raw);

    char * prev = raw;
    char * curr = raw;

    int state = _NRM;
    int nscLen = 0;
    T_TYPE type = C_T_NA;

    while (state != _BRK){

        T_TYPE op = checkSpecialChar(&curr, &prev, &state);

        //non-special characters
        if (state == _NRM && op == C_T_NA){
            ++nscLen;
            ++curr;
            continue;
        }

        //append token if special found
        if (nscLen > 0){
            addToken(prev, prev + nscLen, 0);
            prev += nscLen;
            nscLen = 0;
        }

        //whitespace
        if (state == _WSB){
            prev = curr + 1;
            state = _NRM;
            ++curr;
            continue;
        }

        if (state == _SCM || state == _BRK){
            break;
        }

        //add
        if (op == C_T_CHAR || op == C_T_STR){
            addToken(prev + 1, curr, op);
            prev = curr + 1;
        } else {
            addToken(0, 0, op);
            prev = curr + 1;
        }

        ++curr;
    }

    
    return 0;
}