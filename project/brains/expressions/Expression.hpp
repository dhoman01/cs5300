#ifndef EXPRESSIONS_HPP
#define EXPRESSIONS_HPP
namespace cpsl
{

class Expression
{
    public:
        Expression();

        int AndExpression(int, int);
        int OrExpression(int, int);
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
};

};
#endif