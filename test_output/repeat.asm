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
	li $s0 0
	sw $s0 8($gp)
	# Finished assignment of i
	# Begin Repeat Statement (label RP1)
RP1:

	# Loading value from 8($gp) with type integer
	lw $s1 8($gp)
	# Loaded value from i

	# Writing expression to output
	# Loading string const
	la $s2 S1
	# Loaded string S1
	li $v0 4
	ori $a0 $s2 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	li $v0 1
	ori $a0 $s1 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	# Loading string const
	la $s3 S2
	# Loaded string S2
	li $v0 4
	ori $a0 $s3 0
	syscall
	# Finished writing expression to output

	# Loading value from 8($gp) with type integer
	lw $s4 8($gp)
	# Loaded value from i

	# Plus Expression: $s4 + 1
	addi $s5 $s4 1
	# End Plus Expression

	# Assigning i the value at $s5
	sw $s5 8($gp)
	# Finished assignment of i
	# Loading value from 8($gp) with type integer
	lw $s6 8($gp)
	# Loaded value from i

	# Lt Expression: $s6 < 5
	slti $s7 $s6 5
	# End Lt Expression

	# Repeat Exit Condition (label RP1)
	bne $s7 $zero RP1

	# Begin Repeat Statement (label RP2)
RP2:

	# Loading value from 8($gp) with type integer
	lw $t0 8($gp)
	# Loaded value from i

	# Writing expression to output
	# Loading string const
	la $t1 S3
	# Loaded string S3
	li $v0 4
	ori $a0 $t1 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	li $v0 1
	ori $a0 $t0 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	# Loading string const
	la $t2 S4
	# Loaded string S4
	li $v0 4
	ori $a0 $t2 0
	syscall
	# Finished writing expression to output

	# Loading value from 8($gp) with type integer
	lw $t3 8($gp)
	# Loaded value from i

	# Plus Expression: $t3 + 1
	addi $t4 $t3 1
	# End Plus Expression

	# Assigning i the value at $t4
	sw $t4 8($gp)
	# Finished assignment of i
	# Loading value from 8($gp) with type integer
	lw $t5 8($gp)
	# Loaded value from i

	# Lt Expression: $t5 < 5
	slti $t6 $t5 5
	# End Lt Expression

	# Repeat Exit Condition (label RP2)
	bne $t6 $zero RP2

	# Beginning While Loop (label WB3)
WB3:

	# Loading value from 8($gp) with type integer
	lw $t7 8($gp)
	# Loaded value from i

	# Lt Expression: $t7 < 5
	slti $a0 $t7 5
	# End Lt Expression

	# While Header (label WE3)
	beq $a0 $zero WE3
	# Writing expression to output
	# Loading string const
	la $a1 S5
	# Loaded string S5
	li $v0 4
	ori $a0 $a1 0
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
