#ifndef RTE_HANDLES
#define RTE_HANDLES

typedef struct comp_handle
{

void * _handle;
char * name;

}comp_handle;

typedef struct comp_reg
{

int count;
comp_handle * handles;

} comp_reg;

extern comp_reg _comp_reg ;

void initCompReg();
void loadComponent(char *);

#endif