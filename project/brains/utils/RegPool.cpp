#include "RegPool.hpp"

#include <algorithm>
#include <iostream>

cpsl::Register cpsl::RegPool::acquire()
{
    // Throw a runtime error if we've ran
    // out of registers to allocate
    if(regPool.empty())
        throw std::runtime_error("You ran out of registers! Maybe you have a function with too many parameters!");

    // Grab the register from the back
    // of the stack and pop it
    Register reg = regPool.back();
    regPool.pop_back();

    // Push the acquired register
    // onto the locked stack
    locked.push_back(reg);

    return reg;
}

void cpsl::RegPool::release(cpsl::Register reg)
{
    // const's sometimes get 'released'
    // they have no name so we need
    // to catch that here
    if(reg.name.empty()) return;
    if(reg.name[0] == 'S') return;

    if(verbose) std::cout << "\n\t# Releasing Register " << reg.name << std::endl;

    // Check if the register
    // is already in the pool.
    auto it = std::find(regPool.begin(), regPool.end(), reg);
    
    // If it isn't push it on
    if(it == regPool.end()){
        regPool.push_back(reg);
    }

    // Check if the register
    // is in locked
    it = std::find(locked.begin(), locked.end(), reg);

    // If it is, erase it
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
    // Insert all locked registers
    // back into the pool and clear locked
    regPool.insert(regPool.end(), locked.begin(), locked.end());
    locked.clear();
}

void cpsl::RegPool::spill(cpsl::Register reg)
{
    // Push register onto
    // spilled stack
    spilled.push_back(reg);

    // Release the register
    cpsl::RegPool::release(reg);

    if(verbose)
    {
        std::cout << "\n\t# Spilling Register:      " << reg.name << std::endl;
        std::cout << "\t# # of Spilled Registers: " << spilled.size() << "\n\n";
    }
}

std::vector<cpsl::Register> cpsl::RegPool::inUse()
{
    // Return locked registers
    return locked;
}

std::vector<cpsl::Register> cpsl::RegPool::unspill()
{
    auto temp = spilled;
    
    // Clear the spill
    spilled.clear();

    // Lock the spilled registers
    locked.insert(locked.end(), temp.begin(), temp.end());

    // Remove from pool
    for(auto reg : temp)
    {
        auto it = std::find(regPool.begin(), regPool.end(), reg);
        if(it != regPool.end()) regPool.erase(it);
    }

    return temp;
}