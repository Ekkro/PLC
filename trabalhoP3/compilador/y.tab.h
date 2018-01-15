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
extern YYSTYPE yylval;
