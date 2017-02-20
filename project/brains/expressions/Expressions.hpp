#ifndef EXPRESSIONS_HPP
#define EXPRESSIONS_HPP

#include <string>
#include <vector>
#include <memory>

#include "../utils/structures.hpp"

namespace cpsl
{

class Expressions  : public std::enable_shared_from_this<Expressions>
{
public:
    Expressions() = default;
    Expressions(std::shared_ptr<std::vector<Register>> pool, std::string file = "") : regPool(pool), output_file(file) {};
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
    cpsl::Expression IntConstant(std::string);
    cpsl::Expression CharConstant(std::string);
    cpsl::Expression ChrExpression(cpsl::Expression);
    cpsl::Expression OrdExpression(cpsl::Expression);
    cpsl::Expression PredExpression(cpsl::Expression);
    cpsl::Expression SuccExpression(cpsl::Expression);
private:
    std::shared_ptr<std::vector<Register>> regPool;
    std::string output_file = "";
};

}


#endif