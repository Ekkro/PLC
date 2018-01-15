%{
#include "y.tab.h"
%}

%%
#.*$                        { return(COM); }
\"[^"]*\"                   { yylval.s = strdup(yytext); return(STR); }
[ ]+e[ ]+                   { return(E); }
[ ]+ou[ ]+                  { return(OU); }
[ ]+sin[ ]+                 { return(SIN); }
[ ]+cos[ ]+                 { return(COS); }
==                          { return(EQ); }
\<=                         { return(LEQ); }
>=                          { return(GEQ); }
!=                          { return(NEQ); }
[=;{}(),<>!\+\-\*\/%\[\]]   { return(yytext[0]); }
se|SE                       { return(SE); }
senao|SENAO                 { return(SENAO); }
caso|CASO                   { return(CASO); }
enq|ENQ                     { return(ENQ); }
return                      { return(RETURN); }
[0-9]+\.[0-9]+              { yylval.f = atof(yytext); return(FLOAT); }
int|string|float            { yylval.s = strdup(removeEspacos(yytext)); return(TIPO); }
[0-9]+                      { yylval.i = atoi(yytext); return(NUM); }
[a-zA-Z][a-zA-Z0-9]*        { yylval.s = strdup(yytext); return(VAR); }
[ \t\n]                     { ; }
.                           { printf("Caracter invalido %c\n", yytext[0]); }
%%

int yywrap(){
  return(1);
}
