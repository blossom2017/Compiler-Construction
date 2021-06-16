//MAITRI SHASTRI
//2014B2A70220P

#ifndef parserDef_h
#define parserDef_h

#include "lexerDef.h"
#define numrules 88
#define numt 41
#define numnt 46

struct lhs
	{
		int ntval;
		int flag;
		int count;
		struct rhs * head;
	};

struct rhs
	{
		int val;
		int flag;
		struct rhs* next;
	};

struct parsetreenode
{
	struct parsetreenode * parent;
	struct parsetreenode * child;
	
	struct parsetreenode * sibling;
	int count;
	int num;
	float rnum;
	tkid ttype; 
	char lexeme[100];
	int line;
	int flag;
	char nodesym[100];
	char parentnodesym[100];
	int isleaf;
	int convertflag ;
	int val;
};


#endif
