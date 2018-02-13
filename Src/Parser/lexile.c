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

void addToOperators(T_TYPE type, int prs){
    _L_QUEUE.operators[_L_QUEUE.opIdx].type = type;
    _L_QUEUE.operators[_L_QUEUE.opIdx].precedence = prs;
    _L_QUEUE.opIdx += 1;

    _L_QUEUE._lastPushed = type;
}

void addToOutput(char * str, T_TYPE type, int prs){
    _L_QUEUE.output[_L_QUEUE.outIdx].type = type;
    _L_QUEUE.output[_L_QUEUE.outIdx].precedence = prs;
    _L_QUEUE.output[_L_QUEUE.outIdx].data = str;
    _L_QUEUE.outIdx += 1;

    _L_QUEUE._lastPushed = type;
}

Token * popOperator(){
    if (_L_QUEUE.opIdx == 0)
        return 0;
    return &_L_QUEUE.operators[--_L_QUEUE.opIdx]; 
}

Token * peekOperator(){
    if (_L_QUEUE.opIdx == 0)
        return 0;
    return &_L_QUEUE.operators[_L_QUEUE.opIdx-1];
}

//collapse all if type == 0
int collapseOperators(T_TYPE type){
    
    Token * t = 0;

    if (type == 0){
        do{
            if ((t = popOperator())){
                addToOutput(0, t->type, t->precedence);
            }
        } while(t);
    } else {
        do{
            if ((t = popOperator())){
                if (t->type == type){
                    
                    if (_L_QUEUE._lastPushed == type){
                        addToOutput(0, C_T_VOID, 6);
                    }

                    return 0;
                }

                addToOutput(0, t->type, t->precedence);
            }
        }while(t);

        return -1;
    }

    return 0;
}

void addToQueue(void * data, T_TYPE type, int prs){

    //immediately add operands
    if (prs < 0){
        addToOutput(data, type, prs);
        return;
    }

    //check end closure
    if (type == C_C_BRACK ||
        type == C_C_BRACE ||
        type == C_C_PARAN){
            collapseOperators(type - 1);
            return;
        }

    //shunting-yard
    Token * prev = peekOperator();
    if (prev == 0){
        addToOperators(type, prs);
        return;
    }

    if (prs > prev->precedence || prev->precedence == 9){
        addToOperators(type, prs);
    } else {
        popOperator();
        addToOutput(0, prev->type, prev->precedence);
        addToOperators(type, prs);
    }
}

char getPrecedence(T_TYPE type){

    //operands
    if (type < C_KW_OFFSET || type >= C_FNC_OFFSET){
        return -1;
    }

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
    void * data = 0;

    if (l!=0 && r!=0){
        int len = (r-l);
        str = malloc(len + 1);
        strncpy(str, l, len);
        str[len] = 0;
    }
    
    if (type == C_T_NA){
        type = getType(str);

        if (type == (RAW_DATA | C_T_INT)){
            int * i = malloc(sizeof(int));
            *i = atoi(str);
            data = i;
        } else if (type == (RAW_DATA | C_T_DBL)){
            double * dbl = malloc(sizeof(double));
            *dbl = atof(str);
            data = dbl;
        }
    }

    int prc = getPrecedence(type);

    if (type == C_T_NA      ||
        type == C_T_CHAR    ||
        type == C_T_STR){
        addToQueue(str, type, prc);
    } else {
        addToQueue(data, type, prc);
        free(str);
    }

    return 0;
}

//Check for special character and set indexes accordingly
T_TYPE checkSpecialChar(char ** curr, char ** prev, int * state){

    char c = **curr;
    char c2 = *(*curr+1);
    char c3 = *(*curr+2);

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

        //Math
        case '+':
            if (c2 == '=' || c2 == '+'){
                *curr = *curr + 1;
                return c2 == '=' ? C_ADD_SET : C_INC_SET;
            }
            return C_ADD;
        break;
        case '-':
            if (c2 == '=' || c2 == '-'){
                *curr = *curr + 1;
                return c2 == '=' ? C_SUB_SET : C_DEC_SET;
            }
            return C_SUB;
        break;
        case '*':
            if (c2 == '='){
                *curr = *curr + 1;
                return c2 == C_MULT_SET;
            }
            return C_MULT;
        break;

        //General
        case '=': return C_SET;

        //Enclosure
        case '[': return C_O_BRACK;
        case '(': return C_O_PARAN;
        case '{': return C_O_BRACE;
        case ']': return C_C_BRACK;
        case ')': return C_C_PARAN;
        case '}': return C_C_BRACE;

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
    //T_TYPE type = C_T_NA;

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

    collapseOperators(0);
    
    return 0;
}