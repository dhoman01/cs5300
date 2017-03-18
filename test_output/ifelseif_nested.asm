.globl main
.text

main:
	la $gp, GA
	ori $fp, $sp, 0
	# Store the true and false const values
	li $a3 1
	sw $a3, 0($gp)
	sw $zero, 4($gp)


	# Begin CPSL Program
	# (NO MIPS EMITTED) Storing symbol i with type integer into symbol table
	# (NO MIPS EMITTED) Storing symbol j with type integer into symbol table

	# Writing expression to output
	# Loading string const
	la $25 S1
	# Loaded string S1
	li $v0 4
	ori $a0 $25 0
	syscall
	# Finished writing expression to output

	# Reading in input from user
	li $v0 5
	syscall
	sw $v0 8($gp)
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished reading input. Stored input in i at 8($gp)

	# Assigning j the value j
	li $25 1
	sw $25 12($gp)
	# Finished assignment of j
	# Loading value from 8($gp) with type integer
	lw $25 8($gp)
	# Loaded value from i

	# Lt Expression: $25 < 5
	slti $24 $25 5
	# End Lt Expression

	# Begin If Statement
	beq $24 $zero IE1

	# Writing expression to output
	# Loading string const
	la $24 S2
	# Loaded string S2
	li $v0 4
	ori $a0 $24 0
	syscall
	# Finished writing expression to output

	# Loading value from 12($gp) with type integer
	lw $24 12($gp)
	# Loaded value from j

	# Equal Expression: $24 = 1
	li $25 1
	seq $25 $24 $25
	# End Equal Expression

	# Begin If Statement
	beq $25 $zero IE2

	# Writing expression to output
	# Loading string const
	la $25 S3
	# Loaded string S3
	li $v0 4
	ori $a0 $25 0
	syscall
	# Finished writing expression to output

	# End If then block (label ID2, IE2)
	j ID2
IE2:

	# End If(ElseIf) Statement (label ID2)
ID2:

	# End If then block (label ID1, IE1)
	j ID1
IE1:

	# Loading value from 8($gp) with type integer
	lw $25 8($gp)
	# Loaded value from i

	# Equal Expression: $25 = 5
	li $24 5
	seq $24 $25 $24
	# End Equal Expression

	# Begin If Statement
	beq $24 $zero IE3

	# Writing expression to output
	# Loading string const
	la $24 S4
	# Loaded string S4
	li $v0 4
	ori $a0 $24 0
	syscall
	# Finished writing expression to output

	# End If then block (label ID3, IE3)
	j ID3
IE3:

	# Writing expression to output
	# Loading string const
	la $24 S5
	# Loaded string S5
	li $v0 4
	ori $a0 $24 0
	syscall
	# Finished writing expression to output

	# End If(ElseIf) Statement (label ID3)
ID3:

	# End If(ElseIf) Statement (label ID1)
ID1:

	# End of CPSL Program

	# Exiting program
	li $v0 10
	syscall
	# Exit syscall invoked

	.data

# Write out string constants
S1: .asciiz "Enter an integer between 1 and 10:"
S2: .asciiz "i less than 5!\n"
S3: .asciiz "j is 1\n"
S4: .asciiz "i is 5!"
S5: .asciiz "i is greater than 5!"

# Reset alignment to the nearest word and declare global area
.align 2
GA:
