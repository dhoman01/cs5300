## Control Statement Code-Gen
```bison
whileStat -> WhileHdr Block; { cout << "j " << $1;}
whileHdr -> whileHdrBeginHdr whileEndHdr ; { $$ = $1; }
whileHdrBeginHdr -> WHILE ( ; { auto l = getLabel(); cout << l; $$ = 1;} \\ Need unique label { int getLabel(){ static size_t cur = 0; return ++cur; };  }
whileEndHdr -> expr );  { cout << "bne $1, $2, " << getLabel(); }
```