set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-register --std=c++14")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(cpslc CXX)

cmake_minimum_required(VERSION 3.1)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(parser 
             brains/parser.yy
             ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cc)
FLEX_TARGET(lexer
            brains/lexer.l
            ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.cc)
ADD_FLEX_BISON_DEPENDENCY(lexer parser)

enable_testing()

add_executable(cpslc
            main.cpp
            brains/Brain.cpp
            
            ${BISON_parser_OUTPUTS}
            ${FLEX_lexer_OUTPUTS})
target_include_directories(cpslc
    PRIVATE
        .
        ./brains
        ./brains/expressions
        ./brains/statements
        ${CMAKE_CURRENT_BINARY_DIR})
set_property(TARGET cpslc
             PROPERTY CXX_STANDARD 14)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/integration/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/tester)

find_program(BASH_PROGRAM bash)
if (BASH_PROGRAM)
    file(GLOB test_files tests/integration/TestFiles/*.cpsl)
    add_test(NAME IntegrationTests COMMAND ${BASH_PROGRAM} ${CMAKE_CURRENT_BINARY_DIR}/tester/test.sh ${test_files} ${CMAKE_CURRENT_BINARY_DIR}/cpslc)
endif (BASH_PROGRAM)
