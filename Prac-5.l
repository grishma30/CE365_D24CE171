%{
#include <stdio.h>
#include <string.h>

int symcount = 0;
char symtab[100][30];
int errcount = 0;
char errors[100][100];

int is_present(char *s) {
    for(int i = 0; i < symcount; i++)
        if(strcmp(symtab[i], s) == 0)
            return 1;
    return 0;
}

void add_symbol(char *s) {
    if(!is_present(s)) {
        strcpy(symtab[symcount++], s);
    }
}

void add_error(int line, char *lexeme) {
    sprintf(errors[errcount++], "Line %d : %s invalid lexeme", line, lexeme);
}
%}

%option yylineno

/* Regular Definitions */
KEYWORD     int|char|float|double|void|return|if|else|for|while|do|break|continue|long|short|struct
ID          [a-zA-Z_][a-zA-Z0-9_]*
NUM         [0-9]+
CHAR        '([^'\n]|\\.)'
STRING      \"([^\"\n])*\" 
OPERATOR    \+|\-|\*|\/|=|==|<=|>=|!=|<|>
PUNCT       [\{\}\(\)\[\];,]
COMMENT     \/\/.*|\/\*([^*]|\*+[^*/])*\*+\/
INVALID     [0-9]+[a-zA-Z_][a-zA-Z0-9_]*

%%

{INVALID}      { add_error(yylineno, yytext); }
{KEYWORD}      { printf("Keyword: %s\n", yytext); }
{ID}           { printf("Identifier: %s\n", yytext); add_symbol(yytext); }
{NUM}          { printf("Constant: %s\n", yytext); }
{CHAR}         { printf("Constant: %s\n", yytext); }
{STRING}       { printf("String: %s\n", yytext); }
{OPERATOR}     { printf("Operator: %s\n", yytext); }
{PUNCT}        { printf("Punctuation: %s\n", yytext); }
{COMMENT}      { /* Ignore comments */ }
[ \t\n]+       { /* Ignore whitespace */ }

.              { add_error(yylineno, yytext); }

%%

int main(int argc, char *argv[]) {
    if(argc > 1) {
        FILE *fp = fopen(argv[1], "r");
        if(!fp) {
            printf("Error: Cannot open file %s\n", argv[1]);
            return 1;
        }
        yyin = fp;
    }
    
    printf("TOKENS\n");
    yylex();

    printf("\nLEXICAL ERRORS\n");
    if(errcount == 0) {
        printf("No errors\n");
    } else {
        for(int i = 0; i < errcount; i++)
            printf("%s\n", errors[i]);
    }

    printf("\nSYMBOL TABLE ENTRIES\n");
    for(int i = 0; i < symcount; i++)
        printf("%d) %s\n", i + 1, symtab[i]);

    if(argc > 1)
        fclose(yyin);

    return 0;
}

int yywrap() {
    return 1;
}