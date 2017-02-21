#!/bin/bash
DARK_GREY='\033[1;30m'
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

echo -e "${GREEN} Building CPSL compiler${NC}"
cd project/brains/parser
echo -e "${DARK_GREY} Generating FLEX${NC}"
flex -o lexer.yy.cc lexer.l
echo -e "${DARK_GREY} Generating BISON${NC}"
bison parser.yy
cd ../
echo -e "${DARK_GREY} Compiling compiler${NC}"
g++ ../main.cpp Brain.cpp expressions/Expressions.cpp statements/Statements.cpp parser/parser.tab.cc parser/lexer.yy.cc --std=c++14 -o ../cpslc
echo -e "${GREEN} CPSL compiler located at project/cpslc"
echo -e "${DARK_GREY}"
cd ../
./cpslc
cd ../
echo -e "${NC}"
echo -e "Would you like to run the test script? (y/n)"
read -r res
if [ "$res" == "y" ]; then
    mkdir -p asm_output
    cd project/tests/integration/
    ./test.sh ../../cpslc ../../../asm_output
    cd ../../../
fi
