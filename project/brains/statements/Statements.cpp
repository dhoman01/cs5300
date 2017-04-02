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
    // because `true` is at 0($gp)
    // and `false` is at 4($gp)
    globalOffset = 8;
    localOffset = 0;
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
    }
    catch (const std::exception& ex)
    {
        // TODO: Create variable for user...
        // throw std::runtime_error("Declaring variables in for loops is not yet supported...");        
        std::shared_ptr<cpsl::Type> intType = std::dynamic_pointer_cast<cpsl::Type>(symbolTable->lookup("integer"));
        cpsl::Statements::StoreSymbol(id, intType);

        std::shared_ptr<cpsl::VariableInfo> var = std::dynamic_pointer_cast<cpsl::VariableInfo>(symbolTable->lookup(id));

        // Get a location for the variable
        var->location = std::to_string(globalOffset) + "($gp)";
        globalOffset += intType->size;

        cpsl::Statements::Assignment(id, expr);        
        varExpr = cpsl::Statements::LoadVariable(id);
        info.var = var;
        info.adjustOffset = true;
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
    regPool->release(cond.reg);
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

    // Adjust offset if needed
    if(info.adjustOffset)
        globalOffset += info.var->type->size;
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
        // If condition is false jump to If End
        std::cout << "\tbeq " << expr.reg.name << " $zero " << label << std::endl;
        regPool->release(expr.reg);
    }
    
    return uid;
};

void cpsl::Statements::IfHeader(int uid)
{
    // Jump to the done label
    std::string dLabel = "ID" + std::to_string(uid);
    std::string eLabel = "IE" + std::to_string(uid);
    std::cout << "\n\t# End If then block (label " << dLabel << ", " << eLabel << ")" << std::endl;
    std::cout << "\tj " << dLabel << std::endl;
    std::cout << eLabel << ":" << std::endl;
};

void cpsl::Statements::IfEnd(std::vector<int> uids)
{
    // For each if/elseif statement create a label to jump to
    for(auto uid : uids)
    {
        std::string label = "ID" + std::to_string(uid);
        std::cout << "\n\t# End If(ElseIf) Statement (label " << label << ")" << std::endl;
        std::cout << label << ":" << std::endl;
    }
};

int cpsl::Statements::RepeatBegin()
{
    // Get UID and print begin label
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

    // Emit warning if a constant expression 
    // that may result in an infinite loop
    if(expr.isConstant)
    {
        if(expr.value)
        {
            std::cerr << "WARN: Repeat condition is always true, your repeat loop only executes once..." << std::endl;
        }
        else
        {
            std::cerr << "WARN: Repeat condition is always false, this may lead to an infinite loop. I'll continue, but I sure hope you know what your doing..." << std::endl;
        }
        std::cout << "\t# Acquiring register and loading " << (expr.value ? "1" : "0") << " into it for constant expression" << std::endl;
        expr.reg = regPool->acquire();
        
        std::cout << "\tli " << expr.reg.name << " " << (expr.value ? "1" : "0") << std::endl;
    }

    // If the condition is false, jump to beginning of loop
    std::cout << "\tbeq " << expr.reg.name << " $zero " << label << std::endl;
    regPool->release(expr.reg);
};

int cpsl::Statements::WhileBegin()
{
    // Get UID and print label
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

    // Emit warning for contant conditional expression
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

    // If the condition is false, jump to the end of the loop
    std::cout << "\tbeq " << expr.reg.name << " $zero " << label;
    regPool->release(expr.reg);
};

