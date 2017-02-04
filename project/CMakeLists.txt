cmake_minimum_required(VERSION 3.0.2)
project(cpsl_exe VERSION 0.0.1)

find_package(FLEX)
find_package(BISON)
if(NOT FLEX_FOUND)
    message(FATAL_ERROR "Missing dependancies! Please install flex before running again...")
endif()
if(NOT BISON_FOUND)
    message(FATAL_ERROR "Missing dependancies! Please install bison before running again...")
endif()

BISON_TARGET(parser ../project/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.c VERBOSE ${CMAKE_CURRENT_BINARY_DIR}/parser.log)
FLEX_TARGET(lexer ../project/lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lex.c)
ADD_FLEX_BISON_DEPENDENCY(lexer parser)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++14")

set(main_srcs main.cpp)

set(CMAKE_INSTALL_RPATH ".")
add_executable(cpslcc
    ${main_srcs}
    ${FLEX_lexer_OUTPUTS}
    ${BISON_parser_OUTPUT_SOURCE}
)