%{
#include <stdio.h>
#include <string.h>

    int yylex();
    int yyerror();
    int topo = 0;

    typedef struct variavel{
        char* tipo;
        char* designacao;
        void* valor;    //o artur explica: "É à macho"
	int   quantelem;
        int posicaoStack;
    } *Variavel;

    typedef struct expressao{
        char* tipo;
        char* valor;
        int posicaoStack;
    } Expressao;

    Variavel v[1024] = {0};
    int quantidade = 0;

    int insere (Variavel var, Variavel v[],int N){
	if(N>=1024)return -1;
	
	int x;
	for(x = 0; x<1024 ; x++){
		if(v[x]==NULL)break;	 
	}
	v[x]=var;
	return N++;
    }
    int remove (Variavel var, Variavel v[], int N){
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

    Variavel createvar (char* tipo, char* designacao , void valor,int quantelem, int posicaoStack){
	struct variavel var;
	var.tipo = tipo;
	var.designacao = designacao;
	var.valor = &valor;
	var.quantelem = quantelem;
	var.posicaoStack = posicaoStack;
	return &var;
    }

    void alteraValor (Variavel var, void valor){
	var->valor=&valor;
    }	

    int isapontador (char* t){
	int i;
	for (i=0; t[i]!='\0'; i++);
	return t[i-1]=='*';
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
        | TIPO Eatrib ';' Prog                  { char* tipo = $1; }
        | VAR '=' Expr ';' Prog                 { ; }
        | VAR '[' Expr ']' '=' Expr ';' Prog    { ; }
        | TIPO VAR Ltipo '{' Prog '}' Prog      { ; }
        | VAR Lexpr ';' Prog                    { ; }
        | ';' Prog                              { $$ = $2; } /*check*/
        | COM Prog                              { $$ = $2; } /*check*/
        |                                       { ; } /*check*/
        ;

Eatrib  : VAR                                   { if(isapontador(tipo)){   		}else{createvar(tipo,$1,0,1,topo++); 	fprintf(out, "push"tipo[1]" 0");   }}
        | VAR '[' NUM ']'                       { if($3>0){if(isapontador(tipo)){   	}else{createvar(tipo,$1,0,$3,topo++); 	fprintf(out, "push");		   }}}  	//que tipo de push? pushn?
        | VAR '=' Expr                          { if(isapontador(tipo)){   		}else{createvar(tipo,$1,$3,1,topo++); 	fprintf(out, "push"tipo[1]" "$3);  }}  		//como printo push $3?
        | VAR '[' NUM ']' '=' Expr              { if($3>0){if(isapontador(tipo)){   	}else{createvar(tipo,$1,$6,$3,topo++); 	fprintf(out, "push"tipo[1]" "$3);  }}}		//mistura dos acima
        | Eatrib ',' VAR '=' Expr               { if(isapontador(tipo)){   		}else{createvar(tipo,$3,$5,1,topo++); 	fprintf(out, "push"tipo[1]);       }}		//mistura dos acima
        | Eatrib ',' VAR                        { if(isapontador(tipo)){   		}else{createvar(tipo,$3,0,1,topo++); 	fprintf(out, "push"tipo[1]" 0");   }}
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
        | Expr Cexpr	                        { ; }
        | STR                                   { ; }
        ;

Cexpr	: '+' Expr				{ ; }
	| '-' Expr				{ ; }
	| '*' Expr				{ ; }
	| '/' Expr				{ ; }
	| '%' Expr				{ ; }
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

    //char codigo[1023*1024];

    fprintf(out, "start\n"); 
    yyparse();
    fprintf(out, "stop\n");

    fclose(out);
    return(0);
}

