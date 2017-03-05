#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

#include <memory>
#include <string>

namespace cpsl
{

struct Info {
    Info(){};
    virtual ~Info() {};
    std::string id;
};

struct Type : Info {
    std::size_t size;
};

struct VariableInfo : Info {
    std::shared_ptr<Type> type;
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

struct ForHeaderInfo {
    cpsl::Expression varExpr;
    cpsl::Expression cond;
    int uid;
    std::shared_ptr<cpsl::VariableInfo> var;
    std::string optTo;
    bool exitScope;
};

};

#endif