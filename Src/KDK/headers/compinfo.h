//VERSION--------------------------------
typedef struct version
{
char ver_string[64];

} version;

version * newVersion(int, int, int);

//COMP INFO------------------------------
typedef struct comp_info
{
version * comp_version;

} comp_info;