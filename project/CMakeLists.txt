set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-deprecated-register --std=c++14")

project(cpslc CXX)

cmake_minimum_required(VERSION 3.1)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  list(APPEND CMAKE_FIND_LIBRARY_SUFFIXES ".a")
  find_library(FL_LIBRARY NAMES libfl fl DOC "C:/Program Files (x86)/GnuWin32/lib/libfl.a")
  set(WINDOWS_GNU "C:/Program Files (x86)/GnuWin32/include")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/brains)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/brains/parser)

BISON_TARGET(parser 
             brains/parser/parser.yy
             ${CMAKE_CURRENT_BINARY_DIR}/brains/parser/parser.tab.cc)
FLEX_TARGET(lexer
            brains/parser/lexer.l
            ${CMAKE_CURRENT_BINARY_DIR}/brains/parser/lexer.yy.cc)
ADD_FLEX_BISON_DEPENDENCY(lexer parser)

enable_testing()
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/brains    
    ${CMAKE_CURRENT_SOURCE_DIR}/brains/expressions    
    ${CMAKE_CURRENT_SOURCE_DIR}/brains/parser
    ${CMAKE_CURRENT_SOURCE_DIR}/brains/utils        
    ${CMAKE_CURRENT_SOURCE_DIR}/tests
    ${WINDOWS_GNU}
)

set(main_srcs main.cpp)
source_group("Main" FILES ${main_srcs})

set(brains_srcs
    brains/Brain.hpp
    brains/Brain.cpp 
    
    ${BISON_parser_OUTPUTS}
    ${FLEX_lexer_OUTPTUS}   
    )
source_group("Brains" FILES ${brains_srcs})
set(compiler_srcs ${brains_srcs})

set(expression_srcs
    brains/expressions/Expressions.hpp
    brains/expressions/Expressions.cpp
    )
source_group("Brains/Expressions" FILES ${expression_srcs})
list(APPEND compiler_srcs ${expression_srcs})

set(parser_srcs
    brains/parser/scanner.hpp
    )
source_group("Brains/Parser" FILES ${parser_srcs})
list(APPEND compiler_srcs ${parser_srcs})

set(utils_srcs
    brains/utils/LookupTable.hpp
    brains/utils/structures.hpp
    )
source_group("Brains/Utils" FILES ${utils_srcs})
list(APPEND compiler_srcs ${utils_srcs})

file(GLOB tests tests/unit/*.cpp)
set(test_srcs ${tests}
    tests/main.cpp
    ${BISON_parser_OUTPUTS}
    ${FLEX_lexer_OUTPTUS}
    )
source_group("Testing" FILES ${test_srcs})

set(CMAKE_INSTALL_RPATH ".")
add_library(compiler_common STATIC ${compiler_srcs})

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set_target_properties(compiler_common PROPERTIES MACOSX_RPATH "@loader_path/../lib")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

add_executable(cpslc ${main_srcs})
add_executable(cpslc_test ${test_srcs})

target_include_directories(cpslc
    PRIVATE
        .
        ${CMAKE_CURRENT_BINARY_DIR})
set_property(TARGET cpslc
             PROPERTY CXX_STANDARD 14)

target_link_libraries(cpslc compiler_common)
target_link_libraries(cpslc_test compiler_common)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/integration/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/tester)

add_test(UnitTests cpslc_test)

find_program(BASH_PROGRAM bash)
if (BASH_PROGRAM)
    file(GLOB test_files tests/integration/TestFiles/*.cpsl)
    add_test(NAME IntegrationTests COMMAND ${BASH_PROGRAM} ${CMAKE_CURRENT_BINARY_DIR}/tester/test.sh ${test_files} ${CMAKE_CURRENT_BINARY_DIR}/cpslc)
endif (BASH_PROGRAM)
