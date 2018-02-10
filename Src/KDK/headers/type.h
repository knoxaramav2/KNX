#ifndef KDK_TYPE
#define KDK_TYPE

#define RAW_DATA 0x8000
typedef unsigned int T_TYPE;

/*
    Type partitions : 
    
    PRIMITIVE                       0x0001 - 0x0030 (48)
    KEYWORDS                        0x0031 - 0x00B0 (128)
    MODIFIERS                       0x00B1 - 0x00CA (26)
    MARKERS                         0x00CB - 0x00DA (16)
    FUNCTION DEFINITIONS            0x00DB - 0x04DA (1024)
    TYPE DEFINITIONS                0x04DB - 0x7FFF (1024)
*/


//Major partitions
#define C_PRIM_OFFSET       0x0001   
#define C_KW_OFFSET         0x0031
#define C_MOD_OFFSET        0x00B1
#define C_MRK_OFFSET        0x00CB
#define C_FNC_OFFSET        0x00DB
#define C_TYP_OFFSET        0x04DB        

//Minor partitions
#define C_DECL_OFFSET       0x0031
#define C_MATH_OFFSET       0x0051
#define C_ASGN_OFFSET       0x006F
#define C_COMP_OFFSET       0x007F
#define C_BOOL_OFFSET       0x008F
#define C_BIT_OFFSET        0x0096
#define C_CTL_OFFSET        0x00A0
#define C_MISC_OFFSET       0x00A5

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

//OPERATORS###################
//DECLARATION
#define C_D_INT         0x0031
#define C_D_DBL         0x0032   
#define C_D_BOOL        0x0033
#define C_D_CHAR        0x0034
#define C_D_STR         0x0035
#define C_D_FNC         0x0036
#define C_D_CLASS       0x0037
#define C_D_LIST        0x0038
#define C_D_DICT        0x0039
#define C_D_ENUM        0x003A

//MATH
#define C_ADD           0x0051
#define C_SUB           0x0052
#define C_MULT          0x0053
#define C_DIV           0x0054
#define C_MOD           0x0055
#define C_POW           0x0056
#define C_ROOT          0x0057

//ASSIGNMENT
#define C_SET           0x006F
#define C_ADD_SET       0x0071
#define C_SUB_SET       0x0072
#define C_MULT_SET      0x0073
#define C_DIV_SET       0x0074
#define C_MOD_SET       0x0075
#define C_POW_SET       0x0076
#define C_ROOT_SET      0x0077
#define C_INC_SET       0x0078
#define C_DEC_SET       0x0079


//COMPARISON
#define C_EQU           0x007F
#define C_NEQU          0x0080
#define C_GTR           0x0081
#define C_LSS           0x0082
#define C_GTR_EQU       0x0083
#define C_LSS_EQU       0x0084
#define C_INN_INC       0x0085   //inner range inclusive
#define C_OUT_INC       0x0086   //outer range ...
#define C_INN_EXC       0x0087   //inner range exclusive
#define C_OUT_EXC       0x0088   //outer range ...

//BOOLEAN LOGIC
#define C_L_AND         0x008F
#define C_L_OR          0x0090
#define C_L_NOT         0x0091
#define C_L_NAND        0x0092
#define C_L_NOR         0x0093
#define C_L_XOR         0x0094
#define C_L_XNOR        0x0095

//BITWISE
#define C_B_AND         0x0096
#define C_B_OR          0x0097
#define C_B_XOR         0x0098
#define C_B_INV         0x0099

//CONTROL
#define C_IF            0x00A0
#define C_ELSE          0x00A1
#define C_WHILE         0x00A2
#define C_DO            0x00A3
#define C_SWITCH        0x00A4

//MISC
#define C_IMPORT        0x00A5
#define C_DELETE        0x00A6
#define C_PRINT         0x00A7

//MODIFIERS###################

//MARKERS#####################
#define C_BREAK         0x00E1
#define C_CONTINUE      0x00E2

#endif