%{
#include <stdio.h>
#include <string.h>

    int yylex();
    int yyerror();

    typedef struct variavel{
        char* tipo;
        char* designacao;
        char* valor;
        int posicaoStack;
    } Variavel;

    typedef struct expressao{
        char* tipo;
        char* valor;
        int posicaoStack;
    } Expressao;

%}

%union{
  int i;
  char *s;
  Variavel var;
  Expressao expr; 
}




%token SE SENAO CASO ENQ VAR TIPO NUM EQ NEQ LEQ GEQ E OU STR COM

%type<i> NUM
%type<s> VAR TIPO STR

%type<s> Prog Eatrib Se Lexpr Eexpr Ltipo 
%type<i> Cond


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
        | Expr '+' Expr                         { ; }
        | Expr '-' Expr                         { ; }
        | Expr '*' Expr                         { ; }
        | Expr '/' Expr                         { ; }
        | Expr '%' Expr                         { ; }
        | STR                                   { ; }
        ;

%%

#include "galo.c"

int yyerror(char *s){
    fprintf(stderr, "ERRO SINTATICO: %s \n", s);
}

int main(){
    FILE* out = fopen("a.mv", "w");
    if (out == NULL){
        printf("Error opening file!\n");
        exit(1);
    }

    char codigo[1024*1024];

    fprintf(out, "start\n"); 
    yyparse();
    fprintf(out, "stop\n");

    fclose(out);
    return(0);
}

