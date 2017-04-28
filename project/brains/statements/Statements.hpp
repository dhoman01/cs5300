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
    Statements(register_pool, symbol_table, bool = false);

    /* Control Statements */
    ForHeaderInfo ForBegin(std::string, Expression);
    void ForHeader(ForHeaderInfo&, Expression);
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
    void Assignment(std::shared_ptr<LValue>, Expression);
    void ConstDeclaration(std::string, Expression);
    void EnterScope();
    void ExitScope();
    std::shared_ptr<LValue> LoadArrayElement(std::shared_ptr<LValue>, Expression);
    std::shared_ptr<LValue> LoadRecordMember(std::shared_ptr<LValue>, std::string id);
    std::shared_ptr<LValue> LoadVariable(std::string);
    Expression MakeLValueExpression(std::shared_ptr<LValue>);
    void VariableDeclaration(std::vector<std::string>, std::shared_ptr<Type>);
    void PrintDebugLine(int, int);
    void ResetParamOffset();

    /* Types */
    std::shared_ptr<Type> TypeLookup(std::string);
    void DeclareType(std::string, std::shared_ptr<Type>);
    std::shared_ptr<Array> MakeArray(Expression, Expression, std::shared_ptr<Type>);
    std::shared_ptr<Record> MakeRecord(std::vector<Field>);
    std::vector<Field> MakeFields(std::vector<std::string>, std::shared_ptr<Type>);

    /* Simple Statements */
    void ReadStatement(std::vector<std::shared_ptr<LValue>>);
    void StopStatement();
    void WriteStatement(std::vector<Expression>);

    /* Functions/Procedures */
    void FunctionEpilogue(std::shared_ptr<Procedure>);
    void FunctionPrologue(std::shared_ptr<Procedure>);
    std::pair<int, std::shared_ptr<Procedure>> FunctionPrecall(std::string, std::vector<Expression>);
    Expression FunctionPostcall(std::pair<int, std::shared_ptr<Procedure>>);
    std::shared_ptr<Procedure> MakeFunction(std::string, std::vector<std::shared_ptr<Parameter>>, std::shared_ptr<Type>, bool = false);
    std::vector<std::shared_ptr<Parameter>> MakeParameters(std::string, std::vector<std::string>, std::shared_ptr<Type>);
    std::shared_ptr<Procedure> MakeProcedure(std::string, std::vector<std::shared_ptr<Parameter>>, bool = false);
    void ReturnStatement();    
    void ReturnStatement(Expression);
private:
    void DeepCopy(std::string src, std::string dest, std::size_t size, int offset);
    int getUID();
    void Read(std::shared_ptr<LValue>);
    void StoreSymbol(std::string, std::shared_ptr<Type>);
    void Write(Expression);
    void LoadStringExp(Expression& expr);

    int globalOffset;
    int localOffset;
    int paramOffset;
    bool addNewline;
    bool verbose = false;
    symbol_table symbolTable = nullptr;
    register_pool regPool = nullptr;
};

} 

#endif