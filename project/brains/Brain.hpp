#ifndef BRAIN_HPP
#define BRAIN_HPP 1

#include <cstddef>
#include <fstream>
#include <istream>
#include <memory>
#include <string>

#include "parser/parser.tab.hh"
#include "parser/scanner.hpp"

#include "expressions/Expressions.hpp"
#include "statements/Statements.hpp"
#include "utils/LookupTable.hpp"
#include "utils/RegPool.hpp"

namespace cpsl
{

class Brain
{
public:
    Brain();
    virtual ~Brain() = default;

    void Finalize();

    void Parse(const char* const filename);
    void Parse(std::istream& iss);

    void InitMain();

    Expression AddString(std::string);

    Expressions expressions;
    Statements statements;

private:
    void ParseHelper(std::istream &stream);
    void Init();
    void InitMIPS();
    void InitPredefinedSymbols();

    std::vector<std::string> stringConst;

    std::shared_ptr<LookUpTable<Info>> symbolTable;
    std::shared_ptr<RegPool> regPool;

    std::shared_ptr<Parser> parser = nullptr;
    std::shared_ptr<Scanner> scanner = nullptr;

};

}

#endif