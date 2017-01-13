# Week 1
# Intro
## Admin
Compiler - 70%

Exams - 30%

## Required Software (minimums)
gcc 4.8.1

flex 2.5.4

bison 2.5

CMake or gmake

Mars (MIPS Simulator)

*need flex now, bison for the second*


## What were doing
* simple Compiler
* language is PASCAL-like
* Only integral types and string constants
* MIPS is the target architecture
* Beware - sometimes the dragon wins

---
# Compilers

## Preprocessing Chain
 * Preprocessor
 * Compiler
 * Assembler
 * Linker
 * Loader

## Front End
 * Responsible for language dependent portions
 * Lexical, syntax, and semantic analysis
 * Intermediate code generation

## Optimizer
 * Most work done here
 * Intermediate code to better intermediate code
 * Independent of both source and target language
 * Most complicated part

## Back End
 * Responsible for target dependent options
 * Code generator and machine dependent optimizations

This ^^^ paradigm has these advantages
 * mix and Match front ends and back end
 * new languages only require a front end
 * new machines only require a back end

## Phases
### Scanning
 * Lexical analysis
 * Regular language
 * Transform character stream into tokens

### Parsing
 * syntax analysis
 * context free grammar
 * transform token stream to syntax tree

### Code Generation
 * May include optimization
 * Transform syntax tree to executable code

## Generations
 * First generation - machine code
 * Second generation - assembly code
 * Third generation - general purpose languages
 * Fourth generation - special purpose languages

## Types of languages
 * Imperative vs. Declarative
 * High level vs. Low level

---

# MIPS
## MIPS
 * Microprocessor without interlocked pipeline stages
 * Developed in 1981 by John L. Hennessy
 * One of the first RISC architecture
 
## Signed v. Unsigned
 * signed integers are stored as 2's complement
 * unsigned integers are stored as binary
 * The different formats can not be:
  * compared
  * used in the same expression
  * safely converted

## Co-processor
 * floating point instructions on floating point co-processor
 * Co-processor has different set of instructions

## Load / Store
 * li
 * la
 * lw
 * sw

## Arithmetic
 * add, addi, addu, addiu
 * sub, subu
 * mult, multu
 * div, divu
 * mfhi, mflo - Used to get results of mult ad div

## Conditionals
 * slt, sltu, slti, sltiu
 * and, andi
 * or, ori
 * nor

## Branching
 * beq, bne
 * j, jr, jal

## Types
 * 32 registers $0 - $31
 * mnemonic names to help remember usage

## Reserved
 * $zero - Always 0
 * $at - Assembler Temporary
 * $k0, $k1 - Reserved for Kernal

## Variables
 * $s0 - $s7 - Saved registers
 * $t0 - $t9 - Temporary registers

## Function Calls
 * $v0, $v1 - Return values
 * $a0 - $a3 - Arguments
 * $ra - return address - set by jal

## Memory Management
 * $gp - Global pointer
 * $sp - Stack pointer
 * $fp - Frame pointer

## Conventions
 * The following registers must have the same value after a function call returns as they had before the function call:
  * Saved registers
  **Finish from slides**

## syscall
 * I/O provided by Simulator
 * put system call number into $v0
 * 1 - print integer - $a0 contains integer to print
 * 4 - print string - $a0 contains address of string
 * 5 - read integer - $v0 contains integer value
 * 8 - read string - $a0 contains buffer, $a1 contains length
 * 10 - exit

## Distance

## Sum of array
'''mips
li $t1, 0 #has index
loopbegin:  beq $t1, $a1, loopend
                add $t3, $t1, $a0
                lw $t2, 0($t3)
                add $v0, $t2, $v0
                addi $t1, $t1, 1
                j loopbeg

loopend:
'''

## Write Recursive Factorial