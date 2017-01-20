%{
#include <iostream>
%}

DIGIT    [0-9]
ID       [a-z][a-z0-9]*

%option noyywrap

%%

BEGIN|begin { std::cout << "BEGIN keyword found" << std::endl; }

. { std::cerr << "Lexical error found" << std::endl; }

%%

int main()
{
    yylex();
}
