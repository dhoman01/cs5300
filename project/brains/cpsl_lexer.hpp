#ifdef CPSL_LEXER_HPP
#define CPSL_LEXER_HPP

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "brains/structures.hpp"
#include "brains/cpsl_parser.hpp"
#include "brains/location.hh"

namespace cpsl
{

class cpsl_Lexer : public yyFlexLexer
{
public:
    cpsl_Lexer(std::istream *in) : yyFlexLexer(in)
    {
        loc = new cpsl::cpsl_Parser::location_type();
    };

    virtual ~cpsl_Lexer()
    {
        delete(loc);
    };

    using FlexLexer::yylex;

    virtual int yylex(const cpsl::cpsl_Parser::semantic_type* lval,
              cpsl::cpsl_Parser::location_type* location);
private:
    cpsl::cpsl_Parser::semantic_type* yylval = nullptr;
    cpsl::cpsl_Parser::location_type* loc = nullptr;
};

}

#endif