#ifndef STATEMENTS_HPP
#define STATEMENTS_HPP 1

#include <memory>
#include <vector>
#include "../utils/structures.hpp"
#include "../utils/LookupTable.hpp"

namespace cpsl
{

class Statements  : public std::enable_shared_from_this<Statements>
{
public:
    Statements() = default;
    Statements(std::shared_ptr<std::vector<Register>>, std::shared_ptr<LookUpTable<Info>>);
    
    int WriteStatement(std::vector<Expression>);
    int VariableDeclaration(std::vector<std::string>, std::string id);
    int ConstDeclaration(std::string, Expression);
    int Assignment(std::string, Expression);
    Expression LoadVariable(std::string);
private:
    std::shared_ptr<LookUpTable<Info>> symbolTable;
    std::shared_ptr<std::vector<Register>> regPool;
    int globalLocation;

    void StoreSymbol(std::string, std::shared_ptr<cpslType>);
    void Write(Expression);
};

} 

#endif