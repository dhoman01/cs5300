cmake_minimum_required(VERSION 3.1)
project(cpslc VERSION 0.0.3)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  list(APPEND CMAKE_FIND_LIBRARY_SUFFIXES ".a")
  find_library(FL_LIBRARY NAMES libfl fl DOC "C:/Program Files (x86)/GnuWin32/lib/libfl.a")
  set(WINDOWS_GNU "C:/Program Files (x86)/GnuWin32/include")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/brains)


enable_testing()
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/brains
    ${CMAKE_CURRENT_SOURCE_DIR}/tests
    ${WINDOWS_GNU}
)

set(EXTRA_COMPILE_FLAGS "-Wall -g -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_COMPILE_FLAGS}")

set(parser_srcs
    brains/cpsl_lexer.hpp
    ${BISON_cpsl_parser_OUTPUTS}
    ${FLEX_cpsl_lexer_OUTPUTS}
    )
source_group("Parser" FILES ${parser_srcs})
set(compiler_srcs ${parser_srcs})

BISON_TARGET(cpsl_parser brains/parser.ypp ${CMAKE_CURRENT_BINARY_DIR}/brains/cpsl_parser.cpp)
FLEX_TARGET(cpsl_lexer brains/lexer.l ${CMAKE_CURRENT_BINARY_DIR}/brains/cpsl_lexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(cpsl_lexer cpsl_parser)

set(brains_srcs
    brains/cpsl_lexer.hpp
    brains/Brain.hpp
    brains/Brain.cpp
    brains/structures.hpp
    )
source_group("Brains" FILES ${brains_srcs})
list(APPEND compiler_srcs ${brains_srcs})

set(utils_srcs
    brains/utils/LookupTable.hpp
    )
source_group("Brains/Utils" FILES ${utils_srcs})
list(APPEND compiler_srcs ${expression_srcs})

set(expression_srcs
    brains/expressions/Expressions.hpp
    brains/expressions/Expressions.cpp
    )
source_group("Brains/Expressions" FILES ${expression_srcs})
list(APPEND compiler_srcs ${expression_srcs})

set(main_srcs main.cpp)
source_group("Main" FILES ${main_srcs})

file(GLOB tests tests/unit/*.cpp)
set(test_srcs ${tests}
    tests/main.cpp
    ${BISON_cpsl_parser_OUTPUTS}
    ${FLEX_cpsl_lexer_OUTPTUS}
    )
source_group("Testing" FILES ${test_srcs})

set(CMAKE_INSTALL_RPATH ".")
add_library(compiler_common STATIC ${compiler_srcs})

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set_target_properties(compiler_common PROPERTIES MACOSX_RPATH "@loader_path/../lib")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

add_executable(cpslc ${main_srcs})
add_executable(cpslc_test ${test_srcs})

target_link_libraries(compiler_common ${FLEX_LIBRARIES} ${BISON_LIBRARIES})
target_link_libraries(cpslc compiler_common)
target_link_libraries(cpslc_test compiler_common)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/integration/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/tester)

add_test(UnitTests cpslc_test)

find_program(BASH_PROGRAM bash)
if (BASH_PROGRAM)
    file(GLOB test_files tests/integration/TestFiles/*.cpsl)
    add_test(NAME IntegrationTests COMMAND ${BASH_PROGRAM} ${CMAKE_CURRENT_BINARY_DIR}/tester/test.sh ${test_files} ${CMAKE_CURRENT_BINARY_DIR}/cpslc)
endif (BASH_PROGRAM)