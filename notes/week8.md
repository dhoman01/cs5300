## Control Statement Code-Gen
```bison
whileStat -> WhileHdr Block; { cout << "j " << $1;}
whileHdr -> whileHdrBeginHdr whileEndHdr ; { $$ = $1; }
whileHdrBeginHdr -> WHILE ( ; { auto l = getLabel(); cout << l; $$ = 1;} \\ Need unique label { int getLabel(){ static size_t cur = 0; return ++cur; };  }
whileEndHdr -> expr );  { cout << "bne $1, $2, " << getLabel(); }
```

```cpsl
var i:integer

begin
    i := 0
    while( i < 10 )
    begin
        Write(i);
        i := succ(i);
    end
end.
```

```MIPS
# While loop
        li $t0, 0
        sw $t0 0($gp)
# While's WHILE_KEY
WB0:    
        # EXPR
        lw $t0, 0($gp)
        li $t1, 10
        slt $t2, $0, $t1
        # WHILE_HDR
        beq $2, $zero, WE0
        # STMT LIST
        # Write (i)
        # i := succ(i)
        j WB0
# While's END_KEY
WE0:

```

### IF Statement
```cpsl
var x : integer
begin
    read(x);
    if( x < 10)
        then x := x + 10;
    end;
    if( x < 100)
        then write("foo");
    else
        write("bar")
    end
end
```

```MIPS
    # Read x
    ...
    syscall
    lw $t0, 0($gp)
    li $t1, 10
    slt $t0, $t0, $t1
    beq $t2, $zero, IE0
    lw $t0, 0($gp)
    li $t1, 10
    add $t3, $t0, $t1
    sw $t3, 0($gp)
    j ID0
IE0:
ID0:
    lw $t0, 0($gp)
    li $t1, 100
    slt $t2, $t0, $t1
    beq $t2, $zero, IE1
    ...
    syscall
    j ID1
IE1:
    ...
    syscall
    j ID1
ID1:
```


## Aside Item Set
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