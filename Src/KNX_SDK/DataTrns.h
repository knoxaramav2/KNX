#ifndef KNX_DATATR
#define KNX_DATATR

struct ByteChar
{
	char rawFlag : 1;
	char dataType : 7;
	void*data;
};

struct KNX_API
{

};

#endif