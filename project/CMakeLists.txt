cmake_minimum_required(VERSION 3.0.2)
project(cpslcc)

find_package(FLEX)
if(NOT FLEX_FOUND)
    message(FATAL_ERROR "Missing dependancies! Please install flex before running again...")
endif()

FLEX_TARGET(scanner ../project/lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)
add_executable(cpslcc
    main.cpp
    ${FLEX_scanner_OUTPUTS}
)