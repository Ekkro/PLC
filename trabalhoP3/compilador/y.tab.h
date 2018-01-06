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
extern YYSTYPE yylval;
