#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "error.h"

#define ERR_MSG_TEMPLATE    "Error (%s) : %s"
#define WRN_MSG_TEMPLATE    "Warning (%s): %s"
#define CODE_LIMIT_TEMPLATE  "Error (%u) : Error code limit exceeded\r\n\t>> %s (%u)\r\n"

token * createMessage(char*eMsg, lexeme errtype, unsigned code){

if (code > EW_CODE_MAX){
    char cmsg [128];

    snprintf(cmsg, 128, "%u", code);

    size_t clen = strlen(CODE_LIMIT_TEMPLATE) + strlen(cmsg) + 6;
    char * rmsg = malloc(clen);
    snprintf(rmsg, clen, CODE_LIMIT_TEMPLATE, SYS_CODE_EXCEEDED, cmsg, code);
    return createToken("Error : Message code limit exceeded\r\n", lx_SYS_ERROR, NULL);
}

size_t len = strlen(eMsg);
size_t tlen;
char * message = NULL;

char scode [5];
sprintf(scode, "%u", code);

if (IS_SYS_MSG(code)){
    
} else if (IS_SYS_ERROR(code)){
    code += SYS_ERROR;
    message = ERR_MSG_TEMPLATE;
} else if (IS_SYS_WARNING(code)){
    code += SYS_WARNING;
    message = WRN_MSG_TEMPLATE;
} else if (IS_PLUGIN_ERROR(code)){
    code += PLUGIN_ERROR;
    message = ERR_MSG_TEMPLATE;
} else if (IS_PLUGIN_WARNING(code)){
    code += PLUGIN_WARNING;
    message = WRN_MSG_TEMPLATE;
}

tlen = strlen(message);

char * ret = malloc(len + tlen + 6);
snprintf(ret, len + tlen + 6, message, scode, eMsg);

token * msg = createToken(message, errtype, NULL);
return msg;
};