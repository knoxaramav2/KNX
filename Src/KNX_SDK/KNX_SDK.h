#ifndef KNX_SDK
#define KNX_SDK

#include "NodeCore.h"
#include "Utility.h"
#include "KMem.h"
#include "Debug.h"

/*
This static library declares all required classes, methods and definitions
for building an extension module runnable by the core interpreter.
*/

//KNX DLL calling convention
typedef int(__stdcall *k_imprt)();

#endif