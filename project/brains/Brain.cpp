#include <cctype>
#include <fstream>
#include <cassert>

#include "Brain.hpp"

cpsl::Brain::Brain(std::string file)
{
    output_file = file;
    Init();
    expressions = Expressions(std::shared_ptr<std::vector<Register>>(&regPool), output_file);
    statements = Statements(std::shared_ptr<std::vector<Register>>(&regPool), std::shared_ptr<LookUpTable<Info>>(&symbolTable));
};

cpsl::Brain::~Brain()
{
    std::cout << "\t.data" << std::endl;
    if(stringConst.size() > 0)
    {
        for(int i = 1; i <= stringConst.size(); ++i)
            std::cout << "S" << i << ": .asciiz " << stringConst[ i - 1 ] << std::endl;
    }
    std::cout << ".align 2" << std::endl << "GA:" << std::endl;
}

cpsl::Expression cpsl::Brain::addString(std::string s)
{
    int id = stringConst.size() + 1;
    
    cpsl::Expression expr;
    expr.reg.name = "S" + std::to_string(id);
    expr.isConstant = false;
    expr.type = "string";

    stringConst.push_back(s);
    
    return expr;
}

void cpsl::Brain::parse(const char * const filename)
{
    assert(filename != nullptr);
    std::ifstream in(filename);
    if(!in.good())
    {
        exit(EXIT_FAILURE);
    }
    parse_helper(in);
    return;
}

void cpsl::Brain::parse( std::istream &stream )
{
   if( ! stream.good()  && stream.eof() )
   {
       return;
   }
   //else
   parse_helper( stream ); 
   return;
}

void cpsl::Brain::parse_helper(std::istream &stream)
{
    try
    {
        scanner = std::make_shared<cpsl::Scanner>(&stream);
    }
    catch (std::bad_alloc& ex)
    {
        std::cerr << "Failed setting up scanner: " << ex.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    try
    {
        parser = std::make_shared<cpsl::Parser>((*scanner.get()), (*this));
    }
    catch(std::bad_alloc& ex)
    {
        std::cerr << "Failed setting up parser: " << ex.what() << std::endl;
    }
    
    const int accept( 0 );
    if( parser->parse() != accept )
    {
        std::cerr << "Failed to parse input!" << std::endl;
    }
    return;
}

void cpsl::Brain::InitRegPool()
{
    for(int i = 8; i < 26; i++){
        Register reg;
        reg.name = "$" + std::to_string(i);
        regPool.push_back(reg);
    }
}

void cpsl::Brain::InitMIPS()
{
    std::streambuf* psbuf, *backup;
    std::ofstream output;
    if(!output_file.empty())
    {            
        output.open(output_file);
        backup = std::cout.rdbuf();
        psbuf = output.rdbuf();
        std::cout.rdbuf(psbuf);
    }

    std::cout << ".globl main" << std::endl;
    std::cout << ".text\n" << std::endl;

    std::cout << "main:   la $gp, GA" << std::endl;
    std::cout << "\tori $fp, $sp, 0" << std::endl;
    std::cout << "\t# Store the true and false const values" << std::endl;
    std::cout << "\tli $a3 1" << std::endl;
    std::cout << "\tsw $a3, 0($gp)" << std::endl;
    std::cout << "\tsw $zero, 4($gp)" << std::endl;

    if(!output_file.empty())
    {
        std::cout.rdbuf(backup);
        output.close();
    }
}

void cpsl::Brain::InitPredefinedSymbols()
{
    symbolTable.enterScope();

    std::shared_ptr<cpsl::cpslType> integerType = std::make_shared<cpsl::cpslType>();
    integerType->size = 4;
    integerType->id = "integer";
    symbolTable.store(integerType->id, integerType);

    std::shared_ptr<cpsl::cpslType> characterType = std::make_shared<cpsl::cpslType>();
    characterType->size = 4;
    characterType->id = "char";
    symbolTable.store(characterType->id, characterType);

    std::shared_ptr<cpsl::cpslType> booleanType = std::make_shared<cpsl::cpslType>();
    booleanType->size = 4;
    booleanType->id = "boolean";
    symbolTable.store(booleanType->id, booleanType);

    std::shared_ptr<cpsl::cpslType> stringType = std::make_shared<cpsl::cpslType>();
    stringType->size = 4;
    stringType->id = "string";
    symbolTable.store(stringType->id, stringType);

    // In the MIPS Init function 0($gp) is set to the value 1
    std::shared_ptr<cpsl::VariableInfo> trueConst = std::make_shared<cpsl::VariableInfo>();
    trueConst->id = "true";
    trueConst->location = "0";
    trueConst->type = booleanType;
    symbolTable.store(trueConst->id, trueConst);

    // In the MIPS Init function 4($gp) is set to the value 0
    std::shared_ptr<cpsl::VariableInfo> falseConst = std::make_shared<cpsl::VariableInfo>();
    falseConst->id = "false";
    falseConst->location = "4";
    falseConst->type = booleanType;
    symbolTable.store(falseConst->id, falseConst);

    symbolTable.enterScope();
}

void cpsl::Brain::Init()
{
    InitRegPool();

    InitMIPS();

    InitPredefinedSymbols();
}