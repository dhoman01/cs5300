#include <cassert>
#include <cctype>
#include <fstream>

#include "Brain.hpp"

cpsl::Brain::Brain()
{
    regPool = std::make_shared<RegPool>();
    symbolTable = std::make_shared<cpsl::LookUpTable<cpsl::Info>>();
    Init();
    expressions = Expressions(regPool);
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
    expr.type = "string";

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
    std::cout << "\t# Store the true and false const values" << std::endl;
    std::cout << "\tli $v0 1" << std::endl;
    std::cout << "\tsw $v0, 0($gp)" << std::endl;
    std::cout << "\tsw $zero, 4($gp)" << std::endl;
    std::cout << "\n\n\t# Begin CPSL Program" << std::endl;
}

void cpsl::Brain::InitPredefinedSymbols()
{
    // Enter the Predefined Scope
    symbolTable->enterScope();

    // Create integer type
    std::shared_ptr<cpsl::Type> integerType = std::make_shared<cpsl::Type>();
    integerType->size = 4;
    integerType->id = "integer";
    symbolTable->store("integer", integerType);
    symbolTable->store("INTEGER", integerType);

    // Create char type
    std::shared_ptr<cpsl::Type> characterType = std::make_shared<cpsl::Type>();
    characterType->size = 4;
    characterType->id = "char";
    symbolTable->store("char", characterType);
    symbolTable->store("CHAR", characterType);

    // Create boolean type
    std::shared_ptr<cpsl::Type> booleanType = std::make_shared<cpsl::Type>();
    booleanType->size = 4;
    booleanType->id = "boolean";
    symbolTable->store("boolean", booleanType);
    symbolTable->store("BOOLEAN", booleanType);

    // Create string type
    std::shared_ptr<cpsl::Type> stringType = std::make_shared<cpsl::Type>();
    stringType->size = 4;
    stringType->id = "string";
    symbolTable->store("string", stringType);
    symbolTable->store("STRING", stringType);

    // Create true constant
    // In the MIPS Init function 0($gp) is set to the value 1
    std::shared_ptr<cpsl::VariableInfo> trueConst = std::make_shared<cpsl::VariableInfo>();
    trueConst->id = "true";
    trueConst->location = "0($gp)";
    trueConst->type = booleanType;
    symbolTable->store("true", trueConst);
    symbolTable->store("TRUE", trueConst);

    // Create false constant
    // In the MIPS Init function 4($gp) is set to the value 0
    std::shared_ptr<cpsl::VariableInfo> falseConst = std::make_shared<cpsl::VariableInfo>();
    falseConst->id = "false";
    falseConst->location = "4($gp)";
    falseConst->type = booleanType;
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