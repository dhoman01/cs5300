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
