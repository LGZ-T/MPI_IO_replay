%{
typedef char* string;
#define YYSTYPE	 string
%}
%token ID
%%
file : record file
| record
;
record : ID {
printf("Identifier:%s\t", $1); }
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
