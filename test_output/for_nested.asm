.globl main
.text

main:
	la $gp, GA
	ori $fp, $sp, 0
	# Store the true and false const values
	li $v0 1
	sw $v0, 0($gp)
	sw $zero, 4($gp)


	# Begin CPSL Program

	# For Statement Begin
	# Entering new scope for for loop
	# (NO MIPS EMITTED) Storing symbol i with type integer into symbol table

	# Assigning i the value i
	li $s0 0
	sw $s0 0($fp)
	# Finished assignment of i
	# Loading value from 0($fp) with type integer
	lw $s1 0($fp)
	# Loaded value from i
	# Start of Loop
FB1:
	# Loading constant expression
	li $s2 5
	addi $s2 $s2 1
	beq $s1 $s2 FE1

	# Equal Expression: 1 = 0
	# Folding constant expressions
	# End Equal Expression

	# Begin If Statement
	# Jumping to else(elseif) because if condition is always false
	j IE2

	# Writing expression to output
	# Loading string const
	la $s3 S1
	# Loaded string S1
	li $v0 4
	ori $a0 $s3 0
	syscall
	# Finished writing expression to output

	# End If then block (label ID2, IE2)
	j ID2
IE2:

	# Loading value from 0($fp) with type integer
	lw $s4 0($fp)
	# Loaded value from i

	# Writing expression to output
	# Loading string const
	la $s5 S2
	# Loaded string S2
	li $v0 4
	ori $a0 $s5 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	li $v0 1
	ori $a0 $s4 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	# Loading string const
	la $s6 S3
	# Loaded string S3
	li $v0 4
	ori $a0 $s6 0
	syscall
	# Finished writing expression to output

	# End If(ElseIf) Statement (label ID2)
ID2:

	# For Statement Begin
	# Entering new scope for for loop
	# (NO MIPS EMITTED) Storing symbol j with type integer into symbol table

	# Assigning j the value j
	li $s7 0
	sw $s7 8($gp)
	# Finished assignment of j
	# Loading value from 8($gp) with type integer
	lw $t0 8($gp)
	# Loaded value from j
	# Start of Loop
FB3:
	# Loading constant expression
	li $t1 5
	addi $t1 $t1 1
	beq $t0 $t1 FE3

	# Equal Expression: 1 = 1
	# Folding constant expressions
	# End Equal Expression

	# Begin If Statement
	# No beq emitted because if condition is always true

	# Loading value from 8($gp) with type integer
	lw $t2 8($gp)
	# Loaded value from j

	# Writing expression to output
	# Loading string const
	la $t3 S4
	# Loaded string S4
	li $v0 4
	ori $a0 $t3 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	li $v0 1
	ori $a0 $t2 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	# Loading string const
	la $t4 S5
	# Loaded string S5
	li $v0 4
	ori $a0 $t4 0
	syscall
	# Finished writing expression to output

	# End If then block (label ID4, IE4)
	j ID4
IE4:

	# End If(ElseIf) Statement (label ID4)
ID4:
	# Incrementing counter j
	addi $t0 $t0 1
	sw $t0 8($gp)
	j FB3
FE3:
	# End of For Statement
	# Exited scope for for loop
	# Incrementing counter i
	addi $s1 $s1 1
	sw $s1 0($fp)
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
