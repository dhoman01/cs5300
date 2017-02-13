.globl main
.text

main:   la $gp, GA
        li $t0, 1
        sw $t0, 0($gp)
        li $t0, 2
        sw $t0, 4($gp)
        lw $t0, 0($gp)
        li $v0, 1
        ori $a0, $t0, 0
        syscall
        # Next three lines from http://stackoverflow.com/questions/9875468/printing-newline-in-mips
        addi $a0, $0, 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
        addi $v0, $0, 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
        syscall
        lw $t0, 4($gp)
        li $v0, 1
        ori $a0, $t0, 0
        syscall
        addi $a0, $0, 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
        addi $v0, $0, 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
        syscall
        lw $t0, 0($gp)
        lw $t1, 4($gp)
        add $t2, $t0, $t1
        sw $t2, 0($gp)
        lw $t0, 0($gp)
        lw $t1, 4($gp)
        add $t2, $t0, $t1
        sw $t2, 4($gp)
        lw $t0, 0($gp)
        li $v0, 1
        ori $a0, $t0, 0
        syscall
        addi $a0, $0, 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
        addi $v0, $0, 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
        syscall
        lw $t0, 4($gp)
        li $v0, 1
        ori $a0, $t0, 0
        syscall
        addi $a0, $0, 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
        addi $v0, $0, 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
        syscall
        lw $t0, 0($gp)
        lw $t1, 4($gp)
        mult $t0, $t1
        mflo $t2
        sw $t2, 0($gp)
        lw $t0, 0($gp)
        lw $t1, 4($gp)
        mult $t0, $t1
        mflo $t2
        sw $t2, 4($gp)
        lw $t0, 0($gp)
        li $v0, 1
        ori $a0, $t0, 0
        syscall
        addi $a0, $0, 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
        addi $v0, $0, 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
        syscall
        lw $t0, 4($gp)
        li $v0, 1
        ori $a0, $t0, 0
        syscall
        addi $a0, $0, 0xA #ascii code for LF, if you have any trouble try 0xD for CR.
        addi $v0, $0, 0xB #syscall 11 prints the lower 8 bits of $a0 as an ascii character.
        syscall
        .data
GA: