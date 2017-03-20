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