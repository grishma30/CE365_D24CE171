%{
#include <stdio.h>
%}

%%
[0-9]+      { printf("%s\n", yytext); }
\n          { return 0; }
.           { /* ignore other characters */ }
%%

int main()
{
    printf("Enter the string:\n");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}
