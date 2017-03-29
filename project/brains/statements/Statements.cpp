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
cpsl::Statements::Statements(std::shared_ptr<cpsl::RegPool> pool, std::shared_ptr<cpsl::LookUpTable<cpsl::Info>> table, bool addNew)
{
    // Start globalOffset at 8
    // because true is at 0($gp)
    // and false is at 4($gp)
    globalOffset = 8;
    localOffset = 0;
    paramOffset = 0;
    regPool = pool;
    symbolTable = table;
    addNewline = addNew;
};

/**********************
 * Control Statements *
 * - For Statement    *
 * - If Statement     *
 * - Repeat Statement *
 * - While Statement  *
 *********************/
cpsl::ForHeaderInfo cpsl::Statements::ForBegin(std::string id, cpsl::Expression expr)
{
    // Type check
    if(expr.type != "integer")
        throw std::runtime_error("Type mismatch: " + expr.type + " != integer in for loop condition");

    // Try to find the control variable
    // If found use assign the expr,
    //     load it, and store relevant info
    // Else enter a new scope and create
    //     a new variable. Load it, and
    //     store relevant info
    std::cout << "\n\t# For Statement Begin" << std::endl;
    cpsl::ForHeaderInfo info;
    cpsl::Expression varExpr;
    try
    {
        std::shared_ptr<cpsl::VariableInfo> var = std::dynamic_pointer_cast<cpsl::VariableInfo>(symbolTable->lookup(id));
        cpsl::Statements::Assignment(id, expr);
        varExpr = cpsl::Statements::LoadVariable(id);
        info.var = var;
        info.exitScope = false;
    }
    catch (const std::exception& ex)
    {
        // TODO: Create variable for user...
        std::cout << "\t# Entering new scope for for loop" << std::endl;
        symbolTable->enterScope();
        std::shared_ptr<cpsl::Type> intType = std::dynamic_pointer_cast<cpsl::Type>(symbolTable->lookup("integer"));
        cpsl::Statements::StoreSymbol(id, intType);
        std::shared_ptr<cpsl::VariableInfo> var = std::dynamic_pointer_cast<cpsl::VariableInfo>(symbolTable->lookup(id));
        cpsl::Statements::Assignment(id, expr);        
        varExpr = cpsl::Statements::LoadVariable(id);
        info.var = var;
        info.exitScope = true;
    }

    // Get a uid for for loop
    int uid = cpsl::Statements::getUid();
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
        // If cond is constant load it into a new register
        cond.reg = regPool->acquire();
        std::cout << "\t# Loading constant expression" << std::endl;
        std::cout << "\tli " << cond.reg.name << " " << cond.value << std::endl;
    }
    
    // Add (subtract in downto) 1 from the condition for '=' operator
    std::cout << "\taddi " << cond.reg.name << " " << cond.reg.name << " " << info.optTo << std::endl;
    std::cout << "\tbeq " << info.varExpr.reg.name << " " << cond.reg.name << " FE" << info.uid << std::endl;
};

void cpsl::Statements::ForEnd(cpsl::ForHeaderInfo info)
{
    // Increment counter
    std::cout << "\t# Incrementing counter " << info.var->id << std::endl;
    std::cout << "\taddi " << info.varExpr.reg.name << " " << info.varExpr.reg.name << " " << info.optTo << std::endl;
    std::cout << "\tsw " << info.varExpr.reg.name << " " << info.var->location << std::endl;
    std::cout << "\tj FB" << info.uid << std::endl;
    std::cout << "FE" << info.uid << ":" << std::endl;
    std::cout << "\t# End of For Statement" << std::endl;

    // Release registers
    regPool->release(info.varExpr.reg);
    regPool->release(info.cond.reg);

    // Exit scope if new variable was created for counter
    if(info.exitScope)
    {
        symbolTable->exitScope();
        std::cout << "\t# Exited scope for for loop" << std::endl;
    }
};

int cpsl::Statements::IfBegin(cpsl::Expression expr)
{
    // Type check
    if(expr.type != "boolean")
        throw std::runtime_error("The value of " + std::to_string(expr.value) + " is not boolean.");

    // Get UID for if statement
    int uid = cpsl::Statements::getUid();
    std::string label = "IE" + std::to_string(uid);
    std::cout << "\n\t# Begin If Statement" << std::endl;
    
    // Check for constant If Condition
    if(expr.isConstant)
    {   
        // If condition is always true, no need to branch
        if(expr.value)
        {
            std::cerr << "WARN: If(ElseIf) condition is always true. Skipping executing if condition..." << std::endl;
            std::cout << "\t# No beq emitted because if condition is always true" << std::endl;
        }
        // If condition is always false, just jump to the else block
        else
        {
            std::cerr << "WARN: If(ElseIf) condition is always false, the if branch will never execute. Jumping to else..." << std::endl;
            std::cout << "\t# Jumping to else(elseif) because if condition is always false" << std::endl;
            std::cout << "\tj " << label << std::endl;
        }
    }
    else
    {
        std::cout << "\tbeq " << expr.reg.name << " $zero " << label << std::endl;
        regPool->release(expr.reg);
    }
    
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

int cpsl::Statements::RepeatBegin()
{
    int uid = cpsl::Statements::getUid();
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
        expr.reg = regPool->acquire();
        
        std::cout << "\tli " << expr.reg.name << " " << (expr.value ? "1" : "0") << std::endl;
    }
    std::cout << "\tbne " << expr.reg.name << " $zero " << label << std::endl;
    regPool->release(expr.reg);
};

