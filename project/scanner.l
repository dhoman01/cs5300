/* Lexer for CPSL */

%{
/* need this for the call to atof() below */
#include <math.h>
int numLines = 0;
%}

/* Keywords (Section 2.2) (NOTE: (?i:...) tells flex to be case insenstive) */
KEYWORD              (?i:array|begin|chr|const|do|downto|else|elseif|end|for|forward|function|if|of|ord|pred|procedure|read|record|ref|repeat|return|stop|succ|then|to|type|until|var|while|write)

/* Identifiers (Section 2.3) */
ID                   [a-zA-Z][a-zA-Z0-9_]*

/* Operators and Delimiters (Section 2.4) */
OPERATOR             "+"|"-"|"*"|"/"|"&"|"|"|"~"|"="|"<>"|"<"|"<="|">"|">="|"."|","|":"|";"|"("|")"|"["|"]"|":="|"%"

/* Constants (Section 2.5) */
/* Integer Constants (Section 2.5.1) */
OCTAL                0[0-9]+
HEX                  0x[0-9a-fA-F]+
DIGIT                [0-9]+

/* Character Constants (Section 2.5.2) */
CHR                  '([^'\\\n]|\\.)'
EMPTY_CHR            ''
NON_TERM_CHR         '

/* String Constants (Section 2.5.3) */
STRING               \"(\\.|[^"\n])*\"
NON_TERM_STRING      \"([^\\\"]|\\.)*\n

/* Comments (Section 2.5.5) */
COMMENT              $.*\n




%option noyywrap

%%

{KEYWORD}           {
                        printf( "A keyword: %s\n", yytext );
                    }

{ID}                {
                        printf( "An identifier: %s\n", yytext );
                    }

{OPERATOR}          {
                        printf( "An operator: %s\n", yytext );
                    }

{OCTAL}             {
                        printf( "An octal number: %s\n", yytext );
                    }

{HEX}               {
                        printf( "A hexadecimal number: %s\n", yytext );
                    }

{DIGIT}             {
                        printf( "An integer: %s (%d)\n", yytext,
                        atoi( yytext ) );
                    }

{CHR}               {
                        printf( "A character literal: %s\n", yytext );
                    }

{EMPTY_CHR}         {
                        printf( "Lexical Error(line %d): Empty character literal.\n", numLines + 1 );
                    }

{NON_TERM_CHR}      {
                        printf( "Lexical Error(line %d): Non-terminating character literal.\n", numLines + 1 );
                    }

{STRING}            {
                        printf( "A string literal: %s\n", yytext );
                    }

{NON_TERM_STRING}   {
                        printf( "Lexical Error (line %d): Non-terminating string literal.\n", numLines + 1 );
                    }


{COMMENT}           { 
                        ++numLines;  /* remove comments */
                    }

\n                  {
                        ++numLines;  /* increment line count */
                    }

[ \t]+              /* remove whitespace */

.                   {
                        /* All other lexeme are invalid */
                        printf( "Lexical Error (line %d): Invalid token %s\n", numLines, yytext );
                    }

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