//MAITRI SHASTRI
//2014B2A70220P


#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include "stackadt.h"
#include "parserDef.h"
#include "lexer.h"



char buffer[1024];
int parsingtable[numnt][numt];

 unsigned long long int firstsets[numnt];
 unsigned long long int copyfirstsets[numnt];
 unsigned long long int followsets[numnt];
 unsigned long long int tsets[numnt];

int gettermid (char * ruletok,char * terminals[], char * nonterminals[])
	{
		for(int i=0;i<numt;i++)
		{
			if(strcmp(ruletok,terminals[i])==0)return i;
		}
		return -1;
	}

	int getnontermid(char * ruletok,char * terminals[], char * nonterminals[])
	{
		for(int i=0;i<numnt;i++)
		{
			if(strcmp(ruletok,nonterminals[i])==0)return i;
		}
		return -1;
	}




	struct lhs * populategrammar(char * terminals[],char * nonterminals[])
	{

	struct lhs * grammar=(struct lhs*)malloc(numrules*sizeof(struct lhs ));
	grammar[0].flag=1;
	FILE * fp=fopen("grammar.txt","r");
	int k=0;
	while(!feof(fp))
	{
		
	if(fgets(buffer,1024,fp)!=NULL)
	{
		int index=0;
		int lhs=1;
		int first=1;
		int count=0;
		struct rhs * ptr;
		//printf("%s\n",buffer );
		while(buffer[index]!='\0')
		{
		//	printf("fgets success\n");
			
			char * ruletok=(char *)malloc(100 * sizeof(char));
			int ruleindex=0;
			int ntflag=0;
			int enterloop=0;
			while(buffer[index]!=' '&&buffer[index]!='\0'&&buffer[index]!='\n'&&buffer[index]!='\r'&&(isalpha(buffer[index])||buffer[index]=='_'||isdigit(buffer[index])))
			{
				//all terminals are in upper case
			
				enterloop=1;
				if(isalpha(buffer[index])&& islower(buffer[index]))ntflag=1;
				ruletok[ruleindex++]=buffer[index++];
			}
			
			index++;
			if(enterloop)
			{
				count++;
				ruletok[ruleindex]='\0';
			//printf("ruletoken is %s\n",ruletok );
			if(lhs)
			{
			
			int val=getnontermid(ruletok,terminals,nonterminals);
		//	printf("%d\n",val );
			grammar[k].ntval=val;
			grammar[k].flag=1;
			lhs=0;
			
			}
			else
			{
				struct rhs* node=(struct rhs * )malloc(sizeof(struct rhs));
				node->next=NULL;
				if(!ntflag)
				{
					node->val=gettermid(ruletok,terminals,nonterminals);
				//	printf("%d\n",node->val );
					node->flag=0;

				}
				else
				{
					node->val=getnontermid(ruletok,terminals,nonterminals);
				//	printf("%d\n", node->val);
					node->flag=1;
				}
				if(first)
					{ grammar[k].head=node; first=0; ptr=node;}
				else { ptr->next=node; ptr=ptr->next;}
			}
			
			} 
		}
		grammar[k].count=count;
		k++;

	}

	}
	
	
	return grammar;
	}

	void verifyprintgrammar(struct lhs * grammar,char * terminals[], char * nonterminals[])
	{
		//print grammar on terminal for verification
		printf("GRAMMAR RULES----------------------------------------------------------\n");
		for(int k=0;k<numrules;k++)
		{
			//printf("inside for loop\n");
			printf("%s ",nonterminals[grammar[k].ntval] );
			struct rhs * ptr=grammar[k].head;
			int count=grammar[k].count;
		//	printf("%d count is \n",count );
			while(ptr!=NULL)
			{
				if(ptr->flag)
				{printf("%s ",nonterminals[ptr->val] );}
				else
				{printf("%s ",terminals[ptr->val] );}
			ptr=ptr->next;
			}
			printf("\n");
		}
		
	}



	char* convert(unsigned long long int n) {
	  char * binary=(char* )malloc(100 *sizeof(char));
	  
	  int i=0;
	  while(n>0)
	  {
	  	binary[i]=n%2+'0';
	  //	printf("%c\n",binary[i] );
	  	n=n/2;
	  	i++;
	  }
	  binary[i]='\0';
	  /*
	  char * revbinary=(char* )malloc(100 *sizeof(char));
	  int j=strlen(binary)-1;
	  for(int k=0;k<strlen(binary);k++)
	  {
	  	revbinary[k]=binary[j--];
	  }
	  */
	  return binary;
	} 


	void populatefirstsets(struct lhs* grammar,char * terminals[], char * nonterminals[])
	{
		unsigned long long int todo=0;
	unsigned long long int done=0;
		for(int i=0;i<numnt;i++)firstsets[i]=0;
	while(1)
	{
		
		for(int i=0;i<numnt;i++)copyfirstsets[i]=firstsets[i];
	for(int k=0;k<numrules;k++)
	{
		
		if(grammar[k].head->flag==0 )
		{
			
		if(!((firstsets[grammar[k].ntval]>>grammar[k].head->val)&1)	)firstsets[grammar[k].ntval]|=((unsigned long long int)1<<grammar[k].head->val);

		}
		else if(grammar[k].head->flag==1)
		{
			//printf("here\n");
			
			struct rhs * ptr=grammar[k].head;
			int value=1; 
			while(value&&ptr)
			{
			
				firstsets[grammar[k].ntval]|=firstsets[ptr->val];
			
				value=(unsigned int long long )1&(firstsets[ptr->val]>>39);

				if(value)firstsets[grammar[k].ntval]&=~((unsigned int long long  )1<<39);
				ptr=ptr->next;
				
			}
			if(!ptr&&value)value=firstsets[grammar[k].ntval]|((unsigned int long long  )1<<39);
			
			
		}
		
		



	}	

	int flag=0;
	for(int i=0;i<numnt;i++)
	{
		if(firstsets[i]!=copyfirstsets[i])
			{flag=1;
				break;
			}
	}
	if(!flag )break;
	}
	

	}
	void printfirstsetsverify(char * terminals[], char * nonterminals[])
	{
		printf("FIRST SETS\n");
		for(int i=0;i<numnt;i++)
		{
			printf("%-25s",nonterminals[i] );
			char *str=convert(firstsets[i]);
			for(int k=0;k<strlen(str);k++)
			{
				if(str[k]=='1')printf("%-10s",terminals[k] );
			}
			printf("\n");
		}

		printf("FOLLOW SETS\n");
		for(int i=0;i<numnt;i++)
		{
			printf("%-25s",nonterminals[i] );
			char *str=convert(followsets[i]);
			for(int k=0;k<strlen(str);k++)
			{
				if(str[k]=='1')printf("%-10s",terminals[k] );
			}
			printf("\n");
		}
	}

	void populatefollowsets(struct lhs * grammar,char * terminals[],char * nonterminals[])
	{
		for(int i=0;i<numnt;i++)followsets[i]=0;
			unsigned long long int copyfollowsets[numnt];
		followsets[grammar[0].ntval]|=(unsigned long long int )1<<gettermid("$",terminals,nonterminals);
	while(1)
	{
		for(int i=0;i<numnt;i++)copyfollowsets[i]=followsets[i];

		for(int k=0;k<numrules;k++)
		{
		struct rhs*	ptr=grammar[k].head;
			while(ptr)
			{
				if(ptr->flag==1)
				{
				struct rhs * ptrfoll=ptr->next;
				int value=1;
				while(ptrfoll&&value)
				{

					
					if(ptrfoll->flag==0)
						{followsets[ptr->val]|=(unsigned long long int )1<<ptrfoll->val;
							break;
						}
					else 
					{
					
						followsets[ptr->val]|=firstsets[ptrfoll->val];


						value=(unsigned int long long )1&(firstsets[ptrfoll->val]>>39);
						
						if(value)followsets[ptr->val]&=~((unsigned int long long  )1<<39);

						ptrfoll=ptrfoll->next;
					
					

					}	
				}
				
				if(value&&!ptrfoll)followsets[ptr->val]|=followsets[grammar[k].ntval];

				}
				ptr=ptr->next;
			}
		}	
		int flag=0;
	for(int i=0;i<numnt;i++)
	{
		if(followsets[i]!=copyfollowsets[i])
			{flag=1;
				break;
			}
	}
	if(!flag )break;
	}

	}

	
	void fillparsetableentry(int rulenum, unsigned long long int tsetval,int ntid,char * terminals[],char * nonterminals[])
	{
		
		int i=0;
		while(i<numt)
		{
			unsigned long long int v=(tsetval)&((unsigned long long int )1<<i);
			if(v!=0&&parsingtable[ntid][i]==-1)
			{
				
				parsingtable[ntid][i]=rulenum;
			}
			else if(v!=0&& parsingtable[ntid][i]!=-1)
			{
				printf("clashes\n");
			}
		//	tsetval=tsetval>>i;
			i++;
			
		}
	}

	void printparsingtable()
	{
		for(int i=0;i<numnt;i++)
		{
			for(int j=0;j<numt;j++)
			{
				printf("%-4d",parsingtable[i][j] );
			}
			printf("\n");
		}

	}

	void populateparsingtable(struct lhs * grammar, char * terminals[], char * nonterminals[])
	{
	//	for(int i=0;i<numnt;i++)tsets[i]=(unsigned long long int)0;
	
		for(int i=0;i<numnt;i++)
		{
			for(int j=0;j<numnt;j++)
			{
				parsingtable[i][j]=-1;

			}
		}
		for(int k=0;k<numrules;k++)
		{
			struct rhs * ptr=grammar[k].head;
			unsigned long long int value=1;
			tsets[grammar[k].ntval]=(unsigned long long int )0;	
			//later change try
			//tsets[grammar[k].ntval]|=firstsets[grammar[k].ntval];
		
			while(ptr&&value)
			{
				if(ptr->flag==0&&ptr->val==39)
				{
					
					tsets[grammar[k].ntval]|=followsets[grammar[k].ntval];
					break;
				}
				else if(ptr->flag==0)
				{
				//	printf("before %s %s\n",nonterminals[grammar[k].ntval], convert(tsets[grammar[k].ntval]) );
					tsets[grammar[k].ntval]|=(unsigned int long long)1<<ptr->val;
				//	printf(" after %s %s\n",nonterminals[grammar[k].ntval], convert(tsets[grammar[k].ntval]) );
					break;
				}
				else
				{
					tsets[grammar[k].ntval]|=firstsets[ptr->val];
					value=(unsigned int long long )1&(firstsets[ptr->val]>>39);
					if(value)tsets[ptr->val]&=~((unsigned int long long  )1<<39);
					ptr=ptr->next;
				}
				
			}
			if(!ptr&&value)tsets[grammar[k].ntval]|=followsets[grammar[k].ntval];
			//later change here also 

			unsigned long long int v1=(unsigned int long long )1&(firstsets[grammar[k].ntval]>>39);
			unsigned long long int v2=(unsigned int long long )1&(followsets[grammar[k].ntval]>>40);
			if(v1&&v2)tsets[grammar[k].ntval]|=(unsigned int long long )1&(firstsets[ptr->val]>>40);
			//end of later change

			int rulenum=k;
		//	printf("%s %s\n",nonterminals[grammar[k].ntval], convert(tsets[grammar[k].ntval]) );

			int nonterminalid=grammar[k].ntval;
			fillparsetableentry(rulenum,tsets[grammar[k].ntval],nonterminalid,terminals,nonterminals);
			//tsets[grammar[k].ntval]=0;
		}
	}



	void printfirstsets(char * terminals[], char * nonterminals[])
	{
		printf("FIRST SETS BITSETS(REV)\n");
		for(int i=0;i<numnt;i++)
		{
			printf("%s ",nonterminals[i] );
			printf("%s\n",convert(firstsets[i]) );
		}
		printf("FOLLOW SETS BITSETS(REV)\n");
		for(int i=0;i<numnt;i++)
		{
			printf("%s ",nonterminals[i] );
			printf("%s\n",convert(followsets[i]) );
		}

	}


	
void printparsingorder(struct lhs * grammar,char * terminals[],char *nonterminals[], FILE* fp)
{
	char * tarry[]={"ASSIGNOP","COMMENT","FUNID","ID","NUM","RNUM","STR","END","INT","REAL","STRING","MATRIX","MAIN","SQO","SQC","OP","CL",
					"SEMICOLON","COMMA","IF","ELSE","ENDIF","READ","PRINT","FUNCTION","PLUS","MINUS","MUL","DIV","SIZE","AND","OR","NOT","LT",
					"LE","EQ","GT","GE","NE"};
	printf("PARSING THE INPUT FILE\n");
	struct stack * s=(struct stack*)malloc(sizeof(struct stack));
	
	push(s,"$",0);
	push(s,"mainFunction",1);
	struct snode* x=top(s);
//	printf("%s\n",x->stacksym );
	int t=0;
	token * lookahead;
	lookahead=gettoken(fp);
//	printf("lookahead is %s\n",lookahead->lexeme );
	while(!isempty(s))
	{

//		printf("entering while loop\n");
		struct snode* x=top(s);
		if(strcmp(x->stacksym,"$")==0&&!gettoken(fp))
		{
			printf("Parsing process has ended ..Code syntactically correct\n");
			break;
		}
	//	printf("top is %s\n",x->stacksym );
		//lookahead=gettoken(fp);
	//printf("lookahead lexeme is %s\n",lookahead->lexeme);
	//	printf("%s\n",tarry[lookahead->ttype] );
		if(x->flag==0)
		{
		//	printf("Case terminals\n");
			if(strcmp(x->stacksym,tarry[lookahead->ttype])==0)
			{
				pop(s);
				t++;
				lookahead=gettoken(fp);
				//lookahead=tokens[t++];
			}
			else 
				{printf("Syntax Error: unmatching terminal found at line number %d \n",lnum);
			printf("%s\n",tarry[lookahead->ttype] );
			printf("%s\n",x->stacksym );
			break;
		}

		}
		else if(x->flag==1)
		{
		//	printf("Case non terminals\n");
			int id=getnontermid(x->stacksym,terminals,nonterminals);
			if(parsingtable[id][lookahead->ttype]==-1 )
			{
				printf("Syntax Error:The lookahead token does not match any expected token at line %d\n",lnum);
				printf("The lookahead token is %s\n",tarry[lookahead->ttype]);
				break;
			}
			else
			{
				int rulenum=parsingtable[id][lookahead->ttype];
		//		printf("%s ",nonterminals[grammar[rulenum].ntval] );
				pop(s);
				struct rhs * ptr=grammar[rulenum].head;
				struct stack * tempstack=initializestack();
				while(ptr)
				{
					if(ptr->flag)
						{
				//	printf("%s ",nonterminals[ptr->val] );
					push(tempstack,nonterminals[ptr->val],ptr->flag);
				}
					else 
						{
						//	printf("%s ",terminals[ptr->val] );
					push(tempstack,terminals[ptr->val],ptr->flag);
				}
					ptr=ptr->next;
				}
				if(strcmp(top(tempstack)->stacksym,"EPS")!=0)
				{
				while(!isempty(tempstack))
				{
					struct snode * temp=top(tempstack);
					pop(tempstack);
					//printf("what ...%s\n",temp->stacksym );
					push(s,temp->stacksym,temp->flag);


				}}
			//	printf("\n");

			}
		}
	}
}	


void insertchildren(struct parsetreenode * root,int rulenum,struct lhs* grammar,char * terminals[],char * nonterminals[])
{
	//assuming root node is already made you just have to insert the children
//	printf("inserting children for %s\n ",root->nodesym);
	struct rhs * ptr=grammar[rulenum].head;
	int count=0;
	struct parsetreenode * prev=NULL;
	int setflagt=0;
	int setflagnt=0;

	while(ptr)
	{
	//	if(ptr->flag)printf("inside while loop %s\n",nonterminals[ptr->val]);
	//	else printf("inside while loop %s\n",terminals[ptr->val]);
		count++;
		struct parsetreenode * newnode=(struct parsetreenode *)malloc(sizeof(struct parsetreenode));
		newnode->parent=root;
		newnode->sibling=NULL;
		newnode->flag=ptr->flag;
		
	//	printf("came ouur\n");

		if(!ptr->flag)newnode->isleaf=1;
		else newnode->isleaf=0;
		//strcpy(newnode->lexeme,"");
		
		strcpy(newnode->parentnodesym,root->nodesym);
	if(ptr->flag)	strcpy(newnode->nodesym,nonterminals[ptr->val]);
	else strcpy(newnode->nodesym,terminals[ptr->val]);
	newnode->val=ptr->val;
	newnode->count=0;
	newnode->child=NULL;
	
	if(prev)
		{prev->sibling=newnode; prev=prev->sibling;}
	else
	{ prev=newnode;
		root->child=newnode;
	}
	ptr=ptr->next;

	}
	root->count=count; 
}


struct parsetreenode * printparsingorder1(struct lhs * grammar,char * terminals[],char *nonterminals[],FILE * fp)
{
	char * tarry[]={"ASSIGNOP","COMMENT","FUNID","ID","NUM","RNUM","STR","END","INT","REAL","STRING","MATRIX","MAIN","SQO","SQC","OP","CL",
					"SEMICOLON","COMMA","IF","ELSE","ENDIF","READ","PRINT","FUNCTION","PLUS","MINUS","MUL","DIV","SIZE","AND","OR","NOT","LT",
					"LE","EQ","GT","GE","NE"};
//	printf("entering print parsing order -xxxxxxxxx\n");
	struct stack * s=(struct stack*)malloc(sizeof(struct stack));
	
	
	push(s,"$",0);
	push(s,"mainFunction",1);
	token * lookahead;
	lookahead=gettoken(fp);
	//printf("lookahead is %s\n",lookahead->lexeme );
	///adding tree part
	struct parsetreenode * root=(struct parsetreenode *)malloc(sizeof(struct parsetreenode));
	//struct parsetreenode ** lft;
	strcpy(root->nodesym,"mainFunction");
	root->parent=NULL;
	root->flag=1;
	root->parent=NULL;
	
	root->child=NULL;
	root->sibling=NULL;
	root->count=0;
	root->isleaf=0;
	root->val=0;
	
	strcpy(root->parentnodesym,"ROOT");
	//insertchildren(root,0,grammar,terminals,nonterminals);
	//struct parsetreenode * lf=getnextleft(root);
	//struct parsetreenode** lf=&root;
	struct snode* x=top(s);
//	printf("%s\n",x->stacksym );
	struct parsetreenode * cur=root;
	
	while(!isempty(s))
	{
	//	printf("%s checkning rot",root->nodesym);
	//	printf("leftmost is %s\n",(*lf)->nodesym );
	//	printf("entering while loop\n");
		struct snode* x=top(s);
		if(strcmp(x->stacksym,"$")==0)
		{
		//	printf("%s\n",root->nodesym );
			printf("Parsing process has ended ..Code is syntactically correct\n");
			//return root;
			break;
		}
		//printf("top is %s\n",x->stacksym );
		//lookahead=tokens[t];
		//printf("lookahead lexeme is %s\n",lookahead->lexeme);
	//	printf("%s\n",tarry[lookahead->ttype] );
		if(x->flag==0)
		{
		//	printf("Case terminals\n");
			if(strcmp(x->stacksym,tarry[lookahead->ttype])==0)
			{
				//putting the token value in the leftmost node
				char tempstr[20];
		//		printf("%scheck\n",cur->nodesym );
				strcpy(cur->lexeme,lookahead->lexeme);
				cur->ttype=lookahead->ttype;
				cur->num=lookahead->num;
				cur->rnum=lookahead->rnum;
				cur->line=lookahead->line;
				if(cur->sibling)cur=cur->sibling;
				else 
					{while(cur->parent)
				{
					if(cur->parent&&cur->parent->sibling)
					{
				 cur=cur->parent->sibling;
				 break;
				}
				cur=cur->parent;
				}}
		//		printf("%s change check\n",cur->nodesym );
				//	struct parsetreenode * lft=getleftterminal(root);
			
			//	lft->ttype=lookahead->ttype;
			//	strcpy(tempstr,lookahead->lexeme);
			//	strcpy(lft->lexeme,tempstr);
			//	lft->num=lookahead->num;
			//	lft->rnum=lookahead->rnum;
			//	lft->line=lookahead->line;
				//cur=lft;
			//	printf("saaaa%s\n",lft->lexeme );
			
			//	printf("left most is %s\n",(*lft)->nodesym );
				//lf=getnextleft(lf->child);
			//	printf("leftmost is %s\n",(*lft)->nodesym );
				lookahead=gettoken(fp);
				pop(s);
			//	t++;
				//lookahead=tokens[t++];
			}
			else 
				{printf("Syntax Error: unmatching terminal found at line number %d \n",lnum);
			printf("%s\n",tarry[lookahead->ttype] );
			printf("%s\n",x->stacksym );
			break;
		}

		}
		else if(x->flag==1)
		{
		//	printf("Case non terminals\n");
			int id=getnontermid(x->stacksym,terminals,nonterminals);

			if(parsingtable[id][lookahead->ttype]==-1 )
			{
				printf("Syntax Error:The lookahead token does not match any expected token at line %d\n",lnum);
				break;
			}
			else
			{

				int rulenum=parsingtable[id][lookahead->ttype];
				//inserting children and readjusting lf value
		//		printf("rulenum value is %d\n",rulenum );
			//	lf=getnextleft(root);
				insertchildren(cur,rulenum,grammar,terminals,nonterminals);
		//		printf("%scheck\n",cur->nodesym );
				if(strcmp(cur->child->nodesym,"EPS")!=0)
				{
				cur=cur->child;
				
				}
			else 
			{
				if(cur->sibling)cur=cur->sibling;
				else 
					{while(cur->parent)
				{
					if(cur->parent&&cur->parent->sibling)
					{
						cur=cur->parent->sibling;
						break;
					}
					cur=cur->parent;
				}}
			}
			
		//		printf("%s change check\n",cur->nodesym );
			
			//	printf("left most is %s\n",lf->nodesym );
			//	printf("%d chhhild\n",(*lf)->count );
			//	lf=getnextleft(lf);
			//	printf("left most is %s\n",lf->nodesym );

			//	printf("%s ",nonterminals[grammar[rulenum].ntval] );
				pop(s);
				struct rhs * ptr=grammar[rulenum].head;
				struct stack * tempstack=initializestack();
				while(ptr)
				{
					if(ptr->flag)
						{
						//	printf("%s ",nonterminals[ptr->val] );
					push(tempstack,nonterminals[ptr->val],ptr->flag);
				}
					else 
						{
						//	printf("%s ",terminals[ptr->val] );
					push(tempstack,terminals[ptr->val],ptr->flag);
				}
					ptr=ptr->next;
				}
				if(strcmp(top(tempstack)->stacksym,"EPS")!=0)
				{
				while(!isempty(tempstack))
				{
					struct snode * temp=top(tempstack);
					pop(tempstack);
				//	printf("what ...%s\n",temp->stacksym );
					push(s,temp->stacksym,temp->flag);


				}}
			//	printf("\n");

			}
		}
	}
	//printf("cominnnnnn\n");
	return root;
}	

void printparsingtree(struct parsetreenode * root,FILE * fp)
{
//printf("entering printing finc");	
char * tarry[]={"ASSIGNOP","COMMENT","FUNID","ID","NUM","RNUM","STR","END","INT","REAL","STRING","MATRIX","MAIN","SQO","SQC","OP","CL",
					"SEMICOLON","COMMA","IF","ELSE","ENDIF","READ","PRINT","FUNCTION","PLUS","MINUS","MUL","DIV","SIZE","AND","OR","NOT","LT",
					"LE","EQ","GT","GE","NE"};
//array used to get token name from tkid					
	
	char dummystr[20];
	strcpy(dummystr,"-----");
	
	if(!root)return;
	
	
	//process leftmost child
	if(root->child)printparsingtree(root->child,fp);
	
	//process root
	
	if(root->isleaf==1&&strcmp(root->nodesym,"EPS")!=0)
	{
	//	printf("ifffff\n");
		fprintf(fp,"%-25s",root->lexeme);
		fprintf(fp,"%-10d",root->line);
		fprintf(fp,"%-25s",tarry[root->ttype]);
		if(root->ttype==4)fprintf(fp,"%-10d",root->num);
	else if(root->ttype==5)fprintf(fp,"%-10f",root->rnum);
	else fprintf(fp,"%-10s",dummystr);
		fprintf(fp,"%-25s",root->parentnodesym);
		fprintf(fp,"%-5s","yes");
		fprintf(fp,"%-25s\n",dummystr);
		
		
	}
	else if(root->isleaf==1&&strcmp(root->nodesym,"EPS")==0)
	{
		fprintf(fp,"%-25s",dummystr);
		fprintf(fp,"%-10s",dummystr);
		fprintf(fp,"%-25s","EPS");
		fprintf(fp,"%-10s",dummystr);
		fprintf(fp,"%-25s",root->parentnodesym);
		fprintf(fp,"%-5s","yes");
		fprintf(fp,"%-25s\n",dummystr);

	}
		
	else 
	{
	//	printf("eeeeeeeeeeeeeeeeee%-25s",root->parentnodesym);
		fprintf(fp,"%-25s",dummystr);
		fprintf(fp,"%-10s",dummystr);
		fprintf(fp,"%-25s",dummystr);
		fprintf(fp,"%-10s",dummystr);
		fprintf(fp,"%-25s",root->parentnodesym);
		fprintf(fp,"%-5s","no");
		fprintf(fp,"%-25s\n",root->nodesym);
		
	}
	
	if(root->child)
	{
//process other children leaving the leftmost child
	struct parsetreenode * ptr=root->child;
	while(ptr&&ptr->sibling)
	{
		ptr=ptr->sibling;
		printparsingtree(ptr,fp);
	}
}

}




struct parsetreenode * remove_node(struct parsetreenode * parent , struct parsetreenode * childrem)
{
	//assuming you are given both parent's address and the address of the child to be removed
	//remove nodes that are of no obvious use
	char  *terminals[]={"ASSIGNOP","COMMENT","FUNID","ID","NUM","RNUM","STR","END","INT","REAL","STRING","MATRIX","MAIN","SQO","SQC","OP","CL","SEMICOLON","COMMA","IF","ELSE","ENDIF","READ","PRINT","FUNCTION","PLUS","MINUS","MUL","DIV","SIZE","AND","OR","NOT","LT","LE","EQ","GT","GE","NE","EPS","$"};
	char  *nonterminals[]={"mainFunction","stmtsAndFunctionDefs","stmtOrFunctionDef","x","stmt","functionDef","declarationStmt", "assignmentStmt_type1","assignmentStmt_type2","ifStmt","ioStmt","funCallStmt","parameter_list","remainingList","type","var_list","more_ids","leftHandSide_singleVar","rightHandSide_type1","leftHandSide_listVar","rightHandSide_type2","arithmeticExpression","sizeExpression","booleanExpression","otherStmts","y","inputParameterList","var","listVar","arithmeticTerm" ,"z","operator_lowPrecedence","factor" ,"p","operator_highPrecedence","logicalOp","constrainedVars","relationalOp","matrixElement","matrix","rows","row","remainingColElements","m","j","i"};
	//printf("Entering remove node func");
	struct parsetreenode * sib= childrem->sibling;
	if(sib && !sib->flag)printf("%s\n",terminals[sib->val] );
	else if(sib && sib->flag)printf("%s\n",nonterminals[sib->val] );
	if(!childrem->flag)
	printf("Entering remove node  %s %s \n",nonterminals[parent->val],terminals[childrem->val] );
	else printf("Entering remove node  %s %s \n",nonterminals[parent->val],nonterminals[childrem->val] );
	//printf("hereeee\n");
	if(parent->child==childrem)
	{
		parent->child=childrem->sibling;
		parent->count--;
		//printf("rettuuuu\n");
		free(childrem);
		if( parent ->child && parent->child->flag)printf("new child %s \n" , nonterminals[parent->child->val]);
	else if (parent -> child&& !parent->child->flag)printf("ne child  %s \n",terminals[parent->child->val]);
	return sib;
	
		
	}
	else {
			if(!parent->child->flag)	printf("%sconfirm \n",parent->child->lexeme );
			else printf("%s confirm \n",nonterminals[parent->child->val] );
			parent->count--;
		struct parsetreenode * ptr=parent->child->sibling;
		struct parsetreenode * ptrprev=parent->child;
		while(ptr!=NULL)
		{
			if(ptr==childrem)
			{
				ptrprev->sibling=ptr->sibling;
				
			
				break;
			}
			ptrprev=ptr;
			ptr=ptr->sibling;


	}
	if(parent->child->flag)printf("new child %s \n" , nonterminals[parent->child->val]);
	else printf("ne child  %s \n",terminals[parent->child->val]);
	free(ptr);

	return sib;

}
}


struct parsetreenode * remove_node_keep_children(struct parsetreenode * parent, struct parsetreenode * childrem)
{
	struct parsetreenode * sib= childrem->sibling;

	struct parsetreenode * ptrsib;
	char  *terminals[]={"ASSIGNOP","COMMENT","FUNID","ID","NUM","RNUM","STR","END","INT","REAL","STRING","MATRIX","MAIN","SQO","SQC","OP","CL","SEMICOLON","COMMA","IF","ELSE","ENDIF","READ","PRINT","FUNCTION","PLUS","MINUS","MUL","DIV","SIZE","AND","OR","NOT","LT","LE","EQ","GT","GE","NE","EPS","$"};
	char  *nonterminals[]={"mainFunction","stmtsAndFunctionDefs","stmtOrFunctionDef","x","stmt","functionDef","declarationStmt", "assignmentStmt_type1","assignmentStmt_type2","ifStmt","ioStmt","funCallStmt","parameter_list","remainingList","type","var_list","more_ids","leftHandSide_singleVar","rightHandSide_type1","leftHandSide_listVar","rightHandSide_type2","arithmeticExpression","sizeExpression","booleanExpression","otherStmts","y","inputParameterList","var","listVar","arithmeticTerm" ,"z","operator_lowPrecedence","factor" ,"p","operator_highPrecedence","logicalOp","constrainedVars","relationalOp","matrixElement","matrix","rows","row","remainingColElements","m","j","i"};
	if(!childrem->flag)
	printf("Entering remove node keep children parent %s removing child %s \n",nonterminals[parent->val],terminals[childrem->val] );
	else printf("Entering remove node keep children  parent %s  removing child%s \n",nonterminals[parent->val],nonterminals[childrem->val] );
	if(sib && !sib->flag)printf("%s\n",terminals[sib->val] );
	else if(sib && sib->flag)printf("%s\n",nonterminals[sib->val] );
	if(parent->child==childrem)
	{
		
		parent->child=childrem->child;
		parent->count--;
		parent->child->parent=parent;
		struct parsetreenode * pc=parent->child;
		struct parsetreenode * last ;
				while(pc !=NULL )
				{
					pc->parent=parent;
					strcpy(pc->parentnodesym,nonterminals[parent->val]);
					if(pc->sibling== NULL )last = pc;
					pc=pc->sibling;
				}
		//	pc->parent=parent;
		//	strcpy(pc->parentnodesym,nonterminals[parent->val]);
			last->sibling=sib;
			free(childrem);	

		return sib;
		
	
	}
	else 
	{
		printf("%sconfirm \n",parent->child->lexeme );
		struct parsetreenode * ptr= parent->child->sibling;
		struct parsetreenode * ptrprev=parent->child;
		parent->count--;
		while(ptr!=NULL)
		{
			if(ptr==childrem)
			{
				ptrprev->sibling=ptr->child;
				struct parsetreenode * pc=ptrprev->sibling;
				while(pc!=NULL)
				{
					pc->parent=parent;
					strcpy(pc->parentnodesym,nonterminals[parent->val]);
					if(pc->sibling==NULL)ptrsib=pc;
					pc=pc->sibling;
				}
				ptrsib->sibling=sib;
			
				break;
			}

			ptrprev=ptr;
			ptr=ptr->sibling;
			
		}
	free(childrem);
	 return sib;
		

	}

}



void constructAST(struct parsetreenode * head)
{
	int toremove[]={/*ASSIGNOP=*/0,/*COMMENT=*/1,/*FUNID=2,ID=3,NUM=4,RNUM=5,STR=6,END=*/7,/*INT=8,REAL=9,STRING=10,MATRIX=11,MAIN=*/12,/*SQO=*/13,/*SQC=*/14,/*OP=*/15,/*CL=*/16,
					/*SEMICOLON=*/17,/*COMMA=*/18,/*IF=*/19,/*ELSE=*/20,/*ENDIF=*/21,/*READ=22,PRINT=23FUNCTION=*/24,/*PLUS=25,MINUS=26,MUL=27,DIV=28,SIZE=29,AND=30,OR=31,NOT=32,LT=33,
					LE=34,EQ=35,GT=36,GE=37,NE=38*/};
	char  *terminals[]={"ASSIGNOP","COMMENT","FUNID","ID","NUM","RNUM","STR","END","INT","REAL","STRING","MATRIX","MAIN","SQO","SQC","OP","CL","SEMICOLON","COMMA","IF","ELSE","ENDIF","READ","PRINT","FUNCTION","PLUS","MINUS","MUL","DIV","SIZE","AND","OR","NOT","LT","LE","EQ","GT","GE","NE","EPS","$"};
	char  *nonterminals[]={"mainFunction","stmtsAndFunctionDefs","stmtOrFunctionDef","x","stmt","functionDef","declarationStmt", "assignmentStmt_type1","assignmentStmt_type2","ifStmt","ioStmt","funCallStmt","parameter_list","remainingList","type","var_list","more_ids","leftHandSide_singleVar","rightHandSide_type1","leftHandSide_listVar","rightHandSide_type2","arithmeticExpression","sizeExpression","booleanExpression","otherStmts","y","inputParameterList","var","listVar","arithmeticTerm" ,"z","operator_lowPrecedence","factor" ,"p","operator_highPrecedence","logicalOp","constrainedVars","relationalOp","matrixElement","matrix","rows","row","remainingColElements","m","j","i"};
	if(!head->flag)printf("Entering ast %s %d \n",terminals[head->val],head->flag);
	else printf("Entering ast %s %d \n",nonterminals[head->val],head->flag);
	int size = sizeof(toremove)/sizeof(int);
	if(head==NULL)return ;
	struct parsetreenode * ptr = head->child; 
	while(ptr!=NULL)
	{
		if(ptr->flag==1)
		printf("inside while lppo%d %s \n",ptr->val,nonterminals[ptr->val]);
		else if(ptr->flag==0)
		printf("inside while loop %d %s \n", ptr->val,terminals[ptr->val]);
	if(!ptr->flag && !ptr->convertflag)
	{
		//leaf node from the remove list
		if(strcmp(terminals[ptr->val],"EPS")==0)
			{
				//remove all non terminal nodes having EPS as children
		//	ptr =	remove_node(ptr->parent,ptr);
				//printf("eps RULES----------------------------------------------------------\n");
				struct parsetreenode * ret= ptr->parent;
				ptr->parent->child=NULL;
				return;
				ptr= NULL;
		if(ptr)	printf("%s Modified ptr\n",nonterminals[ptr->val] );
		//printf("i am backkk\n");
				//removing both EPS and it's parent non terminal
		//if(ptr)	ptr =	remove_node(ptr->parent->parent,ptr->parent);
		//	if(ptr)printf("%s Modified ptr\n",nonterminals[ptr->val] );

			continue;

			}//
		int flag=0;
		for(int i=0;i<size;i++)
		{
			if(toremove[i]==ptr->ttype)
			{
				flag=1;
				ptr =remove_node(head,ptr);
				break;
			}

		}
		if(!flag)
		{
		if(ptr->sibling)
		{	
			ptr=ptr->sibling;

			continue;
		}
		else return ;
		}
		else continue;
	}
		else if(ptr->flag || ptr->convertflag)
		{
			constructAST(ptr);

		 if(ptr->child == NULL)
			{
			//	printf("wwwwww\n");
			ptr =	remove_node(ptr->parent,ptr);
			if(ptr)			printf("%s Modified ptr\n",nonterminals[ptr->val] );

			continue;
			}
			
			//non terminals giving one terminal
			//was else if here ... 
			 if(strcmp(nonterminals[ptr->val],"relationalOp")==0||strcmp(nonterminals[ptr->val],"logicalOp")==0||strcmp(nonterminals[ptr->val],"operator_lowPrecedence")==0||strcmp(nonterminals[ptr->val],"operator_highPrecedence")==0)
			{
			ptr =	remove_node_keep_children(ptr->parent,ptr);
			if(ptr)printf("%s Modified ptr\n",nonterminals[ptr->val] );

			continue;
			}
			else if(strcmp(nonterminals[ptr->val],"stmt")==0)
			{
			ptr =	remove_node_keep_children(ptr->parent,ptr);
			if(ptr)printf("%s Modified ptr\n",nonterminals[ptr->val] );
			continue;
			}
			
			else if(strcmp(nonterminals[ptr->val],"rightHandSide_type1")==0)
			{
			ptr =	remove_node_keep_children(ptr->parent,ptr);
			continue;
			}
			else if(strcmp(nonterminals[ptr->val],"rightHandSide_type2")==0)
			{	
			ptr =	remove_node_keep_children(ptr->parent,ptr);
			continue;
			}
			
			else if(strcmp(nonterminals[ptr->val],"x")==0)
			{
				//after we have removed all x nodes containing EPS
			ptr =	remove_node_keep_children(ptr->parent,ptr);
			if(ptr)printf("%s Modified ptr\n",nonterminals[ptr->val] );
			continue;
			}
			else if(strcmp(nonterminals[ptr->val],"stmtOrFunctionDef")==0)
			{
			ptr =	remove_node_keep_children(ptr->parent,ptr);
			if(ptr)printf("%s Modified ptr\n",nonterminals[ptr->val] );
			continue;
			}	
			else if(strcmp(nonterminals[ptr->val],"type")==0)
			{	
			ptr =	remove_node_keep_children(ptr->parent,ptr);
			if(ptr)printf("%s Modified ptr\n",nonterminals[ptr->val] );
			continue;
			}

			else if(strcmp(nonterminals[ptr->val],"stmtsAndFunctionDefs")==0  && strcmp(nonterminals[ptr->parent->val],"stmtsAndFunctionDefs")==0)
			{
				ptr= remove_node_keep_children(ptr->parent->parent,ptr->parent);
				if(ptr)printf("%s Modified ptr\n",nonterminals[ptr->val] );
				continue;
			}
			/*
			else if (strcmp(nonterminals[ptr->val],"stmtsAndFunctionDefs")==0  && strcmp(nonterminals[ptr->child->val],"stmtsAndFunctionDefs")==0)
			{
				ptr= remove_node_keep_children(ptr,ptr->child);
				if(ptr)printf("%s Modified ptr\n",nonterminals[ptr->val] );
				continue;
			}
			*/
			else if(strcmp(nonterminals[ptr->val],"m")==0)
			{
			ptr =	remove_node_keep_children(ptr->parent,ptr);
			if(ptr)printf("%s Modified ptr\n",nonterminals[ptr->val] );
			continue;
			}
			
			else if(strcmp(nonterminals[ptr->val],"i")==0)
			{
			ptr =	remove_node_keep_children(ptr->parent,ptr);
			continue;

			}
			else if(strcmp(nonterminals[ptr->val],"leftHandSide_singleVar")==0)
			{
			ptr =	remove_node_keep_children(ptr->parent,ptr);
			continue;
			}
			else if(strcmp(nonterminals[ptr->val],"matrixelement")==0)
			{
			ptr =	remove_node_keep_children(ptr->parent,ptr);
			continue;
			}
			else if(strcmp(nonterminals[ptr->val],"declarationStmt")==0)
			{
				ptr= remove_node_keep_children(ptr,ptr->child->sibling);
				continue;
			}
			//handle boolean expressions
			else if(strcmp(nonterminals[ptr->val],"constrainedVars")==0)
			{
			ptr =	remove_node_keep_children(ptr->parent,ptr);
			continue;
			}
			else if(strcmp(nonterminals[ptr->val],"booleanExpression")==0)
			{

				if(ptr->child!=NULL && ptr->child->sibling!=NULL && ptr->child->sibling->flag==0)
				{
					//for AND OR and RELATIONAL OPERATORS

					
					ptr->ttype=ptr->child->sibling->ttype; 
					strcpy( ptr->lexeme,ptr->child->sibling->lexeme);
					ptr->line=ptr->child->sibling->line;
					ptr->flag=ptr->child->sibling->flag;
					strcpy(ptr->nodesym,ptr->child->sibling->nodesym);
					ptr->val=ptr->child->sibling->val;
					//don't change isLeaf since it is not a leaf
				ptr =	remove_node(ptr,ptr->child->sibling);
				continue;
				}
				else if(ptr->child!=NULL && ptr->child->flag==0 && strcmp(terminals[ptr->child->val],"NOT")==0)
				{
					//for NOT operator
					ptr->ttype=ptr->child->ttype;
					ptr->line=ptr->child->line;
					ptr->flag=ptr->child->flag;
					strcpy(ptr->nodesym,ptr->child->nodesym);
					strcpy(ptr->lexeme,ptr->child->lexeme);
					ptr->val=ptr->child->val;
				ptr =	remove_node(ptr,ptr->child);
				continue;
				}
				else 
				{
					printf("Something went wrong \n ERROR");
				}
			}
			
			//alternating recursions
			else if(strcmp(nonterminals[ptr->val],"listVar")==0)
			{
			ptr =	remove_node_keep_children(ptr->parent,ptr->child);
			continue;
			}
			else if(strcmp(nonterminals[ptr->val],"inputParameterList")==0)
			{
			ptr =	remove_node_keep_children(ptr,ptr->child->sibling);
			continue;
			}
			else if(strcmp(nonterminals[ptr->val],"remainingList")==0&&strcmp(nonterminals[ptr->parent->val],"parameter_list")==0)
			{
			ptr =	remove_node_keep_children(ptr->parent,ptr);
			continue;
			}
			else if(strcmp(nonterminals[ptr->val],"parameter_list")==0 && strcmp(nonterminals[ptr->parent->val],"remainingList")==0)
			{
			ptr =	remove_node_keep_children(ptr->parent,ptr);
			continue;
			}
			else if(strcmp(nonterminals[ptr->val],"var_list")==0 && strcmp(nonterminals[ptr->parent->val],"more_ids") == 0)
			{
			ptr =	remove_node_keep_children(ptr->parent,ptr);
			if(ptr)printf("%s Modified ptr\n",nonterminals[ptr->val] );
			continue;
			}
			else if(strcmp(nonterminals[ptr->parent->val],"var_list")==0&&strcmp(nonterminals[ptr->val],"more_ids")==0)
			{
			ptr =	remove_node_keep_children(ptr->parent,ptr);
			if(ptr)printf("%s Modified ptr\n",nonterminals[ptr->val] );
			continue;
			}
			//handle recursion
			else if(strcmp(nonterminals[ptr->val],"otherStmts")==0&&strcmp(nonterminals[ptr->parent->val],"otherStmts")==0)
			{
			ptr =	remove_node_keep_children(ptr,ptr->child->sibling);
			if(ptr)printf("%s Modified ptr\n",nonterminals[ptr->val] );
			continue;

			}
			//matrix recursion
			else if(strcmp(nonterminals[ptr->val],"rows")==0)
			{
			ptr =	remove_node_keep_children(ptr->parent,ptr);
			continue;
			}
			else if(strcmp(nonterminals[ptr->val],"j")==0)
			{
			ptr =	remove_node_keep_children(ptr->parent,ptr);
			continue;
				//semicolon removed from j
			}
			else if(strcmp(nonterminals[ptr->val],"remainingColElements")==0)
			{
			ptr =	remove_node_keep_children(ptr->parent,ptr);
			continue;
			}
			else if(strcmp(nonterminals[ptr->val],"rows")==0&&strcmp(nonterminals[ptr->parent->val],"rows")==0)
			{
			ptr =	remove_node_keep_children(ptr->parent,ptr);
			continue;
			}
			else if(strcmp(nonterminals[ptr->val],"var")==0 && !ptr->convertflag )
			{
			ptr =	remove_node_keep_children(ptr->parent,ptr);
			continue;

			}
			else if(strcmp(nonterminals[ptr->val],"arithmeticTerm")==0  || strcmp(nonterminals[ptr->val],"factor")==0 ||
				strcmp(nonterminals[ptr->val],"arithmeticExpression")==0 )
			{
			//	printf("gggggg\n");

			if((strcmp(nonterminals[ptr->val],"arithmeticTerm")==0 ||strcmp(nonterminals[ptr->val],"arithmeticExpression")==0)&& ptr->child && ptr->child->sibling && ! ptr->child->convertflag && ! ptr->child->sibling->convertflag)
			{

				//always inherit from right child
			//	printf("cccccc %s\n",nonterminals[ptr->val]);
			//	if(ptr->sibling)printf("%s dddd\n",nonterminals[ptr->sibling->val] );
			//	printf("bbbbb %s \n",ptr->child->sibling->lexeme );
			//	printf("bbbbb %s \n",ptr->child->lexeme );
			//	printf("bbbbb %s \n",ptr->child->sibling->child->lexeme );

				ptr->ttype=ptr->child->sibling->ttype; 
				strcpy( ptr->lexeme,ptr->child->sibling->lexeme);
				ptr->line=ptr->child->sibling->line;
				ptr->flag=ptr->child->sibling->flag;
				strcpy(ptr->nodesym,ptr->child->sibling->nodesym);
				ptr->val=ptr->child->sibling->val;
				
				ptr->convertflag =1;
				//morning addition
				
				
			//	printf("gggaaaaallllll %d \n", ptr->flag);
			//printf("%s Modified ptrxxx\n",nonterminals[ptr->sibling->val] );	
			
			remove_node_keep_children(ptr,ptr->child->sibling);
			
			//printf("%s Modified ptrxxx\n",nonterminals[ptr->sibling->val] );
			continue;
		}
		else if(!ptr->convertflag)
		{



			//	printf("%s\n",nonterminals[ptr->sibling->val] );
			ptr =	remove_node_keep_children(ptr->parent,ptr);
			if(ptr)printf("%s Modified ptr\n",nonterminals[ptr->val] );
			continue;
			}}
			else if(strcmp(nonterminals[ptr->val],"z")==0||strcmp(nonterminals[ptr->val],"p")==0)
			{
				ptr->ttype=ptr->child->ttype;
			//	printf("CAseeeee\n %d %d ",ptr->flag,ptr->val);
				ptr->line=ptr->child->line;
				ptr->flag=ptr->child->flag;
				strcpy(ptr->nodesym,ptr->child->nodesym);
				strcpy(ptr->lexeme,ptr->child->lexeme);
				ptr->val=ptr->child->val;
				
				ptr->num= ptr->child->num;
				ptr->rnum= ptr->child->rnum;
				ptr->convertflag =1;

			ptr =	remove_node(ptr,ptr->child);

			if(ptr)printf("%s Modified ptr\n",nonterminals[ptr->val] );
			continue;
			}

/*
			else  if((strcmp(nonterminals[ptr->val],"arithmeticTerm")==0 ||strcmp(nonterminals[ptr->val],"arithmeticExpression")==0)&& ptr->child && ptr->child->sibling)
			{

				//always inherit from right child
				printf("bbbbb %s \n",ptr->child->sibling->lexeme );
				printf("bbbbb %s \n",ptr->child->lexeme );
				printf("bbbbb %s \n",ptr->child->sibling->child->lexeme );

				ptr->ttype=ptr->child->sibling->ttype; 
				strcpy( ptr->lexeme,ptr->child->sibling->lexeme);
				ptr->line=ptr->child->sibling->line;
				ptr->flag=ptr->child->sibling->flag;
				strcpy(ptr->nodesym,ptr->child->sibling->nodesym);
				ptr->val=ptr->child->sibling->val;
				
				//morning addition
				strcpy(ptr->child->parentnodesym,ptr->lexeme);
				ptr->num= ptr->child->num;
				ptr->rnum= ptr->child->rnum;
				//don't change isLeaf since it is not a leaf
				printf("gggaaaaallllll %d \n", ptr->flag);
			ptr =	remove_node_keep_children(ptr,ptr->child->sibling);

			if(ptr)printf("%s Modified ptr\n",nonterminals[ptr->val] );
			continue;

			}
*/
			else ptr=ptr->sibling;


		}
		

	}
	if(!head->flag)printf("Exit ast %s %d \n",terminals[head->val],head->flag);
	else printf("Exit ast %s %d \n",nonterminals[head->val],head->flag);

	}

void printAST(struct parsetreenode * head)
{
	char  *terminals[]={"ASSIGNOP","COMMENT","FUNID","ID","NUM","RNUM","STR","END","INT","REAL","STRING","MATRIX","MAIN","SQO","SQC","OP","CL","SEMICOLON","COMMA","IF","ELSE","ENDIF","READ","PRINT","FUNCTION","PLUS","MINUS","MUL","DIV","SIZE","AND","OR","NOT","LT","LE","EQ","GT","GE","NE","EPS","$"};
	char  *nonterminals[]={"mainFunction","stmtsAndFunctionDefs","stmtOrFunctionDef","x","stmt","functionDef","declarationStmt", "assignmentStmt_type1","assignmentStmt_type2","ifStmt","ioStmt","funCallStmt","parameter_list","remainingList","type","var_list","more_ids","leftHandSide_singleVar","rightHandSide_type1","leftHandSide_listVar","rightHandSide_type2","arithmeticExpression","sizeExpression","booleanExpression","otherStmts","y","inputParameterList","var","listVar","arithmeticTerm" ,"z","operator_lowPrecedence","factor" ,"p","operator_highPrecedence","logicalOp","constrainedVars","relationalOp","matrixElement","matrix","rows","row","remainingColElements","m","j","i"};
	if(!head)return ;
	printAST(head->child);
	if( !head->flag && head->parent) printf("%s %s \n",head->lexeme, head->parent->nodesym );
	else if (!head->flag )printf("%s \n",head->lexeme);
	else if(head->flag && head->parent)printf("%s %s \n",nonterminals[head->val],head->parent->nodesym );
	else if ( head->flag )printf("%s\n",nonterminals[head->val] ); 
	if(head->child)
	{
//process other children leaving the leftmost child
	struct parsetreenode * ptr=head->child;
	while(ptr&&ptr->sibling)
	{
		ptr=ptr->sibling;
		printAST(ptr);
	}
}

}
void set_cvf(struct parsetreenode * head)
{
	if(!head)return ;
	set_cvf(head->child);
	head->convertflag =0;
	if(head->child)
	{
		struct parsetreenode * ptr=head->child;
	while(ptr&&ptr->sibling)
	{
		ptr=ptr->sibling;
		set_cvf(ptr);
	}
	}
}


	void  constructAST1(struct parsetreenode ** head)
{
	//printf("hiiiiiiiiiiii\n");
	set_cvf(*head);
	struct parsetreenode ** returnptr= head;
	constructAST(*head);
	printAST(*head);
	FILE * ast = fopen("ast.txt","w");

	printparsingtree(* head,ast);

}



