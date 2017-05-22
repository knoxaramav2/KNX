#ifndef KDK_DATTABLE
#define KDK_DATTABLE

typedef struct DatTable
{

char exeLocation [256];

}DatTable;

extern DatTable datTable;

void initDatTable();
DatTable getDatTable();

#endif