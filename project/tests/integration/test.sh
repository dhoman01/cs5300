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

echo -e "${DARK_GREY} using ${1} to compile test programs${NC}"
mkdir -p ${2}

echo -e "${GREEN} Testing arithmetic expressions (and stop statement) using TestFiles/arithmetic.cpsl${NC}"
${1} TestFiles/arithmetic.cpsl -o ${2}/arithmetic.asm
echo -e "${DARK_GREY} Using MARS to run resulting ASM${NC}"
java -Djava.awt.headless=true -jar ${MARSDIR}${MARSJAR} nc 1000000 ${2}/arithmetic.asm > ${2}/arithmetic.out

echo -e "${GREEN} Testing boolean expressions using TestFiles/boolean.cpsl${NC}"
${1} TestFiles/boolean.cpsl -o ${2}/boolean.asm
echo -e "${DARK_GREY} Using MARS to run resulting ASM${NC}"
java -Djava.awt.headless=true -jar ${MARSDIR}${MARSJAR} nc 1000000 ${2}/boolean.asm > ${2}/boolean.out

echo -e "${GREEN} Testing read statement using TestFiles/read_input.cpsl${NC}"
${1} TestFiles/read_input.cpsl -o ${2}/read_input.asm
echo -e "${DARK_GREY} Using MARS to run resulting ASM${NC}"
java -Djava.awt.headless=true -jar ${MARSDIR}${MARSJAR} nc 1000000 ${2}/read_input.asm

echo -e "${GREEN} Finished Tests!!!!${NC}"

exit