int cpsl::Statements::WhileBegin()
{
    int uid = cpsl::Statements::getUid();
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
        expr.reg = regPool->acquire();
        std::cout << "\tli " << expr.reg.name << " " << (expr.value ? "1" : "0") << std::endl;
    }

    std::cout << "\tbeq " << expr.reg.name << " $zero " << label;
    regPool->release(expr.reg);
};

void cpsl::Statements::WhileEnd(int uid)
{
    std::string bLabel = "WB" + std::to_string(uid);
    std::string eLabel = "WE" + std::to_string(uid);
    std::cout << "\n\t# End of While Loop (label " << bLabel << " - " << eLabel << ")" << std::endl;
    std::cout << "\tj " << bLabel << std::endl;
    std::cout << eLabel << ":" << std::endl;
};

/*****************
 * Helpers       *
 * - Assignment  *
 * - Const Decl  *
 * - Func Body   *
 * - Func Ep     *
 * - Func Pro    *
 * - Enter Scope *
 * - Exit Scope  *
 * - Load Var    *
 * - Make Param  *
 * - Var Decl    *
 ****************/
void cpsl::Statements::Assignment(std::string id, cpsl::Expression expr)
{
    std::shared_ptr<cpsl::VariableInfo> var = std::dynamic_pointer_cast<cpsl::VariableInfo>(symbolTable->lookup(id));
    if(var->type->id != expr.type)
        throw std::runtime_error("Type mismatch: " + var->type->id + " != " + expr.type);
    
    std::cout << "\n\t# Assigning " << id << " the value";
    if(expr.isConstant)
    {
        expr.reg = regPool->acquire();
        
        std::cout << " " << var->id << std::endl;
        std::cout << "\tli " << expr.reg.name << " " << expr.value << std::endl;
    } 
    else
    {
        std::cout << " at " << expr.reg.name << std::endl;
    }

    std::shared_ptr<cpsl::Parameter> param = std::dynamic_pointer_cast<cpsl::Parameter>(var);
    if(param && param->isRef)
    {
        cpsl::Register ref = regPool->acquire();
        std::cout << "\t# Storing value to reference" << std::endl;
        std::cout << "\tlw " << ref.name << " " << param->location << std::endl;
        var->location = "0(" + ref.name + ")";
        regPool->release(ref);
    }

    std::cout << "\tsw " << expr.reg.name << " " << var->location << std::endl;
    regPool->release(expr.reg);
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
        cpsl::Register reg = regPool->acquire();
        
        std::cout << "\tli " << reg.name << " " << expr.value << std::endl;
        std::cout << "\tsw " << reg.name << " " << var->location << std::endl;
        regPool->release(reg);
    } 
    else
    {
        std::cout << "\tsw " << expr.reg.name << " " << var->location << std::endl;
    }
    std::cout << "\t# Loaded constant into " << id << std::endl;

    return;
}

void cpsl::Statements::EnterScope()
{
    symbolTable->enterScope();
}

void cpsl::Statements::ExitScope()
{
    symbolTable->exitScope();
}

void cpsl::Statements::FunctionBody(std::shared_ptr<cpsl::Procedure> procedure)
{
    std::cout << "\tj " << procedure->id << "Epilogue" << std::endl;
}

void cpsl::Statements::FunctionEpilogue(std::shared_ptr<cpsl::Procedure> procedure)
{
    std::cout << "\t# " << procedure->id << " Epilogue" << std::endl;
    std::cout << procedure->id << "Epilogue" << std::endl;
    std::cout << "\taddi $sp $sp " << localOffset << std::endl;
    std::cout << "\tjr $ra" << std::endl;
}

void cpsl::Statements::FunctionPrologue(std::shared_ptr<cpsl::Procedure> procedure)
{
    std::cout << "\t# " << procedure->id << " Prolouge" << std::endl;
    std::cout << procedure->id << std::endl;
    std::cout << "\taddi $sp $sp -" <<  localOffset << std::endl;
}

cpsl::Expression cpsl::Statements::LoadVariable(std::string id)
{
    std::shared_ptr<cpsl::VariableInfo> var = std::dynamic_pointer_cast<cpsl::VariableInfo>(symbolTable->lookup(id));
    // Grab a Register
    // and emit correct MIPS.
    cpsl::Register reg = regPool->acquire();
    

    std::cout << "\n\t# Loading value from " << var->location << " with type " << var->type->id << std::endl;
    std::cout << "\tlw " << reg.name << " " << var->location << std::endl;

    std::shared_ptr<cpsl::Parameter> param = std::dynamic_pointer_cast<cpsl::Parameter>(var);
    if(param && param->isRef)
    {
        cpsl::Register ref = regPool->acquire();
        std::cout << "\t# Loading reference" << std::endl;
        std::cout << "\tlw " << ref.name << " 0(" << reg.name << ")" << std::endl;
        regPool->release(reg);
        reg = ref;
    }
    std::cout << "\t# Loaded value from " << id << std::endl;

    // Generate cpsl::Expression for loaded variable
    cpsl::Expression expr;
    expr.reg = reg;
    expr.isConstant = false;
    expr.type = var->type->id;

    return expr;
}

