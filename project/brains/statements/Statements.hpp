#ifndef STATEMENTS_HPP
#define STATEMENTS_HPP 1

#include <memory>
#include <vector>

#include "../utils/LookupTable.hpp"
#include "../utils/structures.hpp"
#include "../utils/RegPool.hpp"

namespace cpsl
{

class Statements
{
public:
    /* Constructors */
    Statements() = default;
    Statements(std::shared_ptr<RegPool>, std::shared_ptr<LookUpTable<Info>>, bool = false);
    
    /* Control Statements */
    ForHeaderInfo ForBegin(std::string, Expression);
    void ForHeader(ForHeaderInfo&, cpsl::Expression);
    void ForEnd(ForHeaderInfo);
    int IfBegin(Expression);
    void IfHeader(int);
    void IfEnd(std::vector<int>);
    int RepeatBegin();
    void RepeatEnd(int, Expression);
    int WhileBegin();
    void WhileHeader(int, Expression);
    void WhileEnd(int);

    /* Helpers */
    void Assignment(std::string, Expression);
    void ConstDeclaration(std::string, Expression);
    void EnterScope();
    void ExitScope();
    void FunctionBody(std::shared_ptr<cpsl::Procedure>);
    void FunctionEpilogue(std::shared_ptr<cpsl::Procedure>);
    void FunctionPrologue(std::shared_ptr<cpsl::Procedure>);
    Expression LoadVariable(std::string);
    std::vector<std::shared_ptr<cpsl::Parameter>> MakeParameters(std::string, std::vector<std::string>, std::string);
    std::shared_ptr<cpsl::Procedure> MakeProcedure(std::string, std::vector<std::shared_ptr<cpsl::Parameter>>);
    void VariableDeclaration(std::vector<std::string>, std::string);

    /* Simple Statements */
    void ReadStatement(std::vector<std::string>);
    void StopStatement();
    void WriteStatement(std::vector<Expression>);
private:
    int getUid();
    void Read(std::string);
    void StoreSymbol(std::string, std::shared_ptr<Type>);
    void Write(Expression);

    int globalOffset;
    int localOffset;
    int paramOffset;
    bool addNewline;
    std::shared_ptr<LookUpTable<Info>> symbolTable = nullptr;
    std::shared_ptr<RegPool> regPool = nullptr;
};

} 

#endif