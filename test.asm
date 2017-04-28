.globl main
.text

j main

	# DEBUG: 1:9

	# DEBUG: 1:5
	# (NO MIPS EMITTED) Storing symbol s with type string into symbol table

	# DEBUG: 2:28

	# DEBUG: 2:17
	# (NO MIPS EMITTED) Storing  parameter name with type string and offset of 0 into symbol table

	# DEBUG: 2:1

helloBody:

	# DEBUG: 4:7

	# DEBUG: 4:17
	# Loading lvalue name from symbol table

	# DEBUG: 4:17
	# Loading value from 0($fp) with type string
	lw $s0 0($fp)
	# Loaded value from name

	# DEBUG: 4:23

	# DEBUG: 4:28

	# DEBUG: 4:1

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


	# Writing expression to output
	li $v0 4
	ori $a0 $s0 0
	syscall
	# Finished writing expression to output

	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0


	# Writing expression to output
	li $s0 33
	li $v0 11
	ori $a0 $s0 0
	syscall
	# Finished writing expression to output

	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0


	# Writing expression to output
	li $s0 10
	li $v0 11
	ori $a0 $s0 0
	syscall
	# Finished writing expression to output

	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0


	# DEBUG: 2:1
	j helloEpilogue

	# hello Prolouge
hello:
	j helloBody

	# hello Epilogue
helloEpilogue:
	jr $ra
main:
	la $gp, GA


	# Begin CPSL Program

	# DEBUG: 8:1
	# Loading lvalue s from symbol table

	# DEBUG: 8:5

	# DEBUG: 8:1

	# Assigning s the value at S2
la $s0 S2
sw $s0 0($gp)

	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0

	# Finished assignment of s

	# DEBUG: 9:7
	# Loading lvalue s from symbol table

	# DEBUG: 9:7
	# Loading value from 0($gp) with type string
	lw $s0 0($gp)
	# Loaded value from s

	# DEBUG: 9:1

	# hello Precall
	addi $sp $sp -16
	sw $s0 0($sp)

	# Spilling Registers
	sw $s0 4($sp)

	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0


	# Spilling Register:      $s0
	# # of Spilled Registers: 1

	sw $fp 8($sp)
	sw $ra 12($sp)
	ori $fp $sp 0
	jal hello

	# DEBUG: 9:1
	# hello Postcall
	lw $ra 12($sp)
	lw $fp 8($sp)
	lw $s0 4($sp)
	addi $sp $sp 16

	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0


	# End of CPSL Program

	# Exiting program
	li $v0 10
	syscall
	# Exit syscall invoked

	.data

# Write out string constants
S1: .asciiz "Hello "
S2: .asciiz "Dave"

# Reset alignment to the nearest word and declare global area
.align 2
GA:
