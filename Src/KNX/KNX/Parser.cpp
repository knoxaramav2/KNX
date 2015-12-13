#include "Parser.h"

#include <Debug.h>

extern Register masterRecord;
extern unsigned int MAX_NODES;
extern string globalBuffer;
extern systemState sysState;


void resolveSymbol(string::iterator start, string::iterator end, node*loc, ByteCode&seq)
{
	string raw(start,end);
	ByteChar*bc = new ByteChar();
	bc->raw = raw;
	bc->hash = FNV(raw);
	bc->rawFlag = true;

	short nType = getNumberType(raw);
	if (nType == -1)
		goto symbol;
	else if (nType < 2)
	{
		bc->dataType = KMemory::_int_;
		bc->data = (void*)static_cast<int*>(new int(atoi(raw.c_str())));
		seq.add(bc);
	}
	else if (nType == 2)
	{
		bc->dataType = KMemory::_dbl_;
		bc->data = (void*)static_cast<double*>(new double(atof(raw.c_str())));
		seq.add(bc);
	}
	goto end;
	//symbol check
symbol:
	bc->dataType = KMemory::_unknown_;
	seq.add(bc);
	goto end;
end:
//	delete bc;
	bc = nullptr;
}

ByteCode tokenize(string & raw, node*loc)
{
	ByteCode byteSequence;
	enum rMode{_normal,_strlit,_comment,_charlit};
	rMode mode = rMode::_normal;
	unsigned ln = (unsigned)raw.size();

	//Tokenize
	unsigned lIndex = 0;
	for (unsigned loop = 0; loop <= ln; ++loop)
	{
		if (loop == ln)//end point------------------------------
		{
			if (lIndex!=loop)
				switch (mode)
			{
				case rMode::_normal:
					resolveSymbol(raw.begin() + lIndex, raw.end(), loc, byteSequence);
					break;
				case rMode::_strlit:
				{
					ByteChar*bc = new ByteChar();
					bc->raw = string(raw.begin() + lIndex, raw.begin() + loop);
					bc->hash = FNV(bc->raw);
					bc->dataType = KMemory::_string_;
					bc->rawFlag = true;
					bc->data = (void*)static_cast<string*>(new string(raw.begin()+lIndex,raw.begin()+loop));
					byteSequence.add(bc);
					bc = nullptr;
				}
					break;
				case rMode::_comment:
					break;
				case rMode::_charlit:
					if (loop - lIndex == 0)
						printError(EMPTY_CHAR, to_string(lIndex));
					else if (loop - lIndex>1)
						printError(EXCESS_CHAR, to_string(lIndex) + " : " + string(raw.begin() + lIndex, raw.begin() + loop));
					else
					{
						ByteChar*bc = new ByteChar();
						bc->raw = raw[loop - 1];
						bc->hash = FNV(bc->raw);
						bc->dataType = KMemory::_char_;
						bc->rawFlag = true;
						bc->data = (void*)static_cast<char*>(new char(raw[loop-1]));
						byteSequence.add(bc);
						bc = nullptr;
						mode = rMode::_normal;
					}
					
					break;
			}
			break;
		}
		//mode switches------------------------------
		if (mode == rMode::_strlit)
		{
			if (raw[loop] == '\"')
			{
				ByteChar*bc = new ByteChar();
				bc->raw = string(raw.begin() + lIndex, raw.begin() + loop);
				bc->hash = FNV(bc->raw);
				bc->dataType = KMemory::_string_;
				bc->rawFlag = true;
				bc->data = (void*)static_cast<string*>(new string(raw.begin() + lIndex, raw.begin() + loop));
				byteSequence.add(bc);
				bc = nullptr;
				mode = rMode::_normal;
				lIndex = loop + 1;
			}
		}
		else if (mode == rMode::_charlit)
		{
			if (raw[loop] == '\'')
			{
				if (loop - lIndex == 0)
					printError(EMPTY_CHAR, to_string(loop));
				else if (loop-lIndex>1)
					printError(EXCESS_CHAR, to_string(loop) + " : " + string(raw.begin() + lIndex, raw.begin() + loop));
				else
				{
					ByteChar*bc = new ByteChar();
					bc->raw = raw[loop - 1];
					bc->hash = FNV(bc->raw);
					bc->dataType = KMemory::_char_;
					bc->rawFlag = true;
					bc->data = (void*)static_cast<char*>(new char(raw[loop - 1]));
					byteSequence.add(bc);
					bc = nullptr;
					mode = rMode::_normal;
					lIndex = loop + 1;
				}				
				
			}
		}
		else if (mode == rMode::_comment)
		{
			if (raw[loop] == '#')
			{
				lIndex = loop + 1;
				mode = rMode::_normal;
			}
		}
		else
		{//character scanner------------------------------
			switch (raw[loop])
			{
				//misc
			case ' ':
				if (lIndex < loop)
					resolveSymbol(raw.begin() + lIndex, raw.begin() + loop, loc, byteSequence);
				lIndex = loop + 1;
				break;
				//text operators
			case '\"':
				if (lIndex < loop)
					resolveSymbol(raw.begin() + lIndex, raw.begin() + loop, loc, byteSequence);
				mode = rMode::_strlit;
				lIndex = loop + 1;
				break;
			case '\'':
				if (lIndex < loop)
					resolveSymbol(raw.begin() + lIndex, raw.begin() + loop, loc, byteSequence);
				mode = rMode::_charlit;
				lIndex = loop + 1;
				break;
				//comment
			case '#':
				if (lIndex < loop)
					resolveSymbol(raw.begin() + lIndex, raw.begin() + loop, loc, byteSequence);
				mode = rMode::_comment;
				lIndex = loop + 1;
				break;
				//arithematic operators
			case '+':{
				if (lIndex < loop)
					resolveSymbol(raw.begin() + lIndex, raw.begin() + loop, loc, byteSequence);
				lIndex = loop + 1;
				ByteChar*bc = new ByteChar;
				bc->rawFlag = true;
				bc->raw = "+";
				bc->hash = FNV("+");
				bc->dataType = KMemory::_add_;
				byteSequence.add(bc);
				bc->data = nullptr;
				break; }
			case '-':{
				if (lIndex < loop)
					resolveSymbol(raw.begin() + lIndex, raw.begin() + loop, loc, byteSequence);
				ByteChar*bc = new ByteChar;
				bc->rawFlag = true;
				bc->raw = "+";
				bc->hash = FNV("+");
				bc->dataType = KMemory::_sub_;
				byteSequence.add(bc);
				bc->data = nullptr;
				lIndex = loop + 1;
				break; }
			case '/':
			{
				if (lIndex < loop)
					resolveSymbol(raw.begin() + lIndex, raw.begin() + loop, loc, byteSequence);
				ByteChar*bc = new ByteChar;
				bc->rawFlag = true;
				bc->raw = "/";
				bc->hash = FNV("/");
				bc->dataType = KMemory::_div_;
				byteSequence.add(bc);
				bc->data = nullptr;
				lIndex = loop + 1;
				break;
			}
			case '^':
			{
				if (lIndex < loop)
					resolveSymbol(raw.begin() + lIndex, raw.begin() + loop, loc, byteSequence);
				ByteChar*bc = new ByteChar;
				bc->rawFlag = true;
				bc->raw = "^";
				bc->hash = FNV("^");
				bc->dataType = KMemory::_pow_;
				byteSequence.add(bc);
				bc->data = nullptr;
				lIndex = loop + 1;
				break;
			}
			case '%':
			{
				if (lIndex < loop)
					resolveSymbol(raw.begin() + lIndex, raw.begin() + loop, loc, byteSequence);
				ByteChar*bc = new ByteChar;
				bc->rawFlag = true;
				bc->raw = "%";
				bc->hash = FNV("%");
				bc->dataType = KMemory::_mod_;
				byteSequence.add(bc);
				bc->data = nullptr;
				lIndex = loop + 1;
				break;
			}
			case '*':
			{
				if (lIndex < loop)
					resolveSymbol(raw.begin() + lIndex, raw.begin() + loop, loc, byteSequence);
				ByteChar*bc = new ByteChar;
				bc->rawFlag = true;
				bc->raw = "*";
				bc->hash = FNV("*");
				bc->dataType = KMemory::_mult_;
				byteSequence.add(bc);
				bc->data = nullptr;
				lIndex = loop + 1;
				break;
			}
			case (char)-5://root
			{
				if (lIndex < loop)
					resolveSymbol(raw.begin() + lIndex, raw.begin() + loop, loc, byteSequence);
				ByteChar*bc = new ByteChar;
				bc->rawFlag = true;
				bc->raw = (char)-5;
				bc->hash = FNV("" + (char)-5);
				bc->dataType = KMemory::_root_;
				byteSequence.add(bc);
				bc->data = nullptr;
				lIndex = loop + 1;
				break;
			}
				//escape character
			case '\\':
				++loop;
				break;
				//Lexical operators
			case '(':
			{
				if (lIndex < loop)
					resolveSymbol(raw.begin() + lIndex, raw.begin() + loop, loc, byteSequence);
				ByteChar*bc = new ByteChar;
				bc->rawFlag = true;
				bc->raw = "(";
				bc->hash = FNV("(");
				bc->dataType = KMemory::_;
				byteSequence.add(bc);
				bc->data = nullptr;
				lIndex = loop + 1;
				break;
			}
				//Logical operators
			default:

				break;
			}
		}
	}
	
	if (sysState.prntDebug)
		printMem(byteSequence);

	return byteSequence;
}

void interpret(string raw, node*loc)
{
	ByteCode bc = tokenize(raw, loc);
}