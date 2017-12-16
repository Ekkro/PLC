%{
#include <stdio.h>
#include <string.h>

    int numNotas;
    int somaNotas;
    int yylex();
    int yyerror();
%}

%union{
  int vali;
  char *vals;
}


%token SE SENAO VERDADE FALSO CASO ENQ VAR TIPO NUM COMPL FUNL

%%
Prog    : SE Cond '{' Prog '}' Se
        | ENQ Cond '{' Prog '}' Prog
        | TIPO Eatrib ';' Prog
        | TIPO VAR Ltipo '{' Prog '}' Prog
        | VAR Lexpr ';' Prog                /*funcao*/
        | ';' Prog
        | 
        ;

Eatrib  : VAR 
        | VAR '=' Expr 
        | Eatrib ',' VAR '=' Expr 
        | Eatrib ',' VAR 
        ;

Lexpr   : '(' ')'
        | '(' Eexpr ')'
        ;

Eexpr   : Expr
        | Eexpr ',' Expr
        ;

Ltipo   : '(' ')'
        | '(' Etipo ')'
        ;

Etipo   : TIPO VAR
        | Etipo ',' TIPO VAR 
        ;

Se      : Prog
        | CASO Cond '{' Prog '}' SE
        | SENAO '{' Prog '}' Prog
        ;

Cond    : VERDADE
        | FALSO
        | '(' Expr COMPL Expr ')'
        | '(' Cond FUNL Cond ')'
        | '!' Cond
        ;

Simbl   : '=='
        | '!='
        | '<'
        | '>'
        | '<='
        | '>='
        ;

Expr    : VAR
        | VAR '(' ')'
        | NUM
        ;
%%

#include "galo.c"

int yyerror(char *s){
    fprintf(stderr, "ERRO SINTATICO: %s \n", s);
}

int main(){
    yyparse();
    return(0);
}

