#ifndef RTE_CMD
#define RTE_CMD

int initComponents();
int parseCmd(int, char **);
int startRoot();
int shutdown();

#endif