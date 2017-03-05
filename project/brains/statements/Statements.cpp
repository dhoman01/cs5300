#include "Statements.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

/**************
 *   PUBLIC   *
 *************/ 
cpsl::Statements::Statements(std::shared_ptr<std::vector<cpsl::Register>> pool, std::shared_ptr<cpsl::LookUpTable<cpsl::Info>> table, bool addNew)
{
    // Start globalLocation at 8
    // because true is at 0($gp)
    // and false is at 4($gp)
    globalLocation = 8;
    regPool = pool;
    symbolTable = table;
    addNewline = addNew;
};

int cpsl::Statements::WhileBegin()
{
    int uid = cpsl::Statements::getLabel();
    std::string label = "WB" + std::to_string(uid);
    std::cout << "\n\t# Beginning While Loop (label " << label << ")" << std::endl;
    std::cout << label << ":" << std::endl;
    return uid;
};

void cpsl::Statements::WhileHeader(int uid, cpsl::Expression expr)
{
    // Type check
    if(expr.type != "boolean")
        throw std::runtime_error("The value of " + std::to_string(expr.value) + " is not boolean.");

    std::string label = "WE" + std::to_string(uid);
    std::cout << "\n\t# While Header (label " << label << ")" << std::endl;
    if(expr.isConstant)
    {
        if(expr.value)
        {
            std::cerr << "WARN: While condition is always true, this may lead to an infinite loop. I'll continue, but I sure hope you know what your doing..." << std::endl;
        }
        else
        {
            std::cerr << "WARN: While condition is always false, the while loop will never execute. It's wasteful, but I assume you know what your doing and will still emit the MIPS for your while loop..." << std::endl;
        }
        std::cout << "\t# Grapping register and loading " << (expr.value ? "1" : "0") << " into it for constant expression" << std::endl;
        expr.reg = regPool->back();
        std::cout << "\tli " << expr.reg.name << " " << (expr.value ? "1" : "0") << std::endl;
    }

    std::cout << "\tbeq " << expr.reg.name << " $zero " << label;
    regPool->push_back(expr.reg);
};

void cpsl::Statements::WhileEnd(int uid)
{
    std::string bLabel = "WB" + std::to_string(uid);
    std::string eLabel = "WE" + std::to_string(uid);
    std::cout << "\n\t# End of While Loop (label " << bLabel << " - " << eLabel << ")" << std::endl;
    std::cout << "\tj " << bLabel << std::endl;
    std::cout << eLabel << ":" << std::endl;
};

int cpsl::Statements::RepeatBegin()
{
    int uid = cpsl::Statements::getLabel();
    std::string label = "RP" + std::to_string(uid);
    std::cout << "\n\t# Begin Repeat Statement (label " << label << ")" << std::endl;
    std::cout << label << ":" << std::endl;
    return uid;
};

void cpsl::Statements::RepeatEnd(int uid, cpsl::Expression expr)
{
    // Type check
    if(expr.type != "boolean")
        throw std::runtime_error("The value of " + std::to_string(expr.value) + " is not boolean.");

    std::string label = "RP" + std::to_string(uid);
    std::cout << "\n\t# Repeat Exit Condition (label " << label << ")" << std::endl;
    if(expr.isConstant)
    {
        if(expr.value)
        {
            std::cerr << "WARN: Repeat condition is always true, this may lead to an infinite loop. I'll continue, but I sure hope you know what your doing..." << std::endl;
        }
        else
        {
            std::cerr << "WARN: Repeat condition is always false, the repeat loop will never execute. It's wasteful, but I assume you know what your doing and will still emit the MIPS for your repeat loop..." << std::endl;
        }
        std::cout << "\t# Grapping register and loading " << (expr.value ? "1" : "0") << " into it for constant expression" << std::endl;
        expr.reg = regPool->back();
        regPool->pop_back();
        std::cout << "\tli " << expr.reg.name << " " << (expr.value ? "1" : "0") << std::endl;
    }
    std::cout << "\tbne " << expr.reg.name << " $zero " << label << std::endl;
    regPool->push_back(expr.reg);
};

int cpsl::Statements::IfBegin(cpsl::Expression expr)
{
    // Type check
    if(expr.type != "boolean")
        throw std::runtime_error("The value of " + std::to_string(expr.value) + " is not boolean.");

    int uid = cpsl::Statements::getLabel();
    std::string label = "IE" + std::to_string(uid);
    std::cout << "\n\t# Begin If Statement" << std::endl;
    if(expr.isConstant)
    {
        if(expr.value)
        {
            std::cerr << "WARN: If(ElseIf) condition is always true. I'll continue, but I sure hope you know what your doing..." << std::endl;
        }
        else
        {
            std::cerr << "WARN: If(ElseIf) condition is always false, the if branch will never execute. It's wasteful, but I assume you know what your doing and will still emit the MIPS for your if branch..." << std::endl;
        }
        std::cout << "\t# Grapping register and loading " << (expr.value ? "1" : "0") << " into it for constant expression" << std::endl;
        expr.reg = regPool->back();
        regPool->pop_back();
        std::cout << "\tli " << expr.reg.name << " " << (expr.value ? "1" : "0") << std::endl;
    }
    std::cout << "\tbeq " << expr.reg.name << " $zero " << label << std::endl;
    regPool->push_back(expr.reg);
    return uid;
};

