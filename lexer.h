//MAITRI SHASTRI
//2014B2A70220P


#include "lexerDef.h"

#include "lexerDef.h"
extern int getnumvalueoflex(char * lexeme);
extern float getrnumvalueoflex(char * lexeme);
extern tkid gettokenkeyword(char * lexeme, int* flag);
extern void assignrelational(char * lexeme,token * newtoken);
extern FILE * getstream(FILE * newfp);
extern void  removecomments(FILE * fp);
extern token* gettoken(FILE * fp);
extern void printtokens(FILE * fp);
extern void printerrorsonly(FILE * fp);

extern int endflag;
extern int lnum;
