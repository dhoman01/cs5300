#ifndef EXPRESSIONS_HPP
#define EXPRESSIONS_HPP 1

#include <memory>
#include <string>
#include <vector>

#include "../utils/structures.hpp"
#include "../utils/RegPool.hpp"

namespace cpsl
{

class Expressions
{
public:
    Expressions() = default;
    Expressions(std::shared_ptr<RegPool> pool)
    {
        regPool = pool;
    };
    
    // Boolean Expressions
    Expression AndExpression(Expression, Expression);
    Expression OrExpression(Expression, Expression);
    Expression EqExpression(Expression, Expression);
    Expression NotEqExpression(Expression, Expression);
    Expression LtEqExpression(Expression, Expression);
    Expression GtEqExpression(Expression, Expression);
    Expression LtExpression(Expression, Expression);
    Expression GtExpression(Expression, Expression);

    // Arithmetic Expressions
    Expression PlusExpression(Expression, Expression);
    Expression MinusExpression(Expression, Expression);
    Expression MultExpression(Expression, Expression);
    Expression DivExpression(Expression, Expression);
    Expression ModExpression(Expression, Expression);

    // Unary Expressions
    Expression NotExpression(Expression);
    Expression UMinusExpression(Expression);
    Expression ChrExpression(Expression);
    Expression OrdExpression(Expression);
    Expression PredExpression(Expression);
    Expression SuccExpression(Expression);

    // Constant Expressions
    Expression IntConstant(std::string);
    Expression CharConstant(char);
private:
    std::shared_ptr<RegPool> regPool = nullptr;
};

}


#endif