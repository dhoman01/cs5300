# Scanning (FA)
* Theory
    * Pumping Lemma - any regular language must be of the form a(b^n)c
        * Proof?
    * Regular Languages
    * FA <=> RE
        * Thompson Construction -- RE -> NFA -> FA -> MFA -> Lexical Analyzer (switch statement with goto's)
* Compiler
    * Lexemes -> Text that matches
    * Tokens
    * etc...

# Parsing (CFG <=> PDA)
* Theory
    * Pumping Lemma - a(b^n)c(d^n)e
    * Given a CFG -> (LRLR Parser)
        * First (set of terminals that begin a derivation of some non-terminal)
        * Follow (set of terminals that immediately follow a derivation of some non-terminal)
        * Item Sets (states in PDA)
        * Look Ahead (annotate each item set with what the next item is)
    * Recursive Descent (no left recursion allowed)
        * Left factoring
    
     