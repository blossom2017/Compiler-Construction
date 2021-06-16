//MAITRI SHASTRI
//2014B2A70220P


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "stackadt.h"



struct stack * initializestack()
{
	struct stack * s=(struct stack *)malloc(sizeof(struct stack));
	s->top=NULL;
	s->size=0;
	return s;
} 

void pop(struct stack * s)
{
if(s->size==0)
{
	printf("Error:stack is empty\n");
	return;
}
struct snode * temp=s->top->next;
struct snode * ptr=s->top;
free(ptr);
s->top=temp;
s->size--;	
}

void push(struct stack * s,char stacksym[],int flag)
{
	
	struct snode * temp=s->top;
	struct snode * newnode=(struct snode *)malloc(sizeof(struct snode ));
	newnode->flag=flag;
	strcpy(newnode->stacksym,stacksym);
	newnode->next=s->top;
	s->top=newnode;
	s->size++;

}

int sizeofstack(struct stack * s)
{
	return s->size;
}

int isempty(struct stack * s)
{
	if(s->top)return 0;
	else return 1;
}

struct snode * top(struct stack * s)
{
	if(s->top==NULL)return NULL;
	struct snode * newnode=(struct snode * )malloc(sizeof(struct snode));
	strcpy(newnode->stacksym,s->top->stacksym);
	newnode->flag=s->top->flag;
	newnode->next=NULL;
	return newnode;
} 

void printcontents(struct stack * s)
{
	if(s->size==0)printf("Stack is empty\n");
	int count=s->size;
	struct snode * ptr=s->top;
	while(count--)

	{
		printf("%s\n",ptr->stacksym );
		ptr=ptr->next;
	}

}

