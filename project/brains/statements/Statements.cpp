#include "Statements.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

/**************
 *   PUBLIC   *
 *************/ 
cpsl::Statements::Statements(std::shared_ptr<std::vector<cpsl::Register>> pool, std::shared_ptr<cpsl::LookUpTable<cpsl::Info>> table)
{
    // Start globalLocation at 8
    // because true is at 0($gp)
    // and false is at 4($gp)
    globalLocation = 8;
    regPool = pool;
    symbolTable = table;
};

void cpsl::Statements::Assignment(std::string id, cpsl::Expression expr)
{
    std::shared_ptr<cpsl::VariableInfo> var = std::dynamic_pointer_cast<cpsl::VariableInfo>(symbolTable->lookup(id));
    if(var->type->id != expr.type)
        throw std::runtime_error("Type mismatch: " + var->type->id + " != " + expr.type);
    
    std::cout << "\n\t# Assigning " << id << " the value";
    if(expr.isConstant)
    {
        cpsl::Register reg = regPool->back();
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
    return;
}

void cpsl::Statements::ConstDeclaration(std::string id, cpsl::Expression expr)
{
    std::shared_ptr<cpsl::Type> typeInfo = std::dynamic_pointer_cast<cpsl::Type>(symbolTable->lookup(expr.type));
    cpsl::Statements::StoreSymbol(id, typeInfo);
    std::shared_ptr<cpsl::VariableInfo> var = std::dynamic_pointer_cast<cpsl::VariableInfo>(symbolTable->lookup(id));

    std::cout << "\n\t# Loading constant " << expr.value << " into " << id << std::endl;
    if(expr.isConstant){
        cpsl::Register reg = regPool->back();
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

    return;
}

cpsl::Expression cpsl::Statements::LoadVariable(std::string id)
{
    std::shared_ptr<cpsl::VariableInfo> var = std::dynamic_pointer_cast<cpsl::VariableInfo>(symbolTable->lookup(id));
    // Grab a Register
    // and emit correct MIPS.
    cpsl::Register reg = regPool->back();
    regPool->pop_back();

    std::cout << "\n\t# Loading value from " << var->location << "($gp)" << " with type " << var->type->id << std::endl;
    std::cout << "\tlw " << reg.name << " " << var->location << "($gp)" << std::endl;
    std::cout << "\t# Loaded value from " << id << std::endl;

    // Generate cpsl::Expression for loaded variable
    cpsl::Expression expr;
    expr.reg = reg;
    expr.isConstant = false;
    expr.type = var->type->id;

    return expr;
}

void cpsl::Statements::ReadStatement(std::vector<std::string> ids)
{
    for(auto id : ids)
        cpsl::Statements::Read(id);
    return;
}

void cpsl::Statements::StopStatement()
{
    std::cout << "\n\t# Exiting program" << std::endl;
    std::cout << "\tli $v0 10" << std::endl << "\tsyscall" << std::endl;
    std::cout << "\t# Exit syscall invoked" << std::endl;
    return;
}

void cpsl::Statements::VariableDeclaration(std::vector<std::string> ids, std::string typeName)
{
    std::shared_ptr<cpsl::Type> type = std::dynamic_pointer_cast<cpsl::Type>(symbolTable->lookup(typeName));
    for(auto id : ids)
        cpsl::Statements::StoreSymbol(id, type);

    return;
}

void cpsl::Statements::WriteStatement(std::vector<cpsl::Expression> expressionList)
{
    for(auto e : expressionList)
        cpsl::Statements::Write(e);

    // Emit MIPS for newline
    std::cout << "\t# Newline at end of write()" << std::endl;
    std::cout << "\taddi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR." << std::endl;
    std::cout << "\taddi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character." << std::endl;
    std::cout << "\tsyscall" << std::endl;
    std::cout << "\t# Finished newline" << std::endl;
    return;
}

/***********
 * PRIVATE *
 **********/
void cpsl::Statements::Read(std::string id)
{
    std::shared_ptr<cpsl::VariableInfo> var = std::dynamic_pointer_cast<cpsl::VariableInfo>(symbolTable->lookup(id));
    if(var->type->id != "integer" && var->type->id != "char")
        throw std::runtime_error("Could not read into variable '" + id + "', read() is only defined for integer and character types. Not " + var->type->id);

    std::cout << "\n\t# Reading in input from user" << std::endl;
    std::cout << "\tli $v0 " << (var->type->id == "integer" ? "5" : "12") << std::endl << "\tsyscall" << std::endl;
    std::cout << "\tsw $v0 " << var->location << "($gp)" << std::endl;
    std::cout << "\taddi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR." << std::endl;
    std::cout << "\taddi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character." << std::endl;
    std::cout << "\tsyscall" << std::endl;
    std::cout << "\t# Finished reading input. Stored input in " << var->id << " at " << var->location << "($gp)" << std::endl;
    return;
}

void cpsl::Statements::StoreSymbol(std::string id, std::shared_ptr<cpsl::Type> type)
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

void cpsl::Statements::Write(cpsl::Expression expr)
{
        std::cout << "\n\t# Writing expression to output" << std::endl;
        if(expr.isConstant)
        {
            expr.reg = regPool->back();
            regPool->pop_back();
            std::cout << "\tli " << expr.reg.name << " " << expr.value << std::endl;
        }

        if(expr.type == "string")
        {
            cpsl::Register reg = regPool->back();
            regPool->pop_back();
            std::cout << "\t# Loading string const" << std::endl;
            std::cout << "\tla " << reg.name << " " << expr.reg.name << std::endl;
            std::cout << "\t# Loaded string " << expr.reg.name << std::endl;
            expr.reg = reg;
        }
        
        std::cout << "\tli $v0 " << (expr.type == "string" ? "4" : (expr.type == "char" ? "11" : "1")) << std::endl;
        std::cout << "\tori $a0 " << expr.reg.name << " 0" << std::endl;
        std::cout << "\tsyscall" << std::endl;
        std::cout << "\t# Finished writing expression to output" << std::endl;
        regPool->push_back(expr.reg);
        return;
}