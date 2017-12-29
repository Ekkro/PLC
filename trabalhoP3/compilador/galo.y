%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    int yylex();
    int yyerror();
    int topo = 0;
    FILE* out;

    typedef struct variavel{
        char* tipo;
        char* designacao;
        void* valor;    
        int   posicaoStack;
    } *Variavel;

    typedef struct expressao{
        char* tipo;
        char* valor;
        int posicaoStack;
    } Expressao;

    Variavel v[1024] = {0};
    int quant = 0;



    int insereVar (Variavel var, Variavel v[], int N){
	    if(N>=1024)return -1;
	
    	int x;
    	for(x = 0; x<1024 ; x++){
    		if(v[x]==NULL)break;	 
    	}
    	v[x]=var;
    	return N++;
    }

    int removeVar (Variavel var, Variavel v[], int N){
	    if(N==0)return -1;
	    int x , y = 0;
	    for(x = 0; x<1024 && y<N ; x++){
    		if(v[x]!=NULL)y++;
	    	if(v[x]->posicaoStack == var->posicaoStack){
	    		v[x]=NULL;
    			return N--;
    		}
    	}
    	return -1;
    }

    Variavel criaVar (char* tipo, char* designacao , void* valor, int posicaoStack){
    	Variavel var = (Variavel)malloc(sizeof(struct variavel));
    	var->tipo = tipo;
    	var->designacao = designacao;
    	var->valor = valor;
    	var->posicaoStack = posicaoStack;
    	return var;
    }

    void alteraValor (Variavel var, void* valor){
    	var->valor = valor;
    }	

    int isapontador (char* t){
	    int i;
	    for (i=0; t[i]!='\0'; i++);
	    return t[i-1]=='*';
    }

    void atualizaTipoVar(char* tipo, Variavel v[], int N){
        int i, q;
        for(i=0; q<N && i<1024; i++){
            if(v[i]!=NULL)q++;
            if(strcmp(v[i]->tipo,"indef")==0){
                v[i]->tipo = tipo;
            }
        }
    }
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
        | TIPO Eatrib ';' Prog                  { atualizaTipoVar($1,v,quant);}
        | VAR '=' Expr ';' Prog                 { ; }
        | VAR '[' Expr ']' '=' Expr ';' Prog    { ; }
        | TIPO VAR Ltipo '{' Prog '}' Prog      { ; }
        | VAR Lexpr ';' Prog                    { ; }
        | ';' Prog                              { $$ = $2; } /*check*/
        | COM Prog                              { $$ = $2; } /*check*/
        |                                       { ; } /*check*/
        ;

Eatrib  : VAR                                   { int val = 0; insereVar(criaVar("indef",$1,&val,topo++), v, quant++); }
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

Sexpr   : VAR                                   { ; }
        | NUM                                   { ; }
        | VAR '[' Expr ']'                      { ; }
        | VAR Lexpr                             { ; }
        | STR                                   { ; }
        ;

Expr	: Expr '+' Sexpr          			    { ; }
        | Expr '-' Sexpr       		            { ; }
        | Expr '*' Sexpr       		            { ; }
        | Expr '/' Sexpr       		            { ; }
        | Expr '%' Sexpr       		            { ; }
        | '(' Expr ')'                          { ; }
        | Sexpr                                 { ; }
        ;
%%

#include "galo.c"

int yyerror(char *s){
    fprintf(stderr, "ERRO SINTATICO: %s \n", s);
}

int main(){
    out = fopen("a.mv", "w");
    if (out == NULL){
        printf("Error opening file!\n");
        exit(1);
    }
    //char codigo[1023*1024];

    fprintf(out, "start\n"); 
    yyparse();
    fprintf(out, "stop\n");

    fclose(out);
    return(0);
}

