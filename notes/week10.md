## Functions Some More 
**Chandler Cauhth (?sp) Compiler YouTube videos**
```cpsl
function avg(a, b ,c :integer) : integer;
var sum : integer;
begin
    sum := a + b + c;
    return sum / 3;
end;

begin
    write(avg(1,2,3));
end.
```

Symbol Table
----------------
predefined:
    integer type    4
global:
    avg(int, int, int):integer Function avgBegin
local:
    a   integer 0($fp)
    b   integer 4($fp)
    c   integer 8($fp)
    return  integer 12($fp)
    sum integer -4($fp)
```

```mips
avgBegin:
    # Prolouge
    addi $sp, $sp, -4
    # Function Body
    lw $t0, 0($fp)
    lw $t1, 4($fp)
    add $t2, $t0, $t1
    lw $t0, 8($fp)
    add $t1, $t2, $t0
    sw $t1, -4($fp)
    lw $t0, -4($fp)
    li $t1, 3
    div $t0, $t1
    mfhi $t0
    sw $t0, 12($fp)
    j avgEnd
avgEnd:
    # Epilouge
    addi $sp, $sp, 4
    jr $ra

main:
    li $t0, 1
    li $t1, 2
    li $t2, 3
    # Precall
    addi $sp, $sp, -32
    sw $t0, 0($sp)
    sw $t1, 4($sp)
    sw $t2, 8($sp)
    sw $t0, 16($sp)
    sw $t1, 20($sp)
    sw $t2, 24($sp)
    sw $fp, 28($sp)
    sw $ra, 32($sp)
    ori $fp, $sp, 0
    jal avgBegin
    # Postcall
    lw $t3, 12($sp)
    lw $t0, 16($sp)
    lw $t1, 20($sp)
    lw $t2, 24($sp)
    lw $fp, 28($sp)
    lw $ra, 32($sp)
    addi $sp, $sp, 32

    # Write $t3
```

## SWAP procedure
*Procedures don't return anything (void functions)
```cpsl
procdure swap(ref a,b :integer);
var t : integer;
begin
    t := a;
    a := b;
    b := t;
end

var a,b : integer;
begin
    a := 1;
    b := 2;
    swap(a,b);
    write(a, " ", b)
end.
```

Symbol Table
--------------------------
global:
proc    swap(int&, int&)
local:
int&    a   0($fp)
int&    b   4($fp)
int     t   -4($fp)

```mips
swapP:
    # Make room for t
    addi $sp, $sp, -4

    # t := a
    lw $t0, 0($fp)
    lw $t1, 0($t0)
    sw $t1, -4($fp)

    # a := b
    lw $t0, 4($fp)
    lw $t1, 0($t0)
    lw $t0, 0($fp)
    sw $t1, 0($t0)

    # b := t
    lw $t0, -4($fp)
    lw $t1, 4($fp)
    sw $t0, 0($t1)
swapE:
    addi $sp, $sp, 4
    jr $ra

main:
    li $t0, 1
    sw $t0, 0($gp)
    li $t0, 2
    sw $t0, 4($gp)
    addi $sp, $sp -16
    addi $t0, $gp, 0
    sw $t0, 0($sp)
    addi $t0, $gp, 4
    sw $t0, 4($sp)
    sw $ra, 8($sp)
    sw $fp, 12($sp)
    jal swapP
    lw $ra, 8($sp)
    lw $fp, 12($sp)
    addi $sp, $sp, 16
    # Do write
```