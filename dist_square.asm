# Author: Dustin Homan
# P1=($a0, $a1), P2=($a2, $a3)
# Calculate Dist^2 of P1 and P2
main:
	# Create P1, P2
	li $a0, 4
	li $a1, 4
	li $a2, 6
	li $a3, 6
	
	# Find x-dist
	sub $t0, $a0, $a2 # sub x points
	mult $t0, $t0     # mult result
	mflo $t0
	
	# Find y-dist
	sub $t1, $a1, $a3 # sub y points
	mult $t1, $t1     # mult result
	mflo $t1
	
	# Add x and y dists
	add $a0, $t0, $t1
	
	# Print result
	li $v0, 1
	syscall
	
	# Terminate
	li $v0, 10
	syscall