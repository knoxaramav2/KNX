#ifndef REQ_TYPE
#define REQ_TYPE

#include "type.h"

//type register calls

//NUMERICS
int registerInt(type_reg*);
int registerUInt(type_reg*);
int registerLInt(type_reg*);
int registerULInt(type_reg*);
int registerSInt(type_reg*);
int registerUSInt(type_reg*);
int registerFloat(type_reg*);
int registerDouble(type_reg*);

//TEXT
int registerChar(type_reg*);
int registerUChar(type_reg*);
int registerWChar(type_reg*);
int registerString(type_reg*);
int registerWString(type_reg*);

//STRUCTURES
int registerArray(type_reg*);
int registerList(type_reg*);
int registerClass(type_reg*);


//MISC
int registerByte(type_reg*);
int registerFunction(type_reg*);
int registerVoid(type_reg*);
int registerException(type_reg*);
int registerScript(type_reg*);
int registerNull(type_reg*);

#endif