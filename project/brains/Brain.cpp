#include <cctype>
#include <fstream>
#include <cassert>

#include "Brain.hpp"

cpsl::Brain::Brain(std::string file)
{
    globalLocation = 0;
    output_file = file;
    Init();
    expressions = Expressions(&regPool, output_file);
};

cpsl::Brain::~Brain()
{
    delete(scanner);
    scanner = nullptr;
    delete(parser);
    parser = nullptr;
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
    delete(scanner);
    try
    {
        scanner = new cpsl::Scanner(&stream);
    }
    catch (std::bad_alloc& ex)
    {
        std::cerr << "Failed setting up scanner: " << ex.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    delete(parser);
    try
    {
        parser = new cpsl::Parser((*scanner), (*this));
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

    if(!output_file.empty())
    {
        std::cout.rdbuf(backup);
        output.close();
    }
}

void cpsl::Brain::InitPredefinedSymbols()
{
    symbolTable.enterScope();

    cpsl::cpslType integerType;
    integerType.size = 4;
    integerType.id = "integer";
    symbolTable.store(integerType.id, integerType);

    cpsl::cpslType characterType;
    characterType.size = 4;
    characterType.id = "char";
    symbolTable.store(characterType.id, characterType);
}

void cpsl::Brain::Init()
{
    InitRegPool();

    InitMIPS();

    InitPredefinedSymbols();
}