//MAITRI SHASTRI
//2014B2A70220P

#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include "lexerDef.h"

#define SIZE_TEMP 1024
#define BUF_SIZE 2000

//GLOBAL VARIABLES TO DECLARE LINE NO, POINTER IN BUFFER,CHARACTER BUFFER
int lnum=1;
char buf[BUF_SIZE];
int bufptr=0;
int endflag=1;

//LOOKUPTABLE-TO MATCH KEYWORDS
struct lte lookuptable[12]={
{"_main",MAIN},
{"end",END},
{"int",INT},
{"real",REAL},
{"string",STRING},
{"matrix",MATRIX},
{"if",IF},
{"else",ELSE},
{"endif",ENDIF},
{"read",READ},
{"print",PRINT},
{"function",FUNCTION},

};


int getnumvalueoflex(char *lexeme)
{
	//get numerical value of the lexeme if it represents an integer
	int num=0;
	int i=0;
	int fact=1;
	while(lexeme[i]!='\0')
	{
		num=num*fact+(lexeme[i]-'0');
		fact*=10;
		i++;
	}
	return num;
}

float getrnumvalueoflex(char *lexeme)
{
	//get floating point value of a lexeme if it represents a real number
	float num=0;
	int fact=1;
	int i=0;
	while(lexeme[i]!='.')
	{
		num+=num*fact+(lexeme[i]-'0');
		i++;
		fact*=10;
	}
	i++;
	float dp=0;
	float ffact=1;
	int count=1;
	while(lexeme[i]!='\0')
	{
		dp=dp*ffact+(lexeme[i]-'0');
		fact*=10;
		i++;
		count++;
	}
	dp=dp/(pow(10,count));

//if(count>2)printf("Error:Number of digits after the decimal point exceeds the given limit");

	num+=dp;
	return num;
}

int gettokenkeyword(char * lexeme, int* flag)
{
	//return the token id if the lexeme is a keyword else return -1
	for(int i=0;i<12;i++)
	{
		if(strcmp(lexeme,lookuptable[i].keyword)==0)
		{
			*flag=1;
			return lookuptable[i].ttype;
		}
	}
	*flag=0;
return -1;
	//indicate that no matching keyword has been found
}

void assignrelational(char * lexeme,token * newtoken)
{
	//return the relational operator token corresponding to the given lexeme
	strcpy(newtoken->lexeme,lexeme);
	if(strcmp(lexeme,".and.")==0)newtoken->ttype=AND;
	else if(strcmp(lexeme,".or.")==0)newtoken->ttype=OR;
	else newtoken->ttype=NOT;
}

FILE * getstream(FILE * newfp)
{
	//reading characters to buffer from file
//printf("Reading stream\n");
	if(newfp==NULL)
		{
	
			return NULL;
		}	
	if(fgets(buf,BUF_SIZE-1,newfp)==NULL)
		{
//			printf("noww\n");
			endflag=0;
			buf[0]='\0';
			return NULL;
		}
	
	
	return newfp;
	

}

