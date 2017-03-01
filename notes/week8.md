## Control Statement Code-Gen
```bison
whileStat -> WhileHdr Block; { cout << "j " << $1;}
whileHdr -> whileHdrBeginHdr whileEndHdr ; { $$ = $1; }
whileHdrBeginHdr -> WHILE ( ; { auto l = getLabel(); cout << l; $$ = 1;} \\ Need unique label { int getLabel(){ static size_t cur = 0; return ++cur; };  }
whileEndHdr -> expr );  { cout << "bne $1, $2, " << getLabel(); }
```

### Aside Item Set
```cfg
E-> - E
| ( E )
| - V T
...
```
```
0. E'-> E$
1. E -> - E
2. E -> ( E )
3. E -> - V T
4. T -> - E
5. T -> empty
6. V -> a S
7. S -> ( E )
8. S -> empty
```
```states
0. E'-> * E $
   E -> * - E
   E -> * ( E )
   E -> * - V T