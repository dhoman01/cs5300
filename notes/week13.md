## Computing PI * 100
```cpsl
const SIZE := 100;
var i,j,count : integer;

count := 0
for i:=0 to SIZE do
    for j:=0 to SIZE do
        if(i*i + j*j < SIZE * SIZE) then
            count := succ(count);
        end;
    end;
end;
count := count * 4;
write(count / (SIZE * SIZE), ',', count % (SIZE * SIZE));
```

```
st:
i       0($gp)
j       4($gp)
count   8($gp)

values:
*$0 -> 0 gone with A*
*$1 -> SIZE gone with B*
*$2 -> i gone with B*
*$4 -> 0 gone with C*
*$8 -> i gone with E*
*$10 -> j gone with E*

A:
li $0 0
sw $0 8($gp) #count := 0
sw $0 0($gp) #i := 0

B:
li $1 100
lw $2 0($gp)
slt $3 $2 $1 # i < SIZE
beq $3 C ?

C:
li $4 0
sw $4 4($gp) #j := 0

D:
li $5 100
lw $6 4($gp)
slt $7 $6 $ 5 # j < SIZE
beq $7 E ?

E:
li $8 0($gp)
mult $8 $8
mflo $9
li $10 4($gp)
mult $10 $10
mflo $11
add $12 $11 $9
li $13 10000
slt $14 $12 $13
beq $14 ? ?

F:
lw $15 8($gp)
addi $16 $15 1
sw $16 8($gp)

G:
lw $17 4($gp)
addi $18 4($gp)
sw $18 4($gp)
j D

H:
lw $19 0($gp)
addi $20 $19 1
sw $20 0($gp)
j B

I:
lw $21 8($gp)
li $22 4
mult $21 $22
mflo $23
li $24 10000
div $23 $24
mfhi $25
writeint($25)
li $26 '.'
writechar($26)
mflo $27
writeint($27)
```