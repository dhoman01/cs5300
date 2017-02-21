.globl main
.text

main:   la $gp, GA
	ori $fp, $sp, 0
	# Store the true and false const values
	li $a3 1
	sw $a3, 0($gp)
	sw $zero, 4($gp)


	# Begin CPSL Program
	# (NO MIPS EMITTED) Storing symbol a with type integer into symbol table
	# (NO MIPS EMITTED) Storing symbol b with type integer into symbol table
	# (NO MIPS EMITTED) Storing symbol c with type char into symbol table
	# (NO MIPS EMITTED) Storing symbol d with type char into symbol table

	# Writing expression to output
	# Loading string const
	la $25 S1
	# Loaded string S1
	li $v0 4
	ori $a0 $25 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Writing expression to output
	# Loading string const
	la $25 S2
	# Loaded string S2
	li $v0 4
	ori $a0 $25 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Writing expression to output
	# Loading string const
	la $25 S3
	# Loaded string S3
	li $v0 4
	ori $a0 $25 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Reading in input from user
	li $v0 5
	syscall
	sw $v0 8($gp)
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished reading input. Stored input in a at 8($gp)

	# Writing expression to output
	# Loading string const
	la $25 S4
	# Loaded string S4
	li $v0 4
	ori $a0 $25 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Reading in input from user
	li $v0 5
	syscall
	sw $v0 12($gp)
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished reading input. Stored input in b at 12($gp)

	# Loading value from 8($gp) with type integer
	lw $25 8($gp)
	# Loaded value from a

	# Loading value from 12($gp) with type integer
	lw $24 12($gp)
	# Loaded value from b

	# Writing expression to output
	# Loading string const
	la $23 S5
	# Loaded string S5
	li $v0 4
	ori $a0 $23 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	li $v0 1
	ori $a0 $25 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	li $25 10
	li $v0 11
	ori $a0 $25 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	# Loading string const
	la $25 S6
	# Loaded string S6
	li $v0 4
	ori $a0 $25 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	li $v0 1
	ori $a0 $24 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Writing expression to output
	# Loading string const
	la $24 S7
	# Loaded string S7
	li $v0 4
	ori $a0 $24 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Reading in input from user
	li $v0 12
	syscall
	sw $v0 16($gp)
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished reading input. Stored input in c at 16($gp)

	# Writing expression to output
	# Loading string const
	la $24 S8
	# Loaded string S8
	li $v0 4
	ori $a0 $24 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Reading in input from user
	li $v0 12
	syscall
	sw $v0 20($gp)
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished reading input. Stored input in d at 20($gp)

	# Loading value from 16($gp) with type char
	lw $24 16($gp)
	# Loaded value from c

	# Loading value from 20($gp) with type char
	lw $25 20($gp)
	# Loaded value from d

	# Writing expression to output
	# Loading string const
	la $23 S9
	# Loaded string S9
	li $v0 4
	ori $a0 $23 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	li $v0 11
	ori $a0 $24 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	li $24 10
	li $v0 11
	ori $a0 $24 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	# Loading string const
	la $24 S10
	# Loaded string S10
	li $v0 4
	ori $a0 $24 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	li $v0 11
	ori $a0 $25 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Writing expression to output
	# Loading string const
	la $25 S11
	# Loaded string S11
	li $v0 4
	ori $a0 $25 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Writing expression to output
	# Loading string const
	la $25 S12
	# Loaded string S12
	li $v0 4
	ori $a0 $25 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline
	.data

# Write out string constants
S1: .asciiz "Beginning Program"
S2: .asciiz "-----------------\n"
S3: .asciiz "Enter integer value for a:"
S4: .asciiz "\nEnter integer value for b:"
S5: .asciiz "\nFor a you said "
S6: .asciiz "For b you said "
S7: .asciiz "\nEnter character value for c:"
S8: .asciiz "\nEnter character value for d:"
S9: .asciiz "\nFor c you said "
S10: .asciiz "For d you said "
S11: .asciiz "\n--------------"
S12: .asciiz "Ending Program"

# Reset alignment to the nearest word and declare global area
.align 2
GA:
