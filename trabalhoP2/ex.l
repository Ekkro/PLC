%{
#include <stdio.h>
#include <string.h>
%}

%option noyywrap
Abrev ER

%%

[\<>|$] 		{return(yytext[0]);}
\\[bui]<[^>]*>		{ char* mystr = strdup(yytext +3); mystr[strlen(mystr)-2]; 
			  printf("<%c>%s</%c>", yytext[1], yytext, yytext[1]); }
\\h[1-6]<[^>]*>		{ printf("<%c%c>%s</%c%c>", 
                            yytext[1],yytext[2], yytext[]+, yytext[1], yytext[2]); }
\\[uo]l<[^>]*>		{  }
\\dl<[^>]*>		{  }
.            		{ printf("%c", yytext[0]); }
%%

