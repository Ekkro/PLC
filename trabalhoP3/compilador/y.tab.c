/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "galo.y"
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

    void inserefun(Funcao fun, Funcao funcoes[], int numfun){
        int i;
        for(i = 0;i< numfun;i++){
            if(funcoes[i]==0){
                funcoes[i] = fun;
                break;
            }
        }
        return;
    }
    
    Funcao criafun(char* designacao, char* tipos[], int numtipos){
        Funcao fun = (Funcao)malloc(sizeof(struct funcao));
        fun->designacao = designacao;
        int i;
        for(i=0;i<numtipos;i++){
            fun->tipos[i] = tipos[i];
        }
        fun->numtipos = numtipos;
    }
#line 158 "galo.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union{
    int i;
    float f;
    char *s;
    Expressao expr;
    Funcao fun;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 191 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define SE 257
#define SENAO 258
#define CASO 259
#define ENQ 260
#define VAR 261
#define TIPO 262
#define NUM 263
#define FLOAT 264
#define EQ 265
#define NEQ 266
#define LEQ 267
#define GEQ 268
#define E 269
#define OU 270
#define STR 271
#define COM 272
#define RETURN 273
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   13,   13,   13,   13,   13,   13,   13,   13,   13,   13,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    8,
   12,   12,    2,    2,    2,   14,   14,    4,    4,    5,
    5,    6,    6,   15,   15,    3,    3,    3,   11,   11,
   11,    7,    7,    7,    7,    7,    7,    7,    7,    7,
    7,   10,   10,   10,   10,   10,   10,    9,    9,    9,
    9,    9,    9,    9,
};
static const YYINT yylen[] = {                            2,
    2,    2,    3,    5,    8,    2,    3,    2,    2,    0,
    2,    2,    3,    5,    8,    3,    2,    2,    4,    0,
    2,    2,    3,    5,    8,    3,    2,    2,    0,    2,
    3,    4,    2,    5,    1,    3,    2,    2,    3,    1,
    3,    1,    2,    2,    4,    2,    5,    4,    1,    2,
    4,    1,    5,    5,    5,    5,    5,    5,    5,    5,
    2,    1,    1,    1,    4,    1,    1,    5,    5,    5,
    5,    5,    3,    1,
};
static const YYINT yydefred[] = {                        10,
    0,    0,   49,    0,    0,    9,    8,   42,    0,    0,
    0,    0,    0,    6,    0,    0,   52,    0,    0,   46,
    0,    0,    0,   30,    0,    3,   29,   20,    7,   29,
   50,    0,   63,   64,   67,    0,   66,   37,   74,   43,
    0,    0,    0,    0,    0,   61,    0,    0,   38,    0,
   40,   36,    0,   31,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    4,
    0,   39,    0,    0,    0,    0,   28,   27,    0,    0,
    0,    0,    0,    0,   18,    0,   17,   32,    0,    0,
    0,    0,   51,    0,   73,    0,    0,    0,    0,    0,
   45,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   41,   34,    0,    0,    0,   47,   23,   26,    0,    0,
    0,   13,   16,   65,    0,    0,    0,    0,    0,   59,
   60,   53,   54,   57,   58,   55,   56,    0,    0,    0,
    0,    0,   19,   68,   69,   70,   71,   72,    5,   24,
    0,   14,    0,    0,    0,    0,    0,   25,   15,
};
static const YYINT yydgoto[] = {                          1,
   55,   80,   81,   24,   50,   11,   31,   37,   38,   39,
   83,   14,   56,   15,   16,
};
static const YYINT yysindex[] = {                         0,
  -41,  -27,    0,  -10, -251,    0,    0,    0,  -45,  -84,
  -82,  -14,  -28,    0,   27,  -25,    0,  -31,  -27,    0,
   27, -216,  -37,    0,   43,    0,    0,    0,    0,    0,
    0,  -29,    0,    0,    0,   27,    0,    0,    0,    0,
 -213,    0,  -31, -247,   76,    0,   -9,  -39,    0,   -8,
    0,    0, -211,    0,   54,  -19,   60,   27,   98, -206,
   28,  -27,  -27,   27,   27,   27,   27,   27,   27,    0,
    3,    0,   27,  -21,   56, -181,    0,    0, -176,   35,
  -84,   39,  -28,   57,    0,   27,    0,    0,   41,  -84,
   42,  -28,    0,   -7,    0,   27,   27,   27,   27,   27,
    0,   61,   62,   67,   69,   70,   71,   73,   75,   27,
    0,    0,   27, -156,  -53,    0,    0,    0,   27, -148,
   63,    0,    0,    0,   79,   80,   82,   84,   89,    0,
    0,    0,    0,    0,    0,    0,    0,   72,   78,   49,
   85,   53,    0,    0,    0,    0,    0,    0,    0,    0,
   88,    0,   90,   27,   27,   91,   93,    0,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    7,
    0,    0,   15,    0,   94,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  -24,    0,    0,    0,    0,    0,
    0,  -16,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   16,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    1,    0,
   68,    0,   74,    0,    0,    0,    0,    0,    0,   40,
    0,   46,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   95,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
  102,   23,   31,    0,    0,    0,   66,   36,  327,    0,
   33,    0,    0,    0,    0,
};
#define YYTABLESIZE 482
static const YYINT yytable[] = {                          8,
   48,   19,   36,   49,   19,   19,    1,   52,   43,   25,
   23,   18,   18,   26,    2,   40,   44,    7,   41,   44,
   62,   62,   63,    9,   62,   62,   62,   62,   62,   23,
   62,   10,   72,   13,   33,   73,   12,   53,   27,   87,
   28,   48,   62,   62,   29,   62,   48,    1,   60,   70,
   21,   74,   63,   71,  101,    2,   63,   63,   63,   48,
   63,   58,   63,  110,  100,    1,   36,   20,   95,   98,
   96,  112,   97,    2,   99,   63,   62,   63,   89,  115,
   22,  116,   54,   44,   46,  124,   90,   68,   92,   69,
   82,   91,   82,  117,   30,   23,   23,  118,   11,  122,
  123,  130,  131,   52,   12,   88,  140,  132,   44,  133,
  134,  135,   78,  136,  142,  137,  113,  119,   78,  144,
  145,  143,  146,   48,  147,   48,   21,  102,  103,  148,
  149,   57,   22,   53,  100,   68,  150,   69,   95,   98,
   96,  151,   97,  152,   99,  153,  114,  120,  154,  158,
  155,  159,   35,   33,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   11,    0,    0,    0,    0,    0,
   12,    0,    0,    0,    0,    0,    0,    0,   79,    0,
    0,    0,    0,    0,   93,    0,    0,    0,    0,    0,
    0,    0,   21,    0,    0,    0,    0,    0,   22,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    2,    0,    0,    3,    4,
    5,    0,    0,   32,    0,   33,   34,    0,    0,   32,
    6,   42,   34,   35,   17,   17,    0,    2,    0,   35,
    3,   84,   76,    0,   62,    0,   62,   62,   62,   62,
   62,   62,   85,   86,   62,    0,    0,   48,    0,    0,
   48,   48,   48,    1,    0,    0,    1,    1,    1,    0,
    0,    2,   48,   48,    2,    2,    2,    0,    1,    0,
   63,   63,   63,   63,   52,   52,    2,   32,    0,   33,
   34,    0,   64,   65,   66,   67,   11,   35,    0,   11,
   11,   11,   12,    0,    0,   12,   12,   12,    0,    0,
    2,   11,   11,    3,   75,   76,    2,   12,   12,    3,
   75,   76,    0,    0,   21,   77,    0,   21,   21,   21,
   22,   77,    0,   22,   22,   22,    0,    0,    0,   21,
   64,   65,   66,   67,   45,   22,    0,   47,    0,   51,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   59,    0,    0,    0,    0,    0,    0,   61,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   94,    0,    0,    0,    0,    0,
  104,  105,  106,  107,  108,  109,    0,    0,    0,  111,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  121,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  125,  126,  127,  128,  129,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  138,    0,    0,  139,
    0,    0,    0,    0,    0,  141,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  156,  157,
};
static const YYINT yycheck[] = {                         41,
    0,   33,   40,   41,   33,   33,    0,   61,   40,  261,
   40,   40,   40,   59,    0,   41,   41,   59,   44,   44,
   37,  269,  270,    1,   41,   42,   43,   44,   45,   40,
   47,    1,   41,    1,   59,   44,    1,   91,  123,   59,
  123,   41,   59,   60,   59,   62,  263,   41,  262,   59,
   61,  263,   37,   93,  261,   41,   41,   42,   43,   59,
   45,   91,   47,   61,   37,   59,   40,    2,   41,   42,
   43,   93,   45,   59,   47,   60,   93,   62,   56,  261,
   91,  258,   40,   18,   19,   93,   56,   60,   56,   62,
   55,   56,   57,   59,  123,   40,   40,   59,   59,   59,
   59,   41,   41,   61,   59,  125,  263,   41,   43,   41,
   41,   41,   59,   41,  263,   41,   61,   61,   59,   41,
   41,   59,   41,  123,   41,  125,   59,   62,   63,   41,
   59,   30,   59,   91,   37,   60,   59,   62,   41,   42,
   43,   93,   45,   59,   47,   93,   91,   91,   61,   59,
   61,   59,   59,   59,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  125,   -1,   -1,   -1,   -1,   -1,
  125,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  125,   -1,
   -1,   -1,   -1,   -1,  125,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  125,   -1,   -1,   -1,   -1,   -1,  125,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  257,   -1,   -1,  260,  261,
  262,   -1,   -1,  261,   -1,  263,  264,   -1,   -1,  261,
  272,  263,  264,  271,  263,  263,   -1,  257,   -1,  271,
  260,  261,  262,   -1,  261,   -1,  263,  264,  265,  266,
  267,  268,  272,  273,  271,   -1,   -1,  257,   -1,   -1,
  260,  261,  262,  257,   -1,   -1,  260,  261,  262,   -1,
   -1,  257,  272,  273,  260,  261,  262,   -1,  272,   -1,
  265,  266,  267,  268,  269,  270,  272,  261,   -1,  263,
  264,   -1,  265,  266,  267,  268,  257,  271,   -1,  260,
  261,  262,  257,   -1,   -1,  260,  261,  262,   -1,   -1,
  257,  272,  273,  260,  261,  262,  257,  272,  273,  260,
  261,  262,   -1,   -1,  257,  272,   -1,  260,  261,  262,
  257,  272,   -1,  260,  261,  262,   -1,   -1,   -1,  272,
  265,  266,  267,  268,   18,  272,   -1,   21,   -1,   23,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   36,   -1,   -1,   -1,   -1,   -1,   -1,   43,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   58,   -1,   -1,   -1,   -1,   -1,
   64,   65,   66,   67,   68,   69,   -1,   -1,   -1,   73,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   86,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   96,   97,   98,   99,  100,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  110,   -1,   -1,  113,
   -1,   -1,   -1,   -1,   -1,  119,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  154,  155,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 273
#define YYUNDFTOKEN 291
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,0,0,"'%'",0,0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,
0,0,0,0,"';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"SE","SENAO","CASO","ENQ","VAR","TIPO",
"NUM","FLOAT","EQ","NEQ","LEQ","GEQ","E","OU","STR","COM","RETURN",0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : ProgG",
"ProgG : ProgG Se",
"ProgG : ProgG Enq",
"ProgG : ProgG Atrib ';'",
"ProgG : ProgG VAR '=' Expr ';'",
"ProgG : ProgG VAR '[' NUM ']' '=' Expr ';'",
"ProgG : ProgG CriaFun",
"ProgG : ProgG Funcao ';'",
"ProgG : ProgG ';'",
"ProgG : ProgG COM",
"ProgG :",
"ProgF : ProgF Se",
"ProgF : ProgF Enq",
"ProgF : ProgF Atrib ';'",
"ProgF : ProgF VAR '=' Expr ';'",
"ProgF : ProgF VAR '[' NUM ']' '=' Expr ';'",
"ProgF : ProgF Funcao ';'",
"ProgF : ProgF ';'",
"ProgF : ProgF COM",
"ProgF : ProgF RETURN Expr ';'",
"ProgF :",
"Prog : Prog Se",
"Prog : Prog Enq",
"Prog : Prog Atrib ';'",
"Prog : Prog VAR '=' Expr ';'",
"Prog : Prog VAR '[' NUM ']' '=' Expr ';'",
"Prog : Prog Funcao ';'",
"Prog : Prog ';'",
"Prog : Prog COM",
"Prog :",
"Funcao : VAR Lexpr",
"CriaFun : TIPO VAR '('",
"CriaFun : Ltipo '{' ProgF '}'",
"Atrib : TIPO VAR",
"Atrib : TIPO VAR '[' NUM ']'",
"Atrib : Igual",
"Igual : TIPO VAR '='",
"Igual : Igual Expr",
"Lexpr : '(' ')'",
"Lexpr : '(' Eexpr ')'",
"Eexpr : Expr",
"Eexpr : Eexpr ',' Expr",
"Ltipo : ')'",
"Ltipo : Etipo ')'",
"Etipo : TIPO VAR",
"Etipo : Etipo ',' TIPO VAR",
"Se : SE Cond",
"Se : Se '{' Prog '}' SENAO",
"Se : Se '{' Prog '}'",
"Enq : ENQ",
"Enq : Enq Cond",
"Enq : Enq '{' Prog '}'",
"Cond : NUM",
"Cond : '(' Expr EQ Expr ')'",
"Cond : '(' Expr NEQ Expr ')'",
"Cond : '(' Expr '<' Expr ')'",
"Cond : '(' Expr '>' Expr ')'",
"Cond : '(' Expr LEQ Expr ')'",
"Cond : '(' Expr GEQ Expr ')'",
"Cond : '(' Cond E Cond ')'",
"Cond : '(' Cond OU Cond ')'",
"Cond : '!' Cond",
"Sexpr : VAR",
"Sexpr : NUM",
"Sexpr : FLOAT",
"Sexpr : VAR '[' Expr ']'",
"Sexpr : Funcao",
"Sexpr : STR",
"Expr : '(' Expr '+' Expr ')'",
"Expr : '(' Expr '-' Expr ')'",
"Expr : '(' Expr '*' Expr ')'",
"Expr : '(' Expr '/' Expr ')'",
"Expr : '(' Expr '%' Expr ')'",
"Expr : '(' Expr ')'",
"Expr : Sexpr",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 348 "galo.y"

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

#line 585 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 180 "galo.y"
	{ printf("se\n"); }
break;
case 2:
#line 181 "galo.y"
	{ printf("enquanto\n"); }
break;
case 3:
#line 182 "galo.y"
	{ printf("inicializa var\n"); }
break;
case 4:
#line 183 "galo.y"
	{ printf("atualiza var\n"); store(procuraDesig(yystack.l_mark[-3].s,v,quant)); }
break;
case 5:
#line 184 "galo.y"
	{ printf("atualiza vetor\n"); }
break;
case 6:
#line 185 "galo.y"
	{ printf("declarar funcao\n");}
break;
case 7:
#line 186 "galo.y"
	{ printf("chamar funcao\n"); }
break;
case 8:
#line 187 "galo.y"
	{ printf("; desnecessario\n"); }
break;
case 9:
#line 188 "galo.y"
	{ printf("comentario\n"); }
break;
case 10:
#line 189 "galo.y"
	{ printf("inicio\n"); }
break;
case 11:
#line 192 "galo.y"
	{ printf("se\n"); }
break;
case 12:
#line 193 "galo.y"
	{ printf("enquanto\n"); }
break;
case 13:
#line 194 "galo.y"
	{ printf("inicializa var\n"); }
break;
case 14:
#line 195 "galo.y"
	{ printf("atualiza var\n"); store(procuraDesig(yystack.l_mark[-3].s,v,quant)); }
break;
case 15:
#line 196 "galo.y"
	{ printf("atualiza vetor\n"); }
break;
case 16:
#line 197 "galo.y"
	{ printf("chamar funcao\n"); }
break;
case 17:
#line 198 "galo.y"
	{ printf("; desnecessario\n"); }
break;
case 18:
#line 199 "galo.y"
	{ printf("comentario\n"); }
break;
case 19:
#line 200 "galo.y"
	{ printf("return\n"); fprintf(out,"storel %d\nreturn\n",-(numelemfun+1)); }
break;
case 20:
#line 201 "galo.y"
	{ printf("inicio\n"); }
break;
case 21:
#line 204 "galo.y"
	{ printf("se\n"); }
break;
case 22:
#line 205 "galo.y"
	{ printf("enquanto\n"); }
break;
case 23:
#line 206 "galo.y"
	{ printf("inicializa var\n"); }
break;
case 24:
#line 207 "galo.y"
	{ printf("atualiza var\n"); store(procuraDesig(yystack.l_mark[-3].s,v,quant)); }
break;
case 25:
#line 208 "galo.y"
	{ printf("atualiza vetor\n"); }
break;
case 26:
#line 209 "galo.y"
	{ printf("chamar funcao\n"); }
break;
case 27:
#line 210 "galo.y"
	{ printf("; desnecessario\n"); }
break;
case 28:
#line 211 "galo.y"
	{ printf("comentario\n"); }
break;
case 29:
#line 212 "galo.y"
	{ printf("inicio\n"); }
break;
case 30:
#line 215 "galo.y"
	{ if(strcmp(yystack.l_mark[-1].s,"leri")==0){
                                                        fprintf(out,"read\natoi\n");
                                                  }else if(strcmp(yystack.l_mark[-1].s,"lers")==0){
                                                        fprintf(out,"read\n");
                                                  }else if(strcmp(yystack.l_mark[-1].s,"escreveri")==0){
                                                        fprintf(out,"writei\n");
                                                  }else if(strcmp(yystack.l_mark[-1].s,"escrevers")==0){
                                                        fprintf(out,"writes\n");
                                                  }else{
                                                        for(i=0;i<numelemfun;i++){
                                                            
                                                        }
                                                  }
                                                }
break;
case 31:
#line 231 "galo.y"
	{ fprintf(out,"jump fimfun%d\n%s:\nnop\n",numfun,yystack.l_mark[-1].s); dentrofun = 1; 
                                                  inserefun(criafun(yystack.l_mark[-1].s,&yystack.l_mark[-2].s,1),funcoes,numfun); 
                                                }
break;
case 32:
#line 234 "galo.y"
	{ fprintf(out,"fimfun%d:\n",numfun); numfun++; dentrofun = 0; }
break;
case 33:
#line 237 "galo.y"
	{ if(dentrofun){
                                                    aux = criaVar(yystack.l_mark[-1].s,yystack.l_mark[0].s,topol++,0);
                                                    insereVar(aux, vl, quantl++);
                                                    push(aux); push(aux); storel(aux);
                                                  }
                                                  else{
                                                    aux = criaVar(yystack.l_mark[-1].s,yystack.l_mark[0].s,topo++,0);
                                                    insereVar(aux, v, quant++); 
                                                    push(aux); push(aux); store(aux);
                                                  } 
                                                }
break;
case 34:
#line 248 "galo.y"
	{ insereVar(criaVar(yystack.l_mark[-4].s,yystack.l_mark[-3].s,topo++,1), v, quant++);

                                                  store(procuraDesig(yystack.l_mark[-3].s,v,quant)); 
                                                }
break;
case 35:
#line 252 "galo.y"
	{ ; }
break;
case 36:
#line 255 "galo.y"
	{ if(dentrofun){
                                                    aux = criaVar(yystack.l_mark[-2].s,yystack.l_mark[-1].s,topol++,0);
                                                    insereVar(aux, vl, quantl++);
                                                    push(aux);
                                                  }
                                                  else{
                                                    aux = criaVar(yystack.l_mark[-2].s,yystack.l_mark[-1].s,topo++,0); 
                                                    insereVar(aux, v, quant++);
                                                    push(aux);
                                                  }
                                                }
break;
case 37:
#line 266 "galo.y"
	{ if(dentrofun){
                                                    storel(aux);
                                                  }
                                                  else{
                                                    store(aux);
                                                  } 
                                                }
break;
case 38:
#line 276 "galo.y"
	{ numelemfun = 0; }
break;
case 39:
#line 277 "galo.y"
	{ ; }
break;
case 40:
#line 280 "galo.y"
	{ numelemfun = 1; }
break;
case 41:
#line 281 "galo.y"
	{ numelemfun++; }
break;
case 42:
#line 285 "galo.y"
	{ numelemfun = 0 ; }
break;
case 43:
#line 286 "galo.y"
	{ ; }
break;
case 44:
#line 289 "galo.y"
	{ numelemfun = 1; aux = criaVar(yystack.l_mark[-1].s,yystack.l_mark[0].s,-(numelemfun),0);
                                                  insereVar(aux, vl, quantl++);
                                                }
break;
case 45:
#line 292 "galo.y"
	{ numelemfun++; aux = criaVar(yystack.l_mark[-1].s,yystack.l_mark[0].s,-(numelemfun),0);
                                                  insereVar(aux, vl, quantl++);
                                                }
break;
case 46:
#line 297 "galo.y"
	{ fprintf(out, "jz fimse%d\n",numse[apse]); apse++; numse[apse] = numse[apse-1]+1; }
break;
case 47:
#line 298 "galo.y"
	{ apse--; fprintf(out, "jump fimse%d\nfimse%d:\n",numse[apse]+1,numse[apse]);
                                                  numse[apse] = numse[apse+1]; apse++; numse[apse] = numse[apse-1]+1; 
                                                }
break;
case 48:
#line 301 "galo.y"
	{ apse--; fprintf(out, "fimse%d:\n",numse[apse]); numse[apse] = numse[apse+1]; }
break;
case 49:
#line 304 "galo.y"
	{ fprintf(out,"enq%d:\n",numenq[apenq]); }
break;
case 50:
#line 305 "galo.y"
	{ fprintf(out,"jz fimenq%d\n",numenq[apenq]); apenq++; numenq[apenq] = numenq[apenq-1]+1; }
break;
case 51:
#line 306 "galo.y"
	{ apenq--; fprintf(out,"jump enq%d\nfimenq%d:\n",numenq[apenq],numenq[apenq]); 
                                                  numenq[apenq]= numenq[apenq+1]; 
                                                }
break;
case 52:
#line 311 "galo.y"
	{ fprintf(out,"pushi %d\n",yystack.l_mark[0].i!=0); }
break;
case 53:
#line 312 "galo.y"
	{ fprintf(out,"equal\n"); }
break;
case 54:
#line 313 "galo.y"
	{ fprintf(out,"equal\npushi 0\nequal\n"); }
break;
case 55:
#line 314 "galo.y"
	{ fprintf(out,"inf\n"); }
break;
case 56:
#line 315 "galo.y"
	{ fprintf(out,"sup\n"); }
break;
case 57:
#line 316 "galo.y"
	{ fprintf(out,"infeq\n"); }
break;
case 58:
#line 317 "galo.y"
	{ fprintf(out,"supeq\n"); }
break;
case 59:
#line 318 "galo.y"
	{ fprintf(out,"mul\n"); }
break;
case 60:
#line 319 "galo.y"
	{ fprintf(out,"add\n"); }
break;
case 61:
#line 320 "galo.y"
	{ fprintf(out,"pushi 0\nequal\n"); }
break;
case 62:
#line 323 "galo.y"
	{ if(dentrofun){
                                                    fprintf(out,"pushl %d\n",procuraDesig(yystack.l_mark[0].s,vl,quantl)->posicaoStack); 
                                                  }else{
                                                    fprintf(out,"pushg %d\n",procuraDesig(yystack.l_mark[0].s,v,quant)->posicaoStack); 
                                                  }
                                                }
break;
case 63:
#line 329 "galo.y"
	{ fprintf(out,"pushi %d\n", yystack.l_mark[0].i); yyval.expr = (Expressao)malloc(sizeof(struct expressao));
                                                  yyval.expr->tipo = tipoInt; }
break;
case 64:
#line 331 "galo.y"
	{ fprintf(out,"pushf %f\n", yystack.l_mark[0].f); yyval.expr = (Expressao)malloc(sizeof(struct expressao));
                                                  yyval.expr->tipo = tipoFloat; }
break;
case 65:
#line 333 "galo.y"
	{ ; }
break;
case 66:
#line 334 "galo.y"
	{ yyval.expr = (Expressao)malloc(sizeof(struct expressao));
                                                  yyval.expr->tipo = yystack.l_mark[0].fun->tipos[0]; }
break;
case 67:
#line 336 "galo.y"
	{ fprintf(out,"pushs %s\n", yystack.l_mark[0].s); yyval.expr->tipo = tipoString; }
break;
case 68:
#line 339 "galo.y"
	{ fprintf(out,"add\n"); }
break;
case 69:
#line 340 "galo.y"
	{ fprintf(out,"sub\n"); }
break;
case 70:
#line 341 "galo.y"
	{ fprintf(out,"mul\n"); }
break;
case 71:
#line 342 "galo.y"
	{ fprintf(out,"div\n"); }
break;
case 72:
#line 343 "galo.y"
	{ fprintf(out,"mod\n"); }
break;
case 73:
#line 344 "galo.y"
	{ yyval.expr = (Expressao)malloc(sizeof(struct expressao)); yyval.expr = yystack.l_mark[-1].expr; }
break;
case 74:
#line 345 "galo.y"
	{ yyval.expr = (Expressao)malloc(sizeof(struct expressao)); yyval.expr = yystack.l_mark[0].expr; }
break;
#line 1143 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
