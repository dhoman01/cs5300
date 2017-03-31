.globl main
.text

j main
	# (NO MIPS EMITTED) Storing symbol i with type integer into symbol table
	# (NO MIPS EMITTED) Storing symbol a with type integer into symbol table
	# (NO MIPS EMITTED) Storing symbol k with type integer into symbol table
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
	# Begin Repeat Statement (label RP1)
RP1:

	# Loading value from 8($gp) with type integer
	lw $s0 8($gp)
	# Loaded value from i

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
	li $v0 1
	ori $a0 $s0 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0

	# Writing expression to output
	# Loading string const
	la $s0 S2
	# Loaded string S2
	li $v0 4
	ori $a0 $s0 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0

	# Loading value from 8($gp) with type integer
	lw $s0 8($gp)
	# Loaded value from i

	# Plus Expression: $s0 + 1
	addi $s1 $s0 1
	# Releasing Register $s0
	# Available Registers: 17
	# Registers In Use:    1
	# End Plus Expression

	# Assigning i the value at $s1
	sw $s1 8($gp)
	# Releasing Register $s1
	# Available Registers: 18
	# Registers In Use:    0
	# Finished assignment of i
	# Loading value from 8($gp) with type integer
	lw $s1 8($gp)
	# Loaded value from i

	# Lt Expression: $s1 < 5
	slti $s0 $s1 5
	# Releasing Register $s1
	# Available Registers: 17
	# Registers In Use:    1
	# End Lt Expression

	# Repeat Exit Condition (label RP1)
	beq $s0 $zero RP1
	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0

	# Begin Repeat Statement (label RP2)
RP2:

	# Loading value from 8($gp) with type integer
	lw $s0 8($gp)
	# Loaded value from i

	# Writing expression to output
	# Loading string const
	la $s1 S3
	# Loaded string S3
	li $v0 4
	ori $a0 $s1 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s1
	# Available Registers: 17
	# Registers In Use:    1

	# Writing expression to output
	li $v0 1
	ori $a0 $s0 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0

	# Writing expression to output
	# Loading string const
	la $s0 S4
	# Loaded string S4
	li $v0 4
	ori $a0 $s0 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0

	# Loading value from 8($gp) with type integer
	lw $s0 8($gp)
	# Loaded value from i

	# succ($s0)
	addi $s0 $s0 1
	# End succ()

	# Assigning i the value at $s0
	sw $s0 8($gp)
	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0
	# Finished assignment of i
	# Loading value from 8($gp) with type integer
	lw $s0 8($gp)
	# Loaded value from i

	# Lt Expression: $s0 < 5
	slti $s1 $s0 5
	# Releasing Register $s0
	# Available Registers: 17
	# Registers In Use:    1
	# End Lt Expression

	# Repeat Exit Condition (label RP2)
	beq $s1 $zero RP2
	# Releasing Register $s1
	# Available Registers: 18
	# Registers In Use:    0

	# Beginning While Loop (label WB3)
WB3:

	# Loading value from 8($gp) with type integer
	lw $s1 8($gp)
	# Loaded value from i

	# Lt Expression: $s1 < 5
	slti $s0 $s1 5
	# Releasing Register $s1
	# Available Registers: 17
	# Registers In Use:    1
	# End Lt Expression

	# While Header (label WE3)
	beq $s0 $zero WE3	# Releasing Register $s0
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

	# End of While Loop (label WB3 - WE3)
	j WB3
WE3:

	# Assigning k the value k
	li $s0 2
	sw $s0 16($gp)
	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0
	# Finished assignment of k
	# Loading value from 16($gp) with type integer
	lw $s0 16($gp)
	# Loaded value from k

	# Gt Expression: $s0 > 1
	li $s1 1
	sgt $s1 $s0 $s1
	# Releasing Register $s0
	# Available Registers: 17
	# Registers In Use:    1
	# End Gt Expression

	# Writing expression to output
	# Loading string const
	la $s0 S6
	# Loaded string S6
	li $v0 4
	ori $a0 $s0 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s0
	# Available Registers: 17
	# Registers In Use:    1

	# Writing expression to output
	li $v0 1
	ori $a0 $s1 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s1
	# Available Registers: 18
	# Registers In Use:    0

	# Writing expression to output
	# Loading string const
	la $s1 S7
	# Loaded string S7
	li $v0 4
	ori $a0 $s1 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s1
	# Available Registers: 18
	# Registers In Use:    0

	# Loading value from 16($gp) with type integer
	lw $s1 16($gp)
	# Loaded value from k

	# Lt Expression: $s1 < 4
	slti $s0 $s1 4
	# Releasing Register $s1
	# Available Registers: 17
	# Registers In Use:    1
	# End Lt Expression

	# Writing expression to output
	# Loading string const
	la $s1 S8
	# Loaded string S8
	li $v0 4
	ori $a0 $s1 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s1
	# Available Registers: 17
	# Registers In Use:    1

	# Writing expression to output
	li $v0 1
	ori $a0 $s0 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0

	# Writing expression to output
	# Loading string const
	la $s0 S9
	# Loaded string S9
	li $v0 4
	ori $a0 $s0 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0

	# For Statement Begin

	# Assigning a the value a
	li $s0 0
	sw $s0 12($gp)
	# Releasing Register $s0
	# Available Registers: 18
	# Registers In Use:    0
	# Finished assignment of a
	# Loading value from 12($gp) with type integer
	lw $s0 12($gp)
	# Loaded value from a
	# Start of Loop
FB4:
	# Loading constant expression
	li $s1 4
	addi $s1 $s1 1
	beq $s0 $s1 FE4
	# Releasing Register $s1
	# Available Registers: 17
	# Registers In Use:    1

	# Assigning k the value k
	li $s1 0
	sw $s1 16($gp)
	# Releasing Register $s1
	# Available Registers: 17
	# Registers In Use:    1
	# Finished assignment of k
	# Begin Repeat Statement (label RP5)
RP5:

	# Loading value from 16($gp) with type integer
	lw $s1 16($gp)
	# Loaded value from k

	# Equal Expression: $s1 = 0
	li $s2 0
	seq $s2 $s1 $s2
	# Releasing Register $s1
	# Available Registers: 16
	# Registers In Use:    2
	# End Equal Expression

	# Begin If Statement
	beq $s2 $zero IE6
	# Releasing Register $s2
	# Available Registers: 17
	# Registers In Use:    1

	# Loading value from 16($gp) with type integer
	lw $s2 16($gp)
	# Loaded value from k

	# Writing expression to output
	# Loading string const
	la $s1 S10
	# Loaded string S10
	li $v0 4
	ori $a0 $s1 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s1
	# Available Registers: 16
	# Registers In Use:    2

	# Writing expression to output
	li $v0 1
	ori $a0 $s2 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s2
	# Available Registers: 17
	# Registers In Use:    1

	# Writing expression to output
	# Loading string const
	la $s2 S11
	# Loaded string S11
	li $v0 4
	ori $a0 $s2 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s2
	# Available Registers: 17
	# Registers In Use:    1

	# End If then block (label ID6, IE6)
	j ID6
IE6:

	# Loading value from 16($gp) with type integer
	lw $s2 16($gp)
	# Loaded value from k

	# Equal Expression: 1 = $s2
	li $s1 1
	seq $s1 $s1 $s2
	# Releasing Register $s2
	# Available Registers: 16
	# Registers In Use:    2
	# End Equal Expression

	# Begin If Statement
	beq $s1 $zero IE7
	# Releasing Register $s1
	# Available Registers: 17
	# Registers In Use:    1

	# Loading value from 16($gp) with type integer
	lw $s1 16($gp)
	# Loaded value from k

	# Writing expression to output
	# Loading string const
	la $s2 S12
	# Loaded string S12
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
	la $s1 S13
	# Loaded string S13
	li $v0 4
	ori $a0 $s1 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s1
	# Available Registers: 17
	# Registers In Use:    1

	# End If then block (label ID7, IE7)
	j ID7
