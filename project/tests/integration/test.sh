#!/bin/bash
DARK_GREY='\033[1;30m'
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

if [ -z $1 ]; then
    echo "usage: test.sh pattern_for_test_files /path/to/compiler"
    exit 1;
fi

filelist=($@)
echo -e "${DARK_GREY} ${#filelist[@]} file(s) being parsed${NC}"
mkdir parser_logs
PASSED=0
for ((i=0; i < ${#filelist[@]}-1; i++)); do
    filepatharr=(${filelist[$i]//\// })
    filename=${filepatharr[${#filepatharr[@]}-1]}
    echo -e "${DARK_GREY}Parsing ${filelist[$i]}${NC}"
    result="$(${@: -1} ${filelist[$i]})"
    echo "${result}" > parser_logs/${filename}_output.txt
    if [[ $result != *"SYNTAX ERROR"* ]]; then
      echo -e "${GREEN}Successfully parsed ${filename}${NC}"
    else
      echo -e "${RED}Parse errors in ${filename}${RED}"
      PASSED=1
    fi
done

exit ${PASSED}