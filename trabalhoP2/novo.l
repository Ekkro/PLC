%{
/* Declaracoes C diversas */
#include <stdio.h>
int n=0;
char title[100];
char author[100];
FILE * f;

%}

%option noyywrap

%x TEXT SIMB


Abrev ER
%%
title:	{BEGIN TITLE; strcpy(title,""); strcpy(author,"")}

<TEXT>{
	[=*]	{;}
	\n 		{BEGIN META;}
	.		{strcat(title, yytext);}
}

<A>{
	[,;]	{strcat(author, "\nC:");}
	\n 		{BEGIN META;}
	.		{strcat(title, yytext);}
}

<POEMA>{
	title:	{BEGIN TITLE; strcpy(title,"");}
	"<abc>"	{BEGIN ABC;}
	.|\n 	{;}

}

<META>{
	"<abc>"	{BEGIN ABC;}
	(author|music|lyrics):	{BEGIN AUTOR; strcat(author,)}
	\n\n 	{BEGIN POEMA;}
	.|\n 	{;}

}

<ABC>{
	X:.*\n	{fprintf(f,"%sT:%s\nC:%s\n", yytext, title, author);}
	"</abc>"	{BEGIN POEMA; part++;}
	.|\n 	{fprintf(f,"%s", yytext );}

}

<*>.|\n 	{fprintf(stderr, "caracter estranho \n");}

%%

int main(){
	f=fopen("partituras.abc", "w");
	yylex(); 
	printf("Contagem de partituras: %d\n",part );
	fclose(f);
	return 0; 
}