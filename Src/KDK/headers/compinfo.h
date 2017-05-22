#ifndef KDK_COMPINFO
#define KDK_COMPINFO

//VERSION--------------------------------
typedef struct version
{
char ver_string[15];
int major, minor, patch;
} version;

version newVersion(int, int, int);

//COMP INFO------------------------------
typedef struct comp_handle
{
version comp_version;

void * handle;
char * name;

} comp_handle;

//REGISTRATION---------------------------
//typedef comp_handle (*register_module)(void *);

#endif