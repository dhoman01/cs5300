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

	# For Statement Begin

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
	# Start of Loop
FB1:
	# Loading constant expression
	li $s1 5
	addi $s1 $s1 1
	beq $s0 $s1 FE1
	# Releasing Register $s1
	# Available Registers: 17
	# Registers In Use:    1

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
	# Releasing Register $s2
	# Available Registers: 16
	# Registers In Use:    2

	# Writing expression to output
	li $v0 1
	ori $a0 $s1 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s1
	# Available Registers: 17
	# Registers In Use:    1

	# Writing expression to output
	# Loading string const
	la $s1 S2
	# Loaded string S2
	li $v0 4
	ori $a0 $s1 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s1
	# Available Registers: 17
	# Registers In Use:    1

	# Loading value from 8($gp) with type integer
	lw $s1 8($gp)
	# Loaded value from i

	# For Statement Begin

	# Assigning j the value at $s1
	sw $s1 12($gp)
	# Releasing Register $s1
	# Available Registers: 17
	# Registers In Use:    1
	# Finished assignment of j
	# Loading value from 12($gp) with type integer
	lw $s1 12($gp)
	# Loaded value from j
	# Start of Loop
FB2:
	# Loading constant expression
	li $s2 0
	addi $s2 $s2 -1
	beq $s1 $s2 FE2
	# Releasing Register $s2
	# Available Registers: 16
	# Registers In Use:    2

	# Loading value from 12($gp) with type integer
	lw $s2 12($gp)
	# Loaded value from j

	# Writing expression to output
	# Loading string const
	la $s3 S3
	# Loaded string S3
	li $v0 4
	ori $a0 $s3 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s3
	# Available Registers: 15
	# Registers In Use:    3

	# Writing expression to output
	li $v0 1
	ori $a0 $s2 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s2
	# Available Registers: 16
	# Registers In Use:    2

	# Writing expression to output
	# Loading string const
	la $s2 S4
	# Loaded string S4
	li $v0 4
	ori $a0 $s2 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s2
	# Available Registers: 16
	# Registers In Use:    2
	# Incrementing counter j
	addi $s1 $s1 -1
	sw $s1 12($gp)
	j FB2
FE2:
	# End of For Statement
	# Releasing Register $s1
	# Available Registers: 17
	# Registers In Use:    1
	# Releasing Register 
	# Available Registers: 18
	# Registers In Use:    1
	# Incrementing counter i
	addi $s0 $s0 1
	sw $s0 8($gp)
	j FB1
FE1:
	# End of For Statement
	# Releasing Register $s0
	# Available Registers: 19
	# Registers In Use:    0
	# Releasing Register 
	# Available Registers: 19
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
	# Available Registers: 19
	# Registers In Use:    0

	# For Statement Begin

	# Assigning i the value i
	li $s0 5
	sw $s0 8($gp)
	# Releasing Register $s0
	# Available Registers: 19
	# Registers In Use:    0
	# Finished assignment of i
	# Loading value from 8($gp) with type integer
	lw $s0 8($gp)
	# Loaded value from i
	# Start of Loop
FB3:
	# Loading constant expression
	li  0
	addi   -1
	beq $s0  FE3
	# Releasing Register 
	# Available Registers: 18
	# Registers In Use:    1

	# Loading value from 8($gp) with type integer
	lw  8($gp)
	# Loaded value from i

	# Writing expression to output
	# Loading string const
	la $s1 S6
	# Loaded string S6
	li $v0 4
	ori $a0 $s1 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s1
	# Available Registers: 17
	# Registers In Use:    2

	# Writing expression to output
	li $v0 1
	ori $a0  0
	syscall
	# Finished writing expression to output
	# Releasing Register 
	# Available Registers: 18
	# Registers In Use:    1

	# Writing expression to output
	# Loading string const
	la  S7
	# Loaded string S7
	li $v0 4
	ori $a0  0
	syscall
	# Finished writing expression to output
	# Releasing Register 
	# Available Registers: 18
	# Registers In Use:    1

	# Loading value from 8($gp) with type integer
	lw  8($gp)
	# Loaded value from i

	# For Statement Begin

	# Assigning j the value at 
	sw  12($gp)
	# Releasing Register 
	# Available Registers: 18
	# Registers In Use:    1
	# Finished assignment of j
	# Loading value from 12($gp) with type integer
	lw  12($gp)
	# Loaded value from j
	# Start of Loop
FB4:
	# Loading constant expression
	li $s1 5
	addi $s1 $s1 1
	beq  $s1 FE4
	# Releasing Register $s1
	# Available Registers: 17
	# Registers In Use:    2

	# Loading value from 12($gp) with type integer
	lw $s1 12($gp)
	# Loaded value from j

	# Writing expression to output
	# Loading string const
	la $s2 S8
	# Loaded string S8
	li $v0 4
	ori $a0 $s2 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s2
	# Available Registers: 16
	# Registers In Use:    3

	# Writing expression to output
	li $v0 1
	ori $a0 $s1 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s1
	# Available Registers: 17
	# Registers In Use:    2

	# Writing expression to output
	# Loading string const
	la $s1 S9
	# Loaded string S9
	li $v0 4
	ori $a0 $s1 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s1
	# Available Registers: 17
	# Registers In Use:    2
	# Incrementing counter j
	addi   1
	sw  12($gp)
	j FB4
FE4:
	# End of For Statement
	# Releasing Register 
	# Available Registers: 18
	# Registers In Use:    1
	# Releasing Register 
	# Available Registers: 18
	# Registers In Use:    1
	# Incrementing counter i
	addi $s0 $s0 -1
	sw $s0 8($gp)
	j FB3
FE3:
	# End of For Statement
	# Releasing Register $s0
	# Available Registers: 19
	# Registers In Use:    0
	# Releasing Register 
	# Available Registers: 19
	# Registers In Use:    0

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
S5: .asciiz "\n"
S6: .asciiz "i = "
S7: .asciiz "\n"
S8: .asciiz "\tj = "
S9: .asciiz "\n"

# Reset alignment to the nearest word and declare global area
.align 2
GA:
