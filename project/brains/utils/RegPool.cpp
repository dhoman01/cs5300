#include "RegPool.hpp"

#include <algorithm>

cpsl::Register cpsl::RegPool::acquire(){
    if(regPool.empty()) throw std::runtime_error("Register Pool is empty!");
    Register reg = regPool.back();
    regPool.pop_back();

    locked.push_back(reg);

    return reg;
}

void cpsl::RegPool::release(cpsl::Register reg){
    auto it = std::find(regPool.begin(), regPool.end(), reg);
    if(it != regPool.end()){
        regPool.push_back(reg);
    }
    it = std::find(locked.begin(), locked.end(), reg);
    if(it != locked.end()){
        locked.erase(it);
    }
}

std::vector<cpsl::Register> cpsl::RegPool::inUse(){
    return locked;
}