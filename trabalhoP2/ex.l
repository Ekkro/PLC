%{
/* Declaracoes C diversas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max 128

int n = 0;
char simb[32] = {0};
char* st[Max];
FILE* f;

%}

%option noyywrap

%x TEXT SIMB

Abrev ER

%%

			{BEGIN TEXT;}

<TEXT>{
	">"		{fprintf(f, "</%s>", st[--n] ); }
	"\\"		{BEGIN SIMB; strcpy(simb,"");}
	.|\n		{fprintf(f, "%s", yytext );}
}

<SIMB>{
	"<"   	    	{BEGIN TEXT; fprintf(f, "<%s>", simb );st[n++]=simb;}
	.|\n		{strcat(simb, yytext);}
}

%%

int main(){
	f=fopen("novo.html", "w");
	yylex(); 
	fclose(f);
	return 0; 
}
