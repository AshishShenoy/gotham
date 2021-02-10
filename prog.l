%{
#include <string.h>
%}

alpha [a-zA-Z]
digit [0-9]
exp [Ee][+|-]?{digit}+
string {alpha}?\"(\\.|[^\\"])*\"
%%

{alpha}+ printf("%s\t%d\n", yytext, yyleng);
"//".* printf("Comment: %s\n", yytext);

%%

int main() {
	yyin = fopen("test.go", "r");
	yyout = fopen("output.txt", "w");
	fprintf(yyout, "\tLexeme\t\t\tToken\t\t\tValue\n");
	yylex();
	fclose(yyout);
	fclose(yyin);
	return 0;
}
