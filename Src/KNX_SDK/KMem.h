#ifndef KMEM
#define KMEM

#include "Utility.h"
#include "DataTrns.h"

#include <string>
#include <vector>
using namespace std;

//int16,int32,int64,double,char,std::string,array,port,pipe,struct
enum KMemory{
	_unknown_, _bool_, _sint_, _int_, _lint_, _dbl_, _char_, _string_, _arr_, _port_, _pipe_, _struct_, _func_, _file_,
	/*Math ops*/ _add_, _mult_, _div_, _mod_, _sub_, _root_, _pow_,
	/*Fnc Ops*/ _objRef_, _addrRef_, _flag_, _argOp_, _argCl_, _bodOp_, _bodCl_, _member_, _list_,_private_,_public_,_secure_,_heritage_,
	/*Logic Ops*/_and_, _or_, _not_, _nand_, _nor_, _xor_, _xnor_,
	/*Cmpare Ops*/_equ_, _gtr_, _lss_, _equGtr_, _equLss_, _compare_, _notcompare_,
	/*Internal Fncs*/_fif_, _felse_, _finteger_, _fshort_, _flong_, _fmethod_, _fexit_,_fdouble_, _fchar_, _fstring_, _farr_,
	_fport_, _fpipe_, _fstruct_, _ffunc_, _ffile_, _del_, _return_, _xnode_, _friend_, _killChild_, _terminate_, _setMemPolicy_, _send_
};

//Memory object super class
struct Mem
{
	//inherited type
	KMemory mType;
	__int64 hash;//name of target not retained
	bool available;//usage flag, for mutex
};

//Integers

struct _boolean :public Mem
{
	bool value;
	_boolean(std::string, bool value);
};

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

struct _function:public Mem
{
	//title, return type
	_function(std::string, KMemory);

	KMemory retType;

	ByteChar*execute();

	//pre-compiled code to execute
	vector <ByteCode> code;
};

struct _file :public Mem
{
	_file(std::string);
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