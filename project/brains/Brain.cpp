#include <cassert>
#include <cctype>
#include <fstream>

#include "Brain.hpp"

cpsl::Brain::Brain()
{
    regPool = std::make_shared<cpsl::RegPool>();
    symbolTable = std::make_shared<cpsl::LookUpTable<cpsl::Info>>();
    Init();
    expressions = Expressions(regPool, symbolTable);
    statements = Statements(regPool, symbolTable);
};

void cpsl::Brain::Finalize()
{
    std::cout << "\n\t# End of CPSL Program" << std::endl;
    cpsl::Brain::statements.StopStatement();
    std::cout << "\n\t.data" << std::endl;
    if(stringConst.size() > 0)
    {
        std::cout << "\n# Write out string constants" << std::endl;
        for(int i = 1; i <= stringConst.size(); ++i)
            std::cout << "S" << i << ": .asciiz " << stringConst[ i - 1 ] << std::endl;
    }
    std::cout << "\n# Reset alignment to the nearest word and declare global area" << std::endl;
    std::cout << ".align 2" << std::endl << "GA:" << std::endl;
}

// Add a string to the collection
cpsl::Expression cpsl::Brain::AddString(std::string s)
{
    int id = stringConst.size() + 1;
    
    cpsl::Expression expr;
    expr.reg.name = "S" + std::to_string(id);
    expr.isConstant = false;
    expr.type = std::dynamic_pointer_cast<cpsl::Type>(cpsl::Brain::symbolTable->lookup("string"));

    stringConst.push_back(s);
    
    return expr;
}

// Parse from file
void cpsl::Brain::Parse(const char * const filename)
{
    assert(filename != nullptr);
    std::ifstream in(filename);
    if(!in.good())
        exit(EXIT_FAILURE);
    
    ParseHelper(in);
    return;
}

// Parse from stdio
void cpsl::Brain::Parse(std::istream &stream)
{
   if(!stream.good() && stream.eof())
       return;
   
   ParseHelper(stream); 
   return;
}

void cpsl::Brain::ParseHelper(std::istream &stream)
{
    scanner = std::make_shared<cpsl::Scanner>(&stream);
    parser = std::make_shared<cpsl::Parser>((*scanner.get()), (*this));
    parser->parse();
    return;
}

void cpsl::Brain::InitMIPS()
{
    // Write HEAD matter for asm file
    // NOTE: HEAD matter includes
    // boolean constant definitions
    std::cout << ".globl main" << std::endl;
    std::cout << ".text\n" << std::endl;
    std::cout << "j main" << std::endl;    
}

void cpsl::Brain::InitMain()
{
    std::cout << "main:" << std::endl;
    std::cout << "\tla $gp, GA" << std::endl;
    std::cout << "\n\n\t# Begin CPSL Program" << std::endl;
}

void cpsl::Brain::InitPredefinedSymbols()
{
    // Enter the Predefined Scope
    symbolTable->enterScope();

    // Create integer type
    auto integerType = std::make_shared<cpsl::Type>();
    integerType->size = 4;
    integerType->id = "integer";
    symbolTable->store("integer", integerType);
    symbolTable->store("INTEGER", integerType);

    // Create char type
    auto characterType = std::make_shared<cpsl::Type>();
    characterType->size = 4;
    characterType->id = "char";
    symbolTable->store("char", characterType);
    symbolTable->store("CHAR", characterType);

    // Create boolean type
    auto booleanType = std::make_shared<cpsl::Type>();
    booleanType->size = 4;
    booleanType->id = "boolean";
    symbolTable->store("boolean", booleanType);
    symbolTable->store("BOOLEAN", booleanType);

    // Create string type
    auto stringType = std::make_shared<cpsl::Type>();
    stringType->size = 4;
    stringType->id = "string";
    symbolTable->store("string", stringType);
    symbolTable->store("STRING", stringType);

    // Create true constant
    auto trueConst = std::make_shared<cpsl::ConstantLValue>();
    trueConst->id = "true";
    trueConst->expr.isConstant = true;
    trueConst->expr.value = true;
    trueConst->type = booleanType;
    trueConst->expr.type = booleanType;
    symbolTable->store("true", trueConst);
    symbolTable->store("TRUE", trueConst);

    // Create false constant
    auto falseConst = std::make_shared<cpsl::ConstantLValue>();
    falseConst->id = "false";
    falseConst->expr.isConstant = true;
    falseConst->expr.value = false;
    falseConst->type = booleanType;
    falseConst->expr.type = booleanType;
    symbolTable->store("false", falseConst);
    symbolTable->store("FALSE", falseConst);

    // Enter global scope
    symbolTable->enterScope();
}

void cpsl::Brain::Init()
{
    InitMIPS();

    InitPredefinedSymbols();
}