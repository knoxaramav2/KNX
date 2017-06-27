#ifndef KDK_ERROR
#define KDK_ERROR

#include "token.h"

#define SYS_MESSAGE     0
#define SYS_ERROR       10000
#define SYS_WARNING     20000
#define PLUGIN_ERROR    30000
#define PLUGIN_WARNING  40000

#define EW_CODE_MAX     9999

#define IS_SYS_MSG(x) (x>SYS_MESSAGE && x<SYS_ERROR)
#define IS_SYS_ERROR(x) (x>SYS_ERROR && x<SYS_WARNING)
#define IS_SYS_WARNING(x) (x>SYS_WARNING && x<PLUGIN_ERROR)
#define IS_PLUGIN_ERROR(x) (x>PLUGIN_ERROR && x<PLUGIN_WARNING)
#define IS_PLUGIN_WARNING(x) (x>PLUGIN_WARNING)

token * createMessage(char*, lexeme, unsigned);

//Builtin error messages (reserved)

//SYS_ERROR
#define SYS_CODE_EXCEEDED   10001

#endif