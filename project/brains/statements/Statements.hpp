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
    /* Constructors */
    Statements() = default;
    Statements(std::shared_ptr<std::vector<Register>>, std::shared_ptr<LookUpTable<Info>>, bool = false);
    
    /* Control Statements */
    ForHeaderInfo ForBegin(std::string, Expression);
    void ForHeader(ForHeaderInfo&, cpsl::Expression);
    void ForEnd(ForHeaderInfo);
    int IfBegin(Expression expr);
    void IfHeader(int uid);
    void IfEnd(std::vector<int> uid);
    int RepeatBegin();
    void RepeatEnd(int uid, Expression expr);
    int WhileBegin();
    void WhileHeader(int uid, Expression expr);
    void WhileEnd(int uid);

    /* Helpers */
    void Assignment(std::string, Expression);
    void ConstDeclaration(std::string, Expression);
    Expression LoadVariable(std::string);
    void VariableDeclaration(std::vector<std::string>, std::string id);

    /* Simple Statements */
    void ReadStatement(std::vector<std::string>);
    void StopStatement();
    void WriteStatement(std::vector<Expression>);
private:
    int getUid();
    void Read(std::string);
    void StoreSymbol(std::string, std::shared_ptr<Type>);
    void Write(Expression);

    int globalLocation;
    int frameLocation;
    bool addNewline;
    std::shared_ptr<LookUpTable<Info>> symbolTable = nullptr;
    std::shared_ptr<std::vector<Register>> regPool = nullptr;
};

} 

#endif