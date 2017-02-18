#ifndef EXPRESSIONS_HPP
#define EXPRESSIONS_HPP

#include "../Brain.hpp"

Expression* AndExpression(Expression*, Expression*);
Expression* OrExpression(Expression*, Expression*);
Expression* EqExpression(Expression*, Expression*);
Expression* NotEqExpression(Expression*, Expression*);
Expression* LtEqExpression(Expression*, Expression*);
Expression* GtEqExpression(Expression*, Expression*);
Expression* LtExpression(Expression*, Expression*);
Expression* GtExpression(Expression*, Expression*);
Expression* PlusExpression(Expression*, Expression*);
Expression* MinusExpression(Expression*, Expression*);
Expression* MultExpression(Expression*, Expression*);
Expression* DivExpression(Expression*, Expression*);
Expression* ModExpression(Expression*, Expression*);
Expression* NotExpression(Expression*);
Expression* UMinusExpression(Expression*);
Expression* IntConstant(int);
Expression* CharConstant(char);
Expression* StringConstant(char*);

#endif