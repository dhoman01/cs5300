#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <string>
#include <cstddef>
#include <istream>
#include <fstream>

#include "cpsl_lexer.hpp"
#include "cpsl_parser.hpp"

#include "utils/LookupTable.hpp"
#include "expressions/Expressions.hpp"

namespace cpsl
{

class Brain
{
public:
    Brain(){};
    Brain(std::string output_file = "");
    virtual ~Brain();

    // Parse a file
    void parse(const char* filename);

    // Parse from stdin
    void parse(std::istream& iss);

    Expressions expressions;
    LookUpTable<Info> symbolTable;
    int globalLocation;
    std::vector<Register> regPool;

private:
    void parse_helper(std::istream &stream);

    cpsl::cpsl_Parser* parser = nullptr;
    cpsl::cpsl_Lexer* lexer = nullptr;

    std::string output_file;

    void InitRegPool();
    void InitMIPS();
    void InitPredefinedSymbols();
    void Init();
};

}

#endif