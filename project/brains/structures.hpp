#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

#include <string>

namespace cpsl
{

struct Register {
    std::string name;
};

struct Expression {
    bool isConstant;
    Register reg;
    int value;
    std::string type;
};

struct StringConst : Expression {
    char* value;
};

};

#endif