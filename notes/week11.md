"C++ does not hold your hand. It'll happily load the gun and let you shoot yourself" - Dr. Sundberg

```cpsl
const N := 100;

type A : array[0..N] of integer;

procedure merge(ref a : A; var size :integer);
var front, back : A;
    halfPlusOne, i, j, cur : integer;
begin
    for i := 0 to size / 2
    begin
        front[i] = a[i];
    end
    merge(front, size / 2);
    halfPlusOne := size / 2 + 1
    for i := halfPlusOne to size
    begin
        back[i - halfPlusOne] = a[i];
    end
    merge(back, size - halfPlusOne);

    i := 0;
    j := 0;
    cur := 0;
    while(i < size / 2 && j < size - halfPlusOne)
    begin
        if(front[i] < back[j]) then
            a[cur] = front[i];
            i := succ(i);
        else
            a[cur] = back[j];
            j := succ(j);
        end;
        cur := succ(cur);
    end

    $add the rest of the unfinished one
end
```

```mips
# See CS6300 array_arg
aBegin:
    li $t0 'q'
    li $t1 2
    li $t2 2
    sub $t3 $t1 $t2
    li $t1 4
    mult $t3 $t1
    mflo $t3
    add $t3 $t3 $fp
    sw $t0 0($t3)
    lw $t0 16($t3)
    addi $t0 $t0 -2
    li $t1 4
    mult $t0 $t1
    mflo $t0
    add $t0 $t0 $fp
    lw $t1 0($t0)
    sw $t1 20($fp)
    j aEpi
a:
    addi $sp $sp -24
    sw $t0 0($sp)
    sw $t1 4($sp)
    sw $t2 8($sp)
    sw $t3 12($sp)
    j aBegin
aEpi:
    lw $t0 0($sp)
    lw $t1 4($sp)
    lw $t2 8($sp)
    lw $t3 12($sp)
    addi $sp $sp 24
    ja $ra

main:
    # Load the array's values
    # ...
    # first write()
    addi $sp $sp -24
    lw $t0 0($gp)
    sw $t0 0($sp)
    lw $t0 4($gp)
    sw $t0 4($sp)
    lw $t0 8($gp)
    sw $t0 8($sp)
    .
    .
    .
```