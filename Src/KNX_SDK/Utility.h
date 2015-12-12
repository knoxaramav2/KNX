#ifndef UTIL
#define UTIL

#include <string>

using namespace std;

/*
Defines convenient functions for common operations 
*/

//FNV-1a algorithm
__int64 FNV(string input);

//split member/scope reference
string nextScope(string&);

//-1 not valid number, 0  unsigned, 1 signed, 2 double
short getNumberType(string&);

//---------------OUTPUTS----------------//
#define BLACK			0
#define BLUE			1
#define GREEN			2
#define CYAN			3
#define RED				4
#define MAGENTA			5
#define BROWN			6
#define LIGHTGRAY		7
#define DARKGRAY		8
#define LIGHTBLUE		9
#define LIGHTGREEN		10
#define LIGHTCYAN		11
#define LIGHTRED		12
#define LIGHTMAGENTA13	13
#define YELLOW			14
#define WHITE			15

#ifdef _WIN64
void printCLRMessage(string,unsigned);
#endif
#ifndef __linux__
void printCLRMessage(string, unsigned);
#endif
#endif