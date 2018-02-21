#ifndef KDK_TYPE
#define KDK_TYPE

#define RAW_DATA 0x8000
typedef unsigned int T_TYPE;

/*
    Type partitions : 
    
    PRIMITIVE                       0x0000 - 0x0040 (64)
    KEYWORDS/OPERATORS              0x0041 - 0x0280 (575)
    MODIFIERS                       0x0281 - 0x02A0 (32)
    MARKERS                         0x02A1 - 0x02C0 (32)
    FUNCTION DEFINITIONS            0x02C1 - 0x0AC0 (2048)
    TYPE DEFINITIONS                0x0AC1 - 0x12C0 (2048)
*/

//Major partitions
#define C_PRIM_OFFSET       0x0000   
#define C_KW_OFFSET         0x0041
#define C_MOD_OFFSET        0x0281
#define C_MRK_OFFSET        0x02A1
#define C_FNC_OFFSET        0x02C1
#define C_TYP_OFFSET        0x0AC1        

//Minor partitions
#define C_DECL_OFFSET       0x0041
#define C_MATH_OFFSET       0x0081
#define C_ASGN_OFFSET       0x00C1
#define C_COMP_OFFSET       0x0101
#define C_BOOL_OFFSET       0x0141
#define C_BIT_OFFSET        0x0181
#define C_CTL_OFFSET        0x01C1
#define C_MISC_OFFSET       0x0201

#define IS_CORE_EXEC(x) (x>=C_DECL_OFFSET && x<C_MOD_OFFSET)
#define IS_CORE_OP(x) (x>=C_MATH_OFFSET && x<C_CTL_OFFSET)

//TYPES#######################
#define C_T_NA          0x0000

#define C_T_INT         0x0001
#define C_T_DBL         0x0002
#define C_T_BOOL        0x0003
#define C_T_CHAR        0x0004
#define C_T_STR         0x0005
#define C_T_FNC         0x0006
#define C_T_CLASS       0x0007
#define C_T_LIST        0x0008
#define C_T_DICT        0x0009
#define C_T_ENUM        0x000A
#define C_T_VOID        0x000B

//OPERATORS###################
//DECLARATION
#define C_D_INT         0x0041
#define C_D_DBL         0x0042   
#define C_D_BOOL        0x0043
#define C_D_CHAR        0x0044
#define C_D_STR         0x0045
#define C_D_FNC         0x0046
#define C_D_CLASS       0x0047
#define C_D_LIST        0x0048
#define C_D_DICT        0x0049
#define C_D_ENUM        0x004A

//MATH
#define C_ADD           0x0081
#define C_SUB           0x0082
#define C_MULT          0x0083
#define C_DIV           0x0084
#define C_MOD           0x0085
#define C_POW           0x0086
#define C_ROOT          0x0087

//ASSIGNMENT
#define C_SET           0x00C1
#define C_ADD_SET       0x00C2
#define C_SUB_SET       0x00C3
#define C_MULT_SET      0x00C4
#define C_DIV_SET       0x00C5
#define C_MOD_SET       0x00C6
#define C_POW_SET       0x00C7
#define C_ROOT_SET      0x00C8
#define C_INC_SET       0x00C9
#define C_DEC_SET       0x00CA
#define C_INC_SET_PRE   0x00CB
#define C_INC_SET_PST   0x00CC
#define C_DEC_SET_PRE   0x00CD
#define C_DEC_SET_PST   0x00CE

//COMPARISON
#define C_EQU           0x0101
#define C_NEQU          0x0102
#define C_GTR           0x0103
#define C_LSS           0x0104
#define C_GTR_EQU       0x0105
#define C_LSS_EQU       0x0106
#define C_INN_INC       0x0107   //inner range inclusive
#define C_OUT_INC       0x0108   //outer range ...
#define C_INN_EXC       0x0109   //inner range exclusive
#define C_OUT_EXC       0x010A   //outer range ...

//BOOLEAN LOGIC
#define C_L_AND         0x0141
#define C_L_OR          0x0142
#define C_L_NOT         0x0143
#define C_L_NAND        0x0144
#define C_L_NOR         0x0145
#define C_L_XOR         0x0146
#define C_L_XNOR        0x0147

//BITWISE
#define C_B_AND         0x0181
#define C_B_OR          0x0182
#define C_B_XOR         0x0183
#define C_B_INV         0x0184

//CONTROL
#define C_IF            0x01C1
#define C_ELSE          0x01C2
#define C_WHILE         0x01C3
#define C_DO            0x01C4
#define C_SWITCH        0x01C5

//MISC
#define C_IMPORT        0x0201
#define C_DELETE        0x0202
#define C_PRINT         0x0203
#define C_LIST          0x0204
#define C_FLAG          0x0205

//MODIFIERS###################
#define C_M_A           0x0281

//MARKERS#####################
#define C_BREAK         0x02A1
#define C_CONTINUE      0x02A2
#define C_O_PARAN       0x02A3
#define C_C_PARAN       0x02A4
#define C_O_BRACE       0x02A5
#define C_C_BRACE       0x02A6
#define C_O_BRACK       0x02A7
#define C_C_BRACK       0x02A8

#endif