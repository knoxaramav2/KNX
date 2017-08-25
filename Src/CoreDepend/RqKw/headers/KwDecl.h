#ifndef REQ_KW
#define REQ_KW

#define KW_ARG_LIST (HMODULE *, token *);

#include "module.h"
#include "function.h"

//CONTROL
obj * kw_if KW_ARG_LIST
obj * kw_else KW_ARG_LIST
obj * kw_elif KW_ARG_LIST
obj * kw_do KW_ARG_LIST
obj * kw_while KW_ARG_LIST
obj * kw_for KW_ARG_LIST
obj * kw_switch KW_ARG_LIST
obj * kw_case KW_ARG_LIST
obj * kw_break KW_ARG_LIST
obj * kw_continue KW_ARG_LIST

//UTIL
obj * kw_typeof KW_ARG_LIST
obj * kw_delete KW_ARG_LIST
obj * kw_cast KW_ARG_LIST
obj * kw_import KW_ARG_LIST
obj * kw_run KW_ARG_LIST
obj * kw_release KW_ARG_LIST
obj * kw_quit KW_ARG_LIST
obj * kw_print KW_ARG_LIST
obj * kw_throw KW_ARG_LIST
obj * kw_try KW_ARG_LIST
obj * kw_throw KW_ARG_LIST
obj * kw_try KW_ARG_LIST
obj * kw_catch KW_ARG_LIST

#endif