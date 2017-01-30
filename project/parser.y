%{
#include <stdlib.h>
#include <stdio.h>
int yyerror(char *s);
int yylex(void);
%}

%union {
    char* str;
    char chr;
    int integer;
}

%token <integer> INTEGER
%token <str> OCTAL
%token <str> HEX
%token <str> STRING
%token <chr> CHAR
%token <str> KEYWORD
%token <str> IDENTIFIER
%token <str> OPERATOR

%start program

%%
program: statement';' { printf("Program syntax\n"); }
    ;

block: 
    | KEYWORD statements KEYWORD
    ;

statements:
    | statements statement ';'
    | statements block';'
    ;

statement: assignment { printf("Assignment statement\n"); }
    | block           { printf("Block statement\n"); }
    ;

assignment: IDENTIFIER OPERATOR expression { printf("Id = expression\n"); }
    ;

expression: IDENTIFIER
    | INTEGER
    | OCTAL
    | HEX
    | STRING
    | CHAR
    | expression OPERATOR expression
    ;

%%

int yyerror(char* s){
    extern int yylineno;
    extern int yycolno;
    extern char* yytext;
    printf("ERROR: Incorrect value \"%s\" on line %d column %d\n", yytext, yylineno, yycolno);
    exit(1);
}