std::vector<std::shared_ptr<cpsl::Parameter>> cpsl::Statements::MakeParameters(std::string var_ref, std::vector<std::string> ids, std::string typeName)
{
    std::shared_ptr<cpsl::Type> type = std::dynamic_pointer_cast<cpsl::Type>(symbolTable->lookup(typeName));
    std::vector<std::shared_ptr<cpsl::Parameter>> params;
    for(auto id : ids)
    {
        std::shared_ptr<cpsl::Parameter> param = std::make_shared<cpsl::Parameter>();
        param->id = id;
        param->type = type;
        param->isRef = (var_ref == "ref");
        param->location = std::to_string(paramOffset) + "($fp)";
        paramOffset += type->size;
        symbolTable->store(id, param);
        std::cout << "\t# (NO MIPS EMITTED) Storing " << (param->isRef ? "ref to" : "") << " parameter " << id << " with type " << type->id << " into symbol table" << std::endl;        
        params.push_back(param);
    }

    return params;
}

std::shared_ptr<cpsl::Procedure> cpsl::Statements::MakeProcedure(std::string id, std::vector<std::shared_ptr<cpsl::Parameter>> params)
{
    std::shared_ptr<cpsl::Procedure> procedure = std::make_shared<cpsl::Procedure>(id, params);
    symbolTable->store(id, procedure);
}

void cpsl::Statements::VariableDeclaration(std::vector<std::string> ids, std::string typeName)
{
    std::shared_ptr<cpsl::Type> type = std::dynamic_pointer_cast<cpsl::Type>(symbolTable->lookup(typeName));
    for(auto id : ids)
        cpsl::Statements::StoreSymbol(id, type);

    return;
}

/*********************
 * Simple Statements *
 * - Read Statement  *
 * - Stop Statement  *
 * - Write Statement *
 ********************/
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
int cpsl::Statements::getUid()
{
    static std::size_t label = 0;
    return ++label;
}

void cpsl::Statements::Read(std::string id)
{
    std::shared_ptr<cpsl::VariableInfo> var = std::dynamic_pointer_cast<cpsl::VariableInfo>(symbolTable->lookup(id));
    if(var->type->id != "integer" && var->type->id != "char")
        throw std::runtime_error("Could not read into variable '" + id + "', read() is only defined for integer and character types. Not " + var->type->id);

    std::cout << "\n\t# Reading in input from user" << std::endl;
    std::cout << "\tli $v0 " << (var->type->id == "integer" ? "5" : "12") << std::endl << "\tsyscall" << std::endl;
    std::cout << "\tsw $v0 " << var->location << std::endl;
    std::cout << "\taddi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR." << std::endl;
    std::cout << "\taddi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character." << std::endl;
    std::cout << "\tsyscall" << std::endl;
    std::cout << "\t# Finished reading input. Stored input in " << var->id << " at " << var->location << std::endl;
    return;
}

void cpsl::Statements::StoreSymbol(std::string id, std::shared_ptr<cpsl::Type> type)
{
    std::shared_ptr<cpsl::VariableInfo> var = std::make_shared<cpsl::VariableInfo>();
    var->id = id;
    var->type = type;
    if(symbolTable->inLocalScope())
    {
        var->location = std::to_string(-1 * localOffset) + "($fp)";
        localOffset += type->size;
    }
    else
    {
        var->location = std::to_string(globalOffset) + "($gp)";
        globalOffset += type->size;
    }
    symbolTable->store(id, var);
    std::cout << "\t# (NO MIPS EMITTED) Storing symbol " << id << " with type " << type->id << " into symbol table" << std::endl;
    return;
}

void cpsl::Statements::Write(cpsl::Expression expr)
{
        std::cout << "\n\t# Writing expression to output" << std::endl;
        if(expr.isConstant)
        {
            expr.reg = regPool->acquire();
            
            std::cout << "\tli " << expr.reg.name << " " << expr.value << std::endl;
        }

        if(expr.type == "string")
        {
            cpsl::Register reg = regPool->acquire();
            
            std::cout << "\t# Loading string const" << std::endl;
            std::cout << "\tla " << reg.name << " " << expr.reg.name << std::endl;
            std::cout << "\t# Loaded string " << expr.reg.name << std::endl;
            expr.reg = reg;
        }
        
        std::cout << "\tli $v0 " << (expr.type == "string" ? "4" : (expr.type == "char" ? "11" : "1")) << std::endl;
        std::cout << "\tori $a0 " << expr.reg.name << " 0" << std::endl;
        std::cout << "\tsyscall" << std::endl;
        std::cout << "\t# Finished writing expression to output" << std::endl;
        regPool->release(expr.reg);
        return;
}