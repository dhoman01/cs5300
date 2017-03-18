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

	# Equal Expression: 1 = 0
	# Folding constant expressions
	# End Equal Expression

	# Begin If Statement
	# Jumping to else(elseif) because if condition is always false
	j IE2

	# Writing expression to output
	# Loading string const
	la $23 S1
	# Loaded string S1
	li $v0 4
	ori $a0 $23 0
	syscall
	# Finished writing expression to output

	# End If then block (label ID2, IE2)
	j ID2
IE2:

	# Loading value from 0($fp) with type integer
	lw $23 0($fp)
	# Loaded value from i

	# Writing expression to output
	# Loading string const
	la $22 S2
	# Loaded string S2
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
	la $23 S3
	# Loaded string S3
	li $v0 4
	ori $a0 $23 0
	syscall
	# Finished writing expression to output

	# End If(ElseIf) Statement (label ID2)
ID2:

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
FB3:
	# Loading constant expression
	li $22 5
	addi $22 $22 1
	beq $23 $22 FE3

	# Equal Expression: 1 = 1
	# Folding constant expressions
	# End Equal Expression

	# Begin If Statement
	# No beq emitted because if condition is always true

	# Loading value from 8($gp) with type integer
	lw $21 8($gp)
	# Loaded value from j

	# Writing expression to output
	# Loading string const
	la $20 S4
	# Loaded string S4
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
	la $21 S5
	# Loaded string S5
	li $v0 4
	ori $a0 $21 0
	syscall
	# Finished writing expression to output

	# End If then block (label ID4, IE4)
	j ID4
IE4:

	# End If(ElseIf) Statement (label ID4)
ID4:
	# Incrementing counter j
	addi $23 $23 1
	sw $23 8($gp)
	j FB3
FE3:
	# End of For Statement
	# Exited scope for for loop
	# Incrementing counter i
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
S1: .asciiz "This shouldn't have been written"
S2: .asciiz "i = "
S3: .asciiz "\n"
S4: .asciiz "\tj = "
S5: .asciiz "\n"

# Reset alignment to the nearest word and declare global area
.align 2
GA:
