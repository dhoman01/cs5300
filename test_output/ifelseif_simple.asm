.globl main
.text

j main
	# (NO MIPS EMITTED) Storing symbol i with type integer into symbol table
main:
	la $gp, GA
	# Store the true and false const values
	li $v0 1
	sw $v0, 0($gp)
	sw $zero, 4($gp)


	# Begin CPSL Program

	# Assigning i the value i
	li $s0 3
	sw $s0 8($gp)
	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0
	# Finished assignment of i
	# Loading value from 8($gp) with type integer
	lw $s0 8($gp)
	# Loaded value from i

	# Lt Expression: $s0 < 5
	slti $s1 $s0 5
	# Releasing Register $s0
	# Available Registers: 17
	# Registers In Use:    1
	# End Lt Expression

	# Begin If Statement
	beq $s1 $zero IE1
	# Releasing Register $s1
	# Available Registers: 18
	# Registers In Use:    0

	# Writing expression to output
	# Loading string const
	la $s1 S1
	# Loaded string S1
	li $v0 4
	ori $a0 $s1 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s1
	# Available Registers: 18
	# Registers In Use:    0

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
