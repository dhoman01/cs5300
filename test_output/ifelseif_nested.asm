.globl main
.text

j main
	# (NO MIPS EMITTED) Storing symbol i with type integer into symbol table
	# (NO MIPS EMITTED) Storing symbol j with type integer into symbol table
main:
	la $gp, GA
	# Store the true and false const values
	li $v0 1
	sw $v0, 0($gp)
	sw $zero, 4($gp)


	# Begin CPSL Program

	# Writing expression to output
	# Loading string const
	la $s0 S1
	# Loaded string S1
	li $v0 4
	ori $a0 $s0 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0

	# Reading in input from user
	li $v0 5
	syscall
	sw $v0 8($gp)
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished reading input. Stored input in i at 8($gp)

	# Assigning j the value j
	li $s0 1
	sw $s0 12($gp)
	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0
	# Finished assignment of j
	# Loading value from 8($gp) with type integer
	lw $s0 8($gp)
	# Loaded value from i

	# Lt Expression: $s0 < 5
	slti $s1 $s0 5
	# Releasing Register $s0
	# Available Registers: 17
	# Registers In Use:    1
	# End Lt Expression

	# Begin If Statement
	beq $s1 $zero IE1
	# Releasing Register $s1
	# Available Registers: 18
	# Registers In Use:    0

	# Writing expression to output
	# Loading string const
	la $s1 S2
	# Loaded string S2
	li $v0 4
	ori $a0 $s1 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s1
	# Available Registers: 18
	# Registers In Use:    0

	# Loading value from 12($gp) with type integer
	lw $s1 12($gp)
	# Loaded value from j

	# Equal Expression: $s1 = 1
	li $s0 1
	seq $s0 $s1 $s0
	# Releasing Register $s1
	# Available Registers: 17
	# Registers In Use:    1
	# End Equal Expression

	# Begin If Statement
	beq $s0 $zero IE2
	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0

	# Writing expression to output
	# Loading string const
	la $s0 S3
	# Loaded string S3
	li $v0 4
	ori $a0 $s0 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0

	# End If then block (label ID2, IE2)
	j ID2
IE2:

	# End If(ElseIf) Statement (label ID2)
ID2:

	# End If then block (label ID1, IE1)
	j ID1
IE1:

	# Loading value from 8($gp) with type integer
	lw $s0 8($gp)
	# Loaded value from i

	# Equal Expression: $s0 = 5
	li $s1 5
	seq $s1 $s0 $s1
	# Releasing Register $s0
	# Available Registers: 17
	# Registers In Use:    1
	# End Equal Expression

	# Begin If Statement
	beq $s1 $zero IE3
	# Releasing Register $s1
	# Available Registers: 18
	# Registers In Use:    0

	# Writing expression to output
	# Loading string const
	la $s1 S4
	# Loaded string S4
	li $v0 4
	ori $a0 $s1 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s1
	# Available Registers: 18
	# Registers In Use:    0

	# End If then block (label ID3, IE3)
	j ID3
IE3:

	# Loading value from 8($gp) with type integer
	lw $s1 8($gp)
	# Loaded value from i

	# Lt Expression: $s1 < 10
	slti $s0 $s1 10
	# Releasing Register $s1
	# Available Registers: 17
	# Registers In Use:    1
	# End Lt Expression

	# Begin If Statement
	beq $s0 $zero IE4
	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0

	# Writing expression to output
	# Loading string const
	la $s0 S5
	# Loaded string S5
	li $v0 4
	ori $a0 $s0 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0

	# End If then block (label ID4, IE4)
	j ID4
IE4:

	# Writing expression to output
	# Loading string const
	la $s0 S6
	# Loaded string S6
	li $v0 4
	ori $a0 $s0 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0

	# End If(ElseIf) Statement (label ID3)
ID3:

	# End If(ElseIf) Statement (label ID4)
ID4:

	# End If(ElseIf) Statement (label ID1)
ID1:

	# End of CPSL Program

	# Exiting program
	li $v0 10
	syscall
	# Exit syscall invoked

	.data

# Write out string constants
S1: .asciiz "Enter an integer between 1 and 10:"
S2: .asciiz "i less than 5!\n"
S3: .asciiz "j is 1\n"
S4: .asciiz "i is 5!"
S5: .asciiz "i is greater than 5, but less than 10!"
S6: .asciiz "i is 10!"

# Reset alignment to the nearest word and declare global area
.align 2
GA:
