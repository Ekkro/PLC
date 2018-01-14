/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "galo.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1024

    int yylex();
    int yyerror();
    int topo = 0, topol = 0;
    int numse[128] = {0}, apse = 0, numenq[128] = {0}, apenq = 0;
    int numelemfun = 0, numfun = 0, dentrofun = 0; 
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

    Variavel v[MAX] = {0}, aux = NULL, vl[MAX] = {0};
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

#line 193 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SE = 258,
    SENAO = 259,
    CASO = 260,
    ENQ = 261,
    VAR = 262,
    TIPO = 263,
    NUM = 264,
    EQ = 265,
    NEQ = 266,
    LEQ = 267,
    GEQ = 268,
    E = 269,
    OU = 270,
    STR = 271,
    COM = 272,
    RETURN = 273
  };
#endif
/* Tokens.  */
#define SE 258
#define SENAO 259
#define CASO 260
#define ENQ 261
#define VAR 262
#define TIPO 263
#define NUM 264
#define EQ 265
#define NEQ 266
#define LEQ 267
#define GEQ 268
#define E 269
#define OU 270
#define STR 271
#define COM 272
#define RETURN 273

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 128 "galo.y" /* yacc.c:355  */

    int i;
    char *s;
    Expressao expr;

#line 275 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 292 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   191

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  162

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   273

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    30,     2,     2,     2,    35,     2,     2,
      23,    26,    33,    31,    27,    32,     2,    34,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    19,
      28,    20,    29,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    21,     2,    22,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    24,     2,    25,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   146,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   181,   193,   194,   197,   208,   212,   215,   226,   236,
     237,   240,   241,   245,   246,   249,   252,   257,   258,   259,
     261,   264,   265,   266,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   282,   288,   289,   290,   291,   294,
     295,   296,   297,   298,   299,   300
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SE", "SENAO", "CASO", "ENQ", "VAR",
  "TIPO", "NUM", "EQ", "NEQ", "LEQ", "GEQ", "E", "OU", "STR", "COM",
  "RETURN", "';'", "'='", "'['", "']'", "'('", "'{'", "'}'", "')'", "','",
  "'<'", "'>'", "'!'", "'+'", "'-'", "'*'", "'/'", "'%'", "$accept",
  "ProgG", "ProgF", "Prog", "Funcao", "CriaFun", "Atrib", "Igual", "Lexpr",
  "Eexpr", "Ltipo", "Etipo", "Se", "Enq", "Cond", "Sexpr", "Expr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,    59,
      61,    91,    93,    40,   123,   125,    41,    44,    60,    62,
      33,    43,    45,    42,    47,    37
};
# endif

#define YYPACT_NINF -21

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-21)))

#define YYTABLE_NINF -55

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -21,    69,   -21,     3,   -21,     7,    -5,   -21,   -21,   -21,
      12,   -21,    37,    76,    55,   -20,    87,    -1,   -21,    71,
       3,   -21,    76,    16,   124,   -21,    32,   -21,   -21,    89,
     -21,   -21,    76,   -21,   -21,   -21,   -21,   -21,   105,   -21,
     -21,   -21,    -4,    71,    28,    92,   -21,    97,   110,   -21,
      47,   -21,   -21,   115,   -21,    76,   125,    90,   127,   111,
     136,     6,     3,     3,    76,    76,    76,    76,    76,    76,
     -21,   121,   -21,    76,   113,   123,   -21,    76,    76,    76,
      76,    76,    61,   139,   -21,    76,   -21,   -21,   129,   130,
      87,    -1,   -21,   102,   -21,   -21,    85,   133,   135,    87,
      -1,   -21,   137,   138,   140,   141,   142,   143,   144,   145,
      76,   -21,   -21,   -21,   146,   147,   148,   149,   150,    76,
     153,   106,   158,   -21,   -21,    76,   156,   -21,     3,   -21,
     -21,   -21,   -21,   -21,   -21,   -21,   -21,   -21,   -21,   159,
     -21,   -21,   -21,   -21,   -21,   160,   161,   -21,   162,   163,
     -21,   -21,   -21,   164,   -21,   166,    76,    76,   168,   169,
     -21,   -21
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      11,     0,     1,     0,    51,     0,     0,    10,     9,    43,
       0,     7,     0,    36,     0,     0,     2,     3,    54,     0,
       0,    47,     0,     0,     0,    31,    45,     8,     4,    64,
      65,    68,     0,    67,    75,    38,    21,    44,     0,    30,
      30,    52,    65,     0,     0,     0,    63,     0,     0,    39,
       0,    41,    37,     0,    32,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       5,     0,    40,     0,     0,     0,    74,     0,     0,     0,
       0,     0,     0,     0,    19,     0,    18,    33,     0,     0,
      12,    13,    46,     0,    29,    28,    50,     0,     0,    22,
      23,    53,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    42,    35,    66,     0,     0,     0,     0,     0,     0,
       0,    34,     0,    17,    14,     0,     0,    49,     0,    27,
      24,    61,    62,    55,    56,    59,    60,    57,    58,     0,
      69,    70,    71,    72,    73,     0,     0,    20,     0,     0,
      48,     6,    15,     0,    25,     0,     0,     0,     0,     0,
      16,    26
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -21,   -21,   -21,   151,     8,   -21,     0,   -21,   -21,   -21,
     -21,   -21,    13,    14,     1,   -21,   -19
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,    57,    59,    33,    11,    98,    13,    25,    50,
      14,    15,    99,   100,    41,    34,    35
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      45,    12,    26,    47,    21,    51,    37,    38,    18,    10,
     -54,   -54,    18,    56,    16,    17,    64,    65,    66,    67,
      44,    46,    19,    40,    61,    48,    19,    22,    23,    20,
      24,    27,    76,    20,    68,    69,    75,    77,    78,    79,
      80,    81,    62,    63,    44,   104,   105,   106,   107,   108,
     109,   -34,    52,    53,   111,    54,    28,    89,   114,   115,
     116,   117,   118,   102,   103,    88,   122,    97,    97,     2,
      90,    91,     3,    72,    73,     4,     5,     6,    29,    36,
      42,   119,   120,    29,    24,    30,     7,    31,     8,   127,
     128,   139,    31,     3,    43,     9,     4,    82,    83,    32,
     145,    20,    64,    65,    66,    67,   148,    84,    85,    86,
      55,    39,    24,    58,     3,    87,    70,     4,    93,    83,
      68,    69,   125,   126,    74,    24,    52,    53,    94,   150,
      95,    29,    71,    30,    92,   112,    96,   158,   159,     3,
      31,   110,     4,    93,    83,   113,   121,    32,   123,   124,
      49,    76,   129,    94,   130,    95,    77,    78,    79,    80,
      81,   101,   146,   131,   132,   149,   133,   134,   135,   136,
     137,   138,   140,   141,   142,   143,   144,   147,   151,   152,
       0,   154,     0,   153,   156,   155,   157,   160,   161,     0,
       0,    60
};

