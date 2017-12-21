%{
#include <stdio.h>
#include <string.h>

    int yylex();
    int yyerror();

    struct variavel{
        char* designacao;
        char* valor;
        char* tipo;
        int posicaoStack;
    }
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
        | ';' Prog                              { $$ = $2; } /*check*/
        | COM Prog                              { $$ = $2; } /*check*/
        |                                       { ; } /*check*/
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

Cond    : NUM                                   { ; }
        | '(' Expr EQ Expr ')'                  { ; }
        | '(' Expr NEQ Expr ')'                 { ; }
        | '(' Expr '<' Expr ')'                 { ; }
        | '(' Expr '>' Expr ')'                 { ; }
        | '(' Expr LEQ Expr ')'                 { ; }
        | '(' Expr GEQ Expr ')'                 { ; }
        | '(' Cond E Cond ')'                   { ; }
        | '(' Cond OU Cond ')'                  { ; }
        | '!' Cond                              { ; }
        ;

Expr    : VAR                                   { ; }
        | NUM                                   { ; }
        | VAR '[' Expr ']'                      { ; }
        | VAR Lexpr                             { ; }
        | Expr Cexpr                            { ; }
        | STR                                   { ; }
        ;

Cexpr   : '+' Expr                              { ; }
        | '-' Expr                              { ; }
        | '*' Expr                              { ; }
        | '/' Expr                              { ; }
        | '%' Expr                              { ; }
        ;
%%

#include "galo.c"

int yyerror(char *s){
    fprintf(stderr, "ERRO SINTATICO: %s \n", s);
}

int main(int argc, char* argv[]){
    if(argc == 2){
        f1 = fopen(argv[0]);

        printf("start\n"); 
        yyparse();
        printf("stop\n"); 
    }
    return(0);
}

