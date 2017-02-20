#include "Statements.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// Start globalLocation at 8 because true is at 0($gp) and false is at 4($gp)
cpsl::Statements::Statements(std::shared_ptr<std::vector<Register>> pool, std::shared_ptr<LookUpTable<Info>> table)
{
    globalLocation = 8;
    regPool = pool;
    symbolTable = table;
};

int cpsl::Statements::StopStatement()
{
    std::cout << "\t# Exiting program" << std::endl;
    std::cout << "\tli $v0 10" << std::endl << "\tsyscall" << std::endl;
    std::cout << "\t# Exit syscall invoked" << std::endl;
}

void cpsl::Statements::Write(cpsl::Expression expr)
{
        std::cout << "\t# Writing expression to output" << std::endl;
        if(expr.isConstant)
        {
            expr.reg = regPool->back();
            regPool->pop_back();
            std::cout << "\tli " << expr.reg.name << " " << expr.value << std::endl;
        }

        if(expr.type == "string")
        {
            Register reg = regPool->back();
            regPool->pop_back();
            std::cout << "\t# Loading string const" << std::endl;
            std::cout << "\tla " << reg.name << " " << expr.reg.name << std::endl;
            std::cout << "\t# Loaded string " << expr.reg.name << std::endl;
            expr.reg = reg;
        }
        
        std::cout << "\tli $v0 " << (expr.type == "string" ? "4" : (expr.type == "char" ? "11" : "1")) << std::endl;
        std::cout << "\tori $a0 " << expr.reg.name << " 0" << std::endl;
        std::cout << "\tsyscall" << std::endl;
        std::cout << "\taddi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR." << std::endl;
        std::cout << "\taddi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character." << std::endl;
        std::cout << "\tsyscall" << std::endl;
        std::cout << "\t# Finished writing expression to output" << std::endl;
        regPool->push_back(expr.reg);
        return;
}

int cpsl::Statements::WriteStatement(std::vector<cpsl::Expression> expressionList)
{
    for(auto e : expressionList)
        Write(e);
    return 0;
}

void cpsl::Statements::Read(std::string id)
{
    std::shared_ptr<VariableInfo> var = std::dynamic_pointer_cast<VariableInfo>(symbolTable->lookup(id));
    if(var->type->id != "integer" && var->type->id != "char")
        throw std::runtime_error("Could not read into variable '" + id + "', read() is only defined for integer and character types. Not " + var->type->id);
    std::cout << "\t# Reading in input from user" << std::endl;
    std::cout << "\tli $v0 " << (var->type->id == "integer" ? "5" : "12") << std::endl << "\tsyscall" << std::endl;
    std::cout << "\tsw $v0 " << var->location << "($gp)" << std::endl;
    std::cout << "\taddi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR." << std::endl;
    std::cout << "\taddi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character." << std::endl;
    std::cout << "\tsyscall" << std::endl;
    std::cout << "\t# Finished reading input. Stored input in " << var->id << " at " << var->location << "($gp)" << std::endl;
}

int cpsl::Statements::ReadStatement(std::vector<std::string> ids)
{
    for(auto id : ids)
        Read(id);
    return 0;
}

void cpsl::Statements::StoreSymbol(std::string id, std::shared_ptr<cpsl::cpslType> type)
{
    std::shared_ptr<cpsl::VariableInfo> var = std::make_shared<cpsl::VariableInfo>();
    var->id = id;
    var->type = type;
    var->location = std::to_string(globalLocation);
    globalLocation += type->size;
    symbolTable->store(id, var);
    std::cout << "\t# (NO MIPS EMITTED) Storing symbol " << id << " with type " << type->id << " into symbol table" << std::endl;
    return;
}

int cpsl::Statements::VariableDeclaration(std::vector<std::string> vars, std::string type)
{
    std::shared_ptr<cpslType> typeInfo = std::dynamic_pointer_cast<cpslType>(symbolTable->lookup(type));
    for(auto var : vars)
        StoreSymbol(var, typeInfo);

    return 0;
}

int cpsl::Statements::ConstDeclaration(std::string id, cpsl::Expression expr)
{
    std::shared_ptr<cpslType> typeInfo = std::dynamic_pointer_cast<cpslType>(symbolTable->lookup(expr.type));
    StoreSymbol(id, typeInfo);
    std::shared_ptr<VariableInfo> var = std::dynamic_pointer_cast<VariableInfo>(symbolTable->lookup(id));

    std::cout << "\t# Loading constant " << expr.value << " into " << id << std::endl;
    if(expr.isConstant){
        Register reg = regPool->back();
        regPool->pop_back();
        std::cout << "\tli " << reg.name << " " << expr.value << std::endl;
        std::cout << "\tsw " << reg.name << " " << var->location << "($gp)" << std::endl;
        regPool->push_back(reg);
    } 
    else
    {
        std::cout << "\tsw " << expr.reg.name << " " << var->location << "($gp)" << std::endl;
    }
    std::cout << "\t# Loaded constant into " << id << std::endl;

    return 0;
}

int cpsl::Statements::Assignment(std::string id, cpsl::Expression expr)
{
    std::shared_ptr<VariableInfo> var = std::dynamic_pointer_cast<VariableInfo>(symbolTable->lookup(id));
    if(var->type->id != expr.type)
        throw std::runtime_error("Type mismatch: " + var->type->id + " != " + expr.type);
    
    std::cout << "\t# Assigning " << id << " the value";
    if(expr.isConstant)
    {
        Register reg = regPool->back();
        regPool->pop_back();
        std::cout << " " << var->id << std::endl;
        std::cout << "\tli " << reg.name << " " << expr.value << std::endl;
        std::cout << "\tsw " << reg.name << " " << var->location << "($gp)" << std::endl;
        regPool->push_back(reg);
    } 
    else
    {
        std::cout << " at " << expr.reg.name << std::endl;
        std::cout << "\tsw " << expr.reg.name << " " << var->location << "($gp)" << std::endl;
        regPool->push_back(expr.reg);
    }
    std::cout << "\t# Finished assignment of " << id;
    return 0;

}

cpsl::Expression cpsl::Statements::LoadVariable(std::string id)
{
    std::shared_ptr<VariableInfo> var = std::dynamic_pointer_cast<VariableInfo>(symbolTable->lookup(id));
    // Grab a Register
    // and emit correct MIPS.
    Register reg = regPool->back();
    regPool->pop_back();

    std::cout << "\t# Loading value from " << var->location << "($gp)" << " with type " << var->type->id << std::endl;
    std::cout << "\tlw " << reg.name << " " << var->location << "($gp)" << std::endl;
    std::cout << "\t# Loaded value from " << id << std::endl;

    // Create expression for loaded variable
    cpsl::Expression expr;
    expr.reg = reg;
    expr.isConstant = false;
    expr.type = var->type->id;

    return expr;
}