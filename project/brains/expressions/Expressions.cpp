#include <stdexcept>
#include <fstream>
#include <iostream>
#include <string>

#include "Expressions.hpp"

cpsl::Expression cpsl::Expressions::AndExpression(cpsl::Expression a, cpsl::Expression b)
{
    if(a.type != b.type)
        throw std::runtime_error("The value of " + std::to_string(a.value) + " is not the same as " + b.type);
    if(b.type != "boolean")
        throw std::runtime_error("The value of " + std::to_string(b.value) + " is not boolean.");
    
    cpsl::Expression expr;
    expr.type = "boolean";
    expr.value = a.value && b.value;
    std::cout << "\t# Anding " << a.value << " and " << b.value << std::endl;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a.isConstant && b.isConstant){
        expr.isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool->back();
    regPool->pop_back();
    expr.reg = reg;
    expr.isConstant = false;

    // Redirect cout to file if
    // there is a file.
    std::streambuf* psbuf, *backup;
    std::ofstream output;
    if(!output_file.empty())
    {            
        output.open(output_file);
        backup = std::cout.rdbuf();
        psbuf = output.rdbuf();
        std::cout.rdbuf(psbuf);
    }

    if(!a.isConstant && !b.isConstant)
    {
        std::cout << "\tand " << reg.name << " " << a.reg.name << " " << b.reg.name;
        regPool->push_back(a.reg);
        regPool->push_back(b.reg);
    }
    else if(a.isConstant)
    {
        std::cout << "\tandi " << reg.name << " " << b.reg.name << " " << a.value;
        regPool->push_back(b.reg);
    }
    else if(b.isConstant)
    {
        std::cout << "\tandi " << reg.name << " " << a.reg.name << " " << b.value;
        regPool->push_back(a.reg);
    }

    if(!output_file.empty())
    {
        std::cout.rdbuf(backup);
        output.close();
    }
    
    return expr;
}

cpsl::Expression cpsl::Expressions::OrExpression(cpsl::Expression a, cpsl::Expression b)
{
    if(a.type != "boolean")
        throw std::runtime_error("The value of " + std::to_string(a.value) + " is not boolean.");
    if(b.type != "boolean")
        throw std::runtime_error("The value of " + std::to_string(b.value) + " is not boolean.");
    
    cpsl::Expression expr;
    expr.type = "boolean";
    expr.value = a.value || b.value;
    std::cout << "\t# Oring " << a.value << " and " << b.value << std::endl;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a.isConstant && b.isConstant)
    {
        expr.isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool->back();
    regPool->pop_back();
    expr.reg = reg;
    expr.isConstant = false;

    // Redirect cout to file if
    // there is a file.
    std::streambuf* psbuf, *backup;
    std::ofstream output;
    if(!output_file.empty())
    {            
        output.open(output_file);
        backup = std::cout.rdbuf();
        psbuf = output.rdbuf();
        std::cout.rdbuf(psbuf);
    }

    if(!a.isConstant && !b.isConstant)
    {
        std::cout << "\tor " << reg.name << " " << a.reg.name << " " << b.reg.name;
        regPool->push_back(a.reg);
        regPool->push_back(b.reg);
    }
    else if(a.isConstant)
    {
        std::cout << "\tori " << reg.name << " " << b.reg.name << " " << a.value;
        regPool->push_back(b.reg);
    }
    else if(b.isConstant)
    {
        std::cout << "\tori " << reg.name << " " << a.reg.name << " " << b.value;
        regPool->push_back(a.reg);
    }
    
    if(!output_file.empty())
    {
        std::cout.rdbuf(backup);
        output.close();
    }
    
    return expr;
}

cpsl::Expression cpsl::Expressions::EqExpression(cpsl::Expression a, cpsl::Expression b)
{
    if(a.type != b.type)
        throw std::runtime_error("The value of " + a.type + " is not the same as " + b.type);
    
    cpsl::Expression expr;
    expr.type = "boolean";
    expr.value = a.value == b.value;
    std::cout << "\t# Equality check " << a.value << " and " << b.value << std::endl;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a.isConstant && b.isConstant)
    {
        expr.isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool->back();
    regPool->pop_back();
    expr.reg = reg;
    expr.isConstant = false;

    // Redirect cout to file if
    // there is a file.
    std::streambuf* psbuf, *backup;
    std::ofstream output;
    if(!output_file.empty())
    {            
        output.open(output_file);
        backup = std::cout.rdbuf();
        psbuf = output.rdbuf();
        std::cout.rdbuf(psbuf);
    }

    if(!a.isConstant && !b.isConstant)
    {
        std::cout << "\tseq " << reg.name << " " << a.reg.name << " " << b.reg.name;
        regPool->push_back(a.reg);
        regPool->push_back(b.reg);
    }
    else if(a.isConstant)
    {
        std::cout << "\tseqi " << reg.name << " " << b.reg.name << " " << a.value;
        regPool->push_back(b.reg);
    }
    else if(b.isConstant)
    {
        std::cout << "\tseqi " << reg.name << " " << a.reg.name << " " << b.value;
        regPool->push_back(a.reg);
    }

    if(!output_file.empty())
    {
        std::cout.rdbuf(backup);
        output.close();
    }
    
    return expr;
}

cpsl::Expression cpsl::Expressions::NotEqExpression(cpsl::Expression a, cpsl::Expression b)
{
    if(a.type != b.type)
        throw std::runtime_error("The value of " + a.type + " is not the same as " + b.type);
    
    cpsl::Expression expr;
    expr.type = "boolean";
    expr.value = a.value != b.value;
    std::cout << "\t# Not Equal " << a.value << " and " << b.value << std::endl;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a.isConstant && b.isConstant)
    {
        expr.isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool->back();
    regPool->pop_back();
    expr.reg = reg;
    expr.isConstant = false;

    // Redirect cout to file if
    // there is a file.
    std::streambuf* psbuf, *backup;
    std::ofstream output;
    if(!output_file.empty())
    {            
        output.open(output_file);
        backup = std::cout.rdbuf();
        psbuf = output.rdbuf();
        std::cout.rdbuf(psbuf);
    }

    if(!a.isConstant && !b.isConstant)
    {
        std::cout << "\tsne " << reg.name << " " << a.reg.name << " " << b.reg.name;
        regPool->push_back(a.reg);
        regPool->push_back(b.reg);
    }
    else if(a.isConstant)
    {
        std::cout << "\tsnei " << reg.name << " " << b.reg.name << " " << a.value;
        regPool->push_back(b.reg);
    }
    else if(b.isConstant)
    {
        std::cout << "\tsnei " << reg.name << " " << a.reg.name << " " << b.value;
        regPool->push_back(a.reg);
    }
    
    if(!output_file.empty())
    {
        std::cout.rdbuf(backup);
        output.close();
    }
    
    return expr;
}

cpsl::Expression cpsl::Expressions::LtEqExpression(cpsl::Expression a, cpsl::Expression b)
{
    if(a.type != b.type)
        throw std::runtime_error("The value of " + a.type + " is not the same as " + b.type);
    
    cpsl::Expression expr;
    expr.type = "boolean";
    expr.value = a.value <= b.value;
    std::cout << "\t# <= " << a.value << " and " << b.value << std::endl;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a.isConstant && b.isConstant)
    {
        expr.isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool->back();
    regPool->pop_back();
    expr.reg = reg;
    expr.isConstant = false;

    // Redirect cout to file if
    // there is a file.
    std::streambuf* psbuf, *backup;
    std::ofstream output;
    if(!output_file.empty())
    {            
        output.open(output_file);
        backup = std::cout.rdbuf();
        psbuf = output.rdbuf();
        std::cout.rdbuf(psbuf);
    }

    if(!a.isConstant && !b.isConstant)
    {
        std::cout << "\tsle " << reg.name << " " << a.reg.name << " " << b.reg.name;
        regPool->push_back(a.reg);
        regPool->push_back(b.reg);
    }
    else if(a.isConstant)
    {
        std::cout << "\tslei " << reg.name << " " << b.reg.name << " " << a.value;
        regPool->push_back(b.reg);
    }
    else if(b.isConstant)
    {
        std::cout << "\tslei " << reg.name << " " << a.reg.name << " " << b.value;
        regPool->push_back(a.reg);
    }

    if(!output_file.empty())
    {
        std::cout.rdbuf(backup);
        output.close();
    }
    
    return expr;
}

cpsl::Expression cpsl::Expressions::GtEqExpression(cpsl::Expression a, cpsl::Expression b)
{
    if(a.type != b.type)
        throw std::runtime_error("The value of " + a.type + " is not the same as " + b.type);
    
    cpsl::Expression expr;
    expr.type = "boolean";
    expr.value = a.value >= b.value;
    std::cout << "\t# >= " << a.value << " and " << b.value << std::endl;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a.isConstant && b.isConstant)
    {
        expr.isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool->back();
    regPool->pop_back();
    expr.reg = reg;
    expr.isConstant = false;

    // Redirect cout to file if
    // there is a file.
    std::streambuf* psbuf, *backup;
    std::ofstream output;
    if(!output_file.empty())
    {            
        output.open(output_file);
        backup = std::cout.rdbuf();
        psbuf = output.rdbuf();
        std::cout.rdbuf(psbuf);
    }

    if(!a.isConstant && !b.isConstant)
    {
        std::cout << "\tsge " << reg.name << " " << a.reg.name << " " << b.reg.name;
        regPool->push_back(a.reg);
        regPool->push_back(b.reg);
    }
    else if(a.isConstant)
    {
        std::cout << "\tsgei " << reg.name << " " << b.reg.name << " " << a.value;
        regPool->push_back(b.reg);
    }
    else if(b.isConstant)
    {
        std::cout << "\tsgei " << reg.name << " " << a.reg.name << " " << b.value;
        regPool->push_back(a.reg);
    }
    
    if(!output_file.empty())
    {
        std::cout.rdbuf(backup);
        output.close();
    }
    
    return expr;
}

cpsl::Expression cpsl::Expressions::LtExpression(cpsl::Expression a, cpsl::Expression b)
{
    if(a.type != b.type)
        throw std::runtime_error("The value of " + a.type + " is not the same as " + b.type);
    
    cpsl::Expression expr;
    expr.type = "boolean";
    expr.value = a.value < b.value;
    std::cout << "\t# " << a.value << " < " << b.value << std::endl;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a.isConstant && b.isConstant)
    {
        expr.isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool->back();
    regPool->pop_back();
    expr.reg = reg;
    expr.isConstant = false;

    // Redirect cout to file if
    // there is a file.
    std::streambuf* psbuf, *backup;
    std::ofstream output;
    if(!output_file.empty())
    {            
        output.open(output_file);
        backup = std::cout.rdbuf();
        psbuf = output.rdbuf();
        std::cout.rdbuf(psbuf);
    }

    if(!a.isConstant && !b.isConstant)
    {
        std::cout << "\tslt " << reg.name << " " << a.reg.name << " " << b.reg.name;
        regPool->push_back(a.reg);
        regPool->push_back(b.reg);
    }
    else if(a.isConstant)
    {
        std::cout << "\tslti " << reg.name << " " << b.reg.name << " " << a.value;
        regPool->push_back(b.reg);
    }
    else if(b.isConstant)
    {
        std::cout << "\tslti " << reg.name << " " << a.reg.name << " " << b.value;
        regPool->push_back(a.reg);
    }

    if(!output_file.empty())
    {
        std::cout.rdbuf(backup);
        output.close();
    }
    
    return expr;
}

