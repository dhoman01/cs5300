#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

#include <string>

namespace cpsl
{

struct Info {
    std::string INFO;
};

struct cpslType : Info {
    int size;
    std::string id;
};

struct VariableInfo : Info {
    cpslType TYPE;
    std::string LOCATION;
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

struct StringConst : Expression {
    char* value;
};

};

#endif