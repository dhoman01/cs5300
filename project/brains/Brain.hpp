#ifndef BRAIN_HPP
#define BRAIN_HPP

#include "utils/LookupTable.hpp"

namespace cpsl
{

class Brain
{
    private:
        Brain() : globalLocation(0) {};
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
};

};

#endif