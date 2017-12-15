%{
#include "y.tab.h"
%}

%%
[=;{}(),]               { return(yytext[0]); }
se|SE                   { return(SE); }
senao|SENAO             { return(SENAO); }
verdade|VERDADE         { return(VERDADE); }
falso|FALSO             { return(FALSO); }
caso|CASO               { return(CASO); }
int|letra               { return(TIPO); }
[0-9]+                  { return(NUM); }
[a-zA-Z][a-zA-Z0-9]*    { return(VAR); }
[ \t\n]                 { ; }
.                       { printf("Caracter invalido %c\n", yytext[0]); }
%%

int yywrap(){
  return(1);
}
