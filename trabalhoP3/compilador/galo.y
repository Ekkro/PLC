%{
#include <stdio.h>
#include <string.h>

    int yylex();
    int yyerror();
%}

%union{
  int i;
  char *s;
}


%token SE SENAO VERDADE FALSO CASO ENQ VAR TIPO NUM COMPL FUNL EQ NEQ LEQ GEQ E OU STR COM

%type<s> Prog 


%%
Prog    : SE Cond '{' Prog '}' Se               { ; }
        | ENQ Cond '{' Prog '}' Prog            { ; }
        | TIPO Eatrib ';' Prog                  { ; }
        | VAR '=' Expr ';' Prog                 { ; }
        | VAR '[' Expr ']' '=' Expr ';' Prog    { ; }
        | TIPO VAR Ltipo '{' Prog '}' Prog      { ; }
        | VAR Lexpr ';' Prog                    { ; }
        | ';' Prog                              { ; }
        | COM Prog                              { ; }
        |                                       { ; }
        ;

Eatrib  : VAR                                   { ; }
        | VAR '[' Expr ']'                      { ; }
        | VAR '=' Expr                          { ; }
        | VAR '[' Expr ']' '=' Expr             { ; }
        | Eatrib ',' VAR '=' Expr               { ; }
        | Eatrib ',' VAR                        { ; }
        ;

/*lista de expressoes*/
Lexpr   : '(' ')'                               { ; }
        | '(' Eexpr ')'                         { ; }
        ;

Eexpr   : Expr                                  { ; }
        | Eexpr ',' Expr                        { ; }
        ;

/*lista de tipos*/
Ltipo   : '(' ')'                               { ; }
        | '(' Etipo ')'                         { ; }
        ;

Etipo   : TIPO VAR                              { ; }
        | Etipo ',' TIPO VAR                    { ; }
        ;

Se      : Prog                                  { ; }
        | CASO Cond '{' Prog '}' SE             { ; }
        | SENAO '{' Prog '}' Prog               { ; }
        ;

Cond    : VERDADE                               { ; }
        | FALSO                                 { ; }
        | '(' Expr Simbcmp Expr ')'             { ; }
        | '(' Cond Funl Cond ')'                { ; }
        | '!' Cond                              { ; }
        ;

Simbcmp : EQ                                    { ; }
        | NEQ                                   { ; }
        | '<'                                   { ; }
        | '>'                                   { ; }
        | LEQ                                   { ; }
        | GEQ                                   { ; }
        ;

Funl    : E                                     { ; }
        | OU                                    { ; }
        ;

Expr    : VAR                                   { ; }
        | NUM                                   { ; }
        | VAR '[' Expr ']'                      { ; }
        | VAR Lexpr                             { ; }
        | Expr Cexpr                            { ; }
        | STR                                   { ; }
        ;

Cexpr   : Opint VAR                             { ; }
        | Opint NUM                             { ; }
        | Opint VAR Lexpr                       { ; }
        ;

Opint   : '+'                                   { ; }
        | '-'                                   { ; }
        | '*'                                   { ; }
        | '/'                                   { ; }
        | '%'                                   { ; }
        ;
%%

#include "galo.c"

int yyerror(char *s){
    fprintf(stderr, "ERRO SINTATICO: %s \n", s);
}

int main(){
    printf("start\n"); 
    yyparse();
    printf("stop\n"); 
    return(0);
}

