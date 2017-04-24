# Final Review
## Scanning and Parsing
* Pumping Lemma (x2)
    * Not regular
    * Not context free
* Thompson's Construction
* RE -> NFA -> FA -> MFA -> LA
* First and Follow, items sets, CFG, Parsing

## Code-Gen
* Symbol Table
    * Memory allocation
    * Scope Rules
    * UDT (user defined data-types)
* Translation
    * CPSL -> MIPS
* Generate MIPS for given CPSL
* Offsets of variables
* Functions Calls
    * precall
    * postcall
    * prologue
    * epilogue
## Optimizations
### Preform (MIPS to better MIPS)
* Common Sub-expression Elimination
* Constant Folding
* Register Allocations

### Know About
* Loop unroll and Loop jam
* Function Inlining
* Data Flow Analysis
* Single-Static Assignment
    * Need to have an infinite Register space
    * Assign to a register and never assign again
    * In source code (C++) AAA (almost always auto)
        * Only assign to a variable once

