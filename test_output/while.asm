.globl main
.text

	# (NO MIPS EMITTED) Storing symbol i with type integer into symbol table
	# (NO MIPS EMITTED) Storing symbol a with type boolean into symbol table
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
	# Loading value from 8($gp) with type integer
	lw $s1 8($gp)
	# Loaded value from i

	# Lt Expression: $s1 < 13
	slti $s2 $s1 13
	# End Lt Expression

	# Assigning a the value at $s2
	sw $s2 12($gp)
	# Finished assignment of a
	# Beginning While Loop (label WB1)
WB1:

	# Loading value from 12($gp) with type boolean
	lw $s3 12($gp)
	# Loaded value from a

	# Loading value from 0($gp) with type boolean
	lw $s4 0($gp)
	# Loaded value from true

	# Equal Expression: $s3 = $s4
	seq $s5 $s3 $s4
	# End Equal Expression

	# While Header (label WE1)
	beq $s5 $zero WE1
	# Loading value from 8($gp) with type integer
	lw $s6 8($gp)
	# Loaded value from i

	# Writing expression to output
	# Loading string const
	la $s7 S1
	# Loaded string S1
	li $v0 4
	ori $a0 $s7 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	li $v0 1
	ori $a0 $s6 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	# Loading string const
	la $t0 S2
	# Loaded string S2
	li $v0 4
	ori $a0 $t0 0
	syscall
	# Finished writing expression to output

	# Loading value from 8($gp) with type integer
	lw $t1 8($gp)
	# Loaded value from i

	# succ($t1)
	addi $t1 $t1 1
	# End succ()

	# Assigning i the value at $t1
	sw $t1 8($gp)
	# Finished assignment of i
	# Loading value from 8($gp) with type integer
	lw $t2 8($gp)
	# Loaded value from i

	# Lt Expression: $t2 < 13
	slti $t3 $t2 13
	# End Lt Expression

	# Assigning a the value at $t3
	sw $t3 12($gp)
	# Finished assignment of a
	# End of While Loop (label WB1 - WE1)
	j WB1
WE1:

	# End of CPSL Program

	# Exiting program
	li $v0 10
	syscall
	# Exit syscall invoked

	.data

# Write out string constants
S1: .asciiz "i "
S2: .asciiz "\n"

# Reset alignment to the nearest word and declare global area
.align 2
GA:
