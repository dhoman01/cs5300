# Author: Dustin Homan
# $a0 = n
# Recursively calculate n!
main:
	li $a0, 4
	addi $t0, $a0, 0
	addi $t1, $a0, 0
	factorial: # calcs $a0!
		addi $t1, $t1, -1
		beq $t1, $zero, factend
			mult $t0, $t1
			mflo $t0
			j factorial
	# Print result of factorial
	factend:
		addi $a0, $t0, 0
		li $v0, 1
		syscall

	li $v0, 10
	syscall