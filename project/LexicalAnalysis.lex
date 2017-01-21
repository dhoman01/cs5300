/* scanner for a toy Pascal-like language */

%{
/* need this for the call to atof() below */
#include <math.h>
int numLines = 0;
%}

DIGIT    [0-9]
ID       [a-zA-Z][a-zA-Z0-9]*
COMMENT  $.*\n


%option noyywrap

%%

\n|\r {
    ++numLines;
}

{DIGIT}+    {
            printf( "An integer: %s (%d)\n", yytext,
                    atoi( yytext ) );
            }

{DIGIT}+"."{DIGIT}*        {
            printf( "A float: %s (%g)\n", yytext,
                    atof( yytext ) );
            }

array|begin|chr|const|do|downto|else|elseif|end|for|forward|function|if|of|ord|pred|procedure|read|record|ref|repeat|return|stop|succ|then|to|type|until|var|while|write        {
            printf( "A keyword: %s\n", yytext );
            }

'([^'\\\n]|\\.)'   printf("A character literal: %s\n", yytext);
'' printf("Syntax Error: Empty character literal on line %d.\n", numLines);
' printf("Syntax Error: Non-terminating character literal on line %d.\n", numLines);
\"(\\.|[^"])*\"   printf("A string literal: %s\n", yytext);
\" printf("Syntax Error: Non-terminating string literal on line %d.\n", numLines);
{ID}        printf( "An identifier: %s\n", yytext );

"+"|"-"|"*"|"/"|"&"|"~"|"="|"<>"|"<"|"<="|">"|">="|"."|","|":"|";"|"("|")"|"["|"]"|":="|"%"   printf( "An operator: %s\n", yytext );

{COMMENT}    /* eat up one-line comments */

[ \t]+          /* eat up whitespace */

.           printf( "Unrecognized character: %s\n", yytext );

%%

int main( int argc, char **argv )
    {
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
            yyin = fopen( argv[0], "r" );
    else
            yyin = stdin;

    yylex();
    }