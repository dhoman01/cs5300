#include "RegPool.hpp"

#include <algorithm>
#include <iostream>

cpsl::Register cpsl::RegPool::acquire()
{
    if(regPool.empty()) throw std::runtime_error("You ran out of registers! Maybe you have a function with too many parameters!");
    Register reg = regPool.back();
    regPool.pop_back();

    locked.push_back(reg);

    return reg;
}

void cpsl::RegPool::release(cpsl::Register reg)
{
    if(reg.name.empty()) return;

    if(verbose) std::cout << "\n\t# Releasing Register " << reg.name << std::endl;

    auto it = std::find(regPool.begin(), regPool.end(), reg);
    if(it == regPool.end()){
        regPool.push_back(reg);
    }
    it = std::find(locked.begin(), locked.end(), reg);
    if(it != locked.end()){
        locked.erase(it);
    }

    if(verbose) 
    {
        std::cout << "\t# Available Registers: " << regPool.size() << std::endl;
        std::cout << "\t# Registers In Use:    " << locked.size() << "\n\n";
    }
}

void cpsl::RegPool::releaseAll()
{
    regPool.insert(regPool.end(), locked.begin(), locked.end());
    locked.clear();
}

void cpsl::RegPool::spill(cpsl::Register reg)
{
    spilled.push_back(reg);
    cpsl::RegPool::release(reg);
    if(verbose)
    {
        std::cout << "\n\t# Spilling Register:      " << reg.name << std::endl;
        std::cout << "\t# # of Spilled Registers: " << spilled.size() << "\n\n";
    }
}

std::vector<cpsl::Register> cpsl::RegPool::inUse()
{
    return locked;
}

std::vector<cpsl::Register> cpsl::RegPool::unspill()
{
    auto temp = spilled;
    spilled.clear();
    locked.insert(locked.end(), temp.begin(), temp.end());
    for(auto reg : temp)
    {
        auto it = std::find(regPool.begin(), regPool.end(), reg);
        if(it != regPool.end()) regPool.erase(it);
    }
    return temp;
}