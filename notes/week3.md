# Week 3
## Pumping Lemma
 * Used to show some language is not regular "not an automata"
 * If it is an infinite language there must be a loop in the state machine to be regular
 * Must show that there is no loop to show not regular
 * A language is regular if there exists a regular expression that defines it
## Automatic Generation
 * RE->NFA
 * NFA->DFA
 * DFA->MFA
 * MFA->LA
## Thompson's Construction
 * RE to NFA
  * Base Case
  * Alternation
  * Concacenation
  * Closure
## Evaluation TC
 * Simple Transformations for each operator
    * Preserved Properties
    * One start state
    * one end state
    * No transitions from end state
## Subset Construction continue
 * NFA to DFA
## Hopcroft's Algorithm
 * DFA to Minimal DFA
 * Find a set partition of states
  * each set in state must have the same behavior on each input
 * start with start state in one partition and all others in a second
 * find input of which states have different behavior
## Recognizing multiple patterns
 * Multiple FA's
 * slightly different accept
 * back tracking
 * priority
## Table Driven
 * One row per state
 * One column per character
 * Entries are next state
 * Identical columns can be merged into a classifier
## Direct scanners
 * Replace each row (state) in table with code fragment
 * transfer control to correct fragment based on input
 * Violates structured programming, but it is generated
## Hand-code
 * Hand-written to optimize for I/O
