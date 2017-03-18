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

	# For Statement Begin

	# Assigning i the value i
	li $25 10
	sw $25 8($gp)
	# Finished assignment of i
	# Loading value from 8($gp) with type integer
	lw $25 8($gp)
	# Loaded value from i
	# Start of Loop
FB1:
	# Loading constant expression
	li $24 5
	addi $24 $24 -1
	beq $25 $24 FE1

	# Loading value from 8($gp) with type integer
	lw $23 8($gp)
	# Loaded value from i

	# Writing expression to output
	li $v0 1
	ori $a0 $23 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	# Loading string const
	la $23 S1
	# Loaded string S1
	li $v0 4
	ori $a0 $23 0
	syscall
	# Finished writing expression to output
	# Incrementing counter i
	addi $25 $25 -1
	sw $25 8($gp)
	j FB1
FE1:
	# End of For Statement

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
