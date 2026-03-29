%{
#include <stdio.h>
%}

%%
[cC][hH][aA][rR][uU][sS][aA][tT]   { printf("university"); }
\n                                { return 0; }
.                                 { printf("%s", yytext); }
%%

int main()
{
    printf("Enter the input text:\n");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}
