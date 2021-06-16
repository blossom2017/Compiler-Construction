//MAITRI SHASTRI
//2014B2A70220P
#ifndef lexerDef_h
#define lexerDef_h


typedef enum tkid{ASSIGNOP=0,COMMENT,FUNID,ID,NUM,RNUM,STR,END,INT,REAL,STRING,MATRIX,MAIN,SQO,SQC,OP,CL,
					SEMICOLON,COMMA,IF,ELSE,ENDIF,READ,PRINT,FUNCTION,PLUS,MINUS,MUL,DIV,SIZE,AND,OR,NOT,LT,
					LE,EQ,GT,GE,NE}tkid;


struct token
{
	int num;
	float rnum;
	tkid ttype; 
	char lexeme[100];
	int line;
};
typedef struct token token;

struct lte{
char keyword[25];
tkid ttype;
};




#endif