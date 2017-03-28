set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-register --std=c++14")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(cpslc CXX)

cmake_minimum_required(VERSION 3.1)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/parser)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/utils)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/brains/parser/scanner.hpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/parser)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/brains/utils/structures.hpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/utils)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/brains/Brain.hpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
BISON_TARGET(parser 
             brains/parser/parser.yy
             ${CMAKE_CURRENT_BINARY_DIR}/parser/parser.tab.cc)
FLEX_TARGET(lexer
            brains/parser/lexer.l
            ${CMAKE_CURRENT_BINARY_DIR}/parser/lexer.yy.cc)
ADD_FLEX_BISON_DEPENDENCY(lexer parser)

enable_testing()

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/brains
    ${CMAKE_CURRENT_SOURCE_DIR}/tests
)

set(main_srcs main.cpp)

set(brains_srcs
    brains/Brain.hpp
    brains/Brain.cpp
    brains/expressions/Expressions.hpp
    brains/expressions/Expressions.cpp
    brains/statements/Statements.hpp
    brains/statements/Statements.cpp
    brains/utils/LookupTable.hpp
    brains/utils/structures.hpp
    brains/parser/scanner.hpp
    ${BISON_parser_OUTPUTS}
    ${FLEX_scanner_OUTPUTS})

add_library(compiler_common STATIC ${brains_srcs})
add_executable(cpslc ${main_srcs})
target_link_libraries(compiler_common ${FLEX_LIBRARIES} ${BISON_LIBRARIES})
target_link_libraries(cpslc compiler_common)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/integration/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/tester)

find_program(BASH_PROGRAM bash)
if (BASH_PROGRAM)
    file(GLOB test_files tests/integration/TestFiles/*.cpsl)
    add_test(NAME IntegrationTests COMMAND ${BASH_PROGRAM} ${CMAKE_CURRENT_BINARY_DIR}/tester/test.sh ${test_files} ${CMAKE_CURRENT_BINARY_DIR}/cpslc)
endif (BASH_PROGRAM)
