#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "parser.h"

#define isNum(x) (x>='0' && x<='9')
#define isAlpha(x) ((x>='a' && x<='z') || (x>='A' && x<='Z'))
#define isNOChar(x) (x=='.' || x=='_')
#define isText(x) (isNum(x) || isAlpha(x) || isNOChar(x))
#define isWhiteSpace(x) (x==' ' || x=='\t' || x==0)
#define isOCap(x) (x=='(' || x=='[' || x=='{')
#define isECap(x) (x==')' || x==']' || x=='}')

size_t pushOperator(char * str, size_t max)
{
    //printf("{%s}", str);

    lexeme result = lx_NA;
    size_t ret = 0;

    char c0 = str[0];
    char c1 = max >= 2 ? str[1] : 0;
    char c2 = max >= 3 ? str[2] : 0;

    switch (c0){

        case '+':
            if (c1=='+') {result=lx_SET_INC; ret=1;}
            else if (c1=='='){result=lx_SET_ADD; ret=1;}
            else result = lx_ADD;
        break;
        case '-':
            if (c1=='-') {result=lx_SET_DEC; ret=1;}
            else if (c1=='='){result=lx_SET_SUB; ret=1;}
            else result = lx_SUB;
        break;
        case '*':
            if (c1=='=') {result=lx_SET_MULT; ret=1;}
            else result = lx_MULT;
        break;
        case '/':
            if (c1=='=') {result=lx_SET_DIV; ret=1;}
            else result = lx_DIV;
        break;
        case '%':
            result = lx_MOD;
        break;
        case '^':
            if (c1=='&') {result=lx_BIT_AND; ret=1;}
            else if (c1=='|'){result=lx_BIT_OR; ret=1;}
            else if (c1=='!'){result=lx_BIT_NOT; ret=1;}
            else if (c1=='<'){result=lx_BIT_LEFT; ret=1;}
            else if (c1=='>'){result=lx_BIT_RIGHT; ret=1;}
            else result=lx_POW;
        break;
        case (char)251:
        case -30:
            result=lx_ROOT;
        break;

        case '&':
            if (c1=='=') {result=lx_SET_AND; ret=1;}
            else result = lx_LOG_AND;
        break;
        case '|':
            if (c1=='=') {result=lx_SET_OR; ret=1;}
            else if (c1=='|') {result=lx_LOG_XOR; ret=1;}
            else if (c1=='!') {result=lx_LOG_XNOR; ret=1;}
            else result = lx_LOG_OR;
        break;
        case '!':
            if (c1=='=') {result=lx_CMP_NEQU; ret=1;}
            else if (c1=='|') {result=lx_LOG_NOR; ret=1;}
            else if (c1=='&') {result=lx_LOG_NAND; ret=1;}
            else result = lx_LOG_NOT;
        break;
        case '?':
            result = lx_SET_TERN;
        break;

        case '=':
            if (c1=='=') {result=lx_CMP_EQU; ret=1;}
            else result = lx_SET;
        break;

        case '<':
            if (c1=='=') {result=lx_CMP_LSS_EQU; ret=1;}
            else result = lx_CMP_LSS;
        break;
        case '>':
            if (c1=='=') {result=lx_CMP_GTR_EQU; ret=1;}
            else result = lx_CMP_GTR;
        break;

        case ':':
            result = lx_GEN_INDEX;
        break;
        case '$':
            result = lx_GEN_LAMBDA;
        break;
        
        default:
        return 0;
    }

    printf("{%u}", result);

    return ret;
} 

void pushOperand(char * str, size_t max)
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

    for (size_t x=0; x <= len; ++x)
    {
        char c = raw[x];
        //printf("%d\r\n", (int)c);
        if (isText(c)){
            buffer[index++] = c;
        } else {
            if (index > 0){
                buffer[index] = 0;
                pushOperand(buffer, index);
                index = 0;
            }

            if (!isWhiteSpace(c)){
                x += pushOperator(raw + x, len - x);
            }
        }
    }

    printf("\r\n");

    return node->buffer.tCount == 0 ?
        TK_COMPLETE :
        TK_PENDING;
}