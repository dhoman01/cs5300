#ifndef REG_POOL_HPP
#define REG_POOL_HPP

#include <iostream>
#include <vector>

#include "structures.hpp"

namespace cpsl {

class RegPool {
public:
    RegPool():regPool({
        Register("$a3"),
        Register("$a2"),
        Register("$a1"),
        Register("$a0"),
        Register("$t7"),
        Register("$t6"),
        Register("$t5"),
        Register("$t4"),
        Register("$t3"),
        Register("$t2"),
        Register("$t1"),
        Register("$t0"),
        Register("$s7"),
        Register("$s6"),
        Register("$s5"),
        Register("$s4"),
        Register("$s3"),
        Register("$s2"),
        Register("$s1"),
        Register("$s0")        
    }), locked(){};
    Register acquire();
    void release(Register);
    std::vector<Register> inUse();
private:
    std::vector<Register> regPool;
    std::vector<Register> locked;
};

};

#endif