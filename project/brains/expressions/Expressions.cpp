#include "Expressions.hpp"
#include <iostream>
#include <string>
#include <vector>

Expression* AndExpression(Expression* a, Expression* b)
{
    Expression* expr = new Expression();
    expr->type = "boolean";
    expr->value = a->value && b->value;
    std::cout << "\t# Anding " << a->value << " and " << b->value;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a->isConstant && b->isConstant){
        expr->isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool.back();
    regPool.pop_back();
    expr->reg = reg;
    expr->isConstant = false;

    if(!a->isConstant && !b->isConstant)
        std::cout << "\tand " << reg.name << " " << a->reg.name << " " << b->reg.name;
    else if(a->isConstant)
        std::cout << "\tandi " << reg.name << " " << b->reg.name << " " << a->value;
    else if(b->isConstant)
        std::cout << "\tandi " << reg.name << " " << a->reg.name << " " << b->value;

    return expr;
}

Expression*int OrExpression(Expression* a, Expression* b)
{
    Expression* expr = new Expression();
    expr->type = "boolean";
    expr->value = a->value || b->value;
    std::cout << "\t# Oring " << a->value << " and " << b->value;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a->isConstant && b->isConstant)
    {
        expr->isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool.back();
    regPool.pop_back();
    expr->reg = reg;
    expr->isConstant = false;

    if(!a->isConstant && !b->isConstant)
        std::cout << "\tor " << reg.name << " " << a->reg.name << " " << b->reg.name;
    else if(a->isConstant)
        std::cout << "\ori " << reg.name << " " << b->reg.name << " " << a->value;
    else if(b->isConstant)
        std::cout << "\tori " << reg.name << " " << a->reg.name << " " << b->value;

    return expr;
}

int EqExpression(int a, int b)
{
    Expression* expr = new Expression();
    expr->type = "boolean";
    expr->value = a->value == b->value;
    std::cout << "\t# Equality check " << a->value << " and " << b->value;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a->isConstant && b->isConstant)
    {
        expr->isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool.back();
    regPool.pop_back();
    expr->reg = reg;
    expr->isConstant = false;

    if(!a->isConstant && !b->isConstant)
        std::cout << "\tseq " << reg.name << " " << a->reg.name << " " << b->reg.name;
    else if(a->isConstant)
        std::cout << "\seqi " << reg.name << " " << b->reg.name << " " << a->value;
    else if(b->isConstant)
        std::cout << "\tseqi " << reg.name << " " << a->reg.name << " " << b->value;

    return expr;
}

int NotEqExpression(int a, int b)
{
    Expression* expr = new Expression();
    expr->type = "boolean";
    expr->value = a->value != b->value;
    std::cout << "\t# Not Equal " << a->value << " and " << b->value;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a->isConstant && b->isConstant)
    {
        expr->isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool.back();
    regPool.pop_back();
    expr->reg = reg;
    expr->isConstant = false;

    if(!a->isConstant && !b->isConstant)
        std::cout << "\tsne " << reg.name << " " << a->reg.name << " " << b->reg.name;
    else if(a->isConstant)
        std::cout << "\snei " << reg.name << " " << b->reg.name << " " << a->value;
    else if(b->isConstant)
        std::cout << "\tsnei " << reg.name << " " << a->reg.name << " " << b->value;
    
    return expr;
}

int LtEqExpression(int a, int b)
{
    Expression* expr = new Expression();
    expr->type = "boolean";
    expr->value = a->value <= b->value;
    std::cout << "\t# <= " << a->value << " and " << b->value;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a->isConstant && b->isConstant)
    {
        expr->isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool.back();
    regPool.pop_back();
    expr->reg = reg;
    expr->isConstant = false;
    if(!a->isConstant && !b->isConstant)
        std::cout << "\tsle " << reg.name << " " << a->reg.name << " " << b->reg.name;
    else if(a->isConstant)
        std::cout << "\slei " << reg.name << " " << b->reg.name << " " << a->value;
    else if(b->isConstant)
        std::cout << "\tslei " << reg.name << " " << a->reg.name << " " << b->value;

    return expr;
}

int GtEqExpression(int a, int b)
{
    Expression* expr = new Expression();
    expr->type = "boolean";
    expr->value = a->value >= b->value;
    std::cout << "\t# >= " << a->value << " and " << b->value;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a->isConstant && b->isConstant)
    {
        expr->isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool.back();
    regPool.pop_back();
    expr->reg = reg;
    expr->isConstant = false;

    if(!a->isConstant && !b->isConstant)
        std::cout << "\tsge " << reg.name << " " << a->reg.name << " " << b->reg.name;
    else if(a->isConstant)
        std::cout << "\sgei " << reg.name << " " << b->reg.name << " " << a->value;
    else if(b->isConstant)
        std::cout << "\tsgei " << reg.name << " " << a->reg.name << " " << b->value;
    
    return expr;
}

int LtExpression(int a, int b)
{
    Expression* expr = new Expression();
    expr->type = "boolean";
    expr->value = a->value < b->value;
    std::cout << "\t# " << a->value << " < " << b->value;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a->isConstant && b->isConstant)
    {
        expr->isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool.back();
    regPool.pop_back();
    expr->reg = reg;
    expr->isConstant = false;

    if(!a->isConstant && !b->isConstant)
        std::cout << "\tslt " << reg.name << " " << a->reg.name << " " << b->reg.name;
    else if(a->isConstant)
        std::cout << "\slti " << reg.name << " " << b->reg.name << " " << a->value;
    else if(b->isConstant)
        std::cout << "\tslti " << reg.name << " " << a->reg.name << " " << b->value;
    
    return expr;
}

int GtExpression(int a, int b)
{
    Expression* expr = new Expression();
    expr->type = "boolean";
    expr->value = a->value > b->value;
    std::cout << "\t# " << a->value << " > " << b->value;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a->isConstant && b->isConstant)
    {
        expr->isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool.back();
    regPool.pop_back();
    expr->reg = reg;
    expr->isConstant = false;

    if(!a->isConstant && !b->isConstant)
        std::cout << "\tsgt " << reg.name << " " << a->reg.name << " " << b->reg.name;
    else if(a->isConstant)
        std::cout << "\sgti " << reg.name << " " << b->reg.name << " " << a->value;
    else if(b->isConstant)
        std::cout << "\tsgti " << reg.name << " " << a->reg.name << " " << b->value;
    
    return expr;
}

int PlusExpression(int a, int b)
{
    Expression* expr = new Expression();
    expr->type = "integer";
    expr->value = a->value + b->value;
    std::cout << "\t# " << a->value << " + " << b->value << std::endl;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a->isConstant && b->isConstant)
    {
        expr->isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool.back();
    regPool.pop_back();
    expr->reg = reg;
    expr->isConstant = false;

    if(!a->isConstant && !b->isConstant)
        std::cout << "\tadd " << reg.name << " " << a->reg.name << " " << b->reg.name << std::endl;
    else if(a->isConstant)
        std::cout << "\addi " << reg.name << " " << b->reg.name << " " << a->value << std::endl;
    else if(b->isConstant)
        std::cout << "\taddi " << reg.name << " " << a->reg.name << " " << b->value << std::endl;
    
    return expr;
}

int MinusExpression(int a, int b)
{
    Expression* expr = new Expression();
    expr->type = "integer";
    expr->value = a->value - b->value;
    std::cout << "\t# " << a->value << " - " << b->value << std::endl;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a->isConstant && b->isConstant)
    {
        expr->isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool.back();
    regPool.pop_back();
    expr->reg = reg;
    expr->isConstant = false;

    if(!a->isConstant && !b->isConstant)
    {
        std::cout << "\tsub " << reg.name << " " << a->reg.name << " " << b->reg.name << std::endl;
    }
    else if(a->isConstant)
    {
        Register reg2 = regPool.back();
        std::cout << "\tli " << reg2.name << " " << a->value << std::endl;
        std::cout << "\tsub " << reg.name << " " << reg2.name << " " << b->reg.name << std::endl;
    }
    else if(b->isConstant)
    {
        std::cout << "\tsubi " << reg.name << " " << a->reg.name << " " << b->value << std::endl;
    }

    return expr;
}

int MultExpression(int a, int b)
{
    Expression* expr = new Expression();
    expr->type = "integer";
    expr->value = a->value * b->value;
    std::cout << "\t# " << a->value << " * " << b->value << std::endl;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a->isConstant && b->isConstant)
    {
        expr->isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool.back();
    regPool.pop_back();
    expr->reg = reg;
    expr->isConstant = false;

    if(!a->isConstant && !b->isConstant)
    {
        std::cout << "\tmult " << a->reg.name << " " << b->reg.name << std::endl;
        std::cout << "\tmflo " << reg.name << std::endl;
    } 
    else if(a->isConstant)
    {
        Register reg2 = regPool.back();
        std::cout << "li " << reg2.name << " " << a->value << std::endl;
        std::cout << "\tmult " << reg2.name << " " << b->reg.name << std::endl;
        std::cout << "\tmflo " << reg.name << std::endl;
    } 
    else if(b->isConstant)
    {
        Register reg2 = regPool.back();
        std::cout << "li " << reg2.name << " " << b->value << std::endl;
        std::cout << "\tmult " << a->reg.name << " " << reg2.name << std::endl;
        std::cout << "\tmflo " << reg.name << std::endl;
    }

    return expr;
}

int DivExpression(int a, int b)
{
    Expression* expr = new Expression();
    expr->type = "integer";
    expr->value = a->value / b->value;
    std::cout << "\t# " << a->value << " / " << b->value << std::endl;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a->isConstant && b->isConstant)
    {
        expr->isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool.back();
    regPool.pop_back();
    expr->reg = reg;
    expr->isConstant = false;

    if(!a->isConstant && !b->isConstant)
    {
        std::cout << "\tdiv " << a->reg.name << " " << b->reg.name << std::endl;
        std::cout << "\tmflo " << reg.name << std::endl;
    } 
    else if(a->isConstant)
    {
        Register reg2 = regPool.back();
        std::cout << "li " << reg2.name << " " << a->value << std::endl;
        std::cout << "\tdiv " << reg2.name << " " << b->reg.name << std::endl;
        std::cout << "\tmflo " << reg.name << std::endl;
    } 
    else if(b->isConstant)
    {
        Register reg2 = regPool.back();
        std::cout << "li " << reg2.name << " " << b->value << std::endl;
        std::cout << "\tdiv " << a->reg.name << " " << reg2.name << std::endl;
        std::cout << "\tmflo " << reg.name << std::endl;
    }

    return expr;
}

int ModExpression(int a, int b)
{
    Expression* expr = new Expression();
    expr->type = "integer";
    expr->value = a->value % b->value;
    std::cout << "\t# " << a->value << " % " << b->value << std::endl;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a->isConstant && b->isConstant)
    {
        expr->isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool.back();
    regPool.pop_back();
    expr->reg = reg;
    expr->isConstant = false;

    if(!a->isConstant && !b->isConstant)
    {
        std::cout << "\tdiv " << a->reg.name << " " << b->reg.name << std::endl;
        std::cout << "\tmfhi " << reg.name << std::endl;
    } 
    else if(a->isConstant)
    {
        Register reg2 = regPool.back();
        std::cout << "li " << reg2.name << " " << a->value << std::endl;
        std::cout << "\tdiv " << reg2.name << " " << b->reg.name << std::endl;
        std::cout << "\tmfhi " << reg.name << std::endl;
    } 
    else if(b->isConstant)
    {
        Register reg2 = regPool.back();
        std::cout << "li " << reg2.name << " " << b->value << std::endl;
        std::cout << "\tdiv " << a->reg.name << " " << reg2.name << std::endl;
        std::cout << "\tmfhi " << reg.name << std::endl;
    }

    return expr;
}

int NotExpression(int a)
{
    Expression* expr = new Expression();
    expr->type = "boolean";
    expr->value = !a->value;
    std::cout << "\t# !" << a->value << std::endl;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a->isConstant && b->isConstant)
    {
        expr->isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool.back();
    regPool.pop_back();
    expr->reg = reg;
    expr->isConstant = false;

    std::cout << "\tnot " << reg.name << " " << a->reg.name << std::endl;

    return expr;
}

int UMinusExpression(int a)
{
    Expression* expr = new Expression();
    expr->type = "integer";
    expr->value = --a->value;
    std::cout << "\t# -" << a->value << std::endl;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a->isConstant && b->isConstant)
    {
        expr->isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool.back();
    regPool.pop_back();
    expr->reg = reg;
    expr->isConstant = false;

    std::cout << "\taddi " << reg.name << " " << a->reg.name << " -1" << std::endl;

    return expr;
}

Expression* IntConstant(int a)
{
    Expression* expr = new Expression();
    expr->isConstant = true;
    expr->type = "integer";
    expr->value  = a;
    return expr;
}

Expression* CharConstant(char a)
{
    Expression* expr = new Expression();
    expr->isConstant = true;
    expr->type = "char";
    expr->value  = a;
    return expr;
}

Expression* StringConstant(char* a)
{
    StringConst* expr = new StringConst();
    expr->isConstant = true;
    expr->type = "string";
    expr->value  = a;
    return expr;
}