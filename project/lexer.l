/* Lexer for CPSL */
%{
#include <stdlib.h>

#include "parser.tab.h"

int line = 0, yycolno = 0;
%}

%option noyywrap
%option yylineno

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
                        yycolno += yyleng;
                    }

{KEYWORD}           {
                        yycolno += yyleng;
                        yylval.str = yytext;
                        return KEYWORD;
                    }

{ID}                {
                        yycolno += yyleng;
                        yylval.str = yytext;
                        return IDENTIFIER;
                    }

{OPERATOR}          {
                        yycolno += yyleng;
                        yylval.str = yytext;
                        return OPERATOR;
                    }

{OCTAL}             {
                        yycolno += yyleng;
                        yylval.str = yytext;
                        return OCTAL;
                    }

{HEX}               {
                        yycolno += yyleng;
                        yylval.str = yytext;
                        return HEX;
                    }

{DIGIT}             {
                        yycolno += yyleng;
                        yylval.integer = atoi(yytext);
                        return INTEGER;
                    }

{CHR}               {
                        yycolno += yyleng;
                        yylval.chr = yytext[0];
                        return CHAR;
                    }

{EMPTY_CHR}         {
                        fprintf( stderr, "Lexical Error(%d:%d): Empty character constant.\n", line + 1, yycolno + 1 );
                        yycolno += yyleng;
                    }

{NON_TERM_CHR}      {
                        fprintf( stderr, "Lexical Error(%d:%d): Non-terminating character constant. Maybe an unescaped character?\n", line + 1, yycolno + 1 );
                        yycolno += yyleng;
                    }

{STRING}            {
                        yycolno += yyleng;
                        yylval.str = yytext;
                        return STRING;
                    }

{NON_TERM_STRING}   {
                        fprintf( stderr, "Lexical Error (%d:%d): Non-terminating string constant. Maybe an unescaped double quote?\n", line + 1, yycolno + 1 );
                        yycolno += yyleng;
                    }


{COMMENT}           { 
                        ++line;  /* remove comments */
                        yycolno = 0;
                    }

\n                  {
                        ++line;  /* increment line count */
                        yycolno = 0;
                    }

.                   {
                        /* All other lexeme are invalid (Section 2.1) */
                        fprintf( stderr, "Lexical Error (%d:%d): Invalid token %s\n", line, yycolno + 1, yytext );
                        ++yycolno;
                    }

%%