void cpsl::Statements::IfHeader(int uid)
{
    std::string dLabel = "ID" + std::to_string(uid);
    std::string eLabel = "IE" + std::to_string(uid);
    std::cout << "\n\t# End If then block (label " << dLabel << ", " << eLabel << ")" << std::endl;
    std::cout << "\tj " << dLabel << std::endl;
    std::cout << eLabel << ":" << std::endl;
};

void cpsl::Statements::IfEnd(std::vector<int> uids)
{
    for(auto uid : uids)
    {
        std::string label = "ID" + std::to_string(uid);
        std::cout << "\n\t# End If(ElseIf) Statement (label " << label << ")" << std::endl;
        std::cout << label << ":" << std::endl;
    }
};

cpsl::ForHeaderInfo cpsl::Statements::ForBegin(std::string id, cpsl::Expression expr)
{
    // Type check
    if(expr.type != "integer")
        throw std::runtime_error("Type mismatch: " + expr.type + " != integer in for loop condition");

    std::cout << "\n\t# For Statement Begin" << std::endl;
    cpsl::ForHeaderInfo info;
    cpsl::Expression varExpr;
    try
    {
        std::shared_ptr<cpsl::VariableInfo> var = std::dynamic_pointer_cast<cpsl::VariableInfo>(symbolTable->lookup(id));
        cpsl::Statements::Assignment(id, expr);
        varExpr = cpsl::Statements::LoadVariable(id);
        info.var = var;
    }
    catch (const std::exception& ex)
    {
        // TODO: Create variable for user...
        throw std::runtime_error("Declaring variables in for loops is not yet implemented...");
    }

    int uid = cpsl::Statements::getLabel();
    std::string label = "FB" + std::to_string(uid);
    std::cout << "\t# Start of Loop" << std::endl;
    std::cout << label << ":" << std::endl;
    info.varExpr = varExpr;
    info.uid = uid;
    return info;
};

void cpsl::Statements::ForHeader(cpsl::ForHeaderInfo& info, cpsl::Expression cond)
{
    // Type check
    if(cond.type != "integer")
            throw std::runtime_error("Type mismatch: " + cond.type + " != integer in for loop condition");

    info.cond = cond;    
    if(cond.isConstant)
    {
        cond.reg = regPool->back();
        regPool->pop_back();
        std::cout << "\t# Loading constant expression" << std::endl;
        std::cout << "\tli " << cond.reg.name << " " << cond.value << std::endl;
    }
    
    std::cout << "\taddi " << cond.reg.name << " " << cond.reg.name << " " << info.optTo << std::endl;
    std::cout << "\tbeq " << info.varExpr.reg.name << " " << cond.reg.name << " FE" << info.uid << std::endl;
};

void cpsl::Statements::ForEnd(cpsl::ForHeaderInfo info)
{
    std::cout << "\taddi " << info.varExpr.reg.name << " " << info.varExpr.reg.name << " " << info.optTo << std::endl;
    std::cout << "\tsw " << info.varExpr.reg.name << " " << info.var->location << "($gp)" << std::endl;
    std::cout << "\tj FB" << info.uid << std::endl;
    std::cout << "FE" << info.uid << ":" << std::endl;
    std::cout << "\t# End of For Statement" << std::endl;
    regPool->push_back(info.varExpr.reg);
    regPool->push_back(info.cond.reg);
};

void cpsl::Statements::Assignment(std::string id, cpsl::Expression expr)
{
    std::shared_ptr<cpsl::VariableInfo> var = std::dynamic_pointer_cast<cpsl::VariableInfo>(symbolTable->lookup(id));
    if(var->type->id != expr.type)
        throw std::runtime_error("Type mismatch: " + var->type->id + " != " + expr.type);
    
    std::cout << "\n\t# Assigning " << id << " the value";
    if(expr.isConstant)
    {
        expr.reg = regPool->back();
        regPool->pop_back();
        std::cout << " " << var->id << std::endl;
        std::cout << "\tli " << expr.reg.name << " " << expr.value << std::endl;
    } 
    else
    {
        std::cout << " at " << expr.reg.name << std::endl;
    }

    std::cout << "\tsw " << expr.reg.name << " " << var->location << "($gp)" << std::endl;
    regPool->push_back(expr.reg);
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
    if(cpsl::Statements::addNewline)
    {
        std::cout << "\n\t# Newline at end of write()" << std::endl;
        std::cout << "\taddi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR." << std::endl;
        std::cout << "\taddi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character." << std::endl;
        std::cout << "\tsyscall" << std::endl;
        std::cout << "\t# Finished newline" << std::endl;
    }

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

int cpsl::Statements::getLabel()
{
    static std::size_t label = 0;
    return ++label;
}