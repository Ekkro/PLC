%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1024

    int yylex();
    int yyerror();
    int topo = 0, topol = 0, i = 0;
    int numse[128] = {0}, apse = 0, numenq[128] = {0}, apenq = 0;
    int numelemfun = 0, numfun = 0, dentrofun = 0; 
    FILE* out;
    char* tipoString = "string";
    char* tipoInt = "int";
    char* tipoFloat = "float";

    typedef struct variavel{
        int   dimensao;
        char* tipo;
        char* designacao;
        int   posicaoStack;
    } *Variavel;

    typedef struct expressao{
        char* tipo;
    } *Expressao;

    typedef struct funcao{
        char* designacao;
        char* tipos[128];
        int numtipos;
    } *Funcao;

    Variavel v[MAX] = {0}, aux = NULL, vl[MAX] = {0};
    Funcao funcoes[128] = {0};
    int quant = 0, quantl = 0;

    
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

    void storel(Variavel v){
        fprintf(out,"storel %d\n",v->posicaoStack);
    }

    void inserefun(char* tipo, char* designacao, char* funcoes[], int numfun){
        int i;
        for(i = 0;i< numfun;i++){
            if(funcoes[i]==0){
                
            }
        }
    }

%}

%union{
    int i;
    char *s;
    Expressao expr;
}


%token SE SENAO CASO ENQ VAR TIPO NUM FLOAT EQ NEQ LEQ GEQ E OU STR COM RETURN

%type<i> NUM
%type<s> VAR TIPO STR

%type<s> Prog Atrib Se Lexpr Eexpr Ltipo 
%type<i> Cond
%type<expr> Expr Sexpr 


%%
ProgG   : ProgG Se                              { printf("se\n"); }
        | ProgG Enq                             { printf("enquanto\n"); }
        | ProgG Atrib ';'                       { printf("inicializa var\n"); }
        | ProgG VAR '=' Expr ';'                { printf("atualiza var\n"); store(procuraDesig($2,v,quant)); }
        | ProgG VAR '[' NUM ']' '=' Expr ';'    { printf("atualiza vetor\n"); }
        | ProgG CriaFun                         { printf("declarar funcao");}
        | ProgG Funcao ';'                      { printf("chamar funcao\n"); }
        | ProgG ';'                             { printf("; desnecessario\n"); } 
        | ProgG COM                             { printf("comentario\n"); } 
        |                                       { printf("inicio\n"); } 
        ;

ProgF   : ProgF Se                              { printf("se\n"); }
        | ProgF Enq                             { printf("enquanto\n"); }
        | ProgF Atrib ';'                       { printf("inicializa var\n"); }
        | ProgF VAR '=' Expr ';'                { printf("atualiza var\n"); store(procuraDesig($2,v,quant)); }
        | ProgF VAR '[' NUM ']' '=' Expr ';'    { printf("atualiza vetor\n"); }
        | ProgF Funcao ';'                      { printf("chamar funcao\n"); }
        | ProgF ';'                             { printf("; desnecessario\n"); } 
        | ProgF COM                             { printf("comentario\n"); } 
        | ProgF RETURN Expr ';'                 { printf("return\n"); fprintf(out,"storel %d\nreturn\n",-(numelemfun+1)); } 
        |                                       { printf("inicio\n"); } 
        ;

Prog    : Prog Se                               { printf("se\n"); }
        | Prog Enq                              { printf("enquanto\n"); }
        | Prog Atrib ';'                        { printf("inicializa var\n"); }
        | Prog VAR '=' Expr ';'                 { printf("atualiza var\n"); store(procuraDesig($2,v,quant)); }
        | Prog VAR '[' NUM ']' '=' Expr ';'     { printf("atualiza vetor\n"); }
        | Prog Funcao ';'                       { printf("chamar funcao\n"); }
        | Prog ';'                              { printf("; desnecessario\n"); } 
        | Prog COM                              { printf("comentario\n"); } 
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
                                                  }else{
                                                        for(i=0;i<numelemfun;i++){
                                                            
                                                        }
                                                  }
                                                }
        ;

CriaFun : TIPO VAR '('                          { fprintf(out,"jump fimfun%d\n%s:\nnop\n",numfun,$2); dentrofun = 1; inserefun($1,$2,funcoes,numfun); }
        | Ltipo '{' ProgF '}'                   { fprintf(out,"fimfun%d:\n",numfun); numfun++; dentrofun = 0; }
        ;

Atrib   : TIPO VAR                              { if(dentrofun){
                                                    aux = criaVar($1,$2,topol++,0);
                                                    insereVar(aux, vl, quantl++);
                                                    push(aux); push(aux); storel(aux);
                                                  }
                                                  else{
                                                    aux = criaVar($1,$2,topo++,0);
                                                    insereVar(aux, v, quant++); 
                                                    push(aux); push(aux); store(aux);
                                                  } 
                                                }
        | TIPO VAR '[' NUM ']'                  { insereVar(criaVar($1,$2,topo++,1), v, quant++);

                                                  store(procuraDesig($2,v,quant)); 
                                                }
        | Igual                                 { ; }        
        ;

Igual   : TIPO VAR '='                          { if(dentrofun){
                                                    aux = criaVar($1,$2,topol++,0);
                                                    insereVar(aux, vl, quantl++);
                                                    push(aux);
                                                  }
                                                  else{
                                                    aux = criaVar($1,$2,topo++,0); 
                                                    insereVar(aux, v, quant++);
                                                    push(aux);
                                                  }
                                                }
        | Igual Expr                            { if(dentrofun){
                                                    storel(aux);
                                                  }
                                                  else{
                                                    store(aux);
                                                  } 
                                                }
        ;

/*lista de expressoes*/
Lexpr   : '(' ')'                               { numelemfun = 0; }
        | '(' Eexpr ')'                         { ; }
        ;

Eexpr   : Expr                                  { numelemfun = 1; }
        | Eexpr ',' Expr                        { numelemfun++; }
        ;

/*lista de tipos*/
Ltipo   : ')'                                   { numelemfun = 0 ; }
        | Etipo ')'                             { ; }
        ;

Etipo   : TIPO VAR                              { numelemfun = 1; aux = criaVar($1,$2,-(numelemfun),0);
                                                  insereVar(aux, vl, quantl++);
                                                }
        | Etipo ',' TIPO VAR                    { numelemfun++; aux = criaVar($3,$4,-(numelemfun),0);
                                                  insereVar(aux, vl, quantl++);
                                                }
        ;

Se      : SE Cond                               { fprintf(out, "jz fimse%d\n",numse[apse]); apse++; numse[apse] = numse[apse-1]+1; }
        | Se '{' Prog '}' CASO Cond             { ; }
        | Se '{' Prog '}' SENAO                 { apse--; fprintf(out, "jump fimse%d\nfimse%d:\n",numse[apse],numse[apse]+1);
                                                  numse[apse] = numse[apse+1]; apse++; numse[apse] = numse[apse-1]+1; 
                                                }
        | Se '{' Prog '}'                       { apse--; fprintf(out, "fimse%d:\n",numse[apse]); numse[apse] = numse[apse+1]; }
        ;

Enq     : ENQ                                   { fprintf(out,"enq%d:\n",numenq[apenq]); }
        | Enq Cond                              { fprintf(out,"jz fimenq%d\n",numenq[apenq]); apenq++; numenq[apenq] = numenq[apenq-1]+1; }
        | Enq '{' Prog '}'                      { apenq--; fprintf(out,"jump enq%d\nfimenq%d:\n",numenq[apenq],numenq[apenq]); 
                                                  numenq[apenq]= numenq[apenq+1]; 
                                                }
        ;

Cond    : NUM                                   { fprintf(out,"pushi %d\n",$1!=0); }
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

Sexpr   : VAR                                   { if(dentrofun){
                                                    fprintf(out,"pushl %d\n",procuraDesig($1,vl,quantl)->posicaoStack); 
                                                  }else{
                                                    fprintf(out,"pushg %d\n",procuraDesig($1,vl,quantl)->posicaoStack); 
                                                  }
                                                }
        | NUM                                   { fprintf(out,"pushi %d\n", $1); $$->tipo = tipoInt; }
        | FLOAT                                 { $$->tipo = tipoFloat; }
        | VAR '[' Expr ']'                      { ; }
        | Funcao                                { ; } 
        | STR                                   { fprintf(out,"pushs %s\n", $1); $$->tipo = tipoString; }
        ;

Expr	: '(' Expr '+' Expr ')'    			    { fprintf(out,"add\n"); }
        | '(' Expr '-' Expr ')'  	            { fprintf(out,"sub\n"); }
        | '(' Expr '*' Expr ')'    	            { fprintf(out,"mul\n"); }
        | '(' Expr '/' Expr ')'    	            { fprintf(out,"div\n"); }
        | '(' Expr '%' Expr ')'    	            { fprintf(out,"mod\n"); }
        | '(' Expr ')'                          { $$ = (Expressao)malloc(sizeof(struct expressao)); $$ = $2; }
        | Sexpr                                 { $$ = (Expressao)malloc(sizeof(struct expressao)); $$ = $1; }
        ;
%%

#include "galo.c"

int yyerror(char *s){
    fprintf(stderr, "ERRO SINTATICO: %s \n", s);
}

int main(){
    out = fopen("a.vm", "w");
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

