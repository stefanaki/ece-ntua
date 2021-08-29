            addi  $sp, $sp, -8
            sw    $s2, 4($sp)
            sw    $s1, 0($sp) # save previous values of $s1, $s2
            add   $t1, $zero, $zero # $t1 = result
            add   $t2, $zero, $zero # $t2 = i
FOR:        lw    $s1, 0($a0)
            lw    $s2, 0($a1) # $s1 = v[i], $s2 = u[i]
            mul   $s1, $s1, $s2
            add   $t1, $t1, $s1 # add last product to result
            addi  $a0, $a0, 4
            addi  $a1, $a1, 4 # move u, v pointers one position to the right
            addi  $t2, $t2, 1 # i = i + 1
            slt   $t3, $t2, $a2 # $t3 = flag(is i < n)
            bne   $t3, $zero, FOR # if i < n goto FOR
            add   $v0, $t1, $zero
            lw    $s1, 0($sp)
            lw    $s2, 4($sp) # restore previous values of $s1, $s2
            addi  $sp, $sp, 8
            jr    $ra
