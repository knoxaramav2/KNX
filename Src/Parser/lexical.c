#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "parser.h"
#include "debug.h"

#define isNum(x) (x>='0' && x<='9')
#define isAlpha(x) ((x>='a' && x<='z') || (x>='A' && x<='Z'))
#define isNOChar(x) (x=='.' || x=='_')
#define isText(x) (isNum(x) || isAlpha(x) || isNOChar(x))
#define isWhiteSpace(x) (x==' ' || x=='\t' || x==0)
#define isOCap(x) (x=='(' || x=='[' || x=='{')
#define isECap(x) (x==')' || x==']' || x=='}')
#define isQuote(x) (x=='\'' || x=='\"')

char getEscapeChar(char c){

    return c;
}

lexeme resolveSymbol(char * sym){

    return lx_NA;
}

size_t pushOperator(tBuffer * buf, char * str, size_t max)
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

        //encapsulation
        case '(':
        case '{':
        case '[':

        break;
        
        case ')':
        case '}':
        case ']':

        break;

        //start quote states
        case '\'':
        buf->qState = QBIT_S;
        break;
        case '\"':
        buf->qState = QBIT_D;
        break;

        
        default:
        return 0;
    }

    printf("{%u}", result);

    return ret;
} 

void pushOperand(tBuffer * buf, char * str, size_t max, lexeme explicit)
{
    if (explicit == lx_NA)
        explicit = resolveSymbol(str);

    printf("[%s, %d]", str, explicit);
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

        //literal read mode
        if (node->buffer.qState){
            if ((c=='\'' && node->buffer.qState == QBIT_S) ||
                (c=='\"' && node->buffer.qState == QBIT_D)){

                    buffer[index]=0;
                    pushOperand(
                        &node->buffer, 
                        buffer, index, 
                        node->buffer.qState == QBIT_S && index == 1 ? lx_CHAR : lx_STRING);
                    node->buffer.qState = 0;
                    index = 0;
                    ++x;
            }

            if (c=='\\'){
                c == getEscapeChar(c);
                ++index;
            }

            buffer[index++] = c;
            
            continue;
        }

        if (isText(c)){
            buffer[index++] = c;
        } else {
            if (index > 0){
                buffer[index] = 0;
                pushOperand(&node->buffer, buffer, index, lx_NA);
                index = 0;
            }

            if (!isWhiteSpace(c)){
                x += pushOperator(&node->buffer, raw + x, len - x);
            }
        }
    }

    //TODO add quotes and encapsulates

    printBufferStream(&node->buffer);

    printf("\r\n");

    return  node->buffer.oCount == 0 && 
            node->buffer.qState == 0 &&
            !node->buffer.yieldLine ?
        TK_COMPLETE :
        TK_PENDING;
}