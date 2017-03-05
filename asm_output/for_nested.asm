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

	# For Statement Begin
	# Entering new scope for for loop
	# (NO MIPS EMITTED) Storing symbol i with type integer into symbol table

	# Assigning i the value i
	li $25 0
	sw $25 0($fp)
	# Finished assignment of i
	# Loading value from 0($fp) with type integer
	lw $25 0($fp)
	# Loaded value from i
	# Start of Loop
FB1:
	# Loading constant expression
	li $24 5
	addi $24 $24 1
	beq $25 $24 FE1

	# Loading value from 0($fp) with type integer
	lw $23 0($fp)
	# Loaded value from i

	# Writing expression to output
	# Loading string const
	la $22 S1
	# Loaded string S1
	li $v0 4
	ori $a0 $22 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	li $v0 1
	ori $a0 $23 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	# Loading string const
	la $23 S2
	# Loaded string S2
	li $v0 4
	ori $a0 $23 0
	syscall
	# Finished writing expression to output

	# For Statement Begin
	# Entering new scope for for loop
	# (NO MIPS EMITTED) Storing symbol j with type integer into symbol table

	# Assigning j the value j
	li $23 0
	sw $23 8($gp)
	# Finished assignment of j
	# Loading value from 8($gp) with type integer
	lw $23 8($gp)
	# Loaded value from j
	# Start of Loop
FB2:
	# Loading constant expression
	li $22 5
	addi $22 $22 1
	beq $23 $22 FE2

	# Loading value from 8($gp) with type integer
	lw $21 8($gp)
	# Loaded value from j

	# Writing expression to output
	# Loading string const
	la $20 S3
	# Loaded string S3
	li $v0 4
	ori $a0 $20 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	li $v0 1
	ori $a0 $21 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	# Loading string const
	la $21 S4
	# Loaded string S4
	li $v0 4
	ori $a0 $21 0
	syscall
	# Finished writing expression to output
	addi $23 $23 1
	sw $23 8($gp)
	j FB2
FE2:
	# End of For Statement
	# Exited scope for for loop
	addi $25 $25 1
	sw $25 0($fp)
	j FB1
FE1:
	# End of For Statement
	# Exited scope for for loop

	# End of CPSL Program

	# Exiting program
	li $v0 10
	syscall
	# Exit syscall invoked

	.data

# Write out string constants
S1: .asciiz "i = "
S2: .asciiz "\n"
S3: .asciiz "\tj = "
S4: .asciiz "\n"

# Reset alignment to the nearest word and declare global area
.align 2
GA:
