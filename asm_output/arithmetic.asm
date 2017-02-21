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

	# Assigning a the value a
	li $25 1
	sw $25 8($gp)
	# Finished assignment of a
	# Assigning b the value b
	li $25 2
	sw $25 12($gp)
	# Finished assignment of b
	# Loading value from 8($gp) with type integer
	lw $25 8($gp)
	# Loaded value from a

	# Loading value from 12($gp) with type integer
	lw $24 12($gp)
	# Loaded value from b

	# Writing expression to output
	li $v0 1
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
	la $24 S5
	# Loaded string S5
	li $v0 4
	ori $a0 $24 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Loading value from 8($gp) with type integer
	lw $24 8($gp)
	# Loaded value from a

	# Loading value from 12($gp) with type integer
	lw $25 12($gp)
	# Loaded value from b

	# Plus Expression: $24 + $25
	add $23 $24 $25
	# End Plus Expression

	# Assigning a the value at $23
	sw $23 8($gp)
	# Finished assignment of a
	# Loading value from 8($gp) with type integer
	lw $23 8($gp)
	# Loaded value from a

	# Loading value from 12($gp) with type integer
	lw $25 12($gp)
	# Loaded value from b

	# Plus Expression: $23 + $25
	add $24 $23 $25
	# End Plus Expression

	# Assigning b the value at $24
	sw $24 12($gp)
	# Finished assignment of b
	# Loading value from 8($gp) with type integer
	lw $24 8($gp)
	# Loaded value from a

	# Loading value from 12($gp) with type integer
	lw $25 12($gp)
	# Loaded value from b

	# Writing expression to output
	li $v0 1
	ori $a0 $24 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	li $v0 1
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
	la $25 S6
	# Loaded string S6
	li $v0 4
	ori $a0 $25 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Loading value from 8($gp) with type integer
	lw $25 8($gp)
	# Loaded value from a

	# Loading value from 12($gp) with type integer
	lw $24 12($gp)
	# Loaded value from b

	# Mult Expression: $25 * $24
	mult $25 $24
	mflo $23
	# End Mult Expression

	# Assigning a the value at $23
	sw $23 8($gp)
	# Finished assignment of a
	# Loading value from 8($gp) with type integer
	lw $23 8($gp)
	# Loaded value from a

	# Loading value from 12($gp) with type integer
	lw $24 12($gp)
	# Loaded value from b

	# Mult Expression: $23 * $24
	mult $23 $24
	mflo $25
	# End Mult Expression

	# Assigning b the value at $25
	sw $25 12($gp)
	# Finished assignment of b
	# Loading value from 8($gp) with type integer
	lw $25 8($gp)
	# Loaded value from a

	# Loading value from 12($gp) with type integer
	lw $24 12($gp)
	# Loaded value from b

	# Writing expression to output
	li $v0 1
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

	# Loading value from 12($gp) with type integer
	lw $24 12($gp)
	# Loaded value from b

	# Loading value from 8($gp) with type integer
	lw $25 8($gp)
	# Loaded value from a

	# Div Expression: $24 / $25
	div $24 $25
	mflo $23
	# End Div Expression

	# Assigning a the value at $23
	sw $23 8($gp)
	# Finished assignment of a
	# Loading value from 12($gp) with type integer
	lw $23 12($gp)
	# Loaded value from b

	# Loading value from 8($gp) with type integer
	lw $25 8($gp)
	# Loaded value from a

	# Div Expression: $23 / $25
	div $23 $25
	mflo $24
	# End Div Expression

	# Assigning b the value at $24
	sw $24 12($gp)
	# Finished assignment of b
	# Loading value from 8($gp) with type integer
	lw $24 8($gp)
	# Loaded value from a

	# Loading value from 12($gp) with type integer
	lw $25 12($gp)
	# Loaded value from b

	# Writing expression to output
	li $v0 1
	ori $a0 $24 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	li $v0 1
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
	la $25 S8
	# Loaded string S8
	li $v0 4
	ori $a0 $25 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Loading value from 8($gp) with type integer
	lw $25 8($gp)
	# Loaded value from a

	# Mod Expression: $25 % 
	li $23 3
	div $25 $23
	mfhi $24
	# End Mod Expression

	# Assigning a the value at $24
	sw $24 8($gp)
	# Finished assignment of a
	# Loading value from 12($gp) with type integer
	lw $24 12($gp)
	# Loaded value from b

	# Loading value from 8($gp) with type integer
	lw $23 8($gp)
	# Loaded value from a

	# Mod Expression: $24 % $23
	div $24 $23
	mfhi $25
	# End Mod Expression

	# Assigning b the value at $25
	sw $25 12($gp)
	# Finished assignment of b
	# Loading value from 8($gp) with type integer
	lw $25 8($gp)
	# Loaded value from a

	# Loading value from 12($gp) with type integer
	lw $23 12($gp)
	# Loaded value from b

	# Writing expression to output
	li $v0 1
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

	# Writing expression to output
	# Loading string const
	la $23 S9
	# Loaded string S9
	li $v0 4
	ori $a0 $23 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Loading value from 12($gp) with type integer
	lw $23 12($gp)
	# Loaded value from b

	# Loading value from 8($gp) with type integer
	lw $25 8($gp)
	# Loaded value from a

	# Minus Expression: $23 - $25
	sub $24 $23 $25
	# End Minus Expression

	# Assigning a the value at $24
	sw $24 8($gp)
	# Finished assignment of a
	# Loading value from 8($gp) with type integer
	lw $24 8($gp)
	# Loaded value from a

	# Loading value from 12($gp) with type integer
	lw $25 12($gp)
	# Loaded value from b

	# Minus Expression: $24 - $25
	sub $23 $24 $25
	# End Minus Expression

	# Assigning b the value at $23
	sw $23 12($gp)
	# Finished assignment of b
	# Loading value from 8($gp) with type integer
	lw $23 8($gp)
	# Loaded value from a

	# Loading value from 12($gp) with type integer
	lw $25 12($gp)
	# Loaded value from b

	# Writing expression to output
	li $v0 1
	ori $a0 $23 0
	syscall
	# Finished writing expression to output

	# Writing expression to output
	li $v0 1
	ori $a0 $25 0
	syscall
	# Finished writing expression to output
	# Newline at end of write()
	addi $a0 $0 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
	addi $v0 $0 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
	syscall
	# Finished newline

	# Exiting program
	li $v0 10
	syscall
	# Exit syscall invoked

	# Writing expression to output
	# Loading string const
	la $25 S10
	# Loaded string S10
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
	.data

# Write out string constants
S1: .asciiz "Beginning Program"
S2: .asciiz "-----------------"
S3: .asciiz "\n"
S4: .asciiz "Assign a = 1 and b = 2"
S5: .asciiz "\na = a+b then b = a+b"
S6: .asciiz "\na = a*b then b = a*b"
S7: .asciiz "\na = b/a then b = b/a"
S8: .asciiz "\na = a%3 then b = b%a"
S9: .asciiz "\na = b-a then b = a-b"
S10: .asciiz "\n--------------"
S11: .asciiz "Ending Program"

# Reset alignment to the nearest word and declare global area
.align 2
GA:
