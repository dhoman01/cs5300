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

	# For Statement Begin

	# Assigning i the value i
	li $s0 10
	sw $s0 8($gp)
	# Finished assignment of i
	# Loading value from 8($gp) with type integer
	lw $s1 8($gp)
	# Loaded value from i
	# Start of Loop
FB1:
	# Loading constant expression
	li $s2 5
	addi $s2 $s2 -1
	beq $s1 $s2 FE1

	# Loading value from 8($gp) with type integer
	lw $s3 8($gp)
	# Loaded value from i

	# Writing expression to output
	li $v0 1
	ori $a0 $s3 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	# Loading string const
	la $s4 S1
	# Loaded string S1
	li $v0 4
	ori $a0 $s4 0
	syscall
	# Finished writing expression to output
	# Incrementing counter i
	addi $s1 $s1 -1
	sw $s1 8($gp)
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
