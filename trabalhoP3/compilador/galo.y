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
        int   dimensao1;
        int   dimensao2;
        char* tipo;
        char* designacao;
        int   posicaoStack;
    } *Variavel;

    typedef struct funcao{
        char* designacao;
        char* tipos[128];
        int numtipos;
    } *Funcao;

    Variavel v[MAX] = {0}, aux = NULL, vl[MAX] = {0};
    Funcao funcoes[128] = {0}, funaux = NULL;
    int quant = 0, quantl = 0;
    char* tiposaux[128] = {0};
    
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

    Variavel criaVar (char* tipo, char* designacao , int posicaoStack, int dimensao1, int dimensao2){
    	Variavel var = (Variavel)malloc(sizeof(struct variavel));
        var->dimensao1 = dimensao1;
        var->dimensao2 = dimensao2;
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
        if(strcmp(v->tipo,"int")==0){
            if(v->dimensao1==0 && v->dimensao2==0){
                fprintf(out,"pushi 0\n");  
            }else if(v->dimensao1!=0 && v->dimensao2==0){
                fprintf(out,"pushn %d\n",v->dimensao1);
            }else{
                fprintf(out,"pushn %d\n",v->dimensao1*v->dimensao2);
            }
        }else if (strcmp(v->tipo,"string")==0){
            fprintf(out,"pushs \"\"\n");
        }else if (strcmp(v->tipo,"float")==0){
            fprintf(out,"pushf 0.0\n");
        }else {
            printf("ERRO: tipo nao existe");   
        }

    }

    void pushtipo(char* tipo){
        if(strcmp(tipo,"int")==0){
            fprintf(out,"pushi 0\n");  
        }else if (strcmp(tipo,"string")==0){
            fprintf(out,"pushs \"\"\n");
        }else if (strcmp(tipo,"float")==0){
            fprintf(out,"pushf 0.0\n");
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

    void inserefun(Funcao fun, Funcao funcoes[], int numfun){
        funcoes[numfun] = fun;
    }
    
    Funcao criafun(char* designacao, char* tipos[], int numtipos){
        Funcao fun = (Funcao)malloc(sizeof(struct funcao));
        fun->designacao = designacao;
        int i;
        for(i=0;i<numtipos;i++){
            fun->tipos[i] = tipos[i];
        }
        fun->numtipos = numtipos;
        return fun;
    }

    Funcao atualizafun(Funcao fun, char* tipos[], int numtipos){
        int i;
        for (i=fun->numtipos;i<fun->numtipos+numtipos;i++){
            fun->tipos[i] = tipos[i-fun->numtipos];
        }
        fun->numtipos += numtipos;
        return fun;
    }

    Funcao procurafun(char* designacao, Funcao funcoes[], int numfun ){
        int i;
        for(i=0;i<numfun;i++){
            if(strcmp(funcoes[i]->designacao,designacao)==0){
                return funcoes[i];
            }
        }
        return NULL;
    }
    
    void zerar(Variavel vl[], int quantl){
        Variavel aux = NULL;
        int i = 0;
        while(i<quantl){
            if(vl[i]){
                aux = vl[i];
                vl[i] = NULL;
                free(aux);
                i++;
            }
        }
    }
%}

%union{
    int i;
    float f;
    char *s;
    Funcao fun;
}


%token SE SENAO ENQ VAR TIPO NUM FLOAT EQ NEQ LEQ GEQ E OU STR COM RETURN COS SIN

%type<i> NUM
%type<f> FLOAT
%type<s> VAR TIPO STR

%type<s> Prog Atrib Se Lexpr Eexpr Ltipo Funcao 
%type<i> Cond
%type<s> Expr Sexpr 


%%
ProgG   : ProgG Se                              { printf("se\n"); }
        | ProgG Enq                             { printf("enquanto\n"); }
        | ProgG Atrib ';'                       { printf("inicializa var\n"); }
        | ProgG VAR '=' Expr ';'                { printf("atualiza var\n"); store(procuraDesig($2,v,quant)); }
        | ProgG IgualL ';'                      { printf("atualiza vetor\n"); }
        | ProgG CriaFun                         { printf("declarar funcao\n");}
        | ProgG Funcao ';'                      { printf("chamar funcao\n"); }
        | ProgG ';'                             { printf("; desnecessario\n"); } 
        | ProgG COM                             { printf("comentario\n"); } 
        |                                       { printf("inicio\n"); } 
        ;

ProgF   : ProgF Se                              { printf("se\n"); }
        | ProgF Enq                             { printf("enquanto\n"); }
        | ProgF Atrib ';'                       { printf("inicializa var\n"); }
        | ProgF VAR '=' Expr ';'                { printf("atualiza var\n"); store(procuraDesig($2,vl,quantl)); }
        | ProgF IgualL ';'                      { printf("atualiza vetor\n"); }
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
        | Prog IgualL ';'                       { printf("atualiza vetor\n"); }
        | Prog Funcao ';'                       { printf("chamar funcao\n"); }
        | Prog ';'                              { printf("; desnecessario\n"); } 
        | Prog COM                              { printf("comentario\n"); } 
        |                                       { printf("inicio\n"); } 
        ;

Funcao  : VAR Lexpr                             { if(strcmp($1,"leri")==0){
                                                        fprintf(out,"read\natoi\n");
                                                        $$ = tipoInt;
                                                  }else if(strcmp($1,"lerf")==0){
                                                        fprintf(out,"read\natof\n");
                                                        $$ = tipoFloat;
                                                  }else if(strcmp($1,"lers")==0){
                                                        fprintf(out,"read\n");
                                                        $$ = tipoString;
                                                  }else if(strcmp($1,"escreveri")==0){
                                                        fprintf(out,"writei\n");
                                                        $$ = tipoInt;
                                                  }else if(strcmp($1,"escrevers")==0){
                                                        fprintf(out,"writes\n");
                                                        $$ = tipoString;
                                                  }else if(strcmp($1,"escreverf")==0){
                                                        fprintf(out,"writef\n");
                                                        $$ = tipoFloat;
                                                  }else if(strcmp($1,"atoi")==0){
                                                        fprintf(out,"atoi\n");
                                                        $$ = tipoInt;
                                                  }else if(strcmp($1,"atof")==0){
                                                        fprintf(out,"atof\n");
                                                        $$ = tipoFloat;
                                                  }else if(strcmp($1,"ftoi")==0){
                                                        fprintf(out,"ftoi\n");
                                                        $$ = tipoInt;
                                                  }else if(strcmp($1,"itof")==0){
                                                        fprintf(out,"itof\n");
                                                        $$ = tipoFloat;
                                                  }else if(strcmp($1,"stri")==0){
                                                        fprintf(out,"stri\n");
                                                        $$ = tipoString;
                                                  }else if(strcmp($1,"strf")==0){
                                                        fprintf(out,"strf\n");
                                                        $$ = tipoString;
                                                  }else{
                                                        funaux = procurafun($1,funcoes,numfun);
                                                        if(!funaux){
                                                            printf("ERRO: funcao nao encontrada\n");
                                                        }else{
                                                            $$ = funaux->tipos[0];
                                                            pushtipo(funaux->tipos[0]);
                                                            for(i=0;i<numelemfun;i++){
                                                                fprintf(out,"pushl %d\n",topo+numelemfun-i-1);
                                                            }
                                                            fprintf(out,"pusha %s\ncall\nnop\npop %d\n",$1,numelemfun);
                                                            for(i=0;i<numelemfun;i++){
                                                               fprintf(out,"swap\npop 1\n");
                                                            }
                                                        }
                                                  }
                                                }
        ;

CriaFun : TIPO VAR '('                          { fprintf(out,"jump fimfun%d\n%s:\nnop\n",numfun,$2); dentrofun = 1; 
                                                  inserefun(criafun($2,&$1,1),funcoes,numfun); 
                                                }
        | Ltipo '{' ProgF '}'                   { fprintf(out,"fimfun%d:\n",numfun); numfun++; dentrofun = 0; zerar(vl,quantl); quantl = 0; }
        ;

Atrib   : TIPO VAR                              { if(dentrofun){
                                                    aux = criaVar($1,$2,topol++,0,0);
                                                    insereVar(aux, vl, quantl++);
                                                    push(aux); push(aux); storel(aux);
                                                  }
                                                  else{
                                                    aux = criaVar($1,$2,topo++,0,0);
                                                    insereVar(aux, v, quant++); 
                                                    push(aux); push(aux); store(aux);
                                                  } 
                                                } 
        | TIPO VAR '[' NUM ']'                 { if(dentrofun){
                                                    aux = criaVar($1,$2,topol,$4,0); topol += $4;
                                                    insereVar(aux, vl, quantl++);
                                                    push(aux); push(aux); 
                                                    for(i=0;i< $4;i++){
                                                        fprintf(out,"storel %d\n",(i+aux->posicaoStack));
                                                    }
                                                  }
                                                  else{
                                                    aux = criaVar($1,$2,topo,$4,0); topo += $4;
                                                    insereVar(aux, v, quant++); 
                                                    push(aux); push(aux);
                                                    for(i=0;i< $4;i++){
                                                        fprintf(out,"storeg %d\n",(i+aux->posicaoStack));
                                                    }
                                                  }
                                                } 
        | TIPO VAR '[' NUM ',' NUM ']'         { if(dentrofun){
                                                    aux = criaVar($1,$2,topol,$4,$6); topol += $4*$6;
                                                    insereVar(aux, vl, quantl++);
                                                    push(aux); push(aux);
                                                    for(i=0;i< $4*$6;i++){
                                                        fprintf(out,"storel %d\n",(i+aux->posicaoStack));
                                                    }
                                                  }
                                                  else{
                                                    aux = criaVar($1,$2,topo,$4,$6); topo += $4*$6;
                                                    insereVar(aux, v, quant++); 
                                                    push(aux); push(aux);
                                                    for(i=0;i< $4*$6;i++){
                                                        fprintf(out,"storeg %d\n",(i+aux->posicaoStack));
                                                    }
                                                  }
                                                }
        | Igual                                 { ; }       
        ;

Igual   : TIPO VAR '='                          { if(dentrofun){
                                                    aux = criaVar($1,$2,topol++,0,0);
                                                    insereVar(aux, vl, quantl++);
                                                    push(aux);
                                                  }
                                                  else{
                                                    aux = criaVar($1,$2,topo++,0,0); 
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

IgualL  : VAR '[' Expr ']'                      { if(dentrofun){        
                                                    fprintf(out,"pushi %d\nadd\npushgp\nswap\n",procuraDesig($1,vl,quantl)->posicaoStack);
                                                  }else{
                                                    fprintf(out,"pushi %d\nadd\npushgp\nswap\n",procuraDesig($1,v,quant)->posicaoStack);
                                                  }
                                                }
        | IgualL '=' Expr                       { fprintf(out,"storen\n"); }

/*lista de expressoes*/
Lexpr   : '(' ')'                               { numelemfun = 0; }
        | '(' Eexpr ')'                         { ; }
        ;

Eexpr   : Expr                                  { numelemfun = 1; }
        | Eexpr ',' Expr                        { numelemfun++; }
        ;

/*lista de tipos*/
Ltipo   : ')'                                   { numelemfun = 0; }
        | Etipo ')'                             { ; }
        ;

Etipo   : TIPO VAR                              { numelemfun = 1; aux = criaVar($1,$2,-(numelemfun),0,0);
                                                  insereVar(aux, vl, quantl++); atualizafun(funcoes[numfun],&$1,1);  
                                                }
        | Etipo ',' TIPO VAR                    { numelemfun++; aux = criaVar($3,$4,-(numelemfun),0,0);
                                                  insereVar(aux, vl, quantl++); atualizafun(funcoes[numfun],&$3,1); 
                                                }
        ;

Se      : SE Cond                               { fprintf(out, "jz fimse%d\n",numse[apse]); apse++; numse[apse] = numse[apse-1]+1; }
        | Se '{' Prog '}' SENAO                 { apse--; fprintf(out, "jump fimse%d\nfimse%d:\n",numse[apse+1],numse[apse]);
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
        | '(' Expr '<' Expr ')'                 { if(strcmp($2,"int")==0 && strcmp($4,"int")==0){
                                                    fprintf(out,"inf\n");
                                                  }else if(strcmp($2,"float")==0 && strcmp($4,"float")==0){
                                                    fprintf(out,"finf\n");
                                                  }else{
                                                    printf("ERRO: tipos sem sentido na condicao.\n");
                                                  }
                                                }
        | '(' Expr '>' Expr ')'                 { if(strcmp($2,"int")==0 && strcmp($4,"int")==0){
                                                    fprintf(out,"sup\n");
                                                  }else if(strcmp($2,"float")==0 && strcmp($4,"float")==0){
                                                    fprintf(out,"fsup\n");
                                                  }else{
                                                    printf("ERRO: tipos sem sentido na condicao.\n");
                                                  }
                                                }
        | '(' Expr LEQ Expr ')'                 { if(strcmp($2,"int")==0 && strcmp($4,"int")==0){
                                                    fprintf(out,"infeq\n");
                                                  }else if(strcmp($2,"float")==0 && strcmp($4,"float")==0){
                                                    fprintf(out,"finfeq\n");
                                                  }else{
                                                    printf("ERRO: tipos sem sentido na condicao.\n");
                                                  }
                                                }
        | '(' Expr GEQ Expr ')'                 { if(strcmp($2,"int")==0 && strcmp($4,"int")==0){
                                                    fprintf(out,"supeq\n");
                                                  }else if(strcmp($2,"float")==0 && strcmp($4,"float")==0){
                                                    fprintf(out,"fsupeq\n");
                                                  }else{
                                                    printf("ERRO: tipos sem sentido na condicao.\n");
                                                  }
                                                }
        | '(' Cond E Cond ')'                   { fprintf(out,"mul\n"); }
        | '(' Cond OU Cond ')'                  { fprintf(out,"add\n"); }
        | '!' Cond                              { fprintf(out,"pushi 0\nequal\n"); }
        ;

Sexpr   : VAR                                   { if(dentrofun){
                                                    aux = procuraDesig($1,vl,quantl);
                                                    fprintf(out,"pushl %d\n",aux->posicaoStack); 
                                                  }else{
                                                    aux = procuraDesig($1,v,quant);
                                                    fprintf(out,"pushg %d\n",aux->posicaoStack); 
                                                  }
                                                  $$ = aux->tipo;
                                                }
        | NUM                                   { fprintf(out,"pushi %d\n", $1); $$ = tipoInt; }
        | FLOAT                                 { fprintf(out,"pushf %f\n", $1); $$ = tipoFloat; }
        | VAR '[' Expr ']'                      { if(dentrofun){
                                                    aux = procuraDesig($1,vl,quantl);
                                                    fprintf(out,"pushi %d\nadd\npushgp\nswap\nloadn\n", procuraDesig($1,vl,quantl)->posicaoStack);
                                                  }else{
                                                    aux = procuraDesig($1,v,quant);
                                                    fprintf(out,"pushi %d\nadd\npushgp\nswap\nloadn\n", procuraDesig($1,v,quant)->posicaoStack);
                                                  }
                                                  $$ = aux->tipo;
                                                }
        | Funcao                                { $$ = $1; } 
        | STR                                   { fprintf(out,"pushs %s\n", $1); $$ = tipoString; }
        ;

Expr	: '(' Expr '+' Expr ')'    			    { if(strcmp($2,"int")==0 && strcmp($4,"int")==0){
                                                    fprintf(out,"add\n");
                                                    $$ = $2;
                                                  }else if(strcmp($2,"float")==0 && strcmp($4,"float")==0){
                                                    fprintf(out,"fadd\n");
                                                    $$ = $2;
                                                  }else if(strcmp($2,"string")==0 && strcmp($4,"string")==0){
                                                    fprintf(out,"concat\n");
                                                    $$ = $2;
                                                  }else{
                                                    printf("ERRO: Na operacao '+' tipos sem sentido\n");
                                                  }
                                                }
        | '(' Expr '-' Expr ')'  	            { if(strcmp($2,"int")==0 && strcmp($4,"int")==0){
                                                    fprintf(out,"sub\n");
                                                    $$ = $2;
                                                  }else if(strcmp($2,"float")==0 && strcmp($4,"float")==0){
                                                    fprintf(out,"fsub\n");
                                                    $$ = $2;
                                                  }else{
                                                    printf("ERRO: Na operacao '-' tipos sem sentido\n");
                                                  } 
                                                }
        | '(' Expr '*' Expr ')'    	            { if(strcmp($2,"int")==0 && strcmp($4,"int")==0){
                                                    fprintf(out,"mul\n");
                                                    $$ = $2;
                                                  }else if(strcmp($2,"float")==0 && strcmp($4,"float")==0){
                                                    fprintf(out,"fmul\n");
                                                    $$ = $2;
                                                  }else{
                                                    printf("ERRO: Na operacao '*' tipos sem sentido\n");
                                                  } 
                                                }
        | '(' Expr '/' Expr ')'    	            { if(strcmp($2,"int")==0 && strcmp($4,"int")==0){
                                                    fprintf(out,"div\n");
                                                    $$ = $2;
                                                  }else if(strcmp($2,"float")==0 && strcmp($4,"float")==0){
                                                    fprintf(out,"fdiv\n");
                                                    $$ = $2;
                                                  }else{
                                                    printf("ERRO: Na operacao '/' tipos sem sentido\n");
                                                  } 
                                                }
        | '(' Expr '%' Expr ')'    	            { if(strcmp($2,"int")==0 && strcmp($4,"int")==0){
                                                    fprintf(out,"mod\n");
                                                    $$ = $2;
                                                  }else{
                                                    printf("ERRO: Na operacao '%%' tipos sem sentido\n");
                                                  } 
                                                }
        | COS Expr                              { if(strcmp($2,"float")==0){
                                                    fprintf(out,"fcos\n");
                                                    $$ = $2;
                                                  }else{
                                                    printf("ERRO: Na operacao 'cos' tipos sem sentido\n");
                                                  } 
                                                }
        | SIN Expr                              { if(strcmp($2,"float")==0){
                                                    fprintf(out,"fsin\n");
                                                    $$ = $2;
                                                  }else{
                                                    printf("ERRO: Na operacao 'sin' tipos sem sentido\n");
                                                  } 
                                                }
        | '(' Expr ')'                          { $$ = $2; }
        | Sexpr                                 { $$ = $1; }
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

