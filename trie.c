//MAITRI SHASTRI
//2014B2A70220P

//HAVE IMPLEMENTED TRIE TO STORE KEYWORDS FOR O(MAXKEYLENGTH) LOOKUP TIME 
//BUT THIS HAS NOT BEEN USED IN MAIN CODE
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<math.h>
#include "trieDef.h"
#include "lexerDef.h"



struct trienode * createnode()
{
	struct trienode * newnode=(struct trienode * )malloc(sizeof(struct trienode));

	 newnode->isleaf=0;
	newnode->count=0;
	newnode->val=-1;
	for(int i=0;i<27;i++)newnode->child[i]=NULL;
	//only node is initialized and children nodes set to NULL
	return newnode;	
}

void insertkeyword(struct trienode * root,char * string,int value)
{
	int val;
	struct trienode * ptr=root;
	for(int i=0;i<strlen(string);i++)
	{
		if(string[i]!='_')val=string[i]-'a';
		else val=26;
		
		if(ptr->child[val]!=NULL)ptr=ptr->child[val];
		else 
			{ptr->child[val]=createnode();
			ptr->count++;
			ptr=ptr->child[val];
			}	
	}
	ptr->isleaf=1;
	ptr->val=value;
}

int ispresent(struct trienode * root,char * string)
{
	int val;
	struct trienode * ptr=root;
	for(int i=0;i<strlen(string);i++)
	{
		 if(!(islower(string[i])||string[i]=='_') )return -1;
		if(string[i]!='_')val=string[i]-'a';
		else val=26;
	
		//as no keywords can contain digits or special characters
		if(ptr->child[val])ptr=ptr->child[val];
		else return -1;
	}
	if(ptr&&ptr->isleaf)return ptr->val;
	return -1;
}

int main()
{
	char * keywords[]={"_main","end","int","real","string","matrix","if","else","endif","read","print","function"};
	tkid tokenarray[]={MAIN,END,INT,REAL,STRING,MATRIX,IF,ELSE,ENDIF,READ,PRINT,FUNCTION};
	struct trienode* root= createnode();
	for(int i=0;i<12;i++)
	{
		insertkeyword(root,keywords[i],tokenarray[i]);
	}
	int check1=ispresent(root,"heyyy");
	int check2=ispresent(root,"int");
	printf("%d and %d\n",check1,check2 );

	return 0;
}
