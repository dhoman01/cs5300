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

using scope = std::vector< std::map<std::string, std::shared_ptr<cpsl::Info>> >;

template<typename Info>
class LookUpTable
{
public:
    LookUpTable(){};
    void store(std::string id, std::shared_ptr<cpsl::Info> info)
    {
        auto f = scopes.back().find(id);
        if(f != scopes.back().end())
            throw std::runtime_error(id + " is already defined");
        scopes.back()[id] = info;
    }
    std::shared_ptr<cpsl::Info> lookup(std::string id)
    {
        for(int i = scopes.size() - 1; i >= 0; --i)
        {
            auto f = scopes[i].find(id);
            if(f != scopes[i].end())
            {
                return f->second;
            }
        }

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