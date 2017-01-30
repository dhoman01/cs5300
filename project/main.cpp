#include <cstdio>

extern FILE* yyin;
extern "C"
{
    int yyparse(void);  
} 

int main( int argc, char **argv )
{
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
            yyin = fopen( argv[0], "r" );
    else
            yyin = stdin;

    yyparse();
}