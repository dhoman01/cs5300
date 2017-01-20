# Week 2
## Terminology
 * Token
  * Type of word
  * Part of speech
  * implemented as enumeration
 * Lexeme
  * Some kinds of token need associated data
  * value derived from matched text
 * Pattern
  * Regular expressions used to recognize tokens
## Keywords
 * reserved identifiers
 * only token kind is significant
## Literals
 * String, Character, or numeric
 * both token kind and lexem are significant

## Operators
 * Like separators
 * no real difference for lexical analyzer
## identifiers
 * Rules for identifiers very by language

## Comments
 * No syntatic meaning
 * No token
 * Scanner (lexer) skips over Comments
 * Detect erros open comment, no close
## Punctuation
 * separators

## Free form v Fixed form
 * Free form
  * white space doesn't matter
  * only token order
 * Fixed form
  * layout is critical
  * primarily used in historical languages
## Ways to construct
 * Scanner Generator - flex
 * Hand written
  * Performance
   * lexical analysis can be bottleneck
   * Minimize processing per Character
   * large I/O Reads
## Case equivalence
 * Some languages are case insensitive
    * Pascal, Ada
 * Some are not
  * C/C++, Java

## Finite Automata
 * Finite Automata === Regular Expression
  * Alphabet is a b
  * The language is the set of all words with even a's and even b's

## Non-deterministic Finite Automata (NFA)
 * epsilon transitions (consumes no input)
 * Equivalence
  * NFA = FA
  * Proof by construction