cpsl::Expression cpsl::Expressions::GtExpression(cpsl::Expression a, cpsl::Expression b)
{
    if(a.type != b.type)
        throw std::runtime_error("The value of " + a.type + " is not the same as " + b.type);
    
    cpsl::Expression expr;
    expr.type = "boolean";
    expr.value = a.value > b.value;
    std::cout << "\t# " << a.value << " > " << b.value << std::endl;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a.isConstant && b.isConstant)
    {
        expr.isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool->back();
    regPool->pop_back();
    expr.reg = reg;
    expr.isConstant = false;

    // Redirect cout to file if
    // there is a file.
    std::streambuf* psbuf, *backup;
    std::ofstream output;
    if(!output_file.empty())
    {            
        output.open(output_file);
        backup = std::cout.rdbuf();
        psbuf = output.rdbuf();
        std::cout.rdbuf(psbuf);
    }

    if(!a.isConstant && !b.isConstant)
    {
        std::cout << "\tsgt " << reg.name << " " << a.reg.name << " " << b.reg.name;
        regPool->push_back(a.reg);
        regPool->push_back(b.reg);
    }
    else if(a.isConstant)
    {
        std::cout << "\tsgti " << reg.name << " " << b.reg.name << " " << a.value;
        regPool->push_back(b.reg);
    }
    else if(b.isConstant)
    {
        std::cout << "\tsgti " << reg.name << " " << a.reg.name << " " << b.value;
        regPool->push_back(a.reg);
    }
    
    if(!output_file.empty())
    {
        std::cout.rdbuf(backup);
        output.close();
    }
    
    return expr;
}

cpsl::Expression cpsl::Expressions::PlusExpression(cpsl::Expression a, cpsl::Expression b)
{
    if(a.type != "integer")
        throw std::runtime_error("The value of " + a.type + " is not integer.");
    if(b.type != "integer")
        throw std::runtime_error("The value of " + b.type + " is not integer.");
    
    cpsl::Expression expr;
    expr.type = "integer";
    expr.value = a.value + b.value;
    std::cout << "\t# Expression: " << a.value << " + " << b.value << std::endl;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a.isConstant && b.isConstant)
    {
        expr.isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool->back();
    regPool->pop_back();
    expr.reg = reg;
    expr.isConstant = false;

    // Redirect cout to file if
    // there is a file.
    std::streambuf* psbuf, *backup;
    std::ofstream output;
    if(!output_file.empty())
    {            
        output.open(output_file);
        backup = std::cout.rdbuf();
        psbuf = output.rdbuf();
        std::cout.rdbuf(psbuf);
    }

    if(!a.isConstant && !b.isConstant)
    {
        std::cout << "\tadd " << reg.name << " " << a.reg.name << " " << b.reg.name << std::endl;
        regPool->push_back(a.reg);
        regPool->push_back(b.reg);
    }
    else if(a.isConstant)
    {
        std::cout << "\addi " << reg.name << " " << b.reg.name << " " << a.value << std::endl;
        regPool->push_back(b.reg);        
    }
    else if(b.isConstant)
    {
        std::cout << "\taddi " << reg.name << " " << a.reg.name << " " << b.value << std::endl;
        regPool->push_back(a.reg);
    }
    
    if(!output_file.empty())
    {
        std::cout.rdbuf(backup);
        output.close();
    }
    
    return expr;
}

cpsl::Expression cpsl::Expressions::MinusExpression(cpsl::Expression a, cpsl::Expression b)
{
    if(a.type != "integer")
        throw std::runtime_error("The value of " + std::to_string(a.value) + " is not integer.");
    if(b.type != "integer")
        throw std::runtime_error("The value of " + std::to_string(b.value) + " is not integer.");
    
    cpsl::Expression expr;
    expr.type = "integer";
    expr.value = a.value - b.value;
    std::cout << "\t# " << a.value << " - " << b.value << std::endl;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a.isConstant && b.isConstant)
    {
        expr.isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool->back();
    regPool->pop_back();
    expr.reg = reg;
    expr.isConstant = false;

    // Redirect cout to file if
    // there is a file.
    std::streambuf* psbuf, *backup;
    std::ofstream output;
    if(!output_file.empty())
    {            
        output.open(output_file);
        backup = std::cout.rdbuf();
        psbuf = output.rdbuf();
        std::cout.rdbuf(psbuf);
    }

    if(!a.isConstant && !b.isConstant)
    {
        std::cout << "\tsub " << reg.name << " " << a.reg.name << " " << b.reg.name << std::endl;
        regPool->push_back(a.reg);
        regPool->push_back(b.reg);
    }
    else if(a.isConstant)
    {
        Register reg2 = regPool->back();
        std::cout << "\tli " << reg2.name << " " << a.value << std::endl;
        std::cout << "\tsub " << reg.name << " " << reg2.name << " " << b.reg.name << std::endl;
        regPool->push_back(reg2);
        regPool->push_back(b.reg);
    }
    else if(b.isConstant)
    {
        std::cout << "\tsubi " << reg.name << " " << a.reg.name << " " << b.value << std::endl;
        regPool->push_back(a.reg);
    }

    if(!output_file.empty())
    {
        std::cout.rdbuf(backup);
        output.close();
    }
    
    return expr;
}

cpsl::Expression cpsl::Expressions::MultExpression(cpsl::Expression a, cpsl::Expression b)
{
    if(a.type != "integer")
        throw std::runtime_error("The value of " + std::to_string(a.value) + " is not integer.");
    if(b.type != "integer")
        throw std::runtime_error("The value of " + std::to_string(b.value) + " is not integer.");
    
    cpsl::Expression expr;
    expr.type = "integer";
    expr.value = a.value * b.value;
    std::cout << "\t# " << a.value << " * " << b.value << std::endl;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a.isConstant && b.isConstant)
    {
        expr.isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool->back();
    regPool->pop_back();
    expr.reg = reg;
    expr.isConstant = false;

    // Redirect cout to file if
    // there is a file.
    std::streambuf* psbuf, *backup;
    std::ofstream output;
    if(!output_file.empty())
    {            
        output.open(output_file);
        backup = std::cout.rdbuf();
        psbuf = output.rdbuf();
        std::cout.rdbuf(psbuf);
    }

    if(!a.isConstant && !b.isConstant)
    {
        std::cout << "\tmult " << a.reg.name << " " << b.reg.name << std::endl;
        std::cout << "\tmflo " << reg.name << std::endl;
        regPool->push_back(a.reg);
        regPool->push_back(b.reg);
    } 
    else if(a.isConstant)
    {
        Register reg2 = regPool->back();
        std::cout << "\tli " << reg2.name << " " << a.value << std::endl;
        std::cout << "\tmult " << reg2.name << " " << b.reg.name << std::endl;
        std::cout << "\tmflo " << reg.name << std::endl;
        regPool->push_back(reg2);
        regPool->push_back(b.reg);
    } 
    else if(b.isConstant)
    {
        Register reg2 = regPool->back();
        std::cout << "\tli " << reg2.name << " " << b.value << std::endl;
        std::cout << "\tmult " << a.reg.name << " " << reg2.name << std::endl;
        std::cout << "\tmflo " << reg.name << std::endl;
        regPool->push_back(a.reg);
        regPool->push_back(reg2);
    }

    if(!output_file.empty())
    {
        std::cout.rdbuf(backup);
        output.close();
    }
    
    return expr;
}

