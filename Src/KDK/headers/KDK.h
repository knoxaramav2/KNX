#ifndef KDK
#define KDK

/*
Main header file for KDK
Includes are resources in this library
*/

#include "config.h"
#include "compinfo.h"
#include "dat_tables.h"
#include "node.h"
#include "node_reg.h"
#include "debug.h"
#include "token.h"
#include "type.h"
#include "error.h"

//required for some features to work.
//important features, the best features
void init_sdk();


//defines common handle between modules
//allows access to interfaces defined in
//seperate modules declared by KDK
typedef struct HKDK{



} HKDK;

#endif