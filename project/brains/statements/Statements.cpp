#include "Statements.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

cpsl::Statements::Statements(std::vector<Register>* pool, LookUpTable<Info>* table) : regPool(pool), symbolTable(table), globalLocation(0){};

void cpsl::Statements::StoreSymbol(std::string id, cpsl::cpslType* type)
{
    std::cout << "Storing Symbol " << id << " with type " << type->id << std::endl;
    cpsl::VariableInfo* var = new cpsl::VariableInfo();
    var->id = id;
    var->type = type;
    var->location = std::to_string(globalLocation);
    globalLocation += type->size;
    symbolTable->store(id, var);
    return;
}

int cpsl::Statements::VariableDeclaration(std::vector<std::string> vars, std::string type)
{
    cpslType* typeInfo = dynamic_cast<cpslType*>(symbolTable->lookup(type));
    for(auto var : vars)
        StoreSymbol(var, typeInfo);

    return 0;
}

int cpsl::Statements::ConstDeclaration(std::string id, cpsl::Expression expr)
{
    std::cout << "Declaring Constant: ";
    std::cout << id << " to be equal to " << expr.value << std::endl;
    if(!expr.isConstant)
        throw std::runtime_error("RHS of constant declaration must be a constant.");

    cpslType* typeInfo = dynamic_cast<cpslType*>(symbolTable->lookup(expr.type));
    StoreSymbol(id, typeInfo);
    cpsl::VariableInfo* var = dynamic_cast<VariableInfo*>(symbolTable->lookup(id));

    Register reg = regPool->back();
    regPool->pop_back();
    std::cout << "\t# Loading constant " << expr.value << " into " << id << std::endl;
    std::cout << "\tli " << reg.name << " " << expr.value << std::endl;
    std::cout << "\tsw " << reg.name << " " << var->location << "($gp)" << std::endl;
    regPool->push_back(reg);
    return 0;
}

int cpsl::Statements::Assignment(std::string id, cpsl::Expression expr)
{
    std::cout << "Assigning " << id;
    std::cout << " the value " << expr.value << std::endl;
    cpsl::VariableInfo* var = dynamic_cast<VariableInfo*>(symbolTable->lookup(id));
    if(var->type->id != expr.type)
        throw std::runtime_error("Type mismatch: " + var->type->id + " != " + expr.type);
    if(expr.isConstant)
    {
        Register reg = regPool->back();
        regPool->pop_back();
        std::cout << "\t# Storing the value " << expr.value << " in " << var->id << std::endl;
        std::cout << "\tli " << reg.name << " " << expr.value << std::endl;
        std::cout << "\tsw " << reg.name << " " << var->location << "($gp)" << std::endl;
        regPool->push_back(reg);
    } 
    else
    {
        std::cout << "\t# Storing the expr at " << expr.reg.name << " in " << var->id << std::endl;
        std::cout << "\tsw " << expr.reg.name << " " << var->location << "($gp)" << std::endl;
        regPool->push_back(expr.reg);
    }
    return 0;

}

cpsl::Expression cpsl::Statements::LoadVariable(std::string id)
{
    cpsl::VariableInfo* var = dynamic_cast<VariableInfo*>(symbolTable->lookup(id));
    // Grab a Register
    // and emit correct MIPS.
    Register reg = regPool->back();
    regPool->pop_back();

    std::cout << "\t# Loading value from " << var->location << "($gp)" << " with type " << var->type->id << std::endl;
    std::cout << "\tlw " << reg.name << " " << var->location << "($gp)" << std::endl;

    cpsl::Expression expr;
    expr.reg = reg;
    expr.isConstant = false;
    expr.type = var->type->id;

    return expr;
}