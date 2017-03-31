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

	# For Statement Begin

	# Assigning i the value i
	li $s0 10
	sw $s0 8($gp)
	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0
	# Finished assignment of i
	# Loading value from 8($gp) with type integer
	lw $s0 8($gp)
	# Loaded value from i
	# Start of Loop
FB1:
	# Loading constant expression
	li $s1 5
	addi $s1 $s1 -1
	beq $s0 $s1 FE1
	# Releasing Register $s1
	# Available Registers: 17
	# Registers In Use:    1

	# Loading value from 8($gp) with type integer
	lw $s1 8($gp)
	# Loaded value from i

	# Writing expression to output
	li $v0 1
	ori $a0 $s1 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s1
	# Available Registers: 17
	# Registers In Use:    1

	# Writing expression to output
	# Loading string const
	la $s1 S1
	# Loaded string S1
	li $v0 4
	ori $a0 $s1 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s1
	# Available Registers: 17
	# Registers In Use:    1
	# Incrementing counter i
	addi $s0 $s0 -1
	sw $s0 8($gp)
	j FB1
FE1:
	# End of For Statement
	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0
	# Releasing Register 
	# Available Registers: 19
	# Registers In Use:    0

	# End of CPSL Program

	# Exiting program
	li $v0 10
	syscall
	# Exit syscall invoked

	.data

# Write out string constants
S1: .asciiz " \n"

# Reset alignment to the nearest word and declare global area
.align 2
GA:
