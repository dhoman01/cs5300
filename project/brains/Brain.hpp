#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <string>
#include <cstddef>
#include <istream>
#include <fstream>

#include "brains/cpsl_parser.hpp"
#include "brains/cpsl_lexer.hpp"

#include "brains/utils/LookupTable.hpp"
#include "brains/expressions/Expressions.hpp"
#include "brains/structures.hpp"

namespace cpsl
{

class Brain{
public:
    Brain() = default;
    Brain(std::string output_file = "");
    virtual ~Brain();

    // Parse a file
    void parse( const char* filename);

    // Parse from stdin
    void parse( std::istream& iss);

    // Track position
    void add_line();
    void add_chars(int);

    Expressions expressions;
    LookUpTable<Info> symbolTable;
    int globalLocation;
    std::vector<Register> regPool;

private:
    void parse_helper( std::istream &stream);
    std::size_t lines = 0;
    std::size_t chars = 0;

    cpsl::cpsl_Parser* parser = nullptr;
    cpsl::cpsl_Lexer* lexer = nullptr;

    std::string output_file;

    void InitRegPool();
    void InitMIPS();
    void InitPredefinedSymbols();
    void Init();

};

};

#endif