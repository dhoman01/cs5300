.globl main
.text

j main
	# (NO MIPS EMITTED) Storing symbol i with type integer into symbol table
	# (NO MIPS EMITTED) Storing symbol a with type boolean into symbol table
main:
	la $gp, GA
	# Store the true and false const values
	li $v0 1
	sw $v0, 0($gp)
	sw $zero, 4($gp)


	# Begin CPSL Program

	# Assigning i the value i
	li $s0 0
	sw $s0 8($gp)
	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0
	# Finished assignment of i
	# Loading value from 8($gp) with type integer
	lw $s0 8($gp)
	# Loaded value from i

	# Lt Expression: $s0 < 13
	slti $s1 $s0 13
	# Releasing Register $s0
	# Available Registers: 17
	# Registers In Use:    1
	# End Lt Expression

	# Assigning a the value at $s1
	sw $s1 12($gp)
	# Releasing Register $s1
	# Available Registers: 18
	# Registers In Use:    0
	# Finished assignment of a
	# Beginning While Loop (label WB1)
WB1:

	# Loading value from 12($gp) with type boolean
	lw $s1 12($gp)
	# Loaded value from a

	# Loading value from 0($gp) with type boolean
	lw $s0 0($gp)
	# Loaded value from true

	# Equal Expression: $s1 = $s0
	seq $s2 $s1 $s0
	# Releasing Register $s1
	# Available Registers: 16
	# Registers In Use:    2
	# Releasing Register $s0
	# Available Registers: 17
	# Registers In Use:    1
	# End Equal Expression

	# While Header (label WE1)
	beq $s2 $zero WE1	# Releasing Register $s2
	# Available Registers: 18
	# Registers In Use:    0

	# Loading value from 8($gp) with type integer
	lw $s2 8($gp)
	# Loaded value from i

	# Writing expression to output
	# Loading string const
	la $s0 S1
	# Loaded string S1
	li $v0 4
	ori $a0 $s0 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s0
	# Available Registers: 17
	# Registers In Use:    1

	# Writing expression to output
	li $v0 1
	ori $a0 $s2 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s2
	# Available Registers: 18
	# Registers In Use:    0

	# Writing expression to output
	# Loading string const
	la $s2 S2
	# Loaded string S2
	li $v0 4
	ori $a0 $s2 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s2
	# Available Registers: 18
	# Registers In Use:    0

	# Loading value from 8($gp) with type integer
	lw $s2 8($gp)
	# Loaded value from i

	# succ($s2)
	addi $s2 $s2 1
	# End succ()

	# Assigning i the value at $s2
	sw $s2 8($gp)
	# Releasing Register $s2
	# Available Registers: 18
	# Registers In Use:    0
	# Finished assignment of i
	# Loading value from 8($gp) with type integer
	lw $s2 8($gp)
	# Loaded value from i

	# Lt Expression: $s2 < 13
	slti $s0 $s2 13
	# Releasing Register $s2
	# Available Registers: 17
	# Registers In Use:    1
	# End Lt Expression

	# Assigning a the value at $s0
	sw $s0 12($gp)
	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0
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
