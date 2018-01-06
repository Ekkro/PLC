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
#line 115 "galo.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union{
  int i;
  char *s;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 145 "y.tab.c"

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
#define EQ 264
#define NEQ 265
#define LEQ 266
#define GEQ 267
#define E 268
#define OU 269
#define STR 270
#define COM 271
#define RETURN 272
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    2,    2,    2,    2,    2,    2,    4,    4,    5,    5,
    6,    6,    9,    9,    3,    3,    3,    7,    7,    7,
    7,    7,    7,    7,    7,    7,    7,   10,   10,   10,
   10,   10,    8,    8,    8,    8,    8,    8,    8,
};
static const YYINT yylen[] = {                            2,
    7,    6,    4,    5,    8,    7,    4,    2,    2,    0,
    7,    6,    4,    5,    8,    4,    2,    2,    4,    0,
    1,    4,    3,    6,    5,    3,    2,    3,    1,    3,
    2,    3,    2,    4,    0,    6,    4,    1,    5,    5,
    5,    5,    5,    5,    5,    5,    2,    1,    1,    4,
    2,    1,    5,    5,    5,    5,    5,    3,    1,
};
static const YYINT yydefred[] = {                        10,
    0,    0,    0,    0,    0,    9,    8,   38,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   52,    0,    0,    0,   59,   47,   10,   10,   49,    0,
    0,    0,   27,    0,   29,    7,    0,    0,    0,    0,
    3,    0,    0,   51,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    4,    0,    0,   28,
   23,    0,    0,   31,    0,   20,    0,    0,   58,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    2,    0,   30,    0,   33,    0,   32,
    0,    0,   50,    0,    0,    0,    0,    0,   45,   46,
   39,   40,   43,   44,   41,   42,    0,    0,    1,    0,
    0,    0,    0,    0,    0,    0,   18,    0,    6,   17,
   25,   53,   54,   55,   56,   57,   20,    0,    5,   24,
   34,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   20,   20,   20,    0,    0,   16,   13,   19,   37,    0,
    0,    0,   14,    0,    0,    0,   12,    0,   36,   11,
    0,   15,
};
static const YYINT yydgoto[] = {                          1,
   91,   18,  109,   16,   34,   40,   23,   24,   65,   25,
};
static const YYINT yysindex[] = {                         0,
   -5,  -28,  -28,  -29, -246,    0,    0,    0,  -31,  -28,
  -84,  -79,  -34,  -34,  -37,  -13,  -26,    4,  -18,    0,
    0,  -31, -210,   57,    0,    0,    0,    0,    0,  -34,
   16,  -14,    0,   -4,    0,    0,  -34,  -34,  -41,  -25,
    0, -172,  -34,    0,   10,  -28,  -28,  -34,  -34,  -34,
  -34,  -34,  -34,  -51,  -43,   67,    0,   36,  -34,    0,
    0,    6, -159,    0,   49,    0,   50,   23,    0,  -34,
  -34,  -34,  -34,  -34,   74,   77,   79,   80,   81,   82,
   83,   84, -191,    0,  -34,    0,   66,    0, -157,    0,
   22,  -34,    0,   87,   88,   89,   90,   92,    0,    0,
    0,    0,    0,    0,    0,    0,   11,  -28,    0,   76,
  -34, -125,  -28,  -28,  -11, -124,    0,  -34,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   15,    0,    0,
    0,   17,   18,  -34,  -34,   91,  -30,    5,   93,   28,
    0,    0,    0,   95,   53,    0,    0,    0,    0,   35,
   41,   48,    0,   94, -191, -191,    0,  -34,    0,    0,
   97,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   12,    0,  -17,  -24,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   42,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    7,    0,    0,    0,   44,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   12,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    1,   54,    0,    0,    0,    0,
    0,    0,
};
static const YYINT yygindex[] = {                        64,
  -58,   26,  -60,   -9,    0,    0,   31,  314,    0,    0,
};
#define YYTABLESIZE 472
static const YYINT yytable[] = {                         64,
   35,   10,   30,   33,   10,   30,   35,    7,   22,   44,
   15,    9,   49,   39,   17,    7,   49,   49,   49,   48,
   49,   15,   49,   48,   48,   48,   48,   48,   15,   48,
   37,   13,   11,   12,   37,   49,   60,   49,   27,   59,
   26,   48,   48,   28,   48,   36,   74,   42,   42,  134,
   69,   72,   70,    7,   71,   21,   73,   46,   47,   35,
   38,   14,   41,  147,   38,   35,  107,  108,  140,   52,
   21,   53,   43,   83,   57,   48,   75,   76,   58,  135,
  120,   84,  150,  151,  152,   26,  120,   22,   67,   90,
   54,   55,   89,  120,  159,  160,   85,   66,   87,  120,
   26,   88,   22,   74,  112,  136,  120,   69,   72,   70,
   92,   71,   35,   73,   99,   93,   52,  100,   53,  101,
  102,  103,  104,  105,  106,   35,  111,  122,  123,  124,
  125,   35,  126,  127,  129,  131,  137,  141,  128,  142,
  143,  138,    0,  132,  133,  154,  119,    0,    0,  146,
    0,  148,  149,  153,  158,  162,    0,    0,    0,  155,
    0,    0,    0,    0,    0,  156,    0,    0,    0,    0,
    0,    0,  157,    0,    0,    0,    0,    0,   35,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    2,    0,    0,    3,    4,
    5,    0,    0,    2,    0,    0,    3,    4,    5,    6,
   63,    0,    0,   19,    0,   29,   19,    6,   29,   19,
    0,   20,   21,    0,    8,   21,    0,    0,   21,   49,
   49,   49,   49,   38,   38,    0,   48,   48,   48,   48,
    0,    2,    0,    0,    3,    4,    5,   35,    0,    0,
   35,   35,   35,   35,    0,    6,   35,   35,   35,    0,
    0,   35,   35,   48,   49,   50,   51,   35,  113,    0,
    0,  114,  115,  116,  113,    0,    0,  114,  115,  116,
    0,  113,  117,  118,  114,  115,  116,  113,  117,  118,
  114,  115,  116,    0,  113,  117,  118,  114,  115,  116,
   35,  117,  118,   35,   35,   35,    0,    0,  117,  118,
   48,   49,   50,   51,   35,   35,   31,   32,   35,    0,
    0,    0,    0,    0,    0,   45,    0,    0,    0,    0,
    0,    0,    0,   56,    0,    0,    0,    0,    0,    0,
   61,   62,    0,    0,    0,    0,   68,    0,    0,    0,
    0,   77,   78,   79,   80,   81,   82,    0,    0,    0,
    0,    0,   86,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   94,   95,   96,   97,   98,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  110,    0,
    0,    0,    0,    0,    0,  121,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  130,    0,    0,    0,    0,    0,
    0,  139,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  144,  145,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  161,
};
static const YYINT yycheck[] = {                         41,
    0,   33,   40,   41,   33,   40,    0,   59,   40,   19,
   40,   40,   37,   40,  261,   59,   41,   42,   43,   37,
   45,   40,   47,   41,   42,   43,   44,   45,   40,   47,
   61,   61,    2,    3,   61,   60,   41,   62,  123,   44,
   10,   59,   60,  123,   62,   59,   37,   44,   44,   61,
   41,   42,   43,   59,   45,   44,   47,  268,  269,   59,
   91,   91,   59,   59,   91,   59,  258,  259,  127,   60,
   59,   62,   91,  125,   59,   93,   46,   47,   93,   91,
   59,  125,  141,  142,  143,   44,   59,   44,  261,   41,
   27,   28,   44,   59,  155,  156,   61,  123,   93,   59,
   59,  261,   59,   37,  262,  115,   59,   41,   42,   43,
   61,   45,   59,   47,   41,   93,   60,   41,   62,   41,
   41,   41,   41,   41,   41,  125,   61,   41,   41,   41,
   41,  125,   41,  123,   59,  261,  261,  123,  108,  123,
  123,  116,   -1,  113,  114,   93,  125,   -1,   -1,   59,
   -1,   59,  125,   59,   61,   59,   -1,   -1,   -1,  125,
   -1,   -1,   -1,   -1,   -1,  125,   -1,   -1,   -1,   -1,
   -1,   -1,  125,   -1,   -1,   -1,   -1,   -1,  125,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  257,   -1,   -1,  260,  261,
  262,   -1,   -1,  257,   -1,   -1,  260,  261,  262,  271,
  262,   -1,   -1,  261,   -1,  263,  261,  271,  263,  261,
   -1,  263,  270,   -1,  263,  270,   -1,   -1,  270,  264,
  265,  266,  267,  268,  269,   -1,  264,  265,  266,  267,
   -1,  257,   -1,   -1,  260,  261,  262,  257,   -1,   -1,
  260,  261,  262,  257,   -1,  271,  260,  261,  262,   -1,
   -1,  271,  272,  264,  265,  266,  267,  271,  257,   -1,
   -1,  260,  261,  262,  257,   -1,   -1,  260,  261,  262,
   -1,  257,  271,  272,  260,  261,  262,  257,  271,  272,
  260,  261,  262,   -1,  257,  271,  272,  260,  261,  262,
  257,  271,  272,  260,  261,  262,   -1,   -1,  271,  272,
  264,  265,  266,  267,  271,  272,   13,   14,   15,   -1,
   -1,   -1,   -1,   -1,   -1,   22,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   30,   -1,   -1,   -1,   -1,   -1,   -1,
   37,   38,   -1,   -1,   -1,   -1,   43,   -1,   -1,   -1,
   -1,   48,   49,   50,   51,   52,   53,   -1,   -1,   -1,
   -1,   -1,   59,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   70,   71,   72,   73,   74,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   85,   -1,
   -1,   -1,   -1,   -1,   -1,   92,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  111,   -1,   -1,   -1,   -1,   -1,
   -1,  118,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  134,  135,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  158,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 272
#define YYUNDFTOKEN 285
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
"NUM","EQ","NEQ","LEQ","GEQ","E","OU","STR","COM","RETURN",0,0,0,0,0,0,0,0,0,0,
0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : ProgG",
"ProgG : ProgG SE Cond '{' ProgG '}' Se",
"ProgG : ProgG ENQ Cond '{' ProgG '}'",
"ProgG : ProgG TIPO Eatrib ';'",
"ProgG : ProgG VAR '=' Expr ';'",
"ProgG : ProgG VAR '[' Expr ']' '=' Expr ';'",
"ProgG : ProgG TIPO VAR Ltipo '{' Prog '}'",
"ProgG : ProgG VAR Lexpr ';'",
"ProgG : ProgG ';'",
"ProgG : ProgG COM",
"ProgG :",
"Prog : Prog SE Cond '{' Prog '}' Se",
"Prog : Prog ENQ Cond '{' Prog '}'",
"Prog : Prog TIPO Eatrib ';'",
"Prog : Prog VAR '=' Expr ';'",
"Prog : Prog VAR '[' Expr ']' '=' Expr ';'",
"Prog : Prog VAR Lexpr ';'",
"Prog : Prog ';'",
"Prog : Prog COM",
"Prog : Prog RETURN Expr ';'",
"Prog :",
"Eatrib : VAR",
"Eatrib : VAR '[' Expr ']'",
"Eatrib : VAR '=' Expr",
"Eatrib : VAR '[' Expr ']' '=' Expr",
"Eatrib : Eatrib ',' VAR '=' Expr",
"Eatrib : Eatrib ',' VAR",
"Lexpr : '(' ')'",
"Lexpr : '(' Eexpr ')'",
"Eexpr : Expr",
"Eexpr : Eexpr ',' Expr",
"Ltipo : '(' ')'",
"Ltipo : '(' Etipo ')'",
"Etipo : TIPO VAR",
"Etipo : Etipo ',' TIPO VAR",
"Se :",
"Se : CASO Cond '{' Prog '}' Se",
"Se : SENAO '{' Prog '}'",
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
"Sexpr : VAR '[' Expr ']'",
"Sexpr : VAR Lexpr",
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
#line 214 "galo.y"

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

#line 526 "y.tab.c"

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
#line 131 "galo.y"
	{ printf("se\n"); }
break;
case 2:
#line 132 "galo.y"
	{ printf("enquanto\n"); }
break;
case 3:
#line 133 "galo.y"
	{ printf("inicializa var\n"); pushVarInd(out, yystack.l_mark[-2].s, v, quant); atualizaTipoVar(yystack.l_mark[-2].s, v,quant); }
break;
case 4:
#line 134 "galo.y"
	{ printf("atualiza var\n"); }
break;
case 5:
#line 135 "galo.y"
	{ printf("atualiza vetor\n"); }
break;
case 6:
#line 136 "galo.y"
	{ printf("declarar funcao\n"); }
break;
case 7:
#line 137 "galo.y"
	{ printf("chamar funcao\n"); }
break;
case 8:
#line 138 "galo.y"
	{ printf("; desnecessario\n"); }
break;
case 9:
#line 139 "galo.y"
	{ printf("comentario\n"); }
break;
case 10:
#line 140 "galo.y"
	{ printf("inicio\n"); }
break;
case 11:
#line 143 "galo.y"
	{ printf("se\n"); }
break;
case 12:
#line 144 "galo.y"
	{ printf("enquanto\n"); }
break;
case 13:
#line 145 "galo.y"
	{ printf("inicializa var\n"); pushVarInd(out, yystack.l_mark[-2].s, v, quant); atualizaTipoVar(yystack.l_mark[-2].s, v,quant); }
break;
case 14:
#line 146 "galo.y"
	{ printf("atualiza var\n"); }
break;
case 15:
#line 147 "galo.y"
	{ printf("atualiza vetor\n"); }
break;
case 16:
#line 148 "galo.y"
	{ printf("chamar funcao\n"); }
break;
case 17:
#line 149 "galo.y"
	{ printf("; desnecessario\n"); }
break;
case 18:
#line 150 "galo.y"
	{ printf("comentario\n"); }
break;
case 19:
#line 151 "galo.y"
	{ printf("return\n"); }
break;
case 20:
#line 152 "galo.y"
	{ printf("inicio\n"); }
break;
case 21:
#line 155 "galo.y"
	{ insereVar(criaVar("indef",yystack.l_mark[0].s,&ZERO,topo++), v, quant++); }
break;
case 22:
#line 156 "galo.y"
	{ ; }
break;
case 23:
#line 157 "galo.y"
	{ ; }
break;
case 24:
#line 158 "galo.y"
	{ ; }
break;
case 25:
#line 159 "galo.y"
	{ ; }
break;
case 26:
#line 160 "galo.y"
	{ insereVar(criaVar("indef",yystack.l_mark[0].s,&ZERO,topo++), v, quant++); }
break;
case 27:
#line 164 "galo.y"
	{ ; }
break;
case 28:
#line 165 "galo.y"
	{ ; }
break;
case 29:
#line 168 "galo.y"
	{ ; }
break;
case 30:
#line 169 "galo.y"
	{ ; }
break;
case 31:
#line 173 "galo.y"
	{ ; }
break;
case 32:
#line 174 "galo.y"
	{ ; }
break;
case 33:
#line 177 "galo.y"
	{ ; }
break;
case 34:
#line 178 "galo.y"
	{ ; }
break;
case 35:
#line 181 "galo.y"
	{ ; }
break;
case 36:
#line 182 "galo.y"
	{ ; }
break;
case 37:
#line 183 "galo.y"
	{ ; }
break;
case 38:
#line 186 "galo.y"
	{ ; }
break;
case 39:
#line 187 "galo.y"
	{ ; }
break;
case 40:
#line 188 "galo.y"
	{ ; }
break;
case 41:
#line 189 "galo.y"
	{ ; }
break;
case 42:
#line 190 "galo.y"
	{ ; }
break;
case 43:
#line 191 "galo.y"
	{ ; }
break;
case 44:
#line 192 "galo.y"
	{ ; }
break;
case 45:
#line 193 "galo.y"
	{ ; }
break;
case 46:
#line 194 "galo.y"
	{ ; }
break;
case 47:
#line 195 "galo.y"
	{ ; }
break;
case 48:
#line 198 "galo.y"
	{ ; }
break;
case 49:
#line 199 "galo.y"
	{ ; }
break;
case 50:
#line 200 "galo.y"
	{ ; }
break;
case 51:
#line 201 "galo.y"
	{ ; }
break;
case 52:
#line 202 "galo.y"
	{ ; }
break;
case 53:
#line 205 "galo.y"
	{ ; }
break;
case 54:
#line 206 "galo.y"
	{ ; }
break;
case 55:
#line 207 "galo.y"
	{ ; }
break;
case 56:
#line 208 "galo.y"
	{ ; }
break;
case 57:
#line 209 "galo.y"
	{ ; }
break;
case 58:
#line 210 "galo.y"
	{ ; }
break;
case 59:
#line 211 "galo.y"
	{ ; }
break;
#line 964 "y.tab.c"
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
