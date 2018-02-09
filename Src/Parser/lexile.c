#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"
#include "l_queue.h"

L_QUEUE _L_QUEUE;

void addToQueue(){

}

int addToken(char * l, char * r, T_TYPE type){

    int len = (r-l);
    char * str = malloc(len + 1);
    strncpy(str, l, len + 1);
    str[len + 1] = 0;

    printf("[%s %d]\r\n", str, type);

    return 0;
}

int tokenize(char * raw, Stack * stk, Module * mod){

    printf("::%s\r\n", raw);

    char * prev = raw;
    char * curr = raw;

    const int _NRM = 0;
    const int _SQT = 1;
    const int _DQT = 2;
    const int _BRK = 3;

    int state = _NRM;

    while (state != _BRK){

        if (state == _SQT){
            if (*curr == '\''){
                state = _NRM;

                int len = curr-prev;
                T_TYPE ctype;

                if (len != 1){
                    //throw warning, missized char, upgrade to string
                    ctype = C_STR;
                } else {
                    ctype = C_CHAR;
                }

                addToken(prev, curr - 1, ctype);
                prev = curr + 1;
            }

            goto _ordChar;
        } else if (state == _DQT) {

            if (*curr == '\"'){
                state = _NRM;

                addToken(prev, curr-1, C_STR);
                prev = curr + 1;
            }

            goto _ordChar;
        }

        switch (*curr){
            //STRING
            case '\'':
                state = _SQT;
                prev = curr + 1;
                goto _ordChar;
            break;
            case '\"':
                state = _DQT;
                prev = curr + 1;
                goto _ordChar;
            break;
            //MISC

            //BREAK
            case ' ':
            case '\t':
                prev = curr + 1;
                goto _ordChar;
            break;
            case '\0':
                state = _BRK;
            break;
            default:
                goto _ordChar;
        }

        //create token
        if (prev == curr)
            continue;

        addToken(prev, curr - 1, C_NA);
        prev = curr + 1;

        //skip if ordinary character
        _ordChar:;

        ++curr;
        if (*curr == 0)
            state = _BRK;
    }

    return 0;
}