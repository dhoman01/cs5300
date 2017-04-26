#!/bin/bash
DARK_GREY='\033[1;30m'
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

on_die()
{
  echo
  exit 0;
}

cd `dirname "$0"`

TESTDIR=TestFiles/ #test files directory (where all test.cpsl files are)
RESULTS=Results/ #results folder (where to store cpsl run results for comparison)
BASE=Base/ #base folder name (contains results to compare against)

CPSLDIR=../../../build/ #where cpsl compiler binary lives
BINARY=cpslc #binary name
ASM=Asm/ #tmp directory for asm files for mars to run

MARSDIR=./
MARSJAR=mars.jar

if [ -z $1 ]; then
  pushd . >> /dev/null
  cd ${TESTDIR}
  files=`ls *.cpsl`
  popd >>/dev/null
else
  files=$1
fi

#create these directories if they don't exist already
mkdir -p $ASM $RESULTS

trap on_die SIGINT
trap on_die TERM

for file in $files; do
    filename=$(basename "$file")
    filename="${filename%.*}.asm"

    if [[ ! -f ${TESTDIR}${file} ]]; then
        echo -e "${RED}File '${file}' not found${NC}"
        continue
    fi

    ${CPSLDIR}${BINARY} ${TESTDIR}${file} -o ${ASM}${filename}

    if [ $? -ne 0 ]; then
        echo -e "${RED}Error running: ${CPSLDIR}${BINARY} ${TESTDIR}${file} > ${ASM}${filename}${NC}"
        continue
    fi

    printf "${DARK_GREY}Executing: %-40s" ${file}
    java -Djava.awt.headless=true -jar ${MARSDIR}${MARSJAR} nc 1000000 ${ASM}${filename} > ${RESULTS}${file}

    if [ $? -ne 0 ]; then
        echo -e "${RED}Error running: java -jar nc 1000000 ${MARSDIR}${MARSJAR} ${ASM}${filename} > ${RESULTS}${file}${NC}"
        continue
    fi
    printf "${GREEN}%4b${NC}\n" "\u2713"

    cmp ${RESULTS}${file} ${BASE}${file}
done

exit