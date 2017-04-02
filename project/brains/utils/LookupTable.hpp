#ifndef LOOKUP_TABLE_HPP
#define LOOKUP_TABLE_HPP 1

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "structures.hpp"

namespace cpsl
{

using scope = std::vector< std::map<std::string, std::shared_ptr<cpsl::Info>> >;

template<typename Info>
class LookUpTable
{
public:
    LookUpTable(){};

    void store(std::string id, std::shared_ptr<cpsl::Info> info)
    {
        // Check if id exits in curr scope
        auto f = scopes.back().find(id);
        
        // If id exits in curr scope, throw runtime
        if(f != scopes.back().end())
            throw std::runtime_error(id + " is already defined");

        // Else store in curr scope
        scopes.back()[id] = info;
    }
    std::shared_ptr<cpsl::Info> lookup(std::string id)
    {
        // Start at curr scope and look up for the id
        for(int i = scopes.size() - 1; i >= 0; --i)
        {
            auto f = scopes[i].find(id);

            // Id found, return cpsl::Info
            if(f != scopes[i].end())
                return f->second;
        }

        // Couldn't find id, therefore it was not defined
        throw std::runtime_error(id + " is not defined");
    }
    void enterScope()
    {
        scopes.emplace_back();
    }
    void exitScope()
    {
        scopes.pop_back();
    }
    bool inLocalScope()
    {
        return scopes.size() == 3u;
    }
private:
    scope scopes;
};

};

#endif