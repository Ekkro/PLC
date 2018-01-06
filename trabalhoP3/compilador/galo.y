%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1024

    int yylex();
    int yyerror();
    int topo = 0, ZERO = 0;
    FILE* out;

    typedef struct variavel{
        char* tipo;
        char* designacao;
        void* valor;    
        int   posicaoStack;
    } *Variavel;

    typedef struct expressao{
        char* tipo;
        void* valor;
    } Expressao;

    Variavel v[MAX] = {0};
    int quant = 0;



    int insereVar (Variavel var, Variavel v[], int N){
	    if(N>=MAX) return -1;
	
    	int x;
    	for(x = 0; x<MAX ; x++){
    		if(v[x]==NULL) break;	 
    	}
    	v[x] = var;
    	return N++;
    }

    int removeVar (Variavel var, Variavel v[], int N){
	    if(N==0)return -1;
	    int x , y = 0;
	    for(x = 0; x<MAX && y<N ; x++){
    		if(v[x]!=NULL) y++;
	    	if(v[x]->posicaoStack == var->posicaoStack){
	    		v[x] = NULL;
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
        for(i=0; q<N && i<MAX; i++){
            if(v[i]!=NULL) q++;
            if(strcmp(v[i]->tipo,"indef")==0){
                v[i]->tipo = tipo;
            }
        }
    }

    char* removeEspacos(char* s){
        int i = 0, j = 0;
        while(s[j]!='\0'){
            while(s[j]==' '){j++;}
            if(s[j]=='\0') break;
            s[i] = s[j];
            i++;j++;
        }
        s[i] = '\0';
        return s;
    }

    void pushVarInd(FILE* f, char* tipo, Variavel v[], int N){
        int i, q;
        for(i=0; q<N && i<MAX; i++){
            if(v[i]!=NULL){
                q++;
                if(strcmp(v[i]->tipo,"indef")==0){
                    if(strcmp(tipo,"int")==0){
                        fprintf(f, "pushi %d\n",*(int*)(v[i]->valor) );
                    }else if(strcmp(tipo,"char")==0){
                        fprintf(f, "pushs \"%c\"\n",*(char*)(v[i]->valor) );
                    }else if(strcmp(tipo,"int*")==0){
                        fprintf(f, "pushi %d\n",*(int*)(v[i]->valor) );
                    }else if(strcmp(tipo,"char*")==0){
                        fprintf(f, "pushs %s\n",*(char**)(v[i]->valor) );
                    }
                }
            }
        }
    }
%}

%union{
  int i;
  char *s;
}


%token SE SENAO CASO ENQ VAR TIPO NUM EQ NEQ LEQ GEQ E OU STR COM RETURN

%type<i> NUM
%type<s> VAR TIPO STR

%type<s> Prog Eatrib Se Lexpr Eexpr Ltipo 
%type<i> Cond


%%
ProgG   : ProgG SE Cond '{' ProgG '}' Se        { printf("se\n"); }
        | ProgG ENQ Cond '{' ProgG '}'          { printf("enquanto\n"); }
        | ProgG TIPO Eatrib ';'                 { printf("inicializa var\n"); pushVarInd(out, $2, v, quant); atualizaTipoVar($2, v,quant); }
        | ProgG VAR '=' Expr ';'                { printf("atualiza var\n"); }
        | ProgG VAR '[' Expr ']' '=' Expr ';'   { printf("atualiza vetor\n"); }
        | ProgG TIPO VAR Ltipo '{' Prog '}'     { printf("declarar funcao\n"); }
        | ProgG VAR Lexpr ';'                   { printf("chamar funcao\n"); }
        | ProgG ';'                             { printf("; desnecessario\n"); } 
        | ProgG COM                             { printf("comentario\n"); } 
        |                                       { printf("inicio\n"); } 
        ;

Prog    : Prog SE Cond '{' Prog '}' Se          { printf("se\n"); }
        | Prog ENQ Cond '{' Prog '}'            { printf("enquanto\n"); }
        | Prog TIPO Eatrib ';'                  { printf("inicializa var\n"); pushVarInd(out, $2, v, quant); atualizaTipoVar($2, v,quant); }
        | Prog VAR '=' Expr ';'                 { printf("atualiza var\n"); }
        | Prog VAR '[' Expr ']' '=' Expr ';'    { printf("atualiza vetor\n"); }
        | Prog VAR Lexpr ';'                    { printf("chamar funcao\n"); }
        | Prog ';'                              { printf("; desnecessario\n"); } 
        | Prog COM                              { printf("comentario\n"); } 
        | Prog RETURN Expr ';'                  { printf("return\n"); }
        |                                       { printf("inicio\n"); } 
        ;

Eatrib  : VAR                                   { insereVar(criaVar("indef",$1,&ZERO,topo++), v, quant++); }
        | VAR '[' Expr ']'                      { ; }
        | VAR '=' Expr                          { ; }
        | VAR '[' Expr ']' '=' Expr             { ; }
        | Eatrib ',' VAR '=' Expr               { ; }
        | Eatrib ',' VAR                        { insereVar(criaVar("indef",$3,&ZERO,topo++), v, quant++); }
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

Se      :                                       { ; }
        | CASO Cond '{' Prog '}' Se             { ; }
        | SENAO '{' Prog '}'                    { ; }
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

Expr	: '(' Expr '+' Expr ')'    			    { ; }
        | '(' Expr '-' Expr ')'  	            { ; }
        | '(' Expr '*' Expr ')'    	            { ; }
        | '(' Expr '/' Expr ')'    	            { ; }
        | '(' Expr '%' Expr ')'    	            { ; }
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
    
    int i, q = 0;
    for(i=0;i<MAX && q<quant ;i++){
        if(v[i]!=NULL){
            q++;
            printf("%s\n",v[i]->designacao);
        }
    }

    fclose(out);
    return(0);
}