static const yytype_int16 yycheck[] =
{
      19,     1,     7,    22,     3,    24,    26,    27,     9,     1,
      14,    15,     9,    32,     1,     1,    10,    11,    12,    13,
      19,    20,    23,    24,    43,     9,    23,    20,    21,    30,
      23,    19,    26,    30,    28,    29,    55,    31,    32,    33,
      34,    35,    14,    15,    43,    64,    65,    66,    67,    68,
      69,    19,    20,    21,    73,    23,    19,    57,    77,    78,
      79,    80,    81,    62,    63,    57,    85,    59,    60,     0,
      57,    57,     3,    26,    27,     6,     7,     8,     7,    24,
       9,    20,    21,     7,    23,     9,    17,    16,    19,     4,
       5,   110,    16,     3,    23,    26,     6,     7,     8,    23,
     119,    30,    10,    11,    12,    13,   125,    17,    18,    19,
      21,    24,    23,     8,     3,    25,    19,     6,     7,     8,
      28,    29,    20,    21,     9,    23,    20,    21,    17,   128,
      19,     7,    22,     9,     7,    22,    25,   156,   157,     3,
      16,    20,     6,     7,     8,    22,     7,    23,    19,    19,
      26,    26,    19,    17,    19,    19,    31,    32,    33,    34,
      35,    25,     9,    26,    26,     9,    26,    26,    26,    26,
      26,    26,    26,    26,    26,    26,    26,    19,    19,    19,
      -1,    19,    -1,    22,    20,    22,    20,    19,    19,    -1,
      -1,    40
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    37,     0,     3,     6,     7,     8,    17,    19,    26,
      40,    41,    42,    43,    46,    47,    48,    49,     9,    23,
      30,    50,    20,    21,    23,    44,     7,    19,    19,     7,
       9,    16,    23,    40,    51,    52,    24,    26,    27,    24,
      24,    50,     9,    23,    50,    52,    50,    52,     9,    26,
      45,    52,    20,    21,    23,    21,    52,    38,     8,    39,
      39,    52,    14,    15,    10,    11,    12,    13,    28,    29,
      19,    22,    26,    27,     9,    52,    26,    31,    32,    33,
      34,    35,     7,     8,    17,    18,    19,    25,    40,    42,
      48,    49,     7,     7,    17,    19,    25,    40,    42,    48,
      49,    25,    50,    50,    52,    52,    52,    52,    52,    52,
      20,    52,    22,    22,    52,    52,    52,    52,    52,    20,
      21,     7,    52,    19,    19,    20,    21,     4,     5,    19,
      19,    26,    26,    26,    26,    26,    26,    26,    26,    52,
      26,    26,    26,    26,    26,    52,     9,    19,    52,     9,
      50,    19,    19,    22,    19,    22,    20,    20,    52,    52,
      19,    19
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    37,    37,    37,    37,    37,    37,    37,    37,
      37,    37,    38,    38,    38,    38,    38,    38,    38,    38,
      38,    38,    39,    39,    39,    39,    39,    39,    39,    39,
      39,    40,    41,    41,    42,    42,    42,    43,    43,    44,
      44,    45,    45,    46,    46,    47,    47,    48,    48,    48,
      48,    49,    49,    49,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    51,    51,    51,    51,    51,    52,
      52,    52,    52,    52,    52,    52
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     3,     5,     8,     2,     3,     2,
       2,     0,     2,     2,     3,     5,     8,     3,     2,     2,
       4,     0,     2,     2,     3,     5,     8,     3,     2,     2,
       0,     2,     3,     4,     2,     5,     1,     3,     2,     2,
       3,     1,     3,     1,     2,     2,     4,     2,     6,     5,
       4,     1,     2,     4,     1,     5,     5,     5,     5,     5,
       5,     5,     5,     2,     1,     1,     4,     1,     1,     5,
       5,     5,     5,     5,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 146 "galo.y" /* yacc.c:1646  */
    { printf("se\n"); }
#line 1475 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 147 "galo.y" /* yacc.c:1646  */
    { printf("enquanto\n"); }
#line 1481 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 148 "galo.y" /* yacc.c:1646  */
    { printf("inicializa var\n"); }
#line 1487 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 149 "galo.y" /* yacc.c:1646  */
    { printf("atualiza var\n"); store(procuraDesig((yyvsp[-3].s),v,quant)); }
#line 1493 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 150 "galo.y" /* yacc.c:1646  */
    { printf("atualiza vetor\n"); }
#line 1499 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 151 "galo.y" /* yacc.c:1646  */
    { printf("declarar funcao com %d variaveis\n",numelemfun);}
#line 1505 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 152 "galo.y" /* yacc.c:1646  */
    { printf("chamar funcao\n"); }
#line 1511 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 153 "galo.y" /* yacc.c:1646  */
    { printf("; desnecessario\n"); }
#line 1517 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 154 "galo.y" /* yacc.c:1646  */
    { printf("comentario\n"); }
#line 1523 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 155 "galo.y" /* yacc.c:1646  */
    { printf("inicio\n"); }
#line 1529 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 158 "galo.y" /* yacc.c:1646  */
    { printf("se\n"); }
#line 1535 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 159 "galo.y" /* yacc.c:1646  */
    { printf("enquanto\n"); }
#line 1541 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 160 "galo.y" /* yacc.c:1646  */
    { printf("inicializa var\n"); }
#line 1547 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 161 "galo.y" /* yacc.c:1646  */
    { printf("atualiza var\n"); store(procuraDesig((yyvsp[-3].s),v,quant)); }
#line 1553 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 162 "galo.y" /* yacc.c:1646  */
    { printf("atualiza vetor\n"); }
#line 1559 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 163 "galo.y" /* yacc.c:1646  */
    { printf("chamar funcao\n"); }
#line 1565 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 164 "galo.y" /* yacc.c:1646  */
    { printf("; desnecessario\n"); }
#line 1571 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 165 "galo.y" /* yacc.c:1646  */
    { printf("comentario\n"); }
#line 1577 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 166 "galo.y" /* yacc.c:1646  */
    { printf("return\n"); fprintf(out,"storel %d\nreturn\n",-(numelemfun+1)); }
#line 1583 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 167 "galo.y" /* yacc.c:1646  */
    { printf("inicio\n"); }
#line 1589 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 170 "galo.y" /* yacc.c:1646  */
    { printf("se\n"); }
#line 1595 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 171 "galo.y" /* yacc.c:1646  */
    { printf("enquanto\n"); }
#line 1601 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 172 "galo.y" /* yacc.c:1646  */
    { printf("inicializa var\n"); }
#line 1607 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 173 "galo.y" /* yacc.c:1646  */
    { printf("atualiza var\n"); store(procuraDesig((yyvsp[-3].s),v,quant)); }
#line 1613 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 174 "galo.y" /* yacc.c:1646  */
    { printf("atualiza vetor\n"); }
#line 1619 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 175 "galo.y" /* yacc.c:1646  */
    { printf("chamar funcao\n"); }
#line 1625 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 176 "galo.y" /* yacc.c:1646  */
    { printf("; desnecessario\n"); }
#line 1631 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 177 "galo.y" /* yacc.c:1646  */
    { printf("comentario\n"); }
#line 1637 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 178 "galo.y" /* yacc.c:1646  */
    { printf("inicio\n"); }
#line 1643 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 181 "galo.y" /* yacc.c:1646  */
    { if(strcmp((yyvsp[-1].s),"leri")==0){
                                                        fprintf(out,"read\natoi\n");
                                                  }else if(strcmp((yyvsp[-1].s),"lers")==0){
                                                        fprintf(out,"read\n");
                                                  }else if(strcmp((yyvsp[-1].s),"escreveri")==0){
                                                        fprintf(out,"writei\n");
                                                  }else if(strcmp((yyvsp[-1].s),"escrevers")==0){
                                                        fprintf(out,"writes\n");
                                                  } 
                                                }
#line 1658 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 193 "galo.y" /* yacc.c:1646  */
    { fprintf(out,"jump fimfun%d\n%s:\nnop\n",numfun,(yyvsp[-1].s)); dentrofun = 1; }
#line 1664 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 194 "galo.y" /* yacc.c:1646  */
    { fprintf(out,"fimfun%d:\n",numfun); numfun++; dentrofun = 0; }
#line 1670 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 197 "galo.y" /* yacc.c:1646  */
    { if(dentrofun){
                                                    aux = criaVar((yyvsp[-1].s),(yyvsp[0].s),topol++,0);
                                                    insereVar(aux, vl, quantl++);
                                                    push(aux); push(aux); storel(aux);
                                                  }
                                                  else{
                                                    aux = criaVar((yyvsp[-1].s),(yyvsp[0].s),topo++,0);
                                                    insereVar(aux, v, quant++); 
                                                    push(aux); push(aux); store(aux);
                                                  } 
                                                }
#line 1686 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 208 "galo.y" /* yacc.c:1646  */
    { insereVar(criaVar((yyvsp[-4].s),(yyvsp[-3].s),topo++,1), v, quant++);

                                                  store(procuraDesig((yyvsp[-3].s),v,quant)); 
                                                }
#line 1695 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 212 "galo.y" /* yacc.c:1646  */
    { ; }
#line 1701 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 215 "galo.y" /* yacc.c:1646  */
    { if(dentrofun){
                                                    aux = criaVar((yyvsp[-2].s),(yyvsp[-1].s),topol++,0);
                                                    insereVar(aux, vl, quantl++);
                                                    push(aux);
                                                  }
                                                  else{
                                                    aux = criaVar((yyvsp[-2].s),(yyvsp[-1].s),topo++,0); 
                                                    insereVar(aux, v, quant++);
                                                    push(aux);
                                                  }
                                                }
#line 1717 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 226 "galo.y" /* yacc.c:1646  */
    { if(dentrofun){
                                                    storel(aux);
                                                  }
                                                  else{
                                                    store(aux);
                                                  } 
                                                }
#line 1729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 236 "galo.y" /* yacc.c:1646  */
    { ; }
#line 1735 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 237 "galo.y" /* yacc.c:1646  */
    { ; }
#line 1741 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 240 "galo.y" /* yacc.c:1646  */
    { ; }
#line 1747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 241 "galo.y" /* yacc.c:1646  */
    { ; }
#line 1753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 245 "galo.y" /* yacc.c:1646  */
    { numelemfun = 0 ; }
#line 1759 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 246 "galo.y" /* yacc.c:1646  */
    { ; }
#line 1765 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 249 "galo.y" /* yacc.c:1646  */
    { numelemfun = 1; aux = criaVar((yyvsp[-1].s),(yyvsp[0].s),-(numelemfun),0);
                                                  insereVar(aux, vl, quantl++);
                                                }
#line 1773 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 252 "galo.y" /* yacc.c:1646  */
    { numelemfun++; aux = criaVar((yyvsp[-1].s),(yyvsp[0].s),-(numelemfun),0);
                                                  insereVar(aux, vl, quantl++);
                                                }
#line 1781 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 257 "galo.y" /* yacc.c:1646  */
    { fprintf(out, "jz fimse%d\n",numse[apse]); apse++; numse[apse] = numse[apse-1]+1; }
#line 1787 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 258 "galo.y" /* yacc.c:1646  */
    { ; }
#line 1793 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 259 "galo.y" /* yacc.c:1646  */
    { apse--; fprintf(out, "jump fimse%d\nfimse%d:\n",numse[apse],numse[apse]+1);
                                                  numse[apse] = numse[apse+1]; apse++; numse[apse] = numse[apse-1]+1; }
#line 1800 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 261 "galo.y" /* yacc.c:1646  */
    { apse--; fprintf(out, "fimse%d:\n",numse[apse]); numse[apse] = numse[apse+1]; }
#line 1806 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 264 "galo.y" /* yacc.c:1646  */
    { fprintf(out,"enq%d:\n",numenq[apenq]);  }
#line 1812 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 265 "galo.y" /* yacc.c:1646  */
    { fprintf(out,"jz fimenq%d\n",numenq[apenq]); apenq++; numenq[apenq] = numenq[apenq-1]+1; }
#line 1818 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 266 "galo.y" /* yacc.c:1646  */
    { apenq--; fprintf(out,"jump enq%d\nfimenq%d:\n",numenq[apenq],numenq[apenq]); 
                                                  numenq[apenq]= numenq[apenq+1]; }
#line 1825 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 270 "galo.y" /* yacc.c:1646  */
    { fprintf(out,"pushi %d\n",abs((yyvsp[0].i))); }
#line 1831 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 271 "galo.y" /* yacc.c:1646  */
    { fprintf(out,"equal\n"); }
#line 1837 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 272 "galo.y" /* yacc.c:1646  */
    { fprintf(out,"equal\npushi 0\nequal\n"); }
#line 1843 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 273 "galo.y" /* yacc.c:1646  */
    { fprintf(out,"inf\n"); }
#line 1849 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 274 "galo.y" /* yacc.c:1646  */
    { fprintf(out,"sup\n"); }
#line 1855 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 275 "galo.y" /* yacc.c:1646  */
    { fprintf(out,"infeq\n"); }
#line 1861 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 276 "galo.y" /* yacc.c:1646  */
    { fprintf(out,"supeq\n"); }
#line 1867 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 277 "galo.y" /* yacc.c:1646  */
    { fprintf(out,"mul\n"); }
#line 1873 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 278 "galo.y" /* yacc.c:1646  */
    { fprintf(out,"add\n"); }
#line 1879 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 279 "galo.y" /* yacc.c:1646  */
    { fprintf(out,"pushi 0\nequal\n"); }
#line 1885 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 282 "galo.y" /* yacc.c:1646  */
    { if(dentrofun){
                                                    fprintf(out,"pushl %d\n",procuraDesig((yyvsp[0].s),vl,quantl)->posicaoStack); 
                                                  }else{
                                                    fprintf(out,"pushg %d\n",procuraDesig((yyvsp[0].s),vl,quantl)->posicaoStack); 
                                                  }
                                                }
#line 1896 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 288 "galo.y" /* yacc.c:1646  */
    { fprintf(out,"pushi %d\n", (yyvsp[0].i)); }
#line 1902 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 289 "galo.y" /* yacc.c:1646  */
    { ; }
#line 1908 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 290 "galo.y" /* yacc.c:1646  */
    { ; }
#line 1914 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 291 "galo.y" /* yacc.c:1646  */
    { fprintf(out,"pushs %s\n", (yyvsp[0].s)); }
#line 1920 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 294 "galo.y" /* yacc.c:1646  */
    { fprintf(out,"add\n"); }
#line 1926 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 295 "galo.y" /* yacc.c:1646  */
    { fprintf(out,"sub\n"); }
#line 1932 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 296 "galo.y" /* yacc.c:1646  */
    { fprintf(out,"mul\n"); }
#line 1938 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 297 "galo.y" /* yacc.c:1646  */
    { fprintf(out,"div\n"); }
#line 1944 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 298 "galo.y" /* yacc.c:1646  */
    { fprintf(out,"mod\n"); }
#line 1950 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 299 "galo.y" /* yacc.c:1646  */
    { ; }
#line 1956 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 300 "galo.y" /* yacc.c:1646  */
    { ; }
#line 1962 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1966 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 302 "galo.y" /* yacc.c:1906  */


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

