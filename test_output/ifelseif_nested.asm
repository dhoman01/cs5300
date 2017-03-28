.globl main
.text
	# (NO MIPS EMITTED) Storing symbol i with type integer into symbol table
	# (NO MIPS EMITTED) Storing symbol j with type integer into symbol table
main:
	ori $fp, $sp, 0
	# Store the true and false const values
	li $v0 1
	sw $v0, 0($gp)
	sw $zero, 4($gp)


	# Begin CPSL Program

	# Writing expression to output
	# Loading string const
	la $s0 S1
	# Loaded string S1
	li $v0 4
	ori $a0 $s0 0
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
	li $s1 1
	sw $s1 12($gp)
	# Finished assignment of j
	# Loading value from 8($gp) with type integer
	lw $s2 8($gp)
	# Loaded value from i

	# Lt Expression: $s2 < 5
	slti $s3 $s2 5
	# End Lt Expression

	# Begin If Statement
	beq $s3 $zero IE1

	# Writing expression to output
	# Loading string const
	la $s4 S2
	# Loaded string S2
	li $v0 4
	ori $a0 $s4 0
	syscall
	# Finished writing expression to output

	# Loading value from 12($gp) with type integer
	lw $s5 12($gp)
	# Loaded value from j

	# Equal Expression: $s5 = 1
	li $s6 1
	seq $s6 $s5 $s6
	# End Equal Expression

	# Begin If Statement
	beq $s6 $zero IE2

	# Writing expression to output
	# Loading string const
	la $s7 S3
	# Loaded string S3
	li $v0 4
	ori $a0 $s7 0
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
	lw $t0 8($gp)
	# Loaded value from i

	# Equal Expression: $t0 = 5
	li $t1 5
	seq $t1 $t0 $t1
	# End Equal Expression

	# Begin If Statement
	beq $t1 $zero IE3

	# Writing expression to output
	# Loading string const
	la $t2 S4
	# Loaded string S4
	li $v0 4
	ori $a0 $t2 0
	syscall
	# Finished writing expression to output

	# End If then block (label ID3, IE3)
	j ID3
IE3:

	# Writing expression to output
	# Loading string const
	la $t3 S5
	# Loaded string S5
	li $v0 4
	ori $a0 $t3 0
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
