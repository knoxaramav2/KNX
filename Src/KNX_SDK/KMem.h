#ifndef KMEM
#define KMEM

#include "Utility.h"

#include <string>
#include <vector>
using namespace std;

//int16,int32,int64,double,char,std::string,array,port,pipe,struct
enum KMemory{_unknown_=-1,_sint_, _int_, _lint_, _dbl_,_char_,_string_,_arr_,_port_,_pipe_,_struct_};

//Memory object super class
struct Mem
{
	//inherited type
	KMemory mType;
	__int64 hash;//name of target not retained
	bool available;//usage flag, for mutex
};

//Integers

struct _short_integer :public Mem
{
	short value;
	_short_integer(std::string, short);
};

struct _integer :public Mem
{
	int value;
	_integer(std::string, int);
};

struct _long_integer :public Mem
{
	__int64 value;
	_long_integer(std::string,__int64);
};

//Decimal

struct _double :public Mem
{
	double value;
	_double(std::string, double);
};

//Text

struct _char :public Mem
{
	char value;
	_char(std::string, char);
};

struct _string :public Mem
{
	std::string value;
	_string(std::string, std::string);
};

//Peripherals/Device

struct _port :public Mem
{
	std::string target;
	_port(std::string, std::string);
};

struct _pipe :public Mem
{
	_pipe(std::string);
};

//Collections

struct _array :public Mem
{
	//array template
	KMemory targetType;
	vector <Mem*> elements;

	_array(std::string, KMemory);

	KMemory getTemplate();//return array type
	bool hasElement(string);
};

struct _struct :public Mem
{
	vector <_short_integer> sInts;
	vector <_integer> ints;
	vector <_long_integer> lints;

	vector <_double> dbls;
	
	vector <_char> chars;
	vector <_string> strings;

	vector <_port> ports;
	vector <_pipe> pipes;

	vector <_struct> structs;

	_struct(std::string);

	KMemory getItemType(std::string);
	Mem*getObject(std::string);
};


struct memCore
{
	vector <_short_integer> sInts;
	vector <_integer> ints;
	vector <_long_integer> lints;

	vector <_double> dbls;

	vector <_char> chars;
	vector <_string> strings;

	vector <_port> ports;
	vector <_pipe> pipes;

	vector <_struct> structs;

	KMemory getItemType(std::string);
	Mem*getObject(std::string);
};

#endif