#ifndef CPSL_LEXER_HPP
#define CPSL_LEXER_HPP 1

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "parser.tab.hh"
#include "location.hh"

namespace cpsl
{

class Scanner : public yyFlexLexer
{
public:
    Scanner(std::istream *in) : yyFlexLexer(in)
    {
        loc = new Parser::location_type();
    };

    virtual ~Scanner()
    {
        delete loc;
    };

    using FlexLexer::yylex;

    virtual int yylex(Parser::semantic_type* const lval,
              Parser::location_type* location);
    Parser::location_type* GetLocation() { return loc; }
private:
    Parser::semantic_type* yylval = nullptr;
    Parser::location_type* loc = nullptr;
};

}

#endif