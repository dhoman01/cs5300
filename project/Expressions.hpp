#ifndef EXPRESSIONS_HPP
#define EXPRESSIONS_HPP

#include <string>
#include <vector>

#include "structures.hpp"

namespace cpsl
{

class Expressions
{
public:
    Expressions() = default;
    Expressions(std::vector<Register>* pool, std::string file = "") : regPool(pool), output_file(file) {};
    cpsl::Expression AndExpression(cpsl::Expression, cpsl::Expression);
    cpsl::Expression OrExpression(cpsl::Expression, cpsl::Expression);
    cpsl::Expression EqExpression(cpsl::Expression, cpsl::Expression);
    cpsl::Expression NotEqExpression(cpsl::Expression, cpsl::Expression);
    cpsl::Expression LtEqExpression(cpsl::Expression, cpsl::Expression);
    cpsl::Expression GtEqExpression(cpsl::Expression, cpsl::Expression);
    cpsl::Expression LtExpression(cpsl::Expression, cpsl::Expression);
    cpsl::Expression GtExpression(cpsl::Expression, cpsl::Expression);
    cpsl::Expression PlusExpression(cpsl::Expression, cpsl::Expression);
    cpsl::Expression MinusExpression(cpsl::Expression, cpsl::Expression);
    cpsl::Expression MultExpression(cpsl::Expression, cpsl::Expression);
    cpsl::Expression DivExpression(cpsl::Expression, cpsl::Expression);
    cpsl::Expression ModExpression(cpsl::Expression, cpsl::Expression);
    cpsl::Expression NotExpression(cpsl::Expression);
    cpsl::Expression UMinusExpression(cpsl::Expression);
    cpsl::Expression IntConstant(int);
    cpsl::Expression CharConstant(char);
    cpsl::Expression StringConstant(char*);
private:
    std::vector<Register>* regPool;
    std::string output_file = "";
};

}


#endif