cpsl::Expression cpsl::Expressions::DivExpression(cpsl::Expression a, cpsl::Expression b)
{
    if(a.type != "integer")
        throw std::runtime_error("The value of " + std::to_string(a.value) + " is not integer.");
    if(b.type != "integer")
        throw std::runtime_error("The value of " + std::to_string(b.value) + " is not integer.");
    
    cpsl::Expression expr;
    expr.type = "integer";
    expr.value = a.value / b.value;
    std::cout << "\t# " << a.value << " / " << b.value << std::endl;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a.isConstant && b.isConstant)
    {
        expr.isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool->back();
    regPool->pop_back();
    expr.reg = reg;
    expr.isConstant = false;

    // Redirect cout to file if
    // there is a file.
    std::streambuf* psbuf, *backup;
    std::ofstream output;
    if(!output_file.empty())
    {            
        output.open(output_file);
        backup = std::cout.rdbuf();
        psbuf = output.rdbuf();
        std::cout.rdbuf(psbuf);
    }

    if(!a.isConstant && !b.isConstant)
    {
        std::cout << "\tdiv " << a.reg.name << " " << b.reg.name << std::endl;
        std::cout << "\tmflo " << reg.name << std::endl;
        regPool->push_back(a.reg);
        regPool->push_back(b.reg);
    } 
    else if(a.isConstant)
    {
        Register reg2 = regPool->back();
        std::cout << "\tli " << reg2.name << " " << a.value << std::endl;
        std::cout << "\tdiv " << reg2.name << " " << b.reg.name << std::endl;
        std::cout << "\tmflo " << reg.name << std::endl;
        regPool->push_back(reg2);
        regPool->push_back(b.reg);
    } 
    else if(b.isConstant)
    {
        Register reg2 = regPool->back();
        std::cout << "\tli " << reg2.name << " " << b.value << std::endl;
        std::cout << "\tdiv " << a.reg.name << " " << reg2.name << std::endl;
        std::cout << "\tmflo " << reg.name << std::endl;
        regPool->push_back(a.reg);
        regPool->push_back(reg2);
    }

    if(!output_file.empty())
    {
        std::cout.rdbuf(backup);
        output.close();
    }
    
    return expr;
}

cpsl::Expression cpsl::Expressions::ModExpression(cpsl::Expression a, cpsl::Expression b)
{
    if(a.type != "integer")
        throw std::runtime_error("The value of " + std::to_string(a.value) + " is not integer.");
    if(b.type != "integer")
        throw std::runtime_error("The value of " + std::to_string(b.value) + " is not integer.");
    
    cpsl::Expression expr;
    expr.type = "integer";
    expr.value = a.value % b.value;
    std::cout << "\t# " << a.value << " % " << b.value << std::endl;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a.isConstant && b.isConstant)
    {
        expr.isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool->back();
    regPool->pop_back();
    expr.reg = reg;
    expr.isConstant = false;

    // Redirect cout to file if
    // there is a file.
    std::streambuf* psbuf, *backup;
    std::ofstream output;
    if(!output_file.empty())
    {            
        output.open(output_file);
        backup = std::cout.rdbuf();
        psbuf = output.rdbuf();
        std::cout.rdbuf(psbuf);
    }

    if(!a.isConstant && !b.isConstant)
    {
        std::cout << "\tdiv " << a.reg.name << " " << b.reg.name << std::endl;
        std::cout << "\tmfhi " << reg.name << std::endl;
        regPool->push_back(a.reg);
        regPool->push_back(b.reg);
    } 
    else if(a.isConstant)
    {
        Register reg2 = regPool->back();
        std::cout << "\tli " << reg2.name << " " << a.value << std::endl;
        std::cout << "\tdiv " << reg2.name << " " << b.reg.name << std::endl;
        std::cout << "\tmfhi " << reg.name << std::endl;
        regPool->push_back(reg2);
        regPool->push_back(b.reg);
    } 
    else if(b.isConstant)
    {
        Register reg2 = regPool->back();
        std::cout << "\tli " << reg2.name << " " << b.value << std::endl;
        std::cout << "\tdiv " << a.reg.name << " " << reg2.name << std::endl;
        std::cout << "\tmfhi " << reg.name << std::endl;
        regPool->push_back(a.reg);
        regPool->push_back(reg2);
    }

    if(!output_file.empty())
    {
        std::cout.rdbuf(backup);
        output.close();
    }
    
    return expr;
}

cpsl::Expression cpsl::Expressions::NotExpression(cpsl::Expression a)
{
    if(a.type != "boolean")
        throw std::runtime_error("The value of " + std::to_string(a.value) + " is not boolean.");
    
    cpsl::Expression expr;
    expr.type = "boolean";
    expr.value = !a.value;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a.isConstant)
    {
        std::cout << "\t# !" << a.value << std::endl;
        expr.isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool->back();
    regPool->pop_back();
    expr.reg = reg;
    expr.isConstant = false;

    // Redirect cout to file if
    // there is a file.
    std::streambuf* psbuf, *backup;
    std::ofstream output;
    if(!output_file.empty())
    {            
        output.open(output_file);
        backup = std::cout.rdbuf();
        psbuf = output.rdbuf();
        std::cout.rdbuf(psbuf);
    }

    std::cout << "\t# ! " << a.reg.name << std::endl;
    std::cout << "\txori " << reg.name << " " << a.reg.name << " 1" << std::endl;
    regPool->push_back(a.reg);

    if(!output_file.empty())
    {
        std::cout.rdbuf(backup);
        output.close();
    }
    
    return expr;
}

