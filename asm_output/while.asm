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
	# (NO MIPS EMITTED) Storing symbol a with type boolean into symbol table

	# Assigning i the value i
	li $25 0
	sw $25 8($gp)
	# Finished assignment of i
	# Loading value from 8($gp) with type integer
	lw $25 8($gp)
	# Loaded value from i

	# Lt Expression: $25 < 13
	slti $24 $25 13
	# End Lt Expression

	# Assigning a the value at $24
	sw $24 12($gp)
	# Finished assignment of a
	# Beginning While Loop (label WB1)
WB1:

	# Loading value from 12($gp) with type boolean
	lw $24 12($gp)
	# Loaded value from a

	# Loading value from 0($gp) with type boolean
	lw $25 0($gp)
	# Loaded value from true

	# Equal Expression: $24 = $25
	seq $23 $24 $25
	# End Equal Expression

	# While Header (label WE1)
	beq $23 $zero WE1
	# Loading value from 8($gp) with type integer
	lw $23 8($gp)
	# Loaded value from i

	# Writing expression to output
	# Loading string const
	la $25 S1
	# Loaded string S1
	li $v0 4
	ori $a0 $25 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	li $v0 1
	ori $a0 $23 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Loading value from 8($gp) with type integer
	lw $23 8($gp)
	# Loaded value from i

	# succ($23)
	addi $23 $23 1
	# End succ()

	# Assigning i the value at $23
	sw $23 8($gp)
	# Finished assignment of i
	# Loading value from 8($gp) with type integer
	lw $23 8($gp)
	# Loaded value from i

	# Lt Expression: $23 < 13
	slti $25 $23 13
	# End Lt Expression

	# Assigning a the value at $25
	sw $25 12($gp)
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

# Reset alignment to the nearest word and declare global area
.align 2
GA:
