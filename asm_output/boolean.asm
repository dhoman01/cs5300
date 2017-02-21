.globl main
.text

main:   la $gp, GA
	ori $fp, $sp, 0
	# Store the true and false const values
	li $a3 1
	sw $a3, 0($gp)
	sw $zero, 4($gp)


	# Begin CPSL Program

	# Loading value from 0($gp) with type boolean
	lw $25 0($gp)
	# Loaded value from true
	# (NO MIPS EMITTED) Storing symbol a with type boolean into symbol table

	# Loading constant 9928648 into a
	sw $25 8($gp)
	# Loaded constant into a

	# Loading value from 4($gp) with type boolean
	lw $24 4($gp)
	# Loaded value from false
	# (NO MIPS EMITTED) Storing symbol b with type boolean into symbol table

	# Loading constant 9928648 into b
	sw $24 12($gp)
	# Loaded constant into b
	# (NO MIPS EMITTED) Storing symbol c with type boolean into symbol table
	# (NO MIPS EMITTED) Storing symbol d with type integer into symbol table
	# (NO MIPS EMITTED) Storing symbol e with type integer into symbol table

	# Writing expression to output
	# Loading string const
	la $23 S1
	# Loaded string S1
	li $v0 4
	ori $a0 $23 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Writing expression to output
	# Loading string const
	la $23 S2
	# Loaded string S2
	li $v0 4
	ori $a0 $23 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Assigning d the value d
	li $23 10
	sw $23 20($gp)
	# Finished assignment of d
	# Assigning e the value e
	li $23 20
	sw $23 24($gp)
	# Finished assignment of e
	# Writing expression to output
	# Loading string const
	la $23 S3
	# Loaded string S3
	li $v0 4
	ori $a0 $23 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Writing expression to output
	# Loading string const
	la $23 S4
	# Loaded string S4
	li $v0 4
	ori $a0 $23 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Writing expression to output
	# Loading string const
	la $23 S5
	# Loaded string S5
	li $v0 4
	ori $a0 $23 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Loading value from 8($gp) with type boolean
	lw $23 8($gp)
	# Loaded value from a

	# Loading value from 12($gp) with type boolean
	lw $22 12($gp)
	# Loaded value from b

	# And Expression: $23 & $22
	and $21 $23 $22	# End And Expression

	# Assigning c the value at $21
	sw $21 16($gp)
	# Finished assignment of c
	# Loading value from 16($gp) with type boolean
	lw $21 16($gp)
	# Loaded value from c

	# Writing expression to output
	li $v0 1
	ori $a0 $21 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Writing expression to output
	# Loading string const
	la $21 S6
	# Loaded string S6
	li $v0 4
	ori $a0 $21 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Loading value from 8($gp) with type boolean
	lw $21 8($gp)
	# Loaded value from a

	# Loading value from 12($gp) with type boolean
	lw $22 12($gp)
	# Loaded value from b

	# Or Expression: $21 | $22
	or $23 $21 $22	# End Or Expression

	# Assigning c the value at $23
	sw $23 16($gp)
	# Finished assignment of c
	# Loading value from 16($gp) with type boolean
	lw $23 16($gp)
	# Loaded value from c

	# Writing expression to output
	li $v0 1
	ori $a0 $23 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Writing expression to output
	# Loading string const
	la $23 S7
	# Loaded string S7
	li $v0 4
	ori $a0 $23 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Loading value from 20($gp) with type integer
	lw $23 20($gp)
	# Loaded value from d

	# Loading value from 24($gp) with type integer
	lw $22 24($gp)
	# Loaded value from e

	# Gt Expression: $23 > $22
	sgt $21 $23 $22	# End Gt Expression

	# Assigning c the value at $21
	sw $21 16($gp)
	# Finished assignment of c
	# Loading value from 16($gp) with type boolean
	lw $21 16($gp)
	# Loaded value from c

	# Writing expression to output
	li $v0 1
	ori $a0 $21 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Writing expression to output
	# Loading string const
	la $21 S8
	# Loaded string S8
	li $v0 4
	ori $a0 $21 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Loading value from 20($gp) with type integer
	lw $21 20($gp)
	# Loaded value from d

	# Loading value from 24($gp) with type integer
	lw $22 24($gp)
	# Loaded value from e

	# Gt Eq Expression: $21 <= $22
	sge $23 $21 $22	# End Gt Eq Expression

	# Assigning c the value at $23
	sw $23 16($gp)
	# Finished assignment of c
	# Loading value from 16($gp) with type boolean
	lw $23 16($gp)
	# Loaded value from c

	# Writing expression to output
	li $v0 1
	ori $a0 $23 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Writing expression to output
	# Loading string const
	la $23 S9
	# Loaded string S9
	li $v0 4
	ori $a0 $23 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Loading value from 20($gp) with type integer
	lw $23 20($gp)
	# Loaded value from d

	# Loading value from 24($gp) with type integer
	lw $22 24($gp)
	# Loaded value from e

	# Lt Expression: $23 < $22
	slt $21 $23 $22	# End Lt Expression

	# Assigning c the value at $21
	sw $21 16($gp)
	# Finished assignment of c
	# Loading value from 16($gp) with type boolean
	lw $21 16($gp)
	# Loaded value from c

	# Writing expression to output
	li $v0 1
	ori $a0 $21 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Writing expression to output
	# Loading string const
	la $21 S10
	# Loaded string S10
	li $v0 4
	ori $a0 $21 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Loading value from 20($gp) with type integer
	lw $21 20($gp)
	# Loaded value from d

	# Loading value from 24($gp) with type integer
	lw $22 24($gp)
	# Loaded value from e

	# Lt or Eq Expression: $21 <= $22
	sle $23 $21 $22	# End Lt Eq Expression

	# Assigning c the value at $23
	sw $23 16($gp)
	# Finished assignment of c
	# Loading value from 16($gp) with type boolean
	lw $23 16($gp)
	# Loaded value from c

	# Writing expression to output
	li $v0 1
	ori $a0 $23 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Writing expression to output
	# Loading string const
	la $23 S11
	# Loaded string S11
	li $v0 4
	ori $a0 $23 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Loading value from 20($gp) with type integer
	lw $23 20($gp)
	# Loaded value from d

	# Loading value from 24($gp) with type integer
	lw $22 24($gp)
	# Loaded value from e

	# Equal Expression: $23 = $22
	seq $21 $23 $22	# End Equal Expression

	# Assigning c the value at $21
	sw $21 16($gp)
	# Finished assignment of c
	# Loading value from 16($gp) with type boolean
	lw $21 16($gp)
	# Loaded value from c

	# Writing expression to output
	li $v0 1
	ori $a0 $21 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Writing expression to output
	# Loading string const
	la $21 S12
	# Loaded string S12
	li $v0 4
	ori $a0 $21 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Loading value from 20($gp) with type integer
	lw $21 20($gp)
	# Loaded value from d

	# Loading value from 24($gp) with type integer
	lw $22 24($gp)
	# Loaded value from e

	# Not Equal Expression: $21 <> $22
	sne $23 $21 $22	# End Not Equal Expression

	# Assigning c the value at $23
	sw $23 16($gp)
	# Finished assignment of c
	# Loading value from 16($gp) with type boolean
	lw $23 16($gp)
	# Loaded value from c

	# Writing expression to output
	li $v0 1
	ori $a0 $23 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Writing expression to output
	# Loading string const
	la $23 S13
	# Loaded string S13
	li $v0 4
	ori $a0 $23 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Loading value from 8($gp) with type boolean
	lw $23 8($gp)
	# Loaded value from a

	# Not Expression: ~$23
	xori $22 $23 1
	# End Not Expression

	# Assigning c the value at $22
	sw $22 16($gp)
	# Finished assignment of c
	# Loading value from 16($gp) with type boolean
	lw $22 16($gp)
	# Loaded value from c

	# Writing expression to output
	li $v0 1
	ori $a0 $22 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Writing expression to output
	# Loading string const
	la $22 S14
	# Loaded string S14
	li $v0 4
	ori $a0 $22 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Writing expression to output
	# Loading string const
	la $22 S15
	# Loaded string S15
	li $v0 4
	ori $a0 $22 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline
	.data

# Write out string constants
S1: .asciiz "Beginning Program"
S2: .asciiz "-----------------\n"
S3: .asciiz "a=true (1) and b=false(0)"
S4: .asciiz "d=10 and e=20"
S5: .asciiz "\nc := a & b"
S6: .asciiz "\nc := a | b"
S7: .asciiz "\nc := d > e"
S8: .asciiz "\nc := d >= e"
S9: .asciiz "\nc := d < e"
S10: .asciiz "\nc := d <= e"
S11: .asciiz "\nc := d = e"
S12: .asciiz "\nc := d <> e"
S13: .asciiz "\nc := ~a"
S14: .asciiz "\n--------------"
S15: .asciiz "Ending Program"

# Reset alignment to the nearest word and declare global area
.align 2
GA:
