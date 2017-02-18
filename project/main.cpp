#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "brains/Brain.hpp"

int main( int argc, char **argv )
{
    cpsl::Brain brain;
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 ){
        brain.parse(argv[0]);
        return EXIT_SUCCESS;
    }
    
    brain.parse(std::cin);

    return EXIT_SUCCESS;
}