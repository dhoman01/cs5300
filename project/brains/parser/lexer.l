%{
#include <cstring>
#include <cstdlib>
#include <string>

#include "scanner.hpp"
#undef  YY_DECL
#define YY_DECL int cpsl::Scanner::yylex(cpsl::Parser::semantic_type* const lval, cpsl::Parser::location_type* loc)

using token = cpsl::Parser::token;

#define YY_NO_UNISTD_H

#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}

%option debug
%option nodefault
%option yyclass="cpsl::Scanner"
%option noyywrap
%option c++

%%
%{
    yylval = lval;
%}

 /* remove whitespace */
[ \t]+                  {}

 /* Keywords (Section 2.2) */
array|ARRAY             {
                            return token::ARRAY_KEY;
                        }

begin|BEGIN             {
                            return token::BEGIN_KEY;
                        }
                    
chr|CHR                 {
                            return token::CHR_KEY;
                        }
                    
const|CONST             {
                            return token::CONST_KEY;
                        }
                    
do|DO                   {
                            return token::DO_KEY;
                        }
                    
downto|DOWNTO           {
                            return token::DOWN_TO_KEY;
                        }
                    
else|ELSE               {
                            return token::ELSE_KEY;
                        }
  
elseif|ELSEIF           {
                            return token::ELSE_IF_KEY;
                        }
  
end|END                 {
                            return token::END_KEY;
                        }
  
for|FOR                 {
                            return token::FOR_KEY;
                        }
  
forward|FORWARD         {
                            return token::FORWARD_KEY;
                        }
  
function|FUNCTION       {
                            return token::FUNCTION_KEY;
                        }
  
if|IF                   {
                            return token::IF_KEY;
                        }
  
of|OF                   {
                            return token::OF_KEY;
                        }
  
ord|ORD                 {
                            return token::ORD_KEY;
                        }
  
pred|PRED               {
                            return token::PRED_KEY;
                        }
  
procedure|PROCEDURE     {
                            return token::PROCEDURE_KEY;
                        }

read|READ               {
                            return token::READ_KEY;
                        }
  
record|RECORD           {
                            return token::RECORD_KEY;
                        }
  
ref|REF                 {
                            return token::REF_KEY;
                        }
  
repeat|REPEAT           {
                            return token::REPEAT_KEY;
                        }
  
return|RETURN           {
                            return token::RETURN_KEY;
                        }
  
stop|STOP               {
                            return token::STOP_KEY;
                        }
  
succ|SUCC               {
                            return token::SUCC_KEY;
                        }
  
then|THEN               {
                            return token::THEN_KEY;
                        }
  
to|TO                   {
                            return token::TO_KEY;
                        }
  
type|TYPE               {
                            return token::TYPE_KEY;
                        }
  
until|UNTIL             {
                            return token::UNTIL_KEY;
                        }
  
var|VAR                 {
                            return token::VAR_KEY;
                        }

while|WHILE             {
                            return token::WHILE_KEY;
                        }
  
write|WRITE             {
                            return token::WRITE_KEY;
                        }

 /* Identifiers (Section 2.3) */  
[a-zA-Z][a-zA-Z0-9_]*   {
                            yylval->build<std::string>(yytext);
                            return token::IDENTIFIER;
                        }

 /* Operators and Delimiters (Section 2.4) */
"&"                     {
                            return token::AND_OP;
                        }

":="                    {
                            return token::ASSIGN_OP;
                        }
     
"/"                     {
                            return token::DIV_OP;
                        } 
 
"="                     {
                            return token::EQ_OP;
                        }
 
">"                     {
                            return token::GT_OP;
                        }
 
">="                    {
                            return token::GT_EQ_OP;
                        }
 
"<"                     {
                            return token::LT_OP;
                        }
 
"<="                    {
                            return token::LT_EQ_OP;
                        }
 
"-"                     {
                            return token::MINUS_OP;
                        }
 
"%"                     {
                            return token::MOD_OP;
                        }
 
"*"                     {
                            return token::MULT_OP;
                        }
 
"<>"                    {
                            return token::NOT_EQ_OP;
                        }
 
"~"                     {
                            return token::NOT_OP;
                        }
 
"|"                     {
                            return token::OR_OP;
                        }
 
"+"                     {
                            return token::PLUS_OP;
                        }
 
"."                     {
                            return token::DOT;
                        }
 
","                     {
                            return token::COMMA;
                        }
 
":"                     {
                            return token::COL;
                        }
 
";"                     {
                            return token::SEMI_COL;
                        }
 
"("                     {
                            return token::OPEN_PAR;
                        }
 
")"                     {
                            return token::CLOSE_PAR;
                        }
 
"["                     {
                            return token::OPEN_SQ;
                        }
 
"]"                     {
                            return token::CLOSE_SQ;
                        }
 
 
 /* Constants (Section 2.5) */
 /* Integer Constants (Section 2.5.1) */
0[0-7]+                 {
                            yylval->build<std::string>(yytext);
                            return token::INT_CONST;
                        }

0x[0-9a-fA-F]+          {
                            yylval->build<std::string>(yytext);
                            return token::INT_CONST;
                        }

[0-9]+                  {
                            yylval->build<std::string>(yytext);
                            return token::INT_CONST;
                        }

 /* Character Constants (Section 2.5.2) */
'\\n'                   {   
                            yylval->build<char>('\n');
                            return token::CHR_CONST;
                        }

'\\t'                   {
                            yylval->build<char>('\n');
                            return token::CHR_CONST;
                        }

'\\r'                   {
                            yylval->build<char>('\r');
                            return token::CHR_CONST;
                        }

'\\?.'                 {
                            yylval->build<char>(yytext[1]);
                            return token::CHR_CONST;
                        }

 /* String Constants (Section 2.5.3) */
\"(\\.|[^"\n])*\"       {
                            yylval->build<std::string>(yytext);
                            return token::STRING_CONST;
                        }

 /* Comments (Section 2.5.5) */
$.*\n                   { 
                            loc->lines();
                        }

 /* Increment line count */
\n                      {
                            loc->lines();
                        }

 /* All other lexeme are invalid (Section 2.1) */
.                       {
                            std::cerr << "Lexical Error (" << loc << "): Invalid token " << yytext << std::endl;
                        }

%%
