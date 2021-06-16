//MAITRI SHASTRI
//2014B2A70220P


#ifndef stackDef_h
#define stackDef_h

struct snode{
	char stacksym[100];
	int flag;
	struct snode * next;

};
struct stack{
	struct snode * top;
	int size;	
};
#endif