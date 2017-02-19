set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-deprecated-register")

project(cpslc CXX)

cmake_minimum_required(VERSION 3.1)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(parser 
             parser.yy
             ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cc)
FLEX_TARGET(lexer
            lexer.l
            ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.cc)
ADD_FLEX_BISON_DEPENDENCY(lexer parser)

add_executable(cpslc
    main.cpp
    Brain.cpp
    Expressions.cpp

    ${FLEX_lexer_OUTPUTS}
    ${BISON_parser_OUTPUTS}
)
target_include_directories(cpslc
    PRIVATE
        .
        ${CMAKE_CURRENT_BINARY_DIR})
set_property(TARGET cpslc
             PROPERTY CXX_STANDARD 14)
