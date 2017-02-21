#ifndef BRAIN_HPP
#define BRAIN_HPP 1

#include <string>
#include <cstddef>
#include <istream>
#include <fstream>
#include <memory>

#include "parser/scanner.hpp"
#include "parser/parser.tab.hh"

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

    void parse(const char* const filename);
    void parse(std::istream& iss);

    Expression addString(std::string);

    Expressions expressions;
    Statements statements;

private:
    void parse_helper(std::istream &stream);
    void InitRegPool();
    void InitMIPS();
    void InitPredefinedSymbols();
    void Init();

    std::vector<std::string> stringConst;

    std::shared_ptr<LookUpTable<Info>> symbolTable;
    std::shared_ptr<std::vector<Register>> regPool;
    std::shared_ptr<Parser> parser = nullptr;
    std::shared_ptr<Scanner> scanner = nullptr;

    std::string output_file;

};

}

#endif