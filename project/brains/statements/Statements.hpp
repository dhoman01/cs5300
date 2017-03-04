#ifndef STATEMENTS_HPP
#define STATEMENTS_HPP 1

#include <memory>
#include <vector>

#include "../utils/LookupTable.hpp"
#include "../utils/structures.hpp"

namespace cpsl
{

class Statements
{
public:
    Statements() = default;
    Statements(std::shared_ptr<std::vector<Register>>, std::shared_ptr<LookUpTable<Info>>);
    
    int WhileBegin();
    void WhileHeader(int uid, Expression expr);
    void WhileEnd(int uid);
    void Assignment(std::string, Expression);
    void ConstDeclaration(std::string, Expression);
    Expression LoadVariable(std::string);
    void ReadStatement(std::vector<std::string>);
    void StopStatement();
    void VariableDeclaration(std::vector<std::string>, std::string id);
    void WriteStatement(std::vector<Expression>);
private:
    void Read(std::string);
    void StoreSymbol(std::string, std::shared_ptr<Type>);
    void Write(Expression);
    int getLabel();

    int globalLocation;
    std::shared_ptr<LookUpTable<Info>> symbolTable = nullptr;
    std::shared_ptr<std::vector<Register>> regPool = nullptr;
};

} 

#endif