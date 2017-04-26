#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "LookupTable.hpp"

namespace cpsl
{

struct Type : Info {
    std::size_t size;
};

struct LValue : Info {
    std::shared_ptr<Type> type;
    std::string location;
    int offset;
    std::string getLocation(){
        return std::to_string(offset) + "(" + location + ")";
    }
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
    std::shared_ptr<Type> type;
    int value;
    int offset;
};

struct ConstantLValue : LValue {
    Expression expr;
};

struct CharConst : Expression {
    char value;
};

struct StringConst : Expression {
    std::string value;
};

struct ForHeaderInfo {
    Expression varExpr;
    Expression cond;
    int uid;
    std::shared_ptr<LValue> lvalue;
    std::string optTo;
    bool adjustOffset;
};

struct Parameter : LValue {
    bool isRef;
    Register reg;
};

enum Forward { DEFINED, EMPTY };
struct Procedure : Info {
    Procedure(std::string i, std::vector<std::shared_ptr<Parameter>> p) : parameters(p){
        id = i;
    };
    std::vector<std::shared_ptr<Parameter>> parameters;
    Forward forward;    
};

struct Return : LValue {
    std::string function;
};

struct Function : Procedure {
    Function(std::string i, std::vector<std::shared_ptr<Parameter>> p, std::shared_ptr<Return> r) : Procedure(i, p), returnValue(r){};
    std::shared_ptr<Return> returnValue;
};

struct Field : Info {
    std::shared_ptr<Type> type;
    int offset;
};

struct Record : Type {
    Record(){
        size = 0;
        id = "record" + std::to_string(Record::getUID());
    };
    int getUID(){
        static std::size_t uid = 0;
        return ++uid;
    };
    LookUpTable<Field> members;    
};

struct Array : Type {
    Array(){
        size = 0;
        id = "array" + std::to_string(Array::getUID());
    };
    int getUID(){
        static std::size_t uid = 0;
        return ++uid;
    };
    int low;
    int high;
    std::shared_ptr<Type> type;
};

};

#endif