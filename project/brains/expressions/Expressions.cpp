#include "Expressions.hpp"

Expression* Expressions::AndExpression(Expression* a, Expression* b)
{
    Expression expr;
    expr.type = "boolean";
    expr.value = a->value && b->value;
    std::cout << "\t# Anding " << a->value << " and " << b->value;
    if(a->isConstant && b->isConstant){
        expr.isContant = true;
        return expr;
    }

    Register reg = Expressions::regPool.pop_back();
    expr.reg = reg;
    expr.isConstant = false;
    if(a->isConstant){
        std::cout << "\tandi " << reg.name << " " << b->reg.name << " " << a->value;
        return expr;
    }

    if(b.isConstant){
        std::cout << "\tandi " << reg.name << " " << a->reg.name << " " << b->value;
        return expr;
    }

    std::cout << "\tand " << reg.name << " " << a->reg.name << " " << b->reg.name;
    return &expr;
}

int cpsl::Expressions::OrExpression(int a, int b)
{
    return 0;
}

int cpsl::Expressions::EqExpression(int a, int b)
{
    return 0;
}

int cpsl::Expressions::NotEqExpression(int a, int b)
{
    return 0;
}

int cpsl::Expressions::LtEqExpression(int a, int b)
{
    return 0;
}

int cpsl::Expressions::GtEqExpression(int a, int b)
{
    return 0;
}

int cpsl::Expressions::LtExpression(int a, int b)
{
    return 0;
}

int cpsl::Expressions::GtExpression(int a, int b)
{
    return 0;
}

int cpsl::Expressions::PlusExpression(int a, int b)
{
    return 0;
}

int cpsl::Expressions::MinusExpression(int a, int b)
{
    return 0;
}

int cpsl::Expressions::MultExpression(int a, int b)
{
    return 0;
}

int cpsl::Expressions::DivExpression(int a, int b)
{
    return 0;
}

int cpsl::Expressions::ModExpression(int a, int b)
{
    return 0;
}

int cpsl::Expressions::NotExpression(int a)
{
    return 0;
}

int cpsl::Expressions::UMinusExpression(int a)
{
    return 0;
}

Expression* Expressions::IntConstant(int a)
{
    Expression expr;
    expr.isConstant = true;
    expr.type = "integer";
    expr.value  = a;
}

Expression* Expressions::CharConstant(char a)
{
    Expression expr;
    expr.isConstant = true;
    expr.type = "char";
    expr.value  = a;
}

Expression* Expressions::IntConstant(char* a)
{
    Expression expr;
    expr.isConstant = true;
    expr.type = "string";
    expr.value  = a;
}