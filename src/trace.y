%{
#include <stdio.h>
%}
%token ID
%%
file : record file
| record
;
record : ID {
printf("Identifier:%s\n", $1); }
;
%%
int main()
{
	yyparse();
	return 0;
}
int yyerror(char *msg)
{
	printf("Error encountered: %s \n", msg);
}
