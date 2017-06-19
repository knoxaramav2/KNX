#ifndef KDK_LEX
#define KDK_LEX

/*
    Details enum for all supported lexems for lexical analysis
    Some ranges are left open for plugin support
*/

#define isOperator(x) (x>lx_OPERATOR && x<lx_KEYWORD)
#define isKeyword(x) (x>lx_KEYWORD && x<lx_STD_PLUGIN)

typedef enum lexeme
{
    lx_NA,
    lx_NA_OPERAND,
    lx_NA_OPERATOR,
    lx_NA_SYM,

    //primitive types

    //NUMERICS
    lx_NUMERIC,
    lx_INT,
    lx_UINT,
    lx_LINT,
    lx_ULINT,
    lx_SINT,
    lx_USINT,

    //TEXT
    lx_CHAR,
    lx_UCHAR,
    lx_WCHAR,
    lx_STRING,
    lx_WSTRING,

    //DATA STRUCTURES
    lx_ARRAY,       //strong typed
    lx_LIST,        //loose typed
    lx_CLASS,       //data encapsulation

    //MISC
    lx_BYTE,
    lx_FUNCTION,
    lx_VOID,

    //OPERATORS
    lx_OPERATOR,
    //math
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
    lx_LOG_AND,         //&
    lx_LOG_OR,          //|
    lx_LOG_NOT,         //!
    lx_LOG_NAND,        //!&
    lx_LOG_NOR,         //!|
    lx_LOG_XOR,         //||
    lx_LOG_XNOR,        //|!

    //comparison
    lx_CMP_EQU,         //==
    lx_CMP_NEQU,        //!=
    lx_CMP_GTR,         //>
    lx_CMP_LSS,         //<
    lx_CMP_GTR_EQU,     //>=
    lx_CMP_LSS_EQU,     //<=

    //general
    lx_GEN_LISTITEM,    //,
    lx_GEN_MEMBERREF,   //.
    lx_GEN_INDEX,       //:
    lx_GEN_LAMBDA,      //$(arg, arg, ...){expression}

    //encapsulates
    lx_ENC_OBRACK,      //[
    lx_ENC_OBRACE,      //{
    lx_ENC_OPARAN,      //(    
    lx_ENC_CBRACK,      //]
    lx_ENC_CBRACE,      //}
    lx_ENC_CPARAN,      //)
    lx_ENC_DQUOTE,      //"
    lx_ENC_SQUOTE,      //'

    //bitwise
    lx_BIT_AND,         //^&
    lx_BIT_OR,          //^|
    lx_BIT_NOT,         //^!
    lx_BIT_LEFT,        //^<
    lx_BIT_RIGHT,        //^>

    //KEYWORDS
    lx_KEYWORD,
    //primitives
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

    //utility
    lx_KW_TYPEOF,       //typeof(obj)
    lx_KW_DELETE,       //delete(obj)
    lx_KW_CAST,         //cast(obj, type)
    lx_KW_IMPORT,       //import(library)
    lx_KW_RELEASE,      //release(library)
    
    //REGISTER OFFSETS
    lx_STD_PLUGIN = 200,
    lx_EXT_PLUGIN = 500,

    //TYPE OFFSETS
    lx_TYPE_REG=800

} lexeme;

#endif