IE7:

	# Loading value from 16($gp) with type integer
	lw $s1 16($gp)
	# Loaded value from k

	# Not Equal Expression: $s1 <> 3
	li $s2 3
	sne $s2 $s1 $s2
	# Releasing Register $s1
	# Available Registers: 16
	# Registers In Use:    2
	# End Not Equal Expression

	# Begin If Statement
	beq $s2 $zero IE8
	# Releasing Register $s2
	# Available Registers: 17
	# Registers In Use:    1

	# Loading value from 16($gp) with type integer
	lw $s2 16($gp)
	# Loaded value from k

	# Writing expression to output
	# Loading string const
	la $s1 S14
	# Loaded string S14
	li $v0 4
	ori $a0 $s1 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s1
	# Available Registers: 16
	# Registers In Use:    2

	# Writing expression to output
	li $v0 1
	ori $a0 $s2 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s2
	# Available Registers: 17
	# Registers In Use:    1

	# Writing expression to output
	# Loading string const
	la $s2 S15
	# Loaded string S15
	li $v0 4
	ori $a0 $s2 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s2
	# Available Registers: 17
	# Registers In Use:    1

	# End If then block (label ID8, IE8)
	j ID8
IE8:

	# Loading value from 16($gp) with type integer
	lw $s2 16($gp)
	# Loaded value from k

	# Writing expression to output
	# Loading string const
	la $s1 S16
	# Loaded string S16
	li $v0 4
	ori $a0 $s1 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s1
	# Available Registers: 16
	# Registers In Use:    2

	# Writing expression to output
	li $v0 1
	ori $a0 $s2 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s2
	# Available Registers: 17
	# Registers In Use:    1

	# Writing expression to output
	# Loading string const
	la $s2 S17
	# Loaded string S17
	li $v0 4
	ori $a0 $s2 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s2
	# Available Registers: 17
	# Registers In Use:    1

	# End If(ElseIf) Statement (label ID7)
ID7:

	# End If(ElseIf) Statement (label ID8)
ID8:

	# End If(ElseIf) Statement (label ID6)
ID6:

	# Loading value from 16($gp) with type integer
	lw $s2 16($gp)
	# Loaded value from k

	# succ($s2)
	addi $s2 $s2 1
	# End succ()

	# Assigning k the value at $s2
	sw $s2 16($gp)
	# Releasing Register $s2
	# Available Registers: 17
	# Registers In Use:    1
	# Finished assignment of k
	# Loading value from 16($gp) with type integer
	lw $s2 16($gp)
	# Loaded value from k

	# Gt Expression: $s2 > 3
	li $s1 3
	sgt $s1 $s2 $s1
	# Releasing Register $s2
	# Available Registers: 16
	# Registers In Use:    2
	# End Gt Expression

	# Repeat Exit Condition (label RP5)
	beq $s1 $zero RP5
	# Releasing Register $s1
	# Available Registers: 17
	# Registers In Use:    1

	# Loading value from 12($gp) with type integer
	lw $s1 12($gp)
	# Loaded value from a

	# Writing expression to output
	# Loading string const
	la $s2 S18
	# Loaded string S18
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
	li $s1 10
	li $v0 11
	ori $a0 $s1 0
	syscall
	# Finished writing expression to output
	# Releasing Register $s1
	# Available Registers: 17
	# Registers In Use:    1
	# Incrementing counter a
	addi $s0 $s0 1
	sw $s0 12($gp)
	j FB4
FE4:
	# End of For Statement
	# Releasing Register $s0
	# Available Registers: 18
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
S1: .asciiz "i: "
S2: .asciiz " \n"
S3: .asciiz "should only happen once "
S4: .asciiz " \n"
S5: .asciiz "should not happen"
S6: .asciiz "k is "
S7: .asciiz " greater than 1\n"
S8: .asciiz "k is "
S9: .asciiz " less than 4\n"
S10: .asciiz "0="
S11: .asciiz ", "
S12: .asciiz "1="
S13: .asciiz ", "
S14: .asciiz "2="
S15: .asciiz ", "
S16: .asciiz "else="
S17: .asciiz ", "
S18: .asciiz "a="

# Reset alignment to the nearest word and declare global area
.align 2
GA:
