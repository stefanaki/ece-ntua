# $a0 contains *s, that is the address of the first element of s[]
# function returns $v0 = 1 if s is palindrome, $v0 = 0 if it isn't
# using $t1 as a temp pointer to s[0], $t2 as temp a pointer to the last character of s

isPalindrome:
            addi  $sp, $sp, -8
            sw    $s1, 0($sp)
            sw    $s2, 4($sp)

            addi  $v0, $zero, 1 # $v0 equals 1, useful for later comparisons
            addi  $t1, $a0, 0
            addi  $t2, $a0, 0

WHILE:      lb    $t0, 0($t2)
            addi  $t2, $t2, 1 # since chars are 1 byte long, this moves $t2 one position to the right
            bne   $t0, $0, WHILE

            addi  $t2, $t2, -1 # after while loop, $t2 points two positions to the right
                               # of the last element of s
            addi  $t1, $t1, -1

LOOP:       addi  $t1, $t1, 1
            addi  $t2, $t2, -1
            beq   $t1, $t2, END
            slt   $t3, $t2, $t1
            beq   $t3, $v0, END # exit loop if $t2 < $t1, $t2 goes to the left of $t1
            lb    $s1, 0($t1)
            lb    $s2, 0($t2)
            beq   $s1, $s2, LOOP

END:        slt   $t3, $t1, $t2 # $t1 < $t2
            nor   $t3, $t3, $t3 # equivalent to nor($t3, $t3) = not($t3) = $t1 >= $t2
            addi  $v0, $t3, 0

            lw    $s1, 0($sp)
            lw    $s2, 4($sp)
            addi  $sp, $sp, 8
            jr    $ra
