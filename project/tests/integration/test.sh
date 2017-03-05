#!/bin/bash
DARK_GREY='\033[1;30m'
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

MARSDIR=./
MARSJAR=mars.jar

if [ -z $1 ]; then
    echo "usage: test.sh /path/to/compiler /path/to/store/ASM"
    exit 1;
fi

echo -e "${DARK_GREY}using ${1} to compile test programs${NC}"
mkdir -p ${2}

echo -e "${GREEN}Testing While statement using TestFiles/while.cpsl${NC}"
${1} TestFiles/while.cpsl -o ${2}/while.asm
echo -e "${DARK_GREY} Using MARS to run resulting ASM${NC}"
java -Djava.awt.headless=true -jar ${MARSDIR}${MARSJAR} nc 1000000 ${2}/while.asm > ${2}/while.out

echo -e "${GREEN}Testing Repeat statement using TestFiles/repeat.cpsl${NC}"
${1} TestFiles/repeat.cpsl -o ${2}/repeat.asm
echo -e "${DARK_GREY} Using MARS to run resulting ASM${NC}"
java -Djava.awt.headless=true -jar ${MARSDIR}${MARSJAR} nc 1000000 ${2}/repeat.asm > ${2}/repeat.out

echo -e "${GREEN}Testing Simple If statement using TestFiles/ifelseif_simple.cpsl${NC}"
${1} TestFiles/ifelseif_simple.cpsl -o ${2}/ifelseif_simple.asm
echo -e "${DARK_GREY} Using MARS to run resulting ASM${NC}"
java -Djava.awt.headless=true -jar ${MARSDIR}${MARSJAR} nc 1000000 ${2}/ifelseif_simple.asm > ${2}/ifelseif_simple.out

echo -e "${GREEN}Testing Nested If statement using TestFiles/ifelseif_nested.cpsl${NC}"
${1} TestFiles/ifelseif_nested.cpsl -o ${2}/ifelseif_nested.asm
echo -e "${DARK_GREY} Using MARS to run resulting ASM${NC}"
java -Djava.awt.headless=true -jar ${MARSDIR}${MARSJAR} nc 1000000 ${2}/ifelseif_nested.asm | tee ${2}/ifelseif_nested.out

echo -e "${GREEN}Testing Simple For To statement using TestFiles/for_to.cpsl${NC}"
${1} TestFiles/for_to.cpsl -o ${2}/for_to.asm
echo -e "${DARK_GREY} Using MARS to run resulting ASM${NC}"
java -Djava.awt.headless=true -jar ${MARSDIR}${MARSJAR} nc 1000000 ${2}/for_to.asm > ${2}/for_to.out

echo -e "${GREEN}Testing Simple For Down To statement using TestFiles/for_down.cpsl${NC}"
${1} TestFiles/for_down.cpsl -o ${2}/for_down.asm
echo -e "${DARK_GREY} Using MARS to run resulting ASM${NC}"
java -Djava.awt.headless=true -jar ${MARSDIR}${MARSJAR} nc 1000000 ${2}/for_down.asm > ${2}/for_down.out

echo -e "${GREEN}Testing Nested For statements using TestFiles/for_nested.cpsl${NC}"
${1} TestFiles/for_nested.cpsl -o ${2}/for_nested.asm
echo -e "${DARK_GREY} Using MARS to run resulting ASM${NC}"
java -Djava.awt.headless=true -jar ${MARSDIR}${MARSJAR} nc 1000000 ${2}/for_nested.asm > ${2}/for_nested.out

echo -e "${GREEN}Finished Tests!!!!${NC}"
echo -e "${DARK_GREY}Output of test files are at ${2}${NC}"

exit