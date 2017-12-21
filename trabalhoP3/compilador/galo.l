%{
#include "y.tab.h"
%}

%%
#.*$                        { return(COM); }
\"[^"]*\"                   { yyval.s return(STR); }
[ ]+e[ ]+                   { return(E); }
[ ]+ou[ ]+                  { return(OU); }
==                          { return(EQ); }
\<=                         { return(LEQ); }
>=                          { return(GEQ); }
!=                          { return(NEQ); }
[=;{}(),<>!\+\-\*\/%\[\]]   { return(yytext[0]); }
se|SE                       { return(SE); }
senao|SENAO                 { return(SENAO); }
caso|CASO                   { return(CASO); }
enq|ENQ                     { return(ENQ); }
int\ *\*?|void\ *\*?        { return(TIPO); }
[0-9]+                      { return(NUM); }
[a-zA-Z][a-zA-Z0-9]*        { return(VAR); }
[ \t\n]                     { ; }
.                           { printf("Caracter invalido %c\n", yytext[0]); }
%%

int yywrap(){
  return(1);
}
