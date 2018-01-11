%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1024

    int yylex();
    int yyerror();
    int topo = 0, ZERO = 0;
    int  numse = 0, numenq = 0;
    FILE* out;

    typedef struct variavel{
        int   dimensao;
        char* tipo;
        char* designacao;
        int   posicaoStack;
    } *Variavel;

    typedef struct expressao{
        char* tipo;
    } *Expressao;

    Variavel v[MAX] = {0}, aux = NULL;
    int quant = 0;

    
    int removeVarDesig (char* designacao, Variavel v[], int N){
	    if(N==0)return -1;
	    int x , y = 0;
	    for(x = 0; x<MAX && y<N ; x++){
    		if(v[x]!=NULL) y++;
	    	if(strcmp(v[x]->designacao, designacao)==0){
	    		v[x] = NULL;
    			return N--;
    		}
    	}
        return -1;

    }

    int insereVar (Variavel var, Variavel v[], int N){
        N = removeVarDesig(var->designacao,v,N);
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

    Variavel criaVar (char* tipo, char* designacao , int posicaoStack, int dimensao){
    	Variavel var = (Variavel)malloc(sizeof(struct variavel));
        var->dimensao = dimensao;
    	var->tipo = tipo;
    	var->designacao = designacao;
    	var->posicaoStack = posicaoStack;
    	return var;
    }

    int isapontador (char* t){
	    int i;
	    for (i=0; t[i]!='\0'; i++);
	    return t[i-1]=='*';
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

    Variavel procuraDesig(char* designacao, Variavel v[], int N){
        int i ,q = 0;
        for(i=0; q<N && i<MAX; i++){
            if(v[i]!=NULL) q++;
            if(strcmp(v[i]->designacao,designacao)==0){
                return v[i];
            }
        }
        return NULL;
        
    }

    void push(Variavel v){
        if(strcmp(v->tipo,"int")==0 && v->dimensao==0){
            fprintf(out,"pushi 0\n");  
        }else if (strcmp(v->tipo,"string")==0 && v->dimensao==0){
            fprintf(out,"pushs \"\"\n");
        }else {
            printf("ERRO: tipo nao existe");   
        }

    }

    void store(Variavel v){
        fprintf(out,"storeg %d\n",v->posicaoStack);
    }
%}

%union{
    int i;
    char *s;
    Expressao expr;
}


%token SE SENAO CASO ENQ VAR TIPO NUM EQ NEQ LEQ GEQ E OU STR COM RETURN

%type<i> NUM
%type<s> VAR TIPO STR

%type<s> Prog Atrib Se Lexpr Eexpr Ltipo 
%type<i> Cond
%type<expr> Expr 


%%
ProgG   : ProgG Se                              { printf("se\n"); }
        | ProgG Enq                             { printf("enquanto\n"); }
        | ProgG Atrib ';'                       { printf("inicializa var\n"); }
        | ProgG VAR '=' Expr ';'                { printf("atualiza var\n"); store(procuraDesig($2,v,quant)); }
        | ProgG VAR '[' NUM ']' '=' Expr ';'    { printf("atualiza vetor\n"); }
        | ProgG TIPO VAR Ltipo '{' Prog '}'     { printf("declarar funcao\n"); }
        | ProgG Funcao ';'                      { printf("chamar funcao\n"); }
        | ProgG ';'                             { printf("; desnecessario\n"); } 
        | ProgG COM                             { printf("comentario\n"); } 
        |                                       { printf("inicio\n"); } 
        ;

Prog    : Prog SE Cond '{' Prog '}' Se          { printf("se\n"); }
        | Prog ENQ Cond '{' Prog '}'            { printf("enquanto\n"); }
        | Prog Atrib ';'                        { printf("inicializa var\n"); }
        | Prog VAR '=' Expr ';'                 { printf("atualiza var\n"); store(procuraDesig($2,v,quant)); }
        | Prog VAR '[' NUM ']' '=' Expr ';'     { printf("atualiza vetor\n"); }
        | Prog Funcao ';'                       { printf("chamar funcao\n"); }
        | Prog ';'                              { printf("; desnecessario\n"); } 
        | Prog COM                              { printf("comentario\n"); } 
        | Prog RETURN Expr ';'                  { printf("return\n"); } 
        |                                       { printf("inicio\n"); } 
        ;

Funcao  : VAR Lexpr                             { if(strcmp($1,"leri")==0){
                                                        fprintf(out,"read\natoi\n");
                                                  }else if(strcmp($1,"lers")==0){
                                                        fprintf(out,"read\n");
                                                  }else if(strcmp($1,"escreveri")==0){
                                                        fprintf(out,"writei\n");
                                                  }else if(strcmp($1,"escrevers")==0){
                                                        fprintf(out,"writes\n");
                                                  } 
                                                }
        ;

Atrib   : TIPO VAR                              { aux = criaVar($1,$2,topo++,0);
                                                  insereVar(aux, v, quant++); 
                                                  push(aux); push(aux); store(aux); }
        | TIPO VAR '[' NUM ']'                  { insereVar(criaVar($1,$2,topo++,1), v, quant++);

                                                  store(procuraDesig($2,v,quant)); }
        | Igual                                 { ; }        
        ;

Igual   : TIPO VAR '='                          { aux = criaVar($1,$2,topo++,0); 
                                                  insereVar(aux, v, quant++);
                                                  push(aux);
                                                }
        | Igual Expr                            { store(aux); }

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

Se      : SE Cond                               { fprintf(out, "jz senao%d\n",numse); }
        | Se '{' Prog '}' CASO Cond             { ; }
        | Se '{' Prog '}' SENAO                 { fprintf(out, "jump fimse%d\nsenao%d:\n",numse,numse); }
        | Se '{' Prog '}'                       { fprintf(out, "fimse%d:\n",numse++); }
        ;

Enq     : ENQ                                   { fprintf(out,"enq%d:\n",numenq); }
        | Enq Cond                              { fprintf(out,"jz fimenq%d\n",numenq); }
        | Enq '{' Prog '}'                      { fprintf(out,"jump enq%d\nfimenq%d:\n",numenq,numenq); numenq++; }
        ;

Cond    : NUM                                   { fprintf(out,"pushi %d\n",abs($1)); }
        | '(' Expr EQ Expr ')'                  { fprintf(out,"equal\n"); }
        | '(' Expr NEQ Expr ')'                 { fprintf(out,"equal\npushi 0\nequal\n"); }
        | '(' Expr '<' Expr ')'                 { fprintf(out,"inf\n"); }
        | '(' Expr '>' Expr ')'                 { fprintf(out,"sup\n"); }
        | '(' Expr LEQ Expr ')'                 { fprintf(out,"infeq\n"); }
        | '(' Expr GEQ Expr ')'                 { fprintf(out,"supeq\n"); }
        | '(' Cond E Cond ')'                   { fprintf(out,"mul\n"); }
        | '(' Cond OU Cond ')'                  { fprintf(out,"add\n"); }
        | '!' Cond                              { fprintf(out,"pushi 0\nequal\n"); }
        ;

Sexpr   : VAR                                   { fprintf(out,"pushg %d\n",procuraDesig($1,v,quant)->posicaoStack); }
        | NUM                                   { fprintf(out,"pushi %d\n", $1); }
        | VAR '[' Expr ']'                      { ; }
        | Funcao                                { ; } 
        | STR                                   { fprintf(out,"pushs %s\n", $1); }
        ;

Expr	: '(' Expr '+' Expr ')'    			    { fprintf(out,"add\n"); $$->tipo = $2->tipo; }
        | '(' Expr '-' Expr ')'  	            { fprintf(out,"sub\n"); $$->tipo = $2->tipo; }
        | '(' Expr '*' Expr ')'    	            { fprintf(out,"mul\n"); $$->tipo = $2->tipo; }
        | '(' Expr '/' Expr ')'    	            { fprintf(out,"div\n"); $$->tipo = $2->tipo; }
        | '(' Expr '%' Expr ')'    	            { fprintf(out,"mod\n"); $$->tipo = $2->tipo; }
        | '(' Expr ')'                          { $$->tipo = $2->tipo; }
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

