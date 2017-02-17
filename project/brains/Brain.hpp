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
            static Brain instance;

            return instance;
        }
        Brain(Brain const&)          = delete;
        void operator=(Brain const&) = delete;
        LookUpTable<VariableInfo> symbolTable;
        int globalLocation;
};

};

#endif