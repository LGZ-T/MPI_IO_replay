%{
#define YYSTYPE char*
#include "y.tab.h"

#include <stdio.h>
#include <string.h>

extern char * yylval;
%}
char 	[A-Za-z]
digit 	[0-9]
underscore 	_
c_identifier 	({char}|{underscore})({char}|{underscore}|{digit})*
/* the first step is to read every identifier, then print */
%%
{c_identifier} {yylval = strdup(yytext);
return ID; }
%%
int yywrap()
{
	return 1;
}
