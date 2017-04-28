#include "Statements.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

/**************
 *   PUBLIC   *
 *************/ 
cpsl::Statements::Statements(cpsl::register_pool pool, cpsl::symbol_table table, bool addNew)
{
    globalOffset = 0;
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
    auto intType = std::dynamic_pointer_cast<cpsl::Type>(symbolTable->lookup("integer"));
    if(expr.type != intType)
        throw std::runtime_error("Type mismatch: " + expr.type->id + " != integer in for loop condition");

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
        auto lvalue = std::dynamic_pointer_cast<cpsl::LValue>(symbolTable->lookup(id));
        cpsl::Statements::Assignment(lvalue, expr);
        varExpr = cpsl::Statements::MakeLValueExpression(lvalue);
        info.lvalue = lvalue;
    }
    catch (const std::exception& ex)
    {
        // TODO: Create variable for user...
        // throw std::runtime_error("Declaring variables in for loops is not yet supported...");        
        cpsl::Statements::StoreSymbol(id, intType);

        auto lvalue = std::dynamic_pointer_cast<cpsl::LValue>(symbolTable->lookup(id));

        // Get a location for the variable
        lvalue->location = "$gp";
        lvalue->offset = globalOffset;
        globalOffset += intType->size;

        cpsl::Statements::Assignment(lvalue, expr);        
        varExpr = cpsl::Statements::MakeLValueExpression(lvalue);
        info.lvalue = lvalue;
        info.adjustOffset = true;
    }

    // Get a uid for for loop
    auto uid = cpsl::Statements::getUID();
    auto label = "FB" + std::to_string(uid);
    std::cout << "\t# Start of Loop" << std::endl;
    std::cout << label << ":" << std::endl;
    info.varExpr = varExpr;
    info.uid = uid;
    return info;
};

void cpsl::Statements::ForHeader(cpsl::ForHeaderInfo& info, cpsl::Expression cond)
{
    // Type check
    if(cond.type->id != "integer")
        throw std::runtime_error("Type mismatch: " + cond.type->id + " != integer in for loop condition");

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
    std::cout << "\t# Incrementing counter " << info.lvalue->id << std::endl;
    std::cout << "\taddi " << info.varExpr.reg.name << " " << info.varExpr.reg.name << " " << info.optTo << std::endl;
    std::cout << "\tsw " << info.varExpr.reg.name << " " << info.lvalue->getLocation() << std::endl;
    std::cout << "\tj FB" << info.uid << std::endl;
    std::cout << "FE" << info.uid << ":" << std::endl;
    std::cout << "\t# End of For Statement" << std::endl;

    // Release registers
    regPool->release(info.varExpr.reg);
    regPool->release(info.cond.reg);

    // Adjust offset if needed
    if(info.adjustOffset)
    {
        globalOffset += info.lvalue->type->size;
        symbolTable->remove(info.lvalue->id);
    }
};

int cpsl::Statements::IfBegin(cpsl::Expression expr)
{
    // Type check
    if(expr.type->id != "boolean")
        throw std::runtime_error("Expecting a boolean expression as the conditional for an If Statment, not " + expr.type->id);

    // Get UID for if statement
    auto uid = cpsl::Statements::getUID();
    auto label = "IE" + std::to_string(uid);
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
    auto dLabel = "ID" + std::to_string(uid);
    auto eLabel = "IE" + std::to_string(uid);
    std::cout << "\n\t# End If then block (label " << dLabel << ", " << eLabel << ")" << std::endl;
    std::cout << "\tj " << dLabel << std::endl;
    std::cout << eLabel << ":" << std::endl;
};

void cpsl::Statements::IfEnd(std::vector<int> uids)
{
    // For each if/elseif statement create a label to jump to
    for(auto uid : uids)
    {
        auto label = "ID" + std::to_string(uid);
        std::cout << "\n\t# End If(ElseIf) Statement (label " << label << ")" << std::endl;
        std::cout << label << ":" << std::endl;
    }
};

int cpsl::Statements::RepeatBegin()
{
    // Get UID and print begin label
    auto uid = cpsl::Statements::getUID();
    auto label = "RP" + std::to_string(uid);
    std::cout << "\n\t# Begin Repeat Statement (label " << label << ")" << std::endl;
    std::cout << label << ":" << std::endl;
    return uid;
};