void cpsl::Statements::WhileEnd(int uid)
{
    // Print out end of loop label
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
 * - Enter Scope *
 * - Exit Scope  *
 * - Load Var    *
 * - Var Decl    *
 ****************/
void cpsl::Statements::Assignment(std::string id, cpsl::Expression expr)
{
    // Lookup the id in symobal table (throws runtime if not found)
    std::shared_ptr<cpsl::VariableInfo> var = std::dynamic_pointer_cast<cpsl::VariableInfo>(symbolTable->lookup(id));

    // Type check
    if(var->type->id != expr.type)
        throw std::runtime_error("Type mismatch: " + var->type->id + " != " + expr.type);
    
    std::cout << "\n\t# Assigning " << id << " the value";

    // If expr is constant acquire
    // register and load imm
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

    // If the lvalue is a reference parameter
    // acquire a register and update the variables location
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
    std::cout << "\t# Finished assignment of " << id << std::endl;
    return;
}

void cpsl::Statements::ConstDeclaration(std::string id, cpsl::Expression expr)
{
    // Lookup the expressions type
    // and use it to create variable
    std::shared_ptr<cpsl::Type> typeInfo = std::dynamic_pointer_cast<cpsl::Type>(symbolTable->lookup(expr.type));
    cpsl::Statements::StoreSymbol(id, typeInfo);

    // Lookup newly created variable in symbol table (throws runtime if not found)
    std::shared_ptr<cpsl::VariableInfo> var = std::dynamic_pointer_cast<cpsl::VariableInfo>(symbolTable->lookup(id));

    // Load imm and store it at var's location
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
    // Reset local offset
    // Add local scope to symbol table
    localOffset = 0;
    symbolTable->enterScope();
}

void cpsl::Statements::ExitScope()
{
    // Remove local scope from
    // symbol table
    symbolTable->exitScope();
}

cpsl::Expression cpsl::Statements::LoadVariable(std::string id)
{
    // Lookup variable in symbol table (throws runtime if not found)
    std::shared_ptr<cpsl::VariableInfo> var = std::dynamic_pointer_cast<cpsl::VariableInfo>(symbolTable->lookup(id));

    // Grab a Register
    // and emit correct MIPS.
    cpsl::Register reg = regPool->acquire();
    

    std::cout << "\n\t# Loading value from " << var->location << " with type " << var->type->id << std::endl;
    std::cout << "\tlw " << reg.name << " " << var->location << std::endl;

    // If variable is a reference parameter
    // acquire a register and adjust var's location
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
    expr.offset = var->offset;
    expr.isConstant = false;
    expr.type = var->type->id;

    return expr;
}

void cpsl::Statements::VariableDeclaration(std::vector<std::string> ids, std::string typeName)
{
    // Lookup type in symbol table (throws runtime if not found)
    std::shared_ptr<cpsl::Type> type = std::dynamic_pointer_cast<cpsl::Type>(symbolTable->lookup(typeName));

    // Store symbol for each identifer
    // in the given identifier list
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
    // Perform READ on each
    // identifier in list
    for(auto id : ids)
        cpsl::Statements::Read(id);
    return;
}

void cpsl::Statements::StopStatement()
{
    // Emit the MIPS exit syscall
    std::cout << "\n\t# Exiting program" << std::endl;
    std::cout << "\tli $v0 10" << std::endl << "\tsyscall" << std::endl;
    std::cout << "\t# Exit syscall invoked" << std::endl;
    return;
}

void cpsl::Statements::WriteStatement(std::vector<cpsl::Expression> expressionList)
{
    // Perform WRITE for each
    // expression in expression list
    for(auto e : expressionList)
        cpsl::Statements::Write(e);

    // Emit MIPS for newline if
    // addNewline
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

/************************
 * Functions/Procedures *
 * - Func Epilogue      *
 * - Func Prologue      *
 * - Func Precall       *
 * - Func Postcall      *
 * - Make Function      *
 * - Make Params        *
 * - Make Procedure     *
 * - Return Statement   *
 ***********************/
void cpsl::Statements::FunctionEpilogue(std::shared_ptr<cpsl::Procedure> procedure)
{
    // Emit epilogue label
    // Move stack pointer back
    // if localOffset
    // jump to return address
    std::cout << "\n\t# " << procedure->id << " Epilogue" << std::endl;
    std::cout << procedure->id << "Epilogue:" << std::endl;
    if(localOffset != 0) std::cout << "\taddi $sp $sp " << localOffset << std::endl;
    std::cout << "\tjr $ra" << std::endl;
    cpsl::Statements::ExitScope();
}

void cpsl::Statements::FunctionPrologue(std::shared_ptr<cpsl::Procedure> procedure)
{  
    // This line is the end of the function body
    std::cout << "\tj " << procedure->id << "Epilogue" << std::endl;

    // Emit function label
    // Move stack pointer to
    // make room for locals
    // Jump to the body
    std::cout << "\n\t# " << procedure->id << " Prolouge" << std::endl;
    std::cout << procedure->id << ":" << std::endl;
    if(localOffset != 0) std::cout << "\taddi $sp $sp -" <<  localOffset << std::endl;
    std::cout << "\tj " << procedure->id << "Body" << std::endl;;
}

std::pair<int, std::shared_ptr<cpsl::Procedure>> cpsl::Statements::FunctionPrecall(std::string id, std::vector<cpsl::Expression> expressions)
{
    // Lookup id in symbol table (throws runtime if not found)
    auto procedure = std::dynamic_pointer_cast<cpsl::Procedure>(symbolTable->lookup(id));
    auto function = std::dynamic_pointer_cast<cpsl::Function>(procedure);
    auto numParams = procedure->parameters.size();
    auto numExprs = expressions.size();

    // Check that there is the
    // same number of expressions
    // as parameters for the function call
    if(numParams != numExprs)
    {
        std::string type = (function ? "function " : "procedure ");
        throw std::runtime_error("The " + type + id + " is expecting " + std::to_string(numParams) + " parameters not " + std::to_string(numExprs) + "!");
    }
    
    // Room for $fp & $ra, and spill regs
    auto offset = 8 + (regPool->inUse().size() * 4);

    // Room for return value if its a function
    if(function) offset += function->returnValue->type->size;

    // Room for parameters
    for(auto param : procedure->parameters)
        offset += param->type->size;
    
    // Move stackpointer by offset
    std::cout << "\n\t# " << id << " Precall" << std::endl;
    std::cout << "\taddi $sp $sp -" << offset << std::endl;

    auto stackOffset =  0;
    // Store off parameters
    for(int i = 0; i < numParams; i++)
    {
        auto param = procedure->parameters[i];
        auto expr = expressions[i];
        if(param->type->id != expr.type)
            throw std::runtime_error("The type " + expr.type + " cannot be convereted to the type " + param->type->id);
        
        // If expr is constant
        // acquire register and load imm
        if(expr.isConstant)
        {
            expr.reg = regPool->acquire();
            std::cout << "\tli " << expr.reg.name << " " << expr.value << std::endl;
        }

        // If param is a ref
        // load store its location
        if(param->isRef)
        {
            std::cout << "\t# Storing ref to " << param->id << " from expr " << expr.reg.name << std::endl;
            std::cout << "\taddi " << expr.reg.name << " $gp " << expr.offset << std::endl;
        }

        std::cout << "\tsw " << expr.reg.name << " " << stackOffset << "($sp)" << std::endl;
        stackOffset += param->type->size;
        procedure->parameters[i]->reg = expr.reg;
    }

    
    if(function) stackOffset += function->returnValue->type->size;


    // Spill Regsiters that are in use
    for(auto reg : regPool->inUse())
    {
        std::cout << "\tsw " << reg.name << " " << stackOffset << "($sp)" << std::endl;
        stackOffset += 4;
        regPool->spill(reg);
    }

    // Release all remaining registers for function call
    regPool->releaseAll();  

    // Store frame pointer and return address
    // Move frame pointer up to stack pointer
    // jump and link to function
    std::cout << "\tsw $fp " << stackOffset << "($sp)" << std::endl;
    stackOffset += 4;
    std::cout << "\tsw $ra " << stackOffset << "($sp)" << std::endl;
    std::cout << "\tori $fp $sp 0" << std::endl;
    std::cout << "\tjal " << id << std::endl;
    return std::make_pair(stackOffset, procedure);
}

cpsl::Expression cpsl::Statements::FunctionPostcall(std::pair<int, std::shared_ptr<cpsl::Procedure>> precall)
{
    // Try cast to function
    auto function = std::dynamic_pointer_cast<cpsl::Function>(precall.second);
    auto stackOffset = precall.first;
    
    // Load return address and frame pointer
    std::cout << "\t# " << precall.second->id << " Postcall" << std::endl;
    std::cout << "\tlw $ra " << stackOffset << "($sp)" << std::endl;
    stackOffset -= 4;
    std::cout << "\tlw $fp " << stackOffset << "($sp)" << std::endl;
    stackOffset -= 4;

    // Restore spilled registers
    auto spilledRegs = regPool->unspill();
    for(auto rit = spilledRegs.rbegin(); rit != spilledRegs.rend(); ++rit)
    {
        std::cout << "\tlw " << rit->name << " " << stackOffset << "($sp)" << std::endl;
        stackOffset -= 4;
    }

    // Genereate cpsl::Expression
    // for function call return
    cpsl::Expression expr;
    expr.type = "void";
    if(function)
    {
        expr.isConstant = false;
        expr.type = function->returnValue->type->id;
        expr.reg = regPool->acquire();
        std::cout << "\t# Loading return value" << std::endl;
        std::cout << "\tlw " << expr.reg.name << " " << function->returnValue->offset << "($sp)" << std::endl;
    }
    
    // Move stack pointer back
    std::cout << "\taddi $sp $sp " << precall.first + 4 << std::endl;

    // Release registers that were used by
    // function parameters
    for(auto param : precall.second->parameters)
        regPool->release(param->reg);

    return expr;
}

std::shared_ptr<cpsl::Procedure> cpsl::Statements::MakeFunction(std::string id, std::vector<std::shared_ptr<cpsl::Parameter>> params, std::string returnType, bool forward)
{
    // Lookup return type (throws runtime if not found)
    std::shared_ptr<cpsl::Type> type = std::dynamic_pointer_cast<cpsl::Type>(symbolTable->lookup(returnType));

    // Calculate offset for return value
    auto offset = 0;
    if(params.size() > 0)
        offset = params.back()->offset + params.back()->type->size;

    // Create a return
    std::shared_ptr<cpsl::Return> returnValue = std::make_shared<cpsl::Return>();
    returnValue->id = "return";
    returnValue->type = type;
    returnValue->location = std::to_string(offset) + "($fp)";
    returnValue->offset = offset;
    returnValue->function = id;
    offset += type->size;
    std::shared_ptr<cpsl::Function> function;

    // Lookup the function id (for forwarded functions)
    // If not found, catch exception and make new function ptr
    // and store in symbol table
    try
    {
        function = std::dynamic_pointer_cast<cpsl::Function>(symbolTable->lookup(id));
    }
    catch (const std::exception& ex)
    {
        function = std::make_shared<cpsl::Function>(id, params, returnValue);
        symbolTable->store(id, function);
    }
    
    // Set forward state of function
    function->forward = (forward ? cpsl::Forward::EMPTY : cpsl::Forward::DEFINED);

    // If not a forward declaration
    // emit body tag and store
    // parameters in local scope
    if(!forward)
    {
        std::cout << std::endl << id << "Body:" << std::endl;
        cpsl::Statements::EnterScope();
        symbolTable->store(returnValue->id, returnValue);
        for(auto param : params)
            symbolTable->store(param->id, param);
    }

    return function;
}

std::vector<std::shared_ptr<cpsl::Parameter>> cpsl::Statements::MakeParameters(std::string var_ref, std::vector<std::string> ids, std::string typeName)
{
    // Lookup type (throws runtime if not found)
    std::shared_ptr<cpsl::Type> type = std::dynamic_pointer_cast<cpsl::Type>(symbolTable->lookup(typeName));
    std::vector<std::shared_ptr<cpsl::Parameter>> params;

    // Create parameters for each
    // id in the identifier list
    auto offset = 0;
    for(auto id : ids)
    {
        std::shared_ptr<cpsl::Parameter> param = std::make_shared<cpsl::Parameter>();
        param->id = id;
        param->type = type;
        param->isRef = (var_ref == "ref");
        param->location = std::to_string(offset) + "($fp)";
        param->offset = offset;
        offset += type->size;
        std::cout << "\t# (NO MIPS EMITTED) Storing " << (param->isRef ? "reference" : "") << " parameter " << id << " with type " << type->id << " into symbol table" << std::endl;        
        params.push_back(param);
    }

    return params;
}

std::shared_ptr<cpsl::Procedure> cpsl::Statements::MakeProcedure(std::string id, std::vector<std::shared_ptr<cpsl::Parameter>> params, bool forward)
{
    // Lookup up procedure if not found
    // catch runtime and make new procedure ptr
    // then store in symbol table
    std::shared_ptr<cpsl::Procedure> procedure;
    try
    {
        procedure = std::dynamic_pointer_cast<cpsl::Procedure>(symbolTable->lookup(id));
    }
    catch (const std::exception& ex)
    {
        procedure = std::make_shared<cpsl::Procedure>(id, params);
        symbolTable->store(id, procedure);
    }

    // Set forward state
    procedure->forward = (forward ? cpsl::Forward::EMPTY : cpsl::Forward::DEFINED);
    
    // If not a forward declaration
    // emit body label and store params
    if(!forward)
    {
        std::cout << std::endl << id << "Body:" << std::endl;
        cpsl::Statements::EnterScope();
        for(auto param : params)
            symbolTable->store(param->id, param);    
    }    

    return procedure;
}

void cpsl::Statements::ReturnStatement()
{
    // Lookup return in symbol table (throws runtime if not found)
    std::shared_ptr<cpsl::Return> returnValue = std::dynamic_pointer_cast<cpsl::Return>(symbolTable->lookup("return"));
    
    // Emit j to epilouge on return with no value
    std::cout << "\n\t# Returning ";
    std::cout << "\tj " << returnValue->function << "Epilogue" << std::endl;
}

void cpsl::Statements::ReturnStatement(cpsl::Expression expr)
{
    // Lookup return in symbol table (throws runtime if not found)
    std::shared_ptr<cpsl::Return> returnValue = std::dynamic_pointer_cast<cpsl::Return>(symbolTable->lookup("return"));

    // Type check return value
    if(returnValue->type->id != expr.type)
        throw std::runtime_error("Expecting to return type " + returnValue->type->id + " not " + expr.type + "!");
    
    std::cout << "\n\t# Returning ";
    // If constant, acquire
    // register and load imm
    if(expr.isConstant)
    {
        std::cout << expr.value << std::endl;
        expr.reg = regPool->acquire();
        std::cout << "\tli " << expr.reg.name << " " << expr.value << std::endl;
    }
    else
    {
        std::cout << expr.reg.name << std::endl;
    }
    
    // Store the return value and jump to epilogue
    std::cout << "\tsw " << expr.reg.name << " " << returnValue->location << std::endl;
    std::cout << "\tj " << returnValue->function << "Epilogue" << std::endl;
    regPool->release(expr.reg);
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
    // Lookup variable in symbal table (throws runtime if not found)
    std::shared_ptr<cpsl::VariableInfo> var = std::dynamic_pointer_cast<cpsl::VariableInfo>(symbolTable->lookup(id));

    // Type check
    if(var->type->id != "integer" && var->type->id != "char")
        throw std::runtime_error("Could not read into variable '" + id + "', read() is only defined for integer and character types. Not " + var->type->id);

    // Emit MIPS sycall to read from stdin
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
    // Create a cpsl::VariableInfo struct
    std::shared_ptr<cpsl::VariableInfo> var = std::make_shared<cpsl::VariableInfo>();
    var->id = id;
    var->type = type;

    // Set location based on current scope
    // adjust approriate offset
    if(symbolTable->inLocalScope())
    {
        localOffset += type->size;
        var->location = std::to_string(-1 * localOffset) + "($fp)";
        var->offset = -1 * localOffset;
    }
    else
    {
        var->location = std::to_string(globalOffset) + "($gp)";
        var->offset = globalOffset;
        globalOffset += type->size;
    }

    // Store in symbol table (throws if id already exists)
    symbolTable->store(id, var);
    std::cout << "\t# (NO MIPS EMITTED) Storing symbol " << id << " with type " << type->id << " into symbol table" << std::endl;
    return;
}

void cpsl::Statements::Write(cpsl::Expression expr)
{
        std::cout << "\n\t# Writing expression to output" << std::endl;
        
        // If constant acquire register and load imm
        if(expr.isConstant)
        {
            expr.reg = regPool->acquire();
            
            std::cout << "\tli " << expr.reg.name << " " << expr.value << std::endl;
        }

        // If expr is a string
        // load string from address
        if(expr.type == "string")
        {
            cpsl::Register reg = regPool->acquire();
            
            std::cout << "\t# Loading string const" << std::endl;
            std::cout << "\tla " << reg.name << " " << expr.reg.name << std::endl;
            std::cout << "\t# Loaded string " << expr.reg.name << std::endl;
            expr.reg = reg;
            // DO NOT RELEASE
            // register as it is an address (i.e. S1)
        }
        
        // Emit MIPS sycall to print to stdout
        std::cout << "\tli $v0 " << (expr.type == "string" ? "4" : (expr.type == "char" ? "11" : "1")) << std::endl;
        std::cout << "\tori $a0 " << expr.reg.name << " 0" << std::endl;
        std::cout << "\tsyscall" << std::endl;
        std::cout << "\t# Finished writing expression to output" << std::endl;
        regPool->release(expr.reg);
        return;
}