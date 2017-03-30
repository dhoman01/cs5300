#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

#include <memory>
#include <string>
#include <vector>

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
    int offset;
};

struct Register {
    Register(){};
    Register(std::string n):name(n){};
    std::string name;
    bool operator==(const Register& rhs){ name == rhs.name; };
};

struct Expression {
    bool isConstant;
    Register reg;
    int value;
    std::string type;
    int offset;
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

struct Parameter : VariableInfo {
    bool isRef;
    Register reg;
};

struct Procedure : Info {
    Procedure(std::string i, std::vector<std::shared_ptr<cpsl::Parameter>> p) : parameters(p){
        id = i;
    };
    std::vector<std::shared_ptr<cpsl::Parameter>> parameters;
};

struct Return : VariableInfo {
    std::string function;
};

struct Function : Procedure {
    Function(std::string i, std::vector<std::shared_ptr<cpsl::Parameter>> p, std::shared_ptr<Return> r) : Procedure(i, p), returnValue(r){};
    std::shared_ptr<Return> returnValue;
};

};

#endif