#ifndef RTE_CMD
#define RTE_CMD

#include "node.h"

int initComponents();
int parseCmd(int, char **, nodeArg *);
int startRoot(nodeArg *);
int shutdown();

#endif