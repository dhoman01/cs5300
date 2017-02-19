#ifndef BRAIN_HPP
#define BRAIN_HPP 1

#include <string>
#include <cstddef>
#include <istream>
#include <fstream>

#include "scanner.hpp"
#include "parser.tab.hh"

#include "utils/LookupTable.hpp"
#include "expressions/Expressions.hpp"
#include "statements/Statements.hpp"

namespace cpsl
{

class Brain
{
public:
    Brain(std::string output_file = "");
    virtual ~Brain();

    // Parse a file
    void parse(const char* const filename);

    // Parse from stdin
    void parse(std::istream& iss);

    Expressions expressions;
    Statements statements;
    LookUpTable<Info> symbolTable;
    std::vector<Register> regPool;

private:
    void parse_helper(std::istream &stream);

    cpsl::Parser* parser = nullptr;
    cpsl::Scanner* scanner = nullptr;

    std::string output_file;

    void InitRegPool();
    void InitMIPS();
    void InitPredefinedSymbols();
    void Init();
};

}

#endif