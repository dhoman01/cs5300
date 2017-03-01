#ifndef EXPRESSIONS_HPP
#define EXPRESSIONS_HPP 1

#include <memory>
#include <string>
#include <vector>

#include "../utils/structures.hpp"

namespace cpsl
{

class Expressions
{
public:
    Expressions() = default;
    Expressions(std::shared_ptr<std::vector<Register>> pool)
    {
        regPool = pool;
    };
    
    Expression AndExpression(Expression, Expression);
    Expression OrExpression(Expression, Expression);
    Expression EqExpression(Expression, Expression);
    Expression NotEqExpression(Expression, Expression);
    Expression LtEqExpression(Expression, Expression);
    Expression GtEqExpression(Expression, Expression);
    Expression LtExpression(Expression, Expression);
    Expression GtExpression(Expression, Expression);
    Expression PlusExpression(Expression, Expression);
    Expression MinusExpression(Expression, Expression);
    Expression MultExpression(Expression, Expression);
    Expression DivExpression(Expression, Expression);
    Expression ModExpression(Expression, Expression);
    Expression NotExpression(Expression);
    Expression UMinusExpression(Expression);
    Expression ChrExpression(Expression);
    Expression OrdExpression(Expression);
    Expression PredExpression(Expression);
    Expression SuccExpression(Expression);
    Expression IntConstant(std::string);
    Expression CharConstant(char);
private:
    std::shared_ptr<std::vector<Register>> regPool = nullptr;
};

}


#endif