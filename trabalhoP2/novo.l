%{
/* Declaracoes C diversas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int n=0;
char** st;
char* simb;
FILE* f;

typedef struct stack{
	char* s;
	struct stack* next;

} *Stack;

%}

%option noyywrap

%x TEXT SIMB



%%

<TEXT>{
	">"		{fprintf(f, "<%s>", st[n--] ); }
	\\		{BEGIN SIMB; strcpy(simb,"");}
	.|\n	{fprintf(f, "%s\n", yytext );}
}

<SIMB>{
	"<"   	    {BEGIN TEXT; fprintf(f, "<%s>", simb ); n++;  put(st,simb);}
	.|\n		{strcat(simb, yytext);}
}


<*>.|\n 	{fprintf(stderr, "caracter estranho \n");}

%%

int main(){
	f=fopen("novo.html", "w");
	yylex(); 
	fclose(f);
	return 0; 
}