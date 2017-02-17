/* Lexer for CPSL */
%{
#include <stdlib.h>

#include "parser.hpp"
#include "globals.h"
%}

%option noyywrap
%option yylineno

%%

 /* remove whitespace */
[ \t]+                  {
                            yycolno += yyleng;
                        }

 /* Keywords (Section 2.2) (NOTE: (?i:...) tells flex to be case insenstive for the following rule) */
array|ARRAY             {
                            yycolno += yyleng;
                            return ARRAY_KEY;
                        }

begin|BEGIN             {
                            yycolno += yyleng;
                            return BEGIN_KEY;
                        }
                    
chr|CHR                 {
                            yycolno += yyleng;
                            return CHR_KEY;
                        }
                    
const|CONST             {
                            yycolno += yyleng;
                            return CONST_KEY;
                        }
                    
do|DO                   {
                            yycolno += yyleng;
                            return DO_KEY;
                        }
                    
downto|DOWNTO           {
                            yycolno += yyleng;
                            return DOWN_TO_KEY;
                        }
                    
else|ELSE               {
                            yycolno += yyleng;
                            return ELSE_KEY;
                        }
  
elseif|ELSEIF           {
                            yycolno += yyleng;
                            return ELSE_IF_KEY;
                        }
  
end|END                 {
                            yycolno += yyleng;
                            return END_KEY;
                        }
  
for|FOR                 {
                            yycolno += yyleng;
                            return FOR_KEY;
                        }
  
forward|FORWARD         {
                            yycolno += yyleng;
                            return FORWARD_KEY;
                        }
  
function|FUNCTION       {
                            yycolno += yyleng;
                            return FUNCTION_KEY;
                        }
  
if|IF                   {
                            yycolno += yyleng;
                            return IF_KEY;
                        }
  
of|OF                   {
                            yycolno += yyleng;
                            return OF_KEY;
                        }
  
ord|ORD                 {
                            yycolno += yyleng;
                            return ORD_KEY;
                        }
  
pred|PRED               {
                            yycolno += yyleng;
                            return PRED_KEY;
                        }
  
procedure|PROCEDURE     {
                            yycolno += yyleng;
                            yylval.str = yytext;
                            return PROCEDURE_KEY;
                        }

read|READ               {
                            yycolno += yyleng;
                            return READ_KEY;
                        }
  
record|RECORD           {
                            yycolno += yyleng;
                            return RECORD_KEY;
                        }
  
ref|REF                 {
                            yycolno += yyleng;
                            return REF_KEY;
                        }
  
repeat|REPEAT           {
                            yycolno += yyleng;
                            return REPEAT_KEY;
                        }
  
return|RETURN           {
                            yycolno += yyleng;
                            return RETURN_KEY;
                        }
  
stop|STOP               {
                            yycolno += yyleng;
                            return STOP_KEY;
                        }
  
succ|SUCC               {
                            yycolno += yyleng;
                            return SUCC_KEY;
                        }
  
then|THEN               {
                            yycolno += yyleng;
                            return THEN_KEY;
                        }
  
to|TO                   {
                            yycolno += yyleng;
                            return TO_KEY;
                        }
  
type|TYPE               {
                            yycolno += yyleng;
                            return TYPE_KEY;
                        }
  
until|UNTIL             {
                            yycolno += yyleng;
                            return UNTIL_KEY;
                        }
  
var|VAR                 {
                            yycolno += yyleng;
                            return VAR_KEY;
                        }

while|WHILE             {
                            yycolno += yyleng;
                            return WHILE_KEY;
                        }
  
write|WRITE             {
                            yycolno += yyleng;
                            return WRITE_KEY;
                        }

 /* Identifiers (Section 2.3) */  
[a-zA-Z][a-zA-Z0-9_]*   {
                            yycolno += yyleng;
                            yylval.str = strdup(yytext);
                            return IDENTIFIER;
                        }

 /* Operators and Delimiters (Section 2.4) */
"&"                     {
                            yycolno += yyleng;
                            return AND_OP;
                        }

":="                    {
                            yycolno += yyleng;
                            return ASSIGN_OP;
                        }
     
"/"                     {
                            yycolno += yyleng;
                            return DIV_OP;
                        } 
 
"="                     {
                            yycolno += yyleng;
                            return EQ_OP;
                        }
 
">"                     {
                            yycolno += yyleng;
                            return GT_OP;
                        }
 
">="                    {
                            yycolno += yyleng;
                            return GT_EQ_OP;
                        }
 
"<"                     {
                            yycolno += yyleng;
                            return LT_OP;
                        }
 
"<="                    {
                            yycolno += yyleng;
                            return LT_EQ_OP;
                        }
 
"-"                     {
                            yycolno += yyleng;
                            return MINUS_OP;
                        }
 
"%"                     {
                            yycolno += yyleng;
                            return MOD_OP;
                        }
 
"*"                     {
                            yycolno += yyleng;
                            return MULT_OP;
                        }
 
"<>"                    {
                            yycolno += yyleng;
                            return NOT_EQ_OP;
                        }
 
"~"                     {
                            yycolno += yyleng;
                            return NOT_OP;
                        }
 
"|"                     {
                            yycolno += yyleng;
                            return OR_OP;
                        }
 
"+"                     {
                            yycolno += yyleng;
                            return PLUS_OP;
                        }
 
"."                     {
                            yycolno += yyleng;
                            return DOT;
                        }
 
","                     {
                            yycolno += yyleng;
                            return COMMA;
                        }
 
":"                     {
                            yycolno += yyleng;
                            return COL;
                        }
 
";"                     {
                            yycolno += yyleng;
                            return SEMI_COL;
                        }
 
"("                     {
                            yycolno += yyleng;
                            return OPEN_PAR;
                        }
 
")"                     {
                            yycolno += yyleng;
                            return CLOSE_PAR;
                        }
 
"["                     {
                            yycolno += yyleng;
                            return OPEN_SQ;
                        }
 
"]"                     {
                            yycolno += yyleng;
                            return CLOSE_SQ;
                        }
 
 
 /* Constants (Section 2.5) */
 /* Integer Constants (Section 2.5.1) */
0[0-7]+                 {
                            yycolno += yyleng;
                            yylval.integer = strtol(yytext, NULL, 0);
                            return INT_CONST;
                        }

0x[0-9a-fA-F]+          {
                            yycolno += yyleng;
                            yylval.integer = strtol(yytext, NULL, 0);
                            return INT_CONST;
                        }

[0-9]+                  {
                            yycolno += yyleng;
                            yylval.integer = strtol(yytext, NULL, 0);
                            return INT_CONST;
                        }

 /* Character Constants (Section 2.5.2) */
'([^']|\\.)'            {
                            yycolno += yyleng;
                            yylval.chr = yytext[1];
                            return CHR_CONST;
                        }

 /* String Constants (Section 2.5.3) */
\"(\\.|[^"\n])*\"       {
                            yycolno += yyleng;
                            yylval.str = yytext;
                            return STRING_CONST;
                        }

 /* Comments (Section 2.5.5) */
$.*\n                   { 
                            yycolno = 0;
                        }

 /* Increment line count */
\n                      {
                            yycolno = 0;
                        }

 /* All other lexeme are invalid (Section 2.1) */
.                       {
                            fprintf( stderr, "Lexical Error (%d:%d): Invalid token %s\n", yylineno, yycolno + 1, yytext );
                            yycolno += yyleng;
                        }

%%
