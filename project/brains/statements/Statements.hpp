#ifndef STATEMENTS_HPP
#define STATEMENTS_HPP 1

#include <vector>
#include "../utils/structures.hpp"
#include "../utils/LookupTable.hpp"

namespace cpsl
{

class Statements
{
public:
    Statements() = default;
    Statements(std::vector<Register>*, LookUpTable<Info>*);
    
    int WriteStatement(std::vector<Expression>);
    int VariableDeclaration(std::vector<std::string>, std::string id);
    int ConstDeclaration(std::string, Expression);
    int Assignment(std::string, Expression);
    Expression LoadVariable(std::string);
private:
    LookUpTable<Info>* symbolTable;
    std::vector<Register>* regPool;
    int globalLocation;

    void StoreSymbol(std::string, cpslType*);
    void Write(Expression);
};

} 

#endif