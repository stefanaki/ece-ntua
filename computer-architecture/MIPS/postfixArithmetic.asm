postfixArithmetic:
            addi  $sp, $sp, -8
            sw    $ra, 0($sp)
            sw    $a0, 4($sp)

WHILE:      lb    $t0, 0($a0)           # Load current character on $t0
            beq   $t0, '$', EXIT
            beq   $t0, '+', CALCULATE
            beq   $t0, '-', CALCULATE
            beq   $t0, '*', CALCULATE
            beq   $t0, '/', CALCULATE   # If 
            addi  $sp, $sp, -4
            addi  $t0, $t0, -48
            add   $t1, $zero, $t0
            sw    $t1, 0($sp)
            addi  $a0, $a0, 1
            j     WHILE


# Procedure that calculates the needed operations.
# Input arguements: $t2, $t3
# Output register: $t4


CALCULATE:
            lw    $t3, 0($sp)
            lw    $t2, 4($sp)
            beq   $t0, '+', ADD
            beq   $t0, '-', SUB
            beq   $t0, '*', MUL
            beq   $t0, '/', DIV

ADD:        add   $t4, $t2, $t3
            addi  $sp, $sp, 4
            sw    $t4, 0($sp)
            addi  $a0, $a0, 1
            j     WHILE

SUB:        sub   $t4, $t2, $t3
            addi  $sp, $sp, 4
            sw    $t4, 0($sp)
            addi  $a0, $a0, 1
            j     WHILE

MUL:        mult  $t2, $t3
            mflo  $t4
            addi  $sp, $sp, 4
            sw    $t4, 0($sp)
            addi  $a0, $a0, 1
            j     WHILE

DIV:        div    $t2, $t3
            mflo   $t4
            addi   $sp, $sp, 4
            sw     $t4, 0($sp)
            addi   $a0, $a0, 1
            j      WHILE

EXIT:       lw     $v0, 0($sp)
            lw     $ra, 4($sp)
            lw     $a0, 8($sp)
            addi   $sp, $sp, 12
            jr     $ra
