#ifndef LOOKUP_TABLE_HPP
#define LOOKUP_TABLE_HPP

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "structures.hpp"

namespace cpsl
{

template<typename Info>
class LookUpTable
{
public:
    LookUpTable(){};
    void store(std::string id, std::shared_ptr<cpsl::Info> info)
    {
        auto f = lookupTable.back().find(id);
        if(f != lookupTable.back().end())
            throw std::runtime_error(id + " is already defined");
        lookupTable.back()[id] = info;
    }
    std::shared_ptr<cpsl::Info> lookup(std::string id)
    {
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
    std::vector< std::map<std::string, std::shared_ptr<cpsl::Info>> > lookupTable;
    std::vector<int> localLocations;
};

};

#endif