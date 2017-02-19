#ifndef CPSL_LEXER_HPP
#define CPSL_LEXER_HPP 1

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "brains/parser/parser.tab.hh"
#include "brains/parser/location.hh"

namespace cpsl
{

class Scanner : public yyFlexLexer
{
public:
    Scanner(std::istream *in) : yyFlexLexer(in)
    {
        loc = new cpsl::Parser::location_type();
    };

    virtual ~Scanner()
    {
        delete loc;
    };

    using FlexLexer::yylex;

    virtual int yylex(cpsl::Parser::semantic_type* const lval,
              cpsl::Parser::location_type* location);
private:
    cpsl::Parser::semantic_type* yylval = nullptr;
    cpsl::Parser::location_type* loc = nullptr;
};

}

#endif