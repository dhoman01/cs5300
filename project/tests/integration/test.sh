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

echo -e "${GREEN} Testing While statement using TestFiles/while.cpsl${NC}"
${1} TestFiles/while.cpsl -o ${2}/while.asm
echo -e "${DARK_GREY} Using MARS to run resulting ASM${NC}"
java -Djava.awt.headless=true -jar ${MARSDIR}${MARSJAR} nc 1000000 ${2}/while.asm > ${2}/while.out

echo -e "${GREEN} Finished Tests!!!!${NC}"

exit