void cpsl::Statements::RepeatEnd(int uid, cpsl::Expression expr)
{
    // Type check
    if(expr.type->id != "boolean")
        throw std::runtime_error("Expecting a boolean expression for the conditional of a repeat statement, not " + expr.type->id);

    auto label = "RP" + std::to_string(uid);
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
    auto uid = cpsl::Statements::getUID();
    auto label = "WB" + std::to_string(uid);
    std::cout << "\n\t# Beginning While Loop (label " << label << ")" << std::endl;
    std::cout << label << ":" << std::endl;
    return uid;
};

void cpsl::Statements::WhileHeader(int uid, cpsl::Expression expr)
{
    // Type check
    if(expr.type->id != "boolean")
        throw std::runtime_error("Expecting a boolean expression fo the conditional of a While Statement, not " + expr.type->id);

    auto label = "WE" + std::to_string(uid);
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
    auto bLabel = "WB" + std::to_string(uid);
    auto eLabel = "WE" + std::to_string(uid);
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
void cpsl::Statements::Assignment(std::shared_ptr<cpsl::LValue> lvalue, cpsl::Expression expr)
{
    // Type check
    if(lvalue->type != expr.type)
        throw std::runtime_error("Type mismatch: " + lvalue->type->id + " != " + expr.type->id);
    
    std::cout << "\n\t# Assigning " << lvalue->id << " the value";


    // If expr is constant acquire
    // register and load imm
    if(expr.isConstant)
    {
        expr.reg = regPool->acquire();
        
        std::cout << " " << lvalue->id << std::endl;
        std::cout << "\tli " << expr.reg.name << " " << expr.value << std::endl;
    } 
    else
    {
        std::cout << " at " << expr.reg.name << std::endl;
    }

    // If the lvalue is a reference parameter
    // acquire a register and update the variables location
    auto param = std::dynamic_pointer_cast<cpsl::Parameter>(lvalue);
    auto array = std::dynamic_pointer_cast<cpsl::Array>(lvalue->type);
    auto record = std::dynamic_pointer_cast<cpsl::Record>(lvalue->type);
    if(param && param->isRef)
    {
        auto ref = regPool->acquire();
        std::cout << "\t# Storing value to reference" << std::endl;
        std::cout << "\tlw " << ref.name << " " << param->getLocation() << std::endl;
        std::cout << "\tsw " << expr.reg.name << " 0(" << ref.name << ")" << std::endl;
        regPool->release(ref);
    }
    else if(array || record)
    {
        cpsl::Statements::DeepCopy(expr.reg.name, lvalue->location, lvalue->type->size, lvalue->offset);
    }
    else if(lvalue->type == symbolTable->lookup("string"))
    {
        auto reg = regPool->acquire();
        std::cout << "la " << reg.name << " " << expr.reg.name << std::endl;
        std::cout << "sw " << reg.name << " " << lvalue->getLocation() << std::endl;
        expr.reg = reg;
    }
    else
    {
        std::cout << "\tsw " << expr.reg.name << " " << lvalue->getLocation() << std::endl;
    }

    regPool->release(expr.reg);
    std::cout << "\t# Finished assignment of " << lvalue->id << std::endl;
    return;
}

void cpsl::Statements::ConstDeclaration(std::string id, cpsl::Expression expr)
{
    if(!expr.isConstant)
        throw std::runtime_error("Constants can only be defined by constant expressions!");


    auto constant = std::make_shared<cpsl::ConstantLValue>();
    constant->id = id;
    constant->expr = expr;
    constant->type = expr.type;

    symbolTable->store(id, constant);

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

std::shared_ptr<cpsl::LValue> cpsl::Statements::LoadArrayElement(std::shared_ptr<cpsl::LValue> lvalue, cpsl::Expression index)
{
    std::cout << "\t# Loading array member from " << lvalue->id;
    auto array = std::dynamic_pointer_cast<cpsl::Array>(lvalue->type);
    if(!array)
        throw std::runtime_error("The operator [] is only defined for array types, not " + lvalue->type->id);


    auto elementLvalue = std::make_shared<cpsl::LValue>();
    elementLvalue->type = array->type;
    elementLvalue->offset = lvalue->offset;
    elementLvalue->location = lvalue->location;

    auto param = std::dynamic_pointer_cast<cpsl::Parameter>(lvalue);

    if(index.isConstant)
    {
        std::cout << " and index of " << index.value << std::endl;
        elementLvalue->offset += (index.value - array->low) * array->type->size;
    }
    else
    {
        auto reg = regPool->acquire();
        std::cout << " and index at " << index.reg.name << std::endl;
        std::cout << "\t# Shifting index of array " << lvalue->id << std::endl;
        std::cout << "\taddi " << index.reg.name << " " << index.reg.name << std::string(array->low == 0 ? " " : " -") << array->low << std::endl;
        std::cout << "\tli " << reg.name << " " << array->type->size << std::endl;
        std::cout << "\tmult " << index.reg.name << " " << reg.name << std::endl;
        std::cout << "\tmflo " << index.reg.name << std::endl;
        if(param && param->isRef)
        {
            std::cout << "\t# Loading reference" << std::endl;
            std::cout << "\tlw " << reg.name << " " << param->offset << "(" << lvalue->location << ")" << std::endl;
            std::cout << "\tadd " << index.reg.name << " " << index.reg.name << " " << reg.name << std::endl;        
        }
        else
        {
            std::cout << "\tadd " << index.reg.name << " " << index.reg.name << " " << lvalue->location << std::endl;
        }
        elementLvalue->location = index.reg.name;
        regPool->release(reg);
    }

    return elementLvalue;    
}


std::shared_ptr<cpsl::LValue> cpsl::Statements::LoadRecordMember(std::shared_ptr<cpsl::LValue> lvalue, std::string id)
{
    auto record = std::dynamic_pointer_cast<cpsl::Record>(lvalue->type);
    if(!record)
        throw std::runtime_error("Expecting a record type for the lvalue of the . operator, not " + lvalue->type->id);
    
    auto memberLvalue = std::make_shared<cpsl::LValue>();
    auto field = record->members.lookup(id);
    memberLvalue->offset = field->offset + lvalue->offset;
    memberLvalue->type = field->type;
    std::cout << "\t# Loading Member of Record" << std::endl;
    auto param = std::dynamic_pointer_cast<cpsl::Parameter>(lvalue);
    if(param && param->isRef)
    {
        auto reg = regPool->acquire();
        std::cout << "\t# Loading reference to object" << std::endl;
        std::cout << "\tlw " << reg.name << " " << param->offset << "(" << lvalue->location << ")" << std::endl;
        memberLvalue->location = reg.name;
    }
    else
    {
        memberLvalue->location = lvalue->location;
    }
    std::cout << "\t# " << lvalue->id << "." << id << " is at " << memberLvalue->location << std::endl;
    return memberLvalue;
}

std::shared_ptr<cpsl::LValue> cpsl::Statements::LoadVariable(std::string id)
{
    // Lookup variable in symbol table (throws runtime if not found)
    std::cout << "\t# Loading lvalue " << id << " from symbol table" << std::endl;
    auto lvalue = std::dynamic_pointer_cast<cpsl::LValue>(symbolTable->lookup(id));
    if(!lvalue) throw std::runtime_error("Failed to load lvalue with id " + id + "... Maybe your passing a function as a parameter instead of passing its return value?");
    return lvalue;
}

cpsl::Expression cpsl::Statements::MakeLValueExpression(std::shared_ptr<cpsl::LValue> lvalue)
{
    // Check if the lvalue is constant
    auto constant = std::dynamic_pointer_cast<cpsl::ConstantLValue>(lvalue);

    if(constant)
    {
        std::cout << "\t# Loaded constant lvalue " << lvalue->id << " with value " << constant->expr.value << " and type " << constant->expr.type->id << std::endl;
        return constant->expr;
    }

    // Grab a Register
    // and emit correct MIPS.
    auto reg = regPool->acquire();   

    std::cout << "\t# Loading value from " << lvalue->getLocation() << " with type " << lvalue->type->id << std::endl;
    std::cout << "\tlw " << reg.name << " " << lvalue->getLocation() << std::endl;

    // If variable is a reference parameter
    // acquire a register and adjust lvalue's location
    auto param = std::dynamic_pointer_cast<cpsl::Parameter>(lvalue);
    if(param && param->isRef)
    {
        auto ref = regPool->acquire();
        std::cout << "\t# Loading reference" << std::endl;
        std::cout << "\tlw " << ref.name << " 0(" << reg.name << ")" << std::endl;
        regPool->release(reg);
        reg = ref;
    } else if(std::dynamic_pointer_cast<cpsl::Array>(lvalue->type) || std::dynamic_pointer_cast<cpsl::Record>(lvalue->type))
    {
        std::cout << "\t# Loading array location" << std::endl;
        std::cout << "\taddi " << reg.name << " " << lvalue->location << " " << lvalue->offset << std::endl;
    }
    std::cout << "\t# Loaded value from " << lvalue->id << std::endl;

    // Generate cpsl::Expression for loaded variable
    cpsl::Expression expr;
    expr.reg = reg;
    expr.offset = lvalue->offset;
    expr.isConstant = false;
    expr.type = lvalue->type;

    return expr;
}

void cpsl::Statements::VariableDeclaration(std::vector<std::string> ids, std::shared_ptr<cpsl::Type> type)
{
    // Store symbol for each identifer
    // in the given identifier list
    for(auto id : ids)
        cpsl::Statements::StoreSymbol(id, type);

    return;
}

void cpsl::Statements::PrintDebugLine(int line, int col)
{
    std::cout <<"\n\t# DEBUG: " << line << ":" << col << std::endl;    
}

void cpsl::Statements::ResetParamOffset()
{
    cpsl::Statements::paramOffset = 0;
}

/*********************
 * Types             *
 * - Type Lookup     *
 * - Declare Type    *
 * - Make Array      *
 * - Make Record     *
 * - Make Fields     *
 ********************/
std::shared_ptr<cpsl::Type> cpsl::Statements::TypeLookup(std::string id)
{
    return std::dynamic_pointer_cast<cpsl::Type>(symbolTable->lookup(id));
}

void cpsl::Statements::DeclareType(std::string id, std::shared_ptr<cpsl::Type> type)
{
    symbolTable->store(id, type);
}

std::shared_ptr<cpsl::Array> cpsl::Statements::MakeArray(cpsl::Expression low, cpsl::Expression high, std::shared_ptr<cpsl::Type> type)
{
    if(!low.isConstant || !high.isConstant)
        throw std::runtime_error("Array endpoints must be constant values!");

    auto array = std::make_shared<cpsl::Array>();
    array->low = low.value;
    array->high = high.value;
    array->size = (array->high - array->low + 1) * type->size;
    array->type = type;

    std::cout << "\t# Making array type with size " << array->size << " of " << array->type->id << "s" << std::endl; 
    
    return array;
}

std::shared_ptr<cpsl::Record> cpsl::Statements::MakeRecord(std::vector<cpsl::Field> fields)
{
    auto record = std::make_shared<cpsl::Record>();
    record->members.enterScope();
    for(auto f : fields)
    {
        f.offset = record->size;
        record->size += f.type->size;
        auto shared = std::make_shared<cpsl::Field>();
        shared->offset = f.offset;
        shared->id = f.id;
        shared->type = f.type;
        record->members.store(f.id, shared); 
    }

    symbolTable->store(record->id, record);


    return record;
}

std::vector<cpsl::Field> cpsl::Statements::MakeFields(std::vector<std::string> identifierList, std::shared_ptr<cpsl::Type> type)
{
    std::vector<cpsl::Field> fields;
    for(auto id : identifierList)
    {
        cpsl::Field field;
        field.id = id;
        field.type = type;
        fields.push_back(field);
    }

    return fields;
}

/*********************
 * Simple Statements *
 * - Read Statement  *
 * - Stop Statement  *
 * - Write Statement *
 ********************/
void cpsl::Statements::ReadStatement(std::vector<std::shared_ptr<cpsl::LValue>> lvalueList)
{
    // Perform READ on each
    // identifier in list
    for(auto lvalue : lvalueList)
        cpsl::Statements::Read(lvalue);
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
    regPool->releaseAll();
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
        throw std::runtime_error("The " + std::string(function ? "function" : "procedure") + " " + id + " is expecting " + std::to_string(numParams) + " parameters not " + std::to_string(numExprs) + "!");
    
    // Room for $fp & $ra, and spill regs
    auto offset = 8 + (regPool->inUse().size() * 4);

    // Room for return value if its a function
    if(function) offset += function->returnValue->type->size;

    // Room for parameters
    for(auto param : procedure->parameters)
        offset += (param->isRef ? 4 : param->type->size);
    
    // Move stackpointer by offset
    std::cout << "\n\t# " << id << " Precall" << std::endl;
    std::cout << "\taddi $sp $sp -" << offset << std::endl;

    auto stackOffset =  0;
    // Store off parameters
    for(int i = 0; i < numParams; i++)
    {
        auto param = procedure->parameters[i];
        auto expr = expressions[i];
        if(param->type != expr.type)
        {
            std::stringstream ss;
            ss << "Expecting " << id << " to be called like `" << id << "(";
            for(auto p : procedure->parameters)
                ss << p->type->id << std::string(p != procedure->parameters.back() ? "," : ")`\n");
            ss << "\t\tbut got `" << id << "(";
            for(auto e : expressions)
                ss << e.type->id << std::string(e != expressions.back() ? "," : ")`");
            throw std::runtime_error(ss.str());
        }

        if(param->isRef && expr.isConstant)
            throw std::runtime_error("Constants cannot be references. Parameter " + std::to_string(i + 1) + " of " + id + " is a reference.");
        
        // If expr is constant
        // acquire register and load imm
        if(expr.isConstant && expr.type->id != "string")
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
            std::cout << "\tsw " << expr.reg.name << " " << stackOffset << "($sp)" << std::endl;
            stackOffset += 4;            
        }
        else if(std::dynamic_pointer_cast<cpsl::Array>(param->type) || std::dynamic_pointer_cast<cpsl::Record>(param->type))
        {
            cpsl::Statements::DeepCopy(expr.reg.name, "$sp", param->type->size, stackOffset);
            stackOffset += param->type->size;
        }
        else
        {
            if(expr.type->id == "string")
            {
                cpsl::Statements::LoadStringExp(expr);
            }
            std::cout << "\tsw " << expr.reg.name << " " << stackOffset << "($sp)" << std::endl;
            stackOffset += param->type->size;
        }

        procedure->parameters[i]->reg = expr.reg;
    }

    
    if(function) stackOffset += function->returnValue->type->size;


    // Spill Regsiters that are in use
    std::cout << "\n\t# Spilling Registers" << std::endl;
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
    expr.type = nullptr;
    if(function)
    {
        expr.isConstant = false;
        expr.type = function->returnValue->type;
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

std::shared_ptr<cpsl::Procedure> cpsl::Statements::MakeFunction(std::string id, std::vector<std::shared_ptr<cpsl::Parameter>> params, std::shared_ptr<cpsl::Type> returnType, bool forward)
{
    // Calculate offset for return value
    auto offset = 0;
    if(params.size() > 0)
        offset = params.back()->offset + params.back()->type->size;

    // Create a return
    auto returnValue = std::make_shared<cpsl::Return>();
    returnValue->id = "return";
    returnValue->type = returnType;
    returnValue->location = "$fp";
    returnValue->offset = offset;
    returnValue->function = id;
    offset += returnType->size;
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

std::vector<std::shared_ptr<cpsl::Parameter>> cpsl::Statements::MakeParameters(std::string var_ref, std::vector<std::string> ids, std::shared_ptr<cpsl::Type> type)
{
    std::vector<std::shared_ptr<cpsl::Parameter>> params;

    // Create parameters for each
    // id in the identifier list
    for(auto id : ids)
    {
        try
        {
            auto f = symbolTable->lookup(id);
            std::cerr << "WARN: The parameter " << id << " of hides a global variable of the same id." << std::endl;
        }
        catch (const std::exception& ex)
        {
            // Do nothing
        }
        auto param = std::make_shared<cpsl::Parameter>();
        param->id = id;
        param->type = type;
        param->isRef = (var_ref == "ref");
        param->location = "$fp";
        param->offset = cpsl::Statements::paramOffset;
        cpsl::Statements::paramOffset += type->size;
        std::cout << "\t# (NO MIPS EMITTED) Storing " << (param->isRef ? "reference" : "") << " parameter " << id << " with type " << type->id << " and offset of " << param->offset << " into symbol table" << std::endl;        
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

    // Create a return
    auto returnValue = std::make_shared<cpsl::Return>();
    returnValue->id = "return";
    returnValue->type = nullptr;
    returnValue->location = "$fp";
    returnValue->offset = 0;
    returnValue->function = id;
    
    // If not a forward declaration
    // emit body label and store params
    if(!forward)
    {
        std::cout << std::endl << id << "Body:" << std::endl;
        cpsl::Statements::EnterScope();
        symbolTable->store("return", returnValue);
        for(auto param : params)
            symbolTable->store(param->id, param);    
    }    

    return procedure;
}

void cpsl::Statements::ReturnStatement()
{
    // Lookup return in symbol table (throws runtime if not found)
    auto returnValue = std::dynamic_pointer_cast<cpsl::Return>(symbolTable->lookup("return"));
    
    // Emit j to epilouge on return with no value
    std::cout << "\n\t# Returning " << std::endl;
    std::cout << "\tj " << returnValue->function << "Epilogue" << std::endl;
}

void cpsl::Statements::ReturnStatement(cpsl::Expression expr)
{
    // Lookup return in symbol table (throws runtime if not found)
    auto returnValue = std::dynamic_pointer_cast<cpsl::Return>(symbolTable->lookup("return"));

    // Type check return value
    if(returnValue->type != expr.type)
        throw std::runtime_error("Expecting to return type " + returnValue->type->id + " not " + expr.type->id + "!");
    
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
    std::cout << "\tsw " << expr.reg.name << " " << returnValue->getLocation() << std::endl;
    std::cout << "\tj " << returnValue->function << "Epilogue" << std::endl;
    regPool->release(expr.reg);
}


/***********
 * PRIVATE *
 **********/
void cpsl::Statements::DeepCopy(std::string src, std::string dest, std::size_t size, int offset)
{
    std::cout << "\t# Preforming Deep Copy" << std::endl;
    for(int i = 0; i < size; i += 4)
    {
        auto reg = regPool->acquire();
        std::cout << "\tlw " << reg.name << " " << i << "(" << src << ")" << std::endl;
        std::cout << "\tsw " << reg.name << " " << i + offset << "(" << dest << ")" << std::endl;
        regPool->release(reg);
    }
    std::cout << "\t# Deep Copy Finished" << std::endl;
}

int cpsl::Statements::getUID()
{
    static std::size_t label = 0;
    return ++label;
}

void cpsl::Statements::Read(std::shared_ptr<cpsl::LValue> lvalue)
{
    // Type check
    if(lvalue->type->id != "integer" && lvalue->type->id != "char")
        throw std::runtime_error("Could not read into variable '" + lvalue->id + "', read() is only defined for integer and character types. Not " + lvalue->type->id);

    // Emit MIPS sycall to read from stdin
    std::cout << "\n\t# Reading in input from user" << std::endl;
    std::cout << "\tli $v0 " << (lvalue->type->id == "integer" ? "5" : "12") << std::endl << "\tsyscall" << std::endl;
    std::cout << "\tsw $v0 " << lvalue->getLocation() << std::endl;
    std::cout << "\taddi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR." << std::endl;
    std::cout << "\taddi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character." << std::endl;
    std::cout << "\tsyscall" << std::endl;
    std::cout << "\t# Finished reading input. Stored input in " << lvalue->id << " at " << lvalue->getLocation() << std::endl;
    return;
}

void cpsl::Statements::StoreSymbol(std::string id, std::shared_ptr<cpsl::Type> type)
{
    // Create a cpsl::LValue struct
    auto lvalue = std::make_shared<cpsl::LValue>();
    lvalue->id = id;
    lvalue->type = type;

    // Set location based on current scope
    // adjust approriate offset
    if(symbolTable->inLocalScope())
    {
        localOffset += type->size;
        lvalue->location = "$fp";
        lvalue->offset = -1 * localOffset;
    }
    else
    {
        lvalue->location = "$gp";
        lvalue->offset = globalOffset;
        globalOffset += type->size;
    }

    // Store in symbol table (throws if id already exists)
    symbolTable->store(id, lvalue);
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

        if(expr.type->id == "string" && expr.reg.name[0] == 'S')
        {
            cpsl::Statements::LoadStringExp(expr);
        }
        
        // Emit MIPS sycall to print to stdout
        std::cout << "\tli $v0 " << (expr.type->id == "string" ? "4" : (expr.type->id == "char" ? "11" : "1")) << std::endl;
        std::cout << "\tori $a0 " << expr.reg.name << " 0" << std::endl;
        std::cout << "\tsyscall" << std::endl;
        std::cout << "\t# Finished writing expression to output" << std::endl;
        regPool->release(expr.reg);
        return;
}

void cpsl::Statements::LoadStringExp(cpsl::Expression& expr)
{
    // If expr is a string
    // load string from address
    cpsl::Register reg = regPool->acquire();
    
    std::cout << "\t# Loading string const" << std::endl;
    std::cout << "\tla " << reg.name << " " << expr.reg.name << std::endl;
    std::cout << "\t# Loaded string " << expr.reg.name << std::endl;
    expr.reg = reg;
    // DO NOT RELEASE the expr's previous
    // register as it is an address (i.e. S1)
}