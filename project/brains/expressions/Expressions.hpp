#ifndef EXPRESSIONS_HPP
#define EXPRESSIONS_HPP

#include <string>
#include <vector>
#include <memory>

#include "../utils/structures.hpp"

namespace cpsl
{

class Expressions
{
public:
    Expressions() = default;
    Expressions(std::shared_ptr<std::vector<Register>> pool, std::string file = "")
    {
        regPool = pool;
        output_file = file;
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
    Expression IntConstant(std::string);
    Expression CharConstant(std::string);
    Expression ChrExpression(Expression);
    Expression OrdExpression(Expression);
    Expression PredExpression(Expression);
    Expression SuccExpression(Expression);
private:
    std::shared_ptr<std::vector<Register>> regPool = nullptr;
    std::string output_file = "";
};

}


#endif