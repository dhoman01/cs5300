#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#include "brains/Brain.hpp"

bool matchArgs(const char* arg, std::string opt)
{
    return std::strncmp(arg, opt.c_str(), opt.size()) == 0;
}

int main(const int argc, const char **argv)
{
   if(argc >= 2)
   {
      if(matchArgs(argv[1], std::string("--help")) || matchArgs(argv[1], std::string("-h")))
      {
         std::cout << "usage: cpslc [/path/to/file/target | --stdio | --help] [options]" << std::endl;
         std::cout << "Options: " << std::endl;
         std::cout << "\t\u2022 use --help to get this menu" << std::endl;
         std::cout << "\t\u2022 use --stdio for pipe to std::cin" << std::endl;
         std::cout << "\t\u2022 use --output[=filename] for output of MIPS to filename" << std::endl;
         return EXIT_SUCCESS;
      }

      // Redirect std::cout to file if --output has a filename
      std::streambuf* buffer = std::cout.rdbuf();
      bool coutRestore = false;
      std::ofstream asmOut;
      if(argc >= 4 && (matchArgs(argv[2], std::string("--output")) || matchArgs(argv[2], std::string("-o"))))
      {
         asmOut.open(argv[3], std::ofstream::trunc);
         std::cout.rdbuf(asmOut.rdbuf());
         coutRestore = true;
      }

      cpsl::Brain brain;
      if(std::strncmp(argv[ 1 ], "--stdio", 7) == 0)
      {
          try
          {
            brain.parse(std::cin);              
          }
          catch (const std::exception& ex)
          {
              std::cerr << "Runtime Error: " << ex.what() << std::endl;
              return EXIT_FAILURE;
          }
      }
      else
      {
          try
          {
            brain.parse(argv[1]);              
          }
          catch (const std::exception& ex)
          {
              std::cerr << "Runtime Error: " << ex.what() << std::endl;
              return EXIT_FAILURE;
          }
      }

      brain.Finalize();

      if(coutRestore)
        std::cout.rdbuf(buffer);
   }
   else
   {
        std::cerr << "usage: cpslc [/path/to/file/target | --stdio | --help] [options]" << std::endl;
        std::cerr << "Options: " << std::endl;
        std::cerr << "\t\u2022 use --help to get this menu" << std::endl;
        std::cerr << "\t\u2022 use --stdio for pipe to std::cin" << std::endl;
        std::cerr << "\t\u2022 use --output[=filename] for output of MIPS to filename" << std::endl;
        return EXIT_FAILURE;
   }
   return EXIT_SUCCESS;
}