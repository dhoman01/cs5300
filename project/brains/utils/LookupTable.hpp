#ifndef LOOKUP_TABLE_HPP
#define LOOKUP_TABLE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "structures.hpp"

namespace cpsl
{
template<typename Info>
class LookUpTable
{
public:
    LookUpTable(){};
    void store(std::string id, cpsl::Info* info)
    {
        std::cout << "Storing " << id << std::endl;
        auto f = lookupTable.back().find(id);
        if(f != lookupTable.back().end())
            throw std::runtime_error(id + " is already defined");
        lookupTable.back()[id] = info;
    }
    cpsl::Info* lookup(std::string id)
    {
        std::cout << "looking up " << id << std::endl;
        for(int i = lookupTable.size() - 1; i >= 0; --i)
        {
            auto f = lookupTable[i].find(id);
            if(f != lookupTable[i].end())
            {
                return f->second;
            }
        }

        throw std::runtime_error(id + " is not defined");
    }
    void enterScope()
    {
        lookupTable.emplace_back();
    }
    void exitScope()
    {
        lookupTable.pop_back();
    }
    bool inLocalScope()
    {
        return lookupTable.size() == 3u;
    }
private:
    std::vector< std::map<std::string, cpsl::Info*> > lookupTable;
    std::vector<int> localLocations;
};

};

#endif