token* gettoken(FILE * fp)
{
	//returns the next valid token and NULL if eof is reached
	
	if(fp==NULL)return NULL;

	token * newtoken;

	while(endflag)
{	
	if((bufptr>=BUF_SIZE||buf[bufptr]=='\0'))
	{
		
		fp=getstream(fp);
	//	if(!fp||(feof(fp)))break;
		bufptr=0;
	}


	 newtoken=(token*)malloc(sizeof(token));
	newtoken->num=-1;
	newtoken->rnum=-1;
	newtoken->line=lnum;
	
	newtoken->ttype=-1;

		
		char *lexeme=(char *)malloc(100*sizeof(char));

		char *copy=(char *)malloc(100*sizeof(char));

		int lexptr=0;
		int match=0;
		int longlength=0;
		int matchsp=0;
		int patternflag=0;
	
		lexeme[lexptr]=buf[bufptr];
		char val=lexeme[lexptr];
	
		//First handle all single character tokens which have just one state=final state without any lookaheads
		if(val=='\n')
			{
				//printf("a");
				matchsp=1;
				patternflag=1;

				bufptr++;
				if((bufptr>=BUF_SIZE||buf[bufptr]=='\0'))
	{
		
		fp=getstream(fp);
	//	if(!fp||(feof(fp)))break;
		bufptr=0;
	}
				lnum++;
			//	continue;
			}
		else if(val==' '||val=='\t'||val=='\r')
			{
				//printf("b");
				bufptr++;
				matchsp=1;
				patternflag=1;
			//	continue;
				if((bufptr>=BUF_SIZE||buf[bufptr]=='\0'))
	{
		
		fp=getstream(fp);
	//	if(!fp||(feof(fp)))break;
		bufptr=0;
	}
			}
		
		else if(val=='[')
		{	
			//printf("c");
			match=1;
			patternflag=1;
			lexeme[lexptr+1]='\0';
			strcpy(newtoken->lexeme,lexeme);
			newtoken->ttype=SQO;
			bufptr++;
			if((bufptr>=BUF_SIZE||buf[bufptr]=='\0'))
	{
		
		fp=getstream(fp);
	//	if(!fp||(feof(fp)))break;
		bufptr=0;
	}
		//	continue;
		}
		else if(val==']')
		{
			//printf("d");
			match=1;
			patternflag=1;
			lexeme[lexptr+1]='\0';
			strcpy(newtoken->lexeme,lexeme);
			newtoken->ttype=SQC;
			bufptr++;
			if((bufptr>=BUF_SIZE||buf[bufptr]=='\0'))
	{
		
		fp=getstream(fp);
	//	if(!fp||(feof(fp)))break;
		bufptr=0;
	}
		//	continue;
		}
		else if(val=='(')
		{
		//	printf("e");
			match=1;
			patternflag=1;
			lexeme[lexptr+1]='\0';
			strcpy(newtoken->lexeme,lexeme);
			newtoken->ttype=OP;
			bufptr++;
			if((bufptr>=BUF_SIZE||buf[bufptr]=='\0'))
	{
		
		fp=getstream(fp);
	//	if(!fp||(feof(fp)))break;
		bufptr=0;
	}
		//	continue;
		}
		else if(val==')')
		{
			//printf("f");
			match=1;
			patternflag=1;
			lexeme[lexptr+1]='\0';
			strcpy(newtoken->lexeme,lexeme);
			newtoken->ttype=CL;
			bufptr++;
			if((bufptr>=BUF_SIZE||buf[bufptr]=='\0'))
	{
		
		fp=getstream(fp);
	//	if(!fp||(feof(fp)))break;
		bufptr=0;
	}
		//	continue;
		}
		else if(val==';')

		{
			//printf("g");
			match=1;
			patternflag=1;
			lexeme[lexptr+1]='\0';
			strcpy(newtoken->lexeme,lexeme);
			newtoken->ttype=SEMICOLON;
			bufptr++;
			if((bufptr>=BUF_SIZE||buf[bufptr]=='\0'))
	{
		
		fp=getstream(fp);
	//	if(!fp||(feof(fp)))break;
		bufptr=0;
	}
		//	continue;
		}
		else if(val==',')
		{
			//printf("h");
			match=1;
			patternflag=1;
			lexeme[lexptr+1]='\0';
			strcpy(newtoken->lexeme,lexeme);
			newtoken->ttype=COMMA;
			bufptr++;
			if((bufptr>=BUF_SIZE||buf[bufptr]=='\0'))
	{
		
		fp=getstream(fp);
	//	if(!fp||(feof(fp)))break;
		bufptr=0;
	}
			//continue;
		}
		else if(val=='+')
		{
		//	printf("i");
			match=1;
			lexeme[lexptr+1]='\0';
			strcpy(newtoken->lexeme,lexeme);
			newtoken->ttype=PLUS;
			patternflag=1;
			bufptr++;
			if((bufptr>=BUF_SIZE||buf[bufptr]=='\0'))
	{
		
		fp=getstream(fp);
	//	if(!fp||(feof(fp)))break;
		bufptr=0;
	}
			//continue;
		}
		else if(val=='-')
		{
			//printf("j");
			match=1;
			lexeme[lexptr+1]='\0';
			patternflag=1;
			strcpy(newtoken->lexeme,lexeme);
			newtoken->ttype=MINUS;
			bufptr++;
			if((bufptr>=BUF_SIZE||buf[bufptr]=='\0'))
	{
		
		fp=getstream(fp);
	//	if(!fp||(feof(fp)))break;
		bufptr=0;
	}
		//	continue;
		}
		else if(val=='*')
		{
		//	printf("k");
			match=1;
			lexeme[lexptr+1]='\0';
			patternflag=1;
			strcpy(newtoken->lexeme,lexeme);
			newtoken->ttype=MUL;
			bufptr++;
			if((bufptr>=BUF_SIZE||buf[bufptr]=='\0'))
	{
		
		fp=getstream(fp);
	//	if(!fp||(feof(fp)))break;
		bufptr=0;
	}
		//	continue;

		}
		else if(val=='/')
		{
		//	printf("l");
			match=1;
			lexeme[lexptr+1]='\0';
			patternflag=1;
			strcpy(newtoken->lexeme,lexeme);
			newtoken->ttype=DIV;
			bufptr++;
			if((bufptr>=BUF_SIZE||buf[bufptr]=='\0'))
	{
		
		fp=getstream(fp);
	//	if(!fp||(feof(fp)))break;
		bufptr=0;
	}
		//	continue;

		}
		else if(val=='@')
		{
		//	printf("m");
			match=1;
			lexeme[lexptr+1]='\0';
			patternflag=1;
			strcpy(newtoken->lexeme,lexeme);
			newtoken->ttype=SIZE;
			bufptr++;
		//	continue;
		}
		
	
	//check relational operators
		else if(val=='.')
		{
			patternflag=1;
			//printf("n");
			bufptr++;
			if(bufptr>=BUF_SIZE||buf[bufptr]=='\0')
					{
						fp=getstream(fp);
					//	if(!fp||(feof(fp)))break;
						bufptr=0;
						
					}
			lexptr++;
				for(int k=0;k<4;k++)
				{
					
					lexeme[lexptr++]=buf[bufptr++];
					if(bufptr>=BUF_SIZE||buf[bufptr]=='\0')
					{
						fp=getstream(fp);
						bufptr=0;
					//	if(!fp||(feof(fp)))break;
					}
					lexeme[lexptr]='\0';
					if(strcmp(lexeme,".and.")==0||strcmp(lexeme,".or.")==0||strcmp(lexeme,".not.")==0)

					{match=1;break;}
				}
				if(match)assignrelational(lexeme,newtoken);
				else bufptr=bufptr-4;
		}
	//adding comment removal part-move pointer forward in the buffer
	else if(val=='#')
	{
		match=1;
		patternflag=1;
		matchsp=1;
		while(buf[bufptr]!='\n')
		{
			bufptr++;
			if(bufptr>=BUF_SIZE||buf[bufptr]=='\0')
					{
						fp=getstream(fp);
					//	if(!fp||(feof(fp)))break;
						bufptr=0;
						
					}

		}
	}	

	//check for arithmetic operators
	else if(val=='>')
	{
		//printf("o");
		patternflag=1;
		if(bufptr>=BUF_SIZE||buf[bufptr]=='\0')
					{
						fp=getstream(fp);
						bufptr=0;
						
					}
		if(buf[bufptr+1]=='=')
		{
			lexptr++;
			lexeme[lexptr++]='=';
			lexeme[lexptr]='\0';
			bufptr+=2;
			newtoken->ttype=GE;
			strcpy(newtoken->lexeme,lexeme);
		//	continue;
		}
		else {
			lexeme[++lexptr]='\0';
			bufptr++;
			newtoken->ttype=GT;
			strcpy(newtoken->lexeme,lexeme);
		//	continue;
		}
	}
	else if(val=='<')
	{
	patternflag=1;	
		if(bufptr>=BUF_SIZE||buf[bufptr]=='\0')
					{
						fp=getstream(fp);
					//	if(!fp||(feof(fp)))break;
						bufptr=0;
					
					}
		if(buf[bufptr+1]=='=')
		{
			lexptr++;
			lexeme[lexptr++]='=';
			lexeme[lexptr]='\0';
			bufptr+=2;
			newtoken->ttype=LE;
			strcpy(newtoken->lexeme,lexeme);
			
		}
		else {
			lexeme[++lexptr]='\0';
			bufptr++;
			newtoken->ttype=LT;
			strcpy(newtoken->lexeme,lexeme);
		
		}

	}
	else if(val=='=')
	{
		//2 lookaheads max
		patternflag=1;
	
		bufptr++;
	
		if(bufptr>=BUF_SIZE||buf[bufptr]=='\0')
					{
						fp=getstream(fp);
					//	if(!fp||(feof(fp)))break;
						bufptr=0;
						
					}
		lexptr++;
	
		strcpy(copy,lexeme);
		int before=bufptr;
		
		for(int k=0;k<2;k++)
		{

					
					lexeme[lexptr++]=buf[bufptr++];
					//bt++;
					if(bufptr>=BUF_SIZE||buf[bufptr]=='\0')
					{
						fp=getstream(fp);
					//	if(!fp||(feof(fp)))break;
						bufptr=0;
						
						
					}
					lexeme[lexptr]='\0';
			if(strcmp(lexeme,"==")==0||strcmp(lexeme,"=/=")==0)
			{
				match=1;
				break;
			
			}
		}			
			if(match)
			{
				strcpy(newtoken->lexeme,lexeme);
				if(strcmp(lexeme,"==")==0)newtoken->ttype=EQ;
				else newtoken->ttype=NE;
			}
			else 
				{
					match=1;
					bufptr=before;
				

					copy[++lexptr]='\0';
					strcpy(newtoken->lexeme,copy);
					newtoken->ttype=ASSIGNOP;



		}


	}
	//for _main and function id
	else if(val=='_')
{
	patternflag=1;
	
	lexptr++;
	bufptr++;
	if((bufptr>=BUF_SIZE||buf[bufptr]=='\0')&&endflag)
					{
					//	printf("hhhhhhh\n");
						fp=getstream(fp);
					//	if(!fp||(feof(fp)))break;
						bufptr=0;
						
					}
	int f=0;
	//printf("next char is %c",buf[bufptr]);
	
	if(isalpha(buf[bufptr]))
		{ match=1;lexeme[lexptr++]=buf[bufptr++];}
//	printf("next char is \n %c",buf[bufptr]);
	
	while((isalpha(buf[bufptr])||isdigit(buf[bufptr]))&&endflag)
	{
		

		lexeme[lexptr++]=buf[bufptr++];
		if(bufptr>=BUF_SIZE||buf[bufptr]=='\0')
					{
						fp=getstream(fp);
					//	if(!fp||(feof(fp)))break;
						bufptr=0;

					}
		lexeme[lexptr]='\0';
		
	}
	if(strcmp(lexeme,"_main")==0)f=1;
	strcpy(newtoken->lexeme,lexeme);
	if(f)newtoken->ttype=MAIN;
	else newtoken->ttype=FUNID;
}
//for strings 
	else if (val=='"')
	{
		patternflag=1;
	//	printf("xxx");
		int count=0;
	
		lexptr++;
	//	printf("here %c\n",buf[bufptr] );
		bufptr++;
		if(bufptr>=BUF_SIZE||buf[bufptr]=='\0')
					{
					//	printf("come here \n");
						fp=getstream(fp);
					//	if(!fp||(feof(fp)))break;
						bufptr=0;
						
					}
		//printf("after %c\n",buf[bufptr] );
		while((isalpha(buf[bufptr])||(buf[bufptr]=='"')||(buf[bufptr]==' '))&&endflag)
		{
		//	printf("enter this loop \n");
			count++;

			lexeme[lexptr++]=buf[bufptr++];
			if(bufptr>=BUF_SIZE||buf[bufptr]=='\0')
					{
						
						fp=getstream(fp);
					//	if(!fp||(feof(fp)))break;
						bufptr=0;
						
					}
			
			if(buf[bufptr-1]=='"')
			{
				match=1;
				break;
			}
			

		}

		if(match&&count<=20)
		{
			lexeme[lexptr]='\0';
			strcpy(newtoken->lexeme,lexeme);
			newtoken->ttype=STR;
		}
		else if(match&&count>20)
			{
				longlength=1;
				printf(" Line no: %d Lexical Error String %s is longer than the prescribed length\n", lnum,lexeme);
			}

	}
//for real numbers and floating point numbers
	else if(isdigit(val))


	{
		patternflag=1;
		///printf("yyy");
		int f=0;
		lexptr++;
		bufptr++;
		if(bufptr>=BUF_SIZE||buf[bufptr]=='\0')
					{
						fp=getstream(fp);
					//	if(!fp||(feof(fp)))break;
						bufptr=0;
						
					}
	//	printf("%d\n",isdigit(buf[bufptr]) );
		while(isdigit(buf[bufptr])&&bufptr<BUF_SIZE&&endflag)
		{
			
		//	printf("enter the loopnum ");
			lexeme[lexptr++]=buf[bufptr++];
			if(bufptr>=BUF_SIZE||buf[bufptr]=='\0')
					{
						fp=getstream(fp);
					//	if(!fp||(feof(fp)))break;
						bufptr=0;
						
					}
		}

		if(buf[bufptr]=='.')
		{
			patternflag=1;

			f=1;
			lexeme[lexptr++]=buf[bufptr++];
			int ct=0;
			while(isdigit(buf[bufptr])&&ct<2)
			{
				
				ct++;
				lexeme[lexptr++]=buf[bufptr++];
				if(bufptr>=BUF_SIZE||buf[bufptr]=='\0')
					{
						fp=getstream(fp);
					//	if(!fp||(feof(fp)))break;
						bufptr=0;
						
					}
			}
		}
		lexeme[lexptr]='\0';
		if(f)
			{newtoken->rnum=getrnumvalueoflex(lexeme);
				newtoken->ttype=RNUM;
			}
		else 
			{newtoken->num=getnumvalueoflex(lexeme);
				newtoken->ttype=NUM;
			}
			strcpy(newtoken->lexeme,lexeme);
			match=1;


	}
//for keywords and identifiers 	
	else if(isalpha(val))
	{
		patternflag=1;
	
		bufptr++;
		if(bufptr>=BUF_SIZE||buf[bufptr]=='\0')
					{
						fp=getstream(fp);
					//	if(!fp||(feof(fp)))break;
						bufptr=0;
						
					}
		lexptr++;
		int key=0;
		while(isalpha(buf[bufptr])&&buf[bufptr]!='\0'&&endflag)
		{
			
		//	printf("%c\n",buf[bufptr] );
			lexeme[lexptr++]=buf[bufptr++];
			if(bufptr>=BUF_SIZE||buf[bufptr]=='\0')
					{
					//	printf("going here\n");
						fp=getstream(fp);
						//if(!fp||(feof(fp)))break;
						bufptr=0;
						
					}
		}
		if(isdigit(buf[bufptr]))lexeme[lexptr++]=buf[bufptr++];
		lexeme[lexptr]='\0';
if(strlen(lexeme)<=20)
{

		strcpy(newtoken->lexeme,lexeme);
		if(gettokenkeyword(lexeme,&key)!=-1&&key==1)newtoken->ttype=gettokenkeyword(lexeme,&key);
		else newtoken->ttype=ID;
		match=1;
}
else 
{
	printf("Line no: %d Lexical Error Identifier %s is longer than the prescribed length\n", lnum,lexeme);
	longlength=1;
}
}

//return the token only if the lexeme was not \n or whitespace and print the lexical error for unmatched pattern 
if(!match&&!matchsp&&!longlength&&endflag&&!patternflag)
	{
		//if we didn't enter any of the loops language does not recognize this symbol
		printf("Line no: %d Lexical Error Unknown symbol found is %s\n",lnum,lexeme);
bufptr++;
if((bufptr>=BUF_SIZE||buf[bufptr]=='\0'))
	{
		
		fp=getstream(fp);
	//	if(!fp||(feof(fp)))break;
		bufptr=0;
	}

}
else if(!match&&!matchsp&&!longlength&&patternflag)
{
	//if one of the loops had been entered but none could lead to a match
	printf("Line no: %d Lexical Error Unknown pattern found is %c\n",lnum,val);
}


else if(!matchsp&&match)
	{


return newtoken;


}


}
return NULL; 
//eof -returns NULL

}

