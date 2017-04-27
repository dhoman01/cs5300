.globl main
.text

j main
	# Loaded constant lvalue SIZE with value 30 and type integer
	# Making array type with size 120 of integers
	# (NO MIPS EMITTED) Storing symbol powTwo with type array1 into symbol table
	# (NO MIPS EMITTED) Storing reference parameter a with type array1 into symbol table

printBody:

	# For Statement Begin
	# (NO MIPS EMITTED) Storing symbol i with type integer into symbol table

	# Assigning i the value i
	li $s0 1
	sw $s0 120($gp)
	# Finished assignment of i

	# Loading value from 120($gp) with type integer
	lw $s0 120($gp)
	# Loaded value from i
	# Start of Loop
FB1:
	# Loaded constant lvalue SIZE with value 30 and type integer
	# Loading constant expression
	li $s1 30
	addi $s1 $s1 1
	beq $s0 $s1 FE1

	# Loading value from 120($gp) with type integer
	lw $s1 120($gp)
	# Loaded value from i

	# Loading value from 120($gp) with type integer
	lw $s2 120($gp)
	# Loaded value from i
	# Loading array member from a and index at $s2
	# Shifting index of array a
	addi $s2 $s2 -1
	li $s3 4
	mult $s2 $s3
	mflo $s2
	# Loading reference
	lw $s3 0($fp)
	add $s2 $s2 $s3

	# Loading value from 0($s2) with type integer
	lw $s3 0($s2)
	# Loaded value from 

	# Writing expression to output
	# Loading string const
	la $s4 S1
	# Loaded string S1
	li $v0 4
	ori $a0 $s4 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	li $v0 1
	ori $a0 $s1 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	# Loading string const
	la $s1 S2
	# Loaded string S2
	li $v0 4
	ori $a0 $s1 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	li $v0 1
	ori $a0 $s3 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	li $s3 10
	li $v0 11
	ori $a0 $s3 0
	syscall
	# Finished writing expression to output
	# Incrementing counter i
	addi $s0 $s0 1
	sw $s0 120($gp)
	j FB1
FE1:
	# End of For Statement
	j printEpilogue

	# print Prolouge
print:
	addi $sp $sp -4
	j printBody

	# print Epilogue
printEpilogue:
	addi $sp $sp 4
	jr $ra
main:
	la $gp, GA


	# Begin CPSL Program
	# Loading array member from powTwo and index of 1

	# Assigning  the value 
	li $s2 2
	sw $s2 0($gp)
	# Finished assignment of 

	# For Statement Begin
	# (NO MIPS EMITTED) Storing symbol i with type integer into symbol table

	# Assigning i the value i
	li $s2 2
	sw $s2 132($gp)
	# Finished assignment of i

	# Loading value from 132($gp) with type integer
	lw $s2 132($gp)
	# Loaded value from i
	# Start of Loop
FB2:
	# Loaded constant lvalue SIZE with value 30 and type integer
	# Loading constant expression
	li $s0 30
	addi $s0 $s0 1
	beq $s2 $s0 FE2

	# Loading value from 132($gp) with type integer
	lw $s0 132($gp)
	# Loaded value from i
	# Loading array member from powTwo and index at $s0
	# Shifting index of array powTwo
	addi $s0 $s0 -1
	li $s3 4
	mult $s0 $s3
	mflo $s0
	add $s0 $s0 $gp

	# Loading value from 132($gp) with type integer
	lw $s3 132($gp)
	# Loaded value from i

	# Minus Expression: $s3 - 1
	subi $s1 $s3 1
	# End Minus Expression
	# Loading array member from powTwo and index at $s1
	# Shifting index of array powTwo
	addi $s1 $s1 -1
	li $s3 4
	mult $s1 $s3
	mflo $s1
	add $s1 $s1 $gp

	# Loading value from 0($s1) with type integer
	lw $s3 0($s1)
	# Loaded value from 

	# Mult Expression: $s3 * 2
	li $s4 2
	mult $s3 $s4
	mflo $s4
	# End Mult Expression

	# Assigning  the value at $s4
	sw $s4 0($s0)
	# Finished assignment of 
	# Incrementing counter i
	addi $s2 $s2 1
	sw $s2 132($gp)
	j FB2
FE2:
	# End of For Statement

	# Loading value from 0($gp) with type array1
	lw $s2 0($gp)
	# Loading array location
	addi $s2 $gp 0
	# Loaded value from powTwo

	# print Precall
	addi $sp $sp -24
	# Storing ref to a from expr $s2
	addi $s2 $gp 0
	sw $s2 0($sp)

	# Spilling Registers
	sw $s0 4($sp)
	sw $s1 8($sp)
	sw $s2 12($sp)
	sw $fp 16($sp)
	sw $ra 20($sp)
	ori $fp $sp 0
	jal print
	# print Postcall
	lw $ra 20($sp)
	lw $fp 16($sp)
	lw $s2 12($sp)
	lw $s1 8($sp)
	lw $s0 4($sp)
	addi $sp $sp 24

	# End of CPSL Program

	# Exiting program
	li $v0 10
	syscall
	# Exit syscall invoked

	.data

# Write out string constants
S1: .asciiz "2^"
S2: .asciiz " is "

# Reset alignment to the nearest word and declare global area
.align 2
GA:
