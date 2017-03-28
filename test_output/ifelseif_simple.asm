.globl main
.text

	# (NO MIPS EMITTED) Storing symbol i with type integer into symbol table
main:
	la $gp, GA
	ori $fp, $sp, 0
	# Store the true and false const values
	li $v0 1
	sw $v0, 0($gp)
	sw $zero, 4($gp)


	# Begin CPSL Program

	# Assigning i the value i
	li $s0 3
	sw $s0 8($gp)
	# Finished assignment of i
	# Loading value from 8($gp) with type integer
	lw $s1 8($gp)
	# Loaded value from i

	# Lt Expression: $s1 < 5
	slti $s2 $s1 5
	# End Lt Expression

	# Begin If Statement
	beq $s2 $zero IE1

	# Writing expression to output
	# Loading string const
	la $s3 S1
	# Loaded string S1
	li $v0 4
	ori $a0 $s3 0
	syscall
	# Finished writing expression to output

	# End If then block (label ID1, IE1)
	j ID1
IE1:

	# End If(ElseIf) Statement (label ID1)
ID1:

	# End of CPSL Program

	# Exiting program
	li $v0 10
	syscall
	# Exit syscall invoked

	.data

# Write out string constants
S1: .asciiz "i less than 5!\n"

# Reset alignment to the nearest word and declare global area
.align 2
GA:
