# Arrays and Records
```cpsl
type string = array[0..100] of char;
    person : record
        {
            name : string;
            address : string;
            age : integer;
        }

    personnel = array[0..10] of person;

var gPersonnel : personnel;
    i : integer;
begin 
    gPersonnel[5].address[i] = ' ';
end.
```

```mips
# Load i
lw $t0 8040($gp)

# Adjust to array offset
addi $t0 $t0 -1

li $t1 4
mult $t0 $t1
mflo $t0

add $t0 $t0 $gp

li $t1 32
sw $t1 3616($t0)
```