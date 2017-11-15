%{
#include <stdio.h>
#include <string.h>

    int yylex();
    int yyerror();
%}

%union{
  char *s;
}


%token Str SimbF SimbL SimbD
%type <s>Str

%%
Text	: '\' SimbF '<' Text '>'
    	| '\' SimbL '<' List '>'
    	| '\' SimbD '<' Dict '>'
    	| Str				{ printf("%s",$1);}
   	;

List	: Text
	| List '|' Text
	;

Dict	: Text '$' Text
	| List '|' Text '$' Text
	;

%%

#include "lex.yy.c"


int yyerror(char *s){
    fprintf(stderr, "ERRO SINTATICO: %s \n", s);
}

int main(){
    yyparse();
    return(0);
}

