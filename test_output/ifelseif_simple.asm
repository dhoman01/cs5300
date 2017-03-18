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

	# Assigning i the value i
	li $25 3
	sw $25 8($gp)
	# Finished assignment of i
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
	la $24 S1
	# Loaded string S1
	li $v0 4
	ori $a0 $24 0
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
