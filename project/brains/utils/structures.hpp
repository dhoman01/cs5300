#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

#include <string>

namespace cpsl
{

struct Info {
    virtual ~Info() {};
    std::string id;
};

struct cpslType : Info {
    std::size_t size;
};

struct VariableInfo : Info {
    cpslType* type;
    std::string location;
};

struct Register {
    std::string name;
};

struct Expression {
    bool isConstant;
    Register reg;
    int value;
    std::string type;
};

struct CharConst : Expression {
    char value;
};

struct StringConst : Expression {
    std::string value;
};

};

#endif