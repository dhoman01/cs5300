#ifndef BRAIN_HPP
#define BRAIN_HPP

#include "utils/LookupTable.hpp"

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

class Brain
{
    private:
        Brain() : globalLocation(0) {
            InitPoolAndFile();
        };

        void InitPoolAndFile(){
            for(int i = 8; i < 28; i++){
                Register reg;
                reg.name = "$" + std::to_string(i);
                regPool.push_back(reg);
            }
            std::cout << ".globl main" << std::endl;
            std::cout << ".text\n" << std::endl;

            std::cout << "main:   la $gp, GA" << std::endl;
        }
    public:
        static Brain& getInstance()
        {
            static Brain brain;
            brain.symbolTable.enterScope();

            cpsl::cpslType integerType;
            integerType.size = 4;
            integerType.id = "integer";
            brain.symbolTable.store(integerType.id, integerType);

            cpsl::cpslType characterType;
            characterType.size = 4;
            characterType.id = "char";
            brain.symbolTable.store(characterType.id, characterType);
            return brain;
        }
        Brain(Brain const&)          = delete;
        void operator=(Brain const&) = delete;
        LookUpTable<Info> symbolTable;
        int globalLocation;
        std::vector<Register> regPool;

};

};

#endif