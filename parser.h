//MAITRI SHASTRI
//2014B2A70220P

#include "parserDef.h"

extern int gettermid (char * ruletok,char * terminals[], char * nonterminals[]);
extern int getnontermid(char * ruletok,char * terminals[], char * nonterminals[]);
extern struct lhs * populategrammar(char * terminals[],char * nonterminals[]);
extern void verifyprintgrammar(struct lhs * grammar,char * terminals[], char * nonterminals[]);
extern char* convert(unsigned long long int n);
extern void populatefirstsets(struct lhs* grammar,char * terminals[], char * nonterminals[]);
extern void printfirstsetsverify(char * terminals[], char * nonterminals[]);
extern void populatefollowsets(struct lhs * grammar,char * terminals[],char * nonterminals[]);
extern void fillparsetableentry(int rulenum, unsigned long long int tsetval,int ntid,char * terminals[],char * nonterminals[]);
extern void printparsingtable();
extern void populateparsingtable(struct lhs * grammar, char * terminals[], char * nonterminals[]);
extern void printfirstsets(char * terminals[], char * nonterminals[]);
extern struct parsetreenode * getleftterminal(struct parsetreenode * cur);
extern struct parsetreenode * printparsingorder1(struct lhs * grammar,char * terminals[],char *nonterminals[],FILE * fp);
extern void printparsingorder(struct lhs * grammar,char * terminals[],char *nonterminals[],FILE * fp);

extern struct parsetreenode * getnextleft(struct parsetreenode * cur);
extern void insertchildren(struct parsetreenode * root,int rulenum,struct lhs* grammar,char * terminals[], char * nonterminals[]);
extern void printparsingtree(struct parsetreenode * root,FILE * fp);

////
extern int parsingtable[numnt][numt];

extern unsigned long long int firstsets[numnt];
extern unsigned long long int copyfirstsets[numnt];
extern unsigned long long int followsets[numnt];
extern unsigned long long int tsets[numnt];
