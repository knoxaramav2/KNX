#include "Error.h"
#include <stdio.h>
#include <iostream>

using namespace std;

#ifdef _WIN64
#define BLACK	0
#define BLUE	1
#define GREEN	2
#define RED		4
#define YELLOW	14
#define WHITE	15

#include <Windows.h>
void printWrn(string str)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),YELLOW);
	printf("%s",str.c_str());
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

void printErr(string str)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	printf("%s", str.c_str());
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}
#endif
#ifdef __linux__
void printWrn(string str)
{

}

void printErr(string str)
{

}
#endif

void printError(unsigned tp, string input)
{
	if (tp == 0)
		return;

	if (tp < WARN_MAX)
		printWrn("Warning : ");
	else
		printErr(input);
}