void printtokens(FILE * fp)
{
//prints the tokens from file on terminal
//close and open the file again in order to bring fp back to start position	
printf("PRINTING TOKENS -------------------------------------\n");
	while(fp&&!feof(fp)&&endflag)
	{
	
		
		token * newtoken=gettoken(fp);
		//if(feof(fp)||!fp)break;
		if(newtoken!=NULL)
		
		printf("The token number obtained is %d for lexeme %s at line number %d\n",newtoken->ttype,newtoken->lexeme,newtoken->line );
	}
}

void printerrorsonly(FILE * fp)
{
//prints only lexical errors from file on terminal
//close and open the file again in order to bring fp back to start position	
printf("LEXICAL ERRORS IF ANY -------------------------------------\n");
	while(fp&&!feof(fp)&&endflag)
	{
	
		
		token * newtoken=gettoken(fp);
		//if(feof(fp)||!fp)break;
		
	}
}




void  removecomments(FILE * fp)
{
	//printing comment free code on terminal
	printf("PRINTING THE COMMENT FREE CODE ON THE CONSOLE-------------------------------\n");
	char temp[SIZE_TEMP];
	
		int startflag=0;
	int endflag=0;
	
	while(1)
	{

	int size=fread(temp,sizeof(char),SIZE_TEMP-1,fp);
	temp[size]='\0';
	if(size<0)
		{printf("Error in reading file into a buffer\n");
		break;
	}
	
	
	//handles multiple cases where comments may extend across multiple (2) buffers 

	
	int start =0,end=0;
	int startsame=0;
	
	for(int i=0;i<size&&temp[i]!='\0';i++)
	{
		
		if(temp[i]=='#'&&!startflag)
			{startflag=1;
			start=i;
			
			startsame=1;
			
			}
		
		if(temp[i]=='\n'&& startflag && !endflag)
			{end=i;
			int endi=i;
			endflag=1;
			
				if(startsame)
				{
				i=start;
				while(end!='\0'&&end<size)
				{
					
					temp[start++]=temp[end];
					temp[end]='\0';
					end++;

				}
				while(start<=endi)
				{
				temp[start++]='\0';
				}
				start=0;
				end=0;
				startflag=0;
				endflag=0;
				startsame=0;

			}
			else 
			{
				start=0;
				end=i;
				int endi=i;
		
				while(end<size&&temp[end]!='\0')
				{
					
					temp[start++]=temp[end];
					temp[end]='\0';
					end++;
				}	
				while(start<=endi)
				{
				temp[start++]='\0';
				}

				startflag=0;
			endflag=0;
			i=0;
				
			}
			

			
		}



	}
	if(startflag&&!endflag)
	{
	
		while(start<size)
		{

		temp[start]='\0';
		start++;
	}
}
	
 
 printf("%s",temp );
  
if(feof(fp))
		 break;

}
fclose(fp);


}

