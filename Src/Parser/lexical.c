#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "parser.h"

#define isNum(x) (x>='0' && x<='9')
#define isAlpha(x) ((x>='a' && x<='z') || (x>='A' && x<='Z'))
#define isNOChar(x) (x=='.' || x=='_')
#define isText(x) (isNum(x) || isAlpha(x) || isNOChar(x))
#define isWhiteSpace(x) (x==' ' || x=='\t')

void pushOperator(char * str, size_t pos)
{
    printf("{%s}", str);
} 

void pushOperand(char * str, size_t pos)
{
    printf("[%s]", str);
}

//TODO implement modified shunting yard as in docs
int tokenize(node * node, char * raw)
{
    printf("Input: %s from node %d\r\n", raw, node->id_index);

    size_t len = strlen(raw);
    char buffer[1024] = {0};
    size_t index = 0;

    bool parseOp = false;

    for (size_t x=0; x <= len; ++x)
    {
        char c = raw[x];

        //printf("|%c%d%d%d%d|\r\n", c, isNum(c), isAlpha(c), isNOChar(c), isText(c));

        if (isText(c)){

            if (parseOp && index > 0)
            {
                parseOp = false;
                buffer[index] = 0;
                pushOperator(buffer, index);
                index = 0;
            }

            buffer[index++] = c;
        } else {

            bool ws = isWhiteSpace(c);
            parseOp = !ws;

            if (!parseOp && index > 0){
                parseOp = true;
                buffer[index] = 0;
                pushOperand(buffer, index);
                index = 0;
            } else if (parseOp && index > 0 && ws){
                parseOp = false;
                buffer[index] = 0;
                pushOperator(buffer, index);
                index = 0;
            }


            if (!ws)
                buffer[index++] = c;
        }
    }

    printf("\r\n");

    return node->buffer.tCount == 0 ?
        TK_COMPLETE :
        TK_PENDING;
}