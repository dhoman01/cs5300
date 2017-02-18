#ifndef EXPRESSIONS_HPP
#define EXPRESSIONS_HPP

#include <string>
#include <vector>

#include "../utils/LookupTable.hpp"

struct Register {
    std::string name;
};

struct Expression {
    bool isConstant;
    Register reg;
    int value;
    std::string type;
};

class Expressions
{
    private:
        std::vector<Register> regPool;
    public:
        Expressions(): regPool() {
            for(int i = 8; i < 28; i++){
                Register reg;
                reg.name = "$" + std::to_string(i);
                regPool.push_back(reg);
            }
        }

        Expression* AndExpression(Expression*, Expression*);
        Expression OrExpression(Expression*, Expression*);
        int EqExpression(int, int);
        int NotEqExpression(int, int);
        int LtEqExpression(int, int);
        int GtEqExpression(int, int);
        int LtExpression(int, int);
        int GtExpression(int, int);
        int PlusExpression(int, int);
        int MinusExpression(int, int);
        int MultExpression(int, int);
        int DivExpression(int, int);
        int ModExpression(int, int);
        int NotExpression(int);
        int UMinusExpression(int);
        Expression* IntConstant(int);
        Expression* CharConstant(char);
        Expression* StringConstant(char*);
};

#endif