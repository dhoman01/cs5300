## Function/Procedure Calls
** In an optimizing compiler, the best optimzition is function in-lining **
### Parts
1. Pre-call
2. Prolouge
3. Function Body
4. Epilouge
5. Post-call


```cpsl
int add(int x)
{
    return x + 1;
}

write(add(3));
```
ST
-------
add(int x) -> int F0
___________
x       int     0($fp)
return  int     4($fp)
```mips
# Prolouge
F0:
    lw $t0, 0($fp)
    addi $t0, $t0, 1
    sw $t0, 4($fp)
    j FE0
FEO:
    jr $ra

# Pre-call
    jal F0
# Post-call
```

## Functions Continued
```cpsl
function fib(n: integer): integer;
begin
    if n <= 1 then
        return 1;
    end;
    return fib(n - 2) + fib(n - 1);
end;

begin
 write(f(5));
end;
```

#### Symbol Table
fib(int) -> int FB0
------ local -------
n      0 $fp
return 4 $fp
```mips
FBO:
    li $t0 1
    lw $t1 0($fp)
    slt $t0 $t0 $t1
    beq $t0 $zero IE0
    li $t0 1
    # Return
    sw $t0 4($fp)
    j FE0
IE0:
    lw $t0 0($fp)
    addi $t0 $t0 -2
    # Save off all of params, return value, and locals
    # One param, one return, one reg, one local, and fp
    addi $sp $sp -20
    sw $t0 0($sp)
    sw $t0 8($sp)
    sw $ra 12($sp)
    sw $fp 16($sp)
    ori $fp $sp 0
    jal FB0
    lw $fp 16($sp)
    lw $ra 12($sp)
    lw $t0 8($sp)
    lw $t1 4($sp)
    addi $sp $sp 20
    lw $t0 0($fp)
    addi $t0 $t0 -1
    # Save off all of params, return value, locals, regs, and fp
    addi $sp $sp -24
    sw $t0 0($sp)
    sw $t0 8($sp)
    sw $t1 12($sp)
    sw $ra 16($sp)
    sw $fp 20($sp)
    jal FB0
    lw $fp 20($sp)
    lw $ra 16($sp)
    lw $t1 12($sp)
    lw $t0 8($sp)
    lw $t0 4($sp)
    addi $sp $sp 24
    add $t0 $t1 $t0
    sw $t0 4($fp)
    j FE0
FE0:
    jr $ra

main:
    li $t0 5
    addi $sp $sp -12
    sw $t0 0($sp)
    sw $fp 8($sp)
    ori $fp $sp 0
    jal FB0
    lw $fp 8($sp)
    lw $t0 4($sp)
    addi $sp $sp 12
```
