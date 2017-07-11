#ifndef KDK_LEX
#define KDK_LEX

/*
    Details enum for all supported lexems for lexical analysis
    Some ranges are left open for plugin support
*/

//TODO Add unary flag

#include "config.h"

#define MANAGE_CAST 0b10000000000000000000000000000000
#define ORDER_MASK  0b00000000000001110000000000000000
#define TYPE_MASK   0b00000000000000001111111111111111

#define MAX_KW_TYPE 120

#define isType(x) (x> lx_NUMERIC && x<lx_OPERATOR)
#define isOperator(x) (x>lx_OPERATOR && x<lx_KEYWORD)
#define isKeyword(x) (x>lx_KEYWORD && x<lx_STD_PLUGIN)
#define isDecl(x) (x>lx_KW_PRIM && x<lx_CNT)
#define isSetter(x) (x>lx_SET && x<lx_LOG)
#define isLogic(x) (x>lx_LOG && x<lx_CMP)
#define isGeneral(x) (x>lx_GEN && x<lx_ENC)
#define isEncap(x) (x>lx_ENC && x<lx_BIT)
#define isBitwise(x) (x>lx_BIT && x<lx_KEYWORD)
#define isKwDeclare(x) (x>lx_KW_PRIM && x<lx_CNT)
#define isKwUtil(x) (x>lx_KW_UTIL && x<lx_STD_PLUGIN)
#define isFault(x) (x>lx_SYS_ERROR && x<= lx_SYS_MESSAGE)

//use with ctxType (context type) of union 
#define isUnary(x) (isKeyword(x) || x==lx_GEN_LAMBDA || x==lx_LOG_NOT)
#define isCommand(x) (isOperator(x) || isKeyword(x))

#define isMath(x) (x>lx_MATH && x<lx_SET)
#define isOperand(x) (!isCommand(x) || isUnary(x))

typedef enum lexeme
{
    lx_NA,
    lx_NA_OPERAND,
    lx_NA_SYM,
    lx_NA_OPERATOR,

    //primitive types
    //NUMERICS
    lx_TYPE_OFFSET=20,//20
    lx_INT,
    lx_UINT,
    lx_LINT,
    lx_ULINT,
    lx_SINT,
    lx_USINT,
    lx_FLOAT,
    lx_DOUBLE,

    //TEXT
    lx_CHAR,
    lx_UCHAR,
    lx_WCHAR,
    lx_STRING,
    lx_WSTRING,

    //DATA STRUCTURES
    lx_ARRAY,       //strong typed
    lx_LIST,        //loose typed (used internally for argument lists as well)
    lx_CLASS,       //data encapsulation

    //MISC
    lx_BYTE,
    lx_FUNCTION,
    lx_VOID,

    //###################Type registry reserved

    //OPERATORS
    lx_OPERATOR=lx_TYPE_OFFSET + MAX_TYPE_COUNT,//420
    //math
    lx_MATH,
    lx_ADD,             //x+y
    lx_SUB,             //x-y
    lx_MULT,            //x*y
    lx_DIV,             //x/y
    lx_MOD,             //x%y
    lx_POW,             //x^y
    lx_ROOT,            //

    //setters
    lx_SET,             //=
    lx_SET_ADD,         //+=
    lx_SET_SUB,         //-=
    lx_SET_MULT,        //*=
    lx_SET_DIV,         ///=
    lx_SET_AND,         //&=
    lx_SET_OR,          //|=
    lx_SET_NOT,         //~=
    lx_SET_POST_INC,    //x++
    lx_SET_POST_DEC,    //x--
    lx_SET_PRE_INC,     //++x
    lx_SET_PRE_DEC,     //--x
    lx_SET_TERN,        //x ? (cond, true_val, false_val)

    //logic
    lx_LOG,
    lx_LOG_AND,         //&
    lx_LOG_OR,          //|
    lx_LOG_NOT,         //!
    lx_LOG_NAND,        //!&
    lx_LOG_NOR,         //!|
    lx_LOG_XOR,         //||
    lx_LOG_XNOR,        //|!

    //comparison
    lx_CMP,
    lx_CMP_EQU,         //==
    lx_CMP_NEQU,        //!=
    lx_CMP_GTR,         //>
    lx_CMP_LSS,         //<
    lx_CMP_GTR_EQU,     //>=
    lx_CMP_LSS_EQU,     //<=

    //general
    lx_GEN,
    lx_GEN_LISTITEM,    //,
    lx_GEN_MEMBERREF,   //.
    lx_GEN_INDEX,       //:
    lx_GEN_LAMBDA,      //$(arg, arg, {expression})

    //encapsulates
    lx_ENC,
    lx_ENC_OBRACK,      //[
    lx_ENC_OBRACE,      //{
    lx_ENC_OPARAN,      //(    
    lx_ENC_CBRACK,      //]
    lx_ENC_CBRACE,      //}
    lx_ENC_CPARAN,      //)
    lx_ENC_DQUOTE,      //"
    lx_ENC_SQUOTE,      //'

    //bitwise
    lx_BIT,
    lx_BIT_AND,         //^&
    lx_BIT_OR,          //^|
    lx_BIT_NOT,         //^!
    lx_BIT_LEFT,        //^<
    lx_BIT_RIGHT,        //^>

    //KEYWORDS
    lx_KEYWORD=lx_OPERATOR + 100,//520
    //primitives
    lx_KW_PRIM,
    lx_KW_INT,          //int(name, *val)
    lx_KW_UINT,         //uint(name, *val)    
    lx_KW_LINT,         //lint(name, *val)
    lx_KW_SINT,         //sint(name, *val)
    lx_KW_USINT,        //usint(name, *val)
    lx_KW_CHAR,         //char(name, val)    
    lx_KW_UCHAR,        //uchar(name, val)
    lx_KW_WCHAR,        //wchar(name, val)
    lx_KW_STRING,       //string(name, *val)
    lx_KW_WSTRING,      //wstring(name, *val)
    lx_KW_ARRAY,        //arr(name, type)
    lx_KW_LIST,         //list(name, {type(name, ...), type(name, ...)})
    lx_KW_CLASS,        //class(name, *constr({expression}), *destr(expression), type(name, ...))
    lx_KW_BYTE,         //byte(name, length)
    lx_KW_FUNCTION,     //proc(name, type name1, type name2, ..., {expression})
    lx_KW_VOID,         //void 

    //control
    lx_CNT=lx_KEYWORD + MAX_TYPE_COUNT,//920
    lx_CNT_IF,          //if (cond){expression}
    lx_CNT_ELSE,        //else {expression}
    lx_CNT_ELIF,        //elif (cond){expression}
    lx_CNT_DO,          //do(cond){expression}      (condition evaluated at end of loop)
    lx_CNT_WHILE,       //while(cond){expression}
    lx_CNT_FOR,         //for(cond, expression){expression}
                        //for(var collection){expression}
                        //for(loops){expression}
    lx_CNT_SWITCH,      //switch(val){:cond{expression}} TODO
    lx_CNT_CASE,        //
    lx_CNT_BREAK,       //break
    lx_CNT_CONTINUE,    //continue
        //meta
    lx_CNT_ENDBODY,

    //utility
    lx_KW_UTIL,
    lx_KW_TYPEOF,       //typeof(obj)
    lx_KW_DELETE,       //delete(obj)
    lx_KW_CAST,         //cast(obj, type)
    lx_KW_IMPORT,       //import(library)
    lx_KW_RELEASE,      //release(library)
    lx_KW_QUIT,         //quit
    lx_KW_PRINT,        //print(...)

    //common
    
    //REGISTER OFFSETS
    lx_STD_PLUGIN = lx_CNT + 100,//1020
    lx_EXT_PLUGIN = lx_STD_PLUGIN + 100,//1120

    //System messages
    lx_SYS_ERROR=lx_EXT_PLUGIN + 100,//1220
    lx_SYS_WARNING,
    lx_SYS_EXCEPTION,
    lx_LANG_EXCEPTION,
    lx_SYS_MESSAGE
} lexeme;

/*
CONTEXT ORDERING

1st level------
    Grouping: () {} []

    Appended to stack and remains until closing
    operator detected.

    All operators are popped until opening
2nd level------
    Priority operators
        ig. * / ^ %, ect.

        These will be popped prior to pushing
        an operator within this or the 3rd level
3rd level------
    Petty operators
        ig. + - = 

        ignored when pushing further operators

4th level-------
    Useful for keywords


*/

#define LEVEL_FOUR  0b00000000000001000000000000000000
#define LEVEL_THREE 0b00000000000000110000000000000000
#define LEVEL_TWO   0b00000000000000100000000000000000
#define LEVEL_ONE   0b00000000000000010000000000000000

#define CHKTYPE(x) (x & TYPE_MASK)
#define CHKLVL(x) ((ORDER_MASK & x) >> 16)

//UTIL
#define KW2TYPE(x) (x-lx_KW_PRIM+lx_TYPE_OFFSET)

#endif