cpsl::Expression cpsl::Expressions::UMinusExpression(cpsl::Expression a)
{
    if(a.type != "integer")
        throw std::runtime_error("The value of " + std::to_string(a.value) + " is not integer.");
    
    cpsl::Expression expr;
    expr.type = "integer";
    expr.value = --a.value;
    std::cout << "\t# -" << a.value << std::endl;

    // If a && b are constants this is a
    // constant expression. No MIPS emitted.
    if(a.isConstant)
    {
        expr.isConstant = true;
        return expr;
    }

    // a || b are not constants. This is not
    // a constant expression. Grab a Register
    // and emit correct MIPS.
    Register reg = regPool->back();
    regPool->pop_back();
    expr.reg = reg;
    expr.isConstant = false;

    // Redirect cout to file if
    // there is a file.
    std::streambuf* psbuf, *backup;
    std::ofstream output;
    if(!output_file.empty())
    {            
        output.open(output_file);
        backup = std::cout.rdbuf();
        psbuf = output.rdbuf();
        std::cout.rdbuf(psbuf);
    }

    std::cout << "\taddi " << reg.name << " " << a.reg.name << " -1" << std::endl;
    regPool->push_back(a.reg);

    if(!output_file.empty())
    {
        std::cout.rdbuf(backup);
        output.close();
    }

    return expr;
}

cpsl::Expression cpsl::Expressions::IntConstant(std::string a)
{
    cpsl::Expression expr;
    expr.isConstant = true;
    expr.type = "integer";
    expr.value  = stoi(a);
    return expr;
}

cpsl::Expression cpsl::Expressions::CharConstant(std::string a)
{
    cpsl::CharConst expr;
    expr.isConstant = true;
    expr.type = "char";
    expr.value  = a[0];
    return expr;
}

cpsl::Expression cpsl::Expressions::ChrExpression(cpsl::Expression expr)
{
    if(expr.type != "integer")
        throw std::runtime_error("chr() requires an integer argument. Not a " + expr.type);

    expr.type = "char";
    return expr;
}

cpsl::Expression cpsl::Expressions::OrdExpression(cpsl::Expression expr)
{
    if(expr.type != "char")
        throw std::runtime_error("ord() requires a character argument. Not a " + expr.type);

    expr.type = "integer";
    return expr;
}

cpsl::Expression cpsl::Expressions::PredExpression(cpsl::Expression expr)
{
    if(expr.isConstant)
    {
        if(expr.type == "boolean")
            expr.value = !expr.value;
        else
            expr.value--;
        return expr;
    }

    std::cout << "\t# pred(" << expr.reg.name << ")" << std::endl;
    if(expr.type == "boolean")
        std::cout << "\txori " << expr.reg.name << " " << expr.reg.name << " 1" << std::endl;
    else
        std::cout << "\t# addi " << expr.reg.name << " " << expr.reg.name << " -1" << std::endl;
    return expr;
}

cpsl::Expression cpsl::Expressions::SuccExpression(cpsl::Expression expr)
{
    if(expr.isConstant)
    {
        if(expr.type == "boolean")
            expr.value = !expr.value;
        else
            expr.value--;
        return expr;
    }

    std::cout << "\t# pred(" << expr.reg.name << ")" << std::endl;
    if(expr.type == "boolean")
        std::cout << "\txori " << expr.reg.name << " " << expr.reg.name << " 1" << std::endl;
    else
        std::cout << "\t# addi " << expr.reg.name << " " << expr.reg.name << " 1" << std::endl;
    return expr;
}