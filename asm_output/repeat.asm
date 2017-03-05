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
	li $25 0
	sw $25 8($gp)
	# Finished assignment of i
	# Begin Repeat Statement (label RP1)
RP1:

	# Loading value from 8($gp) with type integer
	lw $25 8($gp)
	# Loaded value from i

	# Writing expression to output
	# Loading string const
	la $24 S1
	# Loaded string S1
	li $v0 4
	ori $a0 $24 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	li $v0 1
	ori $a0 $25 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	# Loading string const
	la $25 S2
	# Loaded string S2
	li $v0 4
	ori $a0 $25 0
	syscall
	# Finished writing expression to output

	# Loading value from 8($gp) with type integer
	lw $25 8($gp)
	# Loaded value from i

	# Plus Expression: $25 + 1
	addi $24 $25 1
	# End Plus Expression

	# Assigning i the value at $24
	sw $24 8($gp)
	# Finished assignment of i
	# Loading value from 8($gp) with type integer
	lw $24 8($gp)
	# Loaded value from i

	# Lt Expression: $24 < 5
	slti $25 $24 5
	# End Lt Expression

	# Repeat Exit Condition (label RP1)
	bne $25 $zero RP1

	# Begin Repeat Statement (label RP2)
RP2:

	# Loading value from 8($gp) with type integer
	lw $25 8($gp)
	# Loaded value from i

	# Writing expression to output
	# Loading string const
	la $24 S3
	# Loaded string S3
	li $v0 4
	ori $a0 $24 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	li $v0 1
	ori $a0 $25 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	# Loading string const
	la $25 S4
	# Loaded string S4
	li $v0 4
	ori $a0 $25 0
	syscall
	# Finished writing expression to output

	# Loading value from 8($gp) with type integer
	lw $25 8($gp)
	# Loaded value from i

	# Plus Expression: $25 + 1
	addi $24 $25 1
	# End Plus Expression

	# Assigning i the value at $24
	sw $24 8($gp)
	# Finished assignment of i
	# Loading value from 8($gp) with type integer
	lw $24 8($gp)
	# Loaded value from i

	# Lt Expression: $24 < 5
	slti $25 $24 5
	# End Lt Expression

	# Repeat Exit Condition (label RP2)
	bne $25 $zero RP2

	# Beginning While Loop (label WB3)
WB3:

	# Loading value from 8($gp) with type integer
	lw $25 8($gp)
	# Loaded value from i

	# Lt Expression: $25 < 5
	slti $24 $25 5
	# End Lt Expression

	# While Header (label WE3)
	beq $24 $zero WE3
	# Writing expression to output
	# Loading string const
	la $24 S5
	# Loaded string S5
	li $v0 4
	ori $a0 $24 0
	syscall
	# Finished writing expression to output

	# End of While Loop (label WB3 - WE3)
	j WB3
WE3:

	# End of CPSL Program

	# Exiting program
	li $v0 10
	syscall
	# Exit syscall invoked

	.data

# Write out string constants
S1: .asciiz "i: "
S2: .asciiz " \n"
S3: .asciiz "should only happen once "
S4: .asciiz " \n"
S5: .asciiz "should not happen"

# Reset alignment to the nearest word and declare global area
.align 2
GA:
