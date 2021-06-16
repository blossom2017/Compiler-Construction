//MAITRI SHASTRI
//2014B2A70220P


#include "stackDef.h"


extern struct stack * initializestack();
extern void pop( struct stack * s);
extern void push(struct stack * s,char stacksym[],int flag);
extern struct snode* top(struct stack * s);
extern int sizeofstack(struct stack * s);
extern int isempty(struct stack * s);
extern void printcontents(struct stack * s);
