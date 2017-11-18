%{
/* Declaracoes C diversas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max 128

int n = 0;
char st[Max][32] = {0};
FILE* f;

void insere(char *id ){
	int i;
	for (i=0; id[i]!='\0'; i++){
		st[n][i] = id[i];
	}
	st[n][i-1] = '\0';
}

%}

%option noyywrap

%x TEXT SIMB

Abrev ER

%%

			{BEGIN TEXT;}

<TEXT>{
	">"		{fprintf(f, "</%s>", st[--n] );}
	"]"		{fprintf(f, "</li></%s>", st[--n]);}
	"|"		{fprintf(f,"</li>\n<li>");}
	"}"		{fprintf(f, "</dd></%s>", st[--n]);}
	"$"		{fprintf(f,"</dd>\n<dt>");}
	":"		{fprintf(f,"</dt>\n<dd>");}
	"\\"		{BEGIN SIMB; strcpy(st[n],"");}
	.|\n		{fprintf(f, "%s", yytext );}
}

<SIMB>{
	[bui]<|h[1-6]< 	{BEGIN TEXT; insere(yytext); fprintf(f, "<%s>", st[n++] ); }
	[ou]l\[ 	{BEGIN TEXT; insere(yytext); fprintf(f, "<%s><li>", st[n++] );}
	dl\{ 		{BEGIN TEXT; insere(yytext); fprintf(f, "<%s><dt>", st[n++] );}
	.|\n		{BEGIN TEXT; fprintf(f,"%s",yytext);}
}

%%

int main(){
	f=fopen("ex.html", "w");
	yylex(); 
	fclose(f);
	return 0; 
}
