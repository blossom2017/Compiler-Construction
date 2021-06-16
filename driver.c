//MAITRI SHASTRI
//2014B2A70220P

#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include "lexer.h"
#include "parser.h"

int main(int argc,char *argv[])
{
char  *terminals[]={"ASSIGNOP","COMMENT","FUNID","ID","NUM","RNUM","STR","END","INT","REAL","STRING","MATRIX","MAIN","SQO","SQC","OP","CL","SEMICOLON","COMMA","IF","ELSE","ENDIF","READ","PRINT","FUNCTION","PLUS","MINUS","MUL","DIV","SIZE","AND","OR","NOT","LT","LE","EQ","GT","GE","NE","EPS","$"};


char  *nonterminals[]={"mainFunction","stmtsAndFunctionDefs","stmtOrFunctionDef","x","stmt","functionDef","declarationStmt", "assignmentStmt_type1","assignmentStmt_type2","ifStmt","ioStmt","funCallStmt","parameter_list","remainingList","type","var_list","more_ids","leftHandSide_singleVar","rightHandSide_type1","leftHandSide_listVar","rightHandSide_type2","arithmeticExpression","sizeExpression","booleanExpression","otherStmts","y","inputParameterList","var","listVar","arithmeticTerm" ,"z","operator_lowPrecedence","factor" ,"p","operator_highPrecedence","logicalOp","constrainedVars","relationalOp","matrixElement","matrix","rows","row","remainingColElements","m","j","i"};
//ntval or val field represents the index in this array 
int option;
printf("Necesssary information about code\n");
printf("(a)First and Follow sets automated\n");
printf("(b)Lexical Analyzer developed\n");
printf("(c)Parser developed and verifies syntactic correctness but does not do error recovery\n");
printf("(d)Parse tree constructed and printed for syntactically correct testcases\n");
printf("(e)Code works for syntactically correct testcases 1-4 \n");
printf("(f)Only the first error is detected in testcase4 since panic mode error recovery has not been implemented\n" );
printf("OPTIONS AVAILABLE:-\n");
printf("OPTION 1-PRINT COMMENT FREE CODE ON THE TERMINAL\n");
printf("OPTION 2-PRINT LIST OF ALL TOKENS\n");
printf("OPTION 3-REPORT ERRORS AND PARSE TO VERIFY SYNTACTIC CORRECTNESS OF THE CODE\n");

printf("OPTION 4-PARSE THE INPUT FILE AND PRINT PARSE TREE TO A FILE \n");
printf("OPTION 5 - PRINT ABSTRACT SYNTAX TREE\n");
printf("Enter your option 1/2/3/4/5 \n");
scanf("%d",&option);
FILE * fp=fopen(argv[1],"r");
endflag=1;
lnum=1;
if(fp==NULL)
{
	printf("Error in opening the given testcase file\n");
}

if(option==1)
{
	removecomments(fp);
	endflag=1;
	lnum=1;
	//for the next pass adjust these parameters so that next time if file is read in the same program line numbers start from 1 only
}
else if(option==2)

{

	printtokens(fp);
	endflag=1;
	lnum=1;
	//fclose(fp);
}
else if(option==3)
{
	//uncommnent the printing functions to verify whether the information has been calculated correctly and populated in the appropriate data-structures
	printerrorsonly(fp);
	endflag=1;
	lnum=1;
	fclose(fp);

	FILE * nfp=fopen(argv[1],"r");
	struct lhs * g=populategrammar(terminals,nonterminals);
	//struct lhs * g=populategrammar(terminals,nonterminals);
	populatefirstsets(g,terminals,nonterminals);
	populatefollowsets(g,terminals,nonterminals);
	//printfirstsetsverify(terminals,nonterminals);
	populateparsingtable(g,terminals,nonterminals);
	//printparsingtable();
	endflag=1;
	lnum=1;
	//verifies syntactic correctness without constructing the tree and only using stack
	printparsingorder(g,terminals,nonterminals,nfp);

}
else if(option==4)
{
	//uncommnent the printing functions to verify whether the information has been calculated correctly and populated in the appropriate data-structures
	FILE * writefp=fopen(argv[2],"w");
	if(writefp==NULL)
	{
		printf("Error in opening new file for printing inorder traversal\n");
	}


	struct lhs * g=populategrammar(terminals,nonterminals);
	//verifyprintgrammar(g,terminals,nonterminals);
	populatefirstsets(g,terminals,nonterminals);
	populatefollowsets(g,terminals,nonterminals);
	//printfirstsetsverify(terminals,nonterminals);
	populateparsingtable(g,terminals,nonterminals);
	//printparsingtable();
	endflag=1;
	lnum=1;
	//verifies syntactic correctness without constructing the tree and only using stack
	struct parsetreenode* root	=printparsingorder1(g,terminals,nonterminals,fp);
	printparsingtree(root,writefp);
//	constructAST1(&root);
//	printf("%s\n",nonterminals[root->child->val] );
//	printf("%s\n",nonterminals[root->child->child->val] );
//	printf("%s\n",nonterminals[root->child->child->sibling->val] );
//	printf("%s\n",nonterminals[root->child->child->val] );
	
//	printf("%s\n",nonterminals[root->child->val] );
	fclose(writefp);
}
else if ( option == 5 )
{
	FILE * writefp=fopen(argv[2],"w");
	if(writefp==NULL)
	{
		printf("Error in opening new file for printing inorder traversal\n");
	}


	struct lhs * g=populategrammar(terminals,nonterminals);
	//verifyprintgrammar(g,terminals,nonterminals);
	populatefirstsets(g,terminals,nonterminals);
	populatefollowsets(g,terminals,nonterminals);
	//printfirstsetsverify(terminals,nonterminals);
	populateparsingtable(g,terminals,nonterminals);
	//printparsingtable();
	endflag=1;
	lnum=1;
	//verifies syntactic correctness without constructing the tree and only using stack
	struct parsetreenode* root	=printparsingorder1(g,terminals,nonterminals,fp);
	printparsingtree(root,writefp);
	constructAST1(&root);
}
	





	return 0;
}
