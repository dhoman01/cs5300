#ifndef EXPRESSIONS_HPP
#define EXPRESSIONS_HPP 1

#include <memory>
#include <string>
#include <vector>

#include "../utils/structures.hpp"
#include "../utils/RegPool.hpp"
#include "../utils/LookupTable.hpp"

namespace cpsl
{

class Expressions
{
public:
    Expressions() = default;
    Expressions(register_pool pool, symbol_table st)
    {
        regPool = pool;
        symbolTable = st;
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
    int getUID();

    register_pool regPool = nullptr;
    symbol_table symbolTable = nullptr;
};

}


#endif