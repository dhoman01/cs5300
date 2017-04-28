# User Defined Data Types
## Instructions for Assignment THE FINAL COMPILER
```shell
# Requires Bison 3.0.4, Flex 2.6.0, and a C++14 compiler
$> make
$> make test
```
*Makefile will create build dir with the executable at build/cpslc*

*make test will create Asm/ and Results/ dir in project/tests/integration/*

*it then compares the Results to Base*

*includes all tests from [https://github.com/ksundberg/CS5300](https://github.com/ksundberg/CS5300) as well as some of my own*

## Compiler Executable
```Usage: ./build/cpslc [/path/to/file | --stdio] [-o /path/to/output]```

# Evaluation of what I've accomplished
I have implemented a compiler that can handle simple expressions, control flow, functions/procedures, and user defined data types. I can pass user defined data types by reference. I even have a test file that implements [Gaussian elimination](./project/tests/compiler/TestFiles/linsolv.cpsl) (as we don't have FP numbers, you have to be very selective of the problems you solve). Pretty cool right? My compiler also passes all the test files found in [https://github.com/ksundberg/CS5300](https://github.com/ksundberg/CS5300) as well as some I created to test edge cases the others miss. I know there are probably edge cases I haven't considered and probably not all paths of my code are tested. However, I feel I have gone beyond what was put forth as requirements and therefore should receive a 100%.

# Affect of Random Grading
I received a 100% on all assignments (how many did the grader actually look at? ¯\_(ツ)_/¯ ). I maintained integerity with the test files given in the CS5300 repo so I am pretty sure of my standing. However, part of that confidence was coming from the assumption that somebody else ran my code and reached the same conculsion.
