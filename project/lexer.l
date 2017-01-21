/* Lexer for CPSL */
%{
#include <stdlib.h>
%}

/* Remove for future assignments */
%option noyywrap
                     int line = 0, col = 0;

/* Keywords (Section 2.2) (NOTE: (?i:...) tells flex to be case insenstive for the following rule) */
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
CHR                  '([^']|\\.)'
EMPTY_CHR            ''
NON_TERM_CHR         '

/* String Constants (Section 2.5.3) */
STRING               \"(\\.|[^"\n])*\"
NON_TERM_STRING      \"([^\\\"]|\\.)*\n

/* Comments (Section 2.5.5) */
COMMENT              $.*\n

%%

[ \t]+              {
                        /* remove whitespace */
                        col += yyleng;
                    }

{KEYWORD}           {
                        printf( "A keyword: %s\n", yytext );
                        col += yyleng;
                    }

{ID}                {
                        printf( "An identifier: %s\n", yytext );
                        col += yyleng;
                    }

{OPERATOR}          {
                        printf( "An operator: %s\n", yytext );
                        col += yyleng;
                    }

{OCTAL}             {
                        printf( "An integer constant (octal): %s\n", yytext );
                        col += yyleng;
                    }

{HEX}               {
                        printf( "An integer constant (hexadecimal): %s\n", yytext );
                        col += yyleng;
                    }

{DIGIT}             {
                        printf( "An integer constant (decimal): %s\n", yytext );
                        col += yyleng;
                    }

{CHR}               {
                        printf( "A character constant: %s\n", yytext );
                        col += yyleng;
                    }

{EMPTY_CHR}         {
                        fprintf( stderr, "Lexical Error(%d:%d): Empty character constant.\n", line + 1, col + 1 );
                        col += yyleng;
                    }

{NON_TERM_CHR}      {
                        fprintf( stderr, "Lexical Error(%d:%d): Non-terminating character constant. Maybe an unescaped character?\n", line + 1, col + 1 );
                        col += yyleng;
                    }

{STRING}            {
                        printf( "A string constant: %s\n", yytext );
                        col += yyleng;
                    }

{NON_TERM_STRING}   {
                        fprintf( stderr, "Lexical Error (%d:%d): Non-terminating string constant. Maybe an unescaped double quote?\n", line + 1, col + 1 );
                        col += yyleng;
                    }


{COMMENT}           { 
                        ++line;  /* remove comments */
                        col = 0;
                    }

\n                  {
                        ++line;  /* increment line count */
                        col = 0;
                    }

.                   {
                        /* All other lexeme are invalid (Section 2.1) */
                        fprintf( stderr, "Lexical Error (%d:%d): Invalid token %s\n", line, col + 1, yytext );
                        ++col;
                    }

%%
