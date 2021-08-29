
PRINT MACRO CHAR
    PUSH AX
    PUSH DX      ;store register values that will be changed
    MOV DL,CHAR
    MOV AH,2
    INT 21H
    POP DX
    POP AX
ENDM  

NEWLINE MACRO
    PUSH BX
    MOV BL,13
    PRINT BL
    MOV BL,10 ;ASCII code for new line
    PRINT BL
    POP BX
ENDM 

PRINT_BYTE MACRO BYTE
    PUSH DX
    MOV DL,BYTE
    AND DL,0F0H ;first hex digit
    SHR DL,4
    CALL PRINT_HEX_DIGIT
    MOV DL,BYTE
    AND DL,0FH ;second hex digit
    CALL PRINT_HEX_DIGIT
    POP DX
ENDM  




DATA_SEG SEGMENT 
    TABLE DB 128 DUP(?)  
DATA_SEG ENDS 


CODE_SEG SEGMENT
    ASSUME CS:CODE_SEG, DS:DATA_SEG  
    
PRINT_DEC PROC NEAR      
    PUSH AX
    PUSH BX
    MOV AH,0
    MOV BL,10   ; divide with 10
    DIV BL      ; AL now contains tens and AH contains ones
    ADD AL,30H  ; ASCII code of digits 0-9
    PRINT AL    ; print tens
    ADD AH,30H  ; ASCII code of digits 0-9  
    PRINT AH    ; print ones
    POP BX
    POP AX
    RET   
PRINT_DEC ENDP  


PRINT_HEX_DIGIT PROC NEAR
    PUSH DX
    CMP DL,9 ;hex digit in DL, compare with 9 to find whether it is 0-9 or A-F
    JG ADDR1
    SUB DL,07H ;must add 30 if hex digit is 0-9 (ASCII code)

ADDR1:
    ADD DL,37H ;must add 37 if hex digit is A-F (ASCII code)
    PRINT DL
    POP DX
    RET
PRINT_HEX_DIGIT ENDP
    
    

MAIN PROC FAR
    MOV AX,DATA_SEG
    MOV DS,AX
    
    MOV BL,129    ;   elements
    MOV DI,0      ;   index

FILL:                  
    DEC BL             ; first element is 128
    MOV TABLE[DI],BL   ; store it in the array
    INC DI             ;next array element
    CMP BL,1           ;finish fill if 1
    JNE FILL
    MOV DI,0
    MOV AX,0
    INC DI             ; first odd is at index 1 (127)

ADD_ODD:      
         
    MOV BL,TABLE[DI]  ; get the odd number
    MOV BH,0
    ADD AX,BX         ; add odd number to AX
    INC DI 
    INC DI
    CMP DI,129
    JNE ADD_ODD
    MOV BL,64
    DIV BL         ; divide with 64 to find mean value, result in AL     
    CALL PRINT_DEC
    NEWLINE  
  
    MOV DI,0
    MOV BL,TABLE[DI] ;min, initialization  
    MOV BH,TABLE[DI] ;max, initialization
  
  
COMPARE:
    INC DI
    CMP BL,TABLE[DI]
    JB NOT_MIN
    MOV BL,TABLE[DI] ;update min

NOT_MIN:
    CMP BH,TABLE[DI]
    JA NOT_MAX
    MOV BH,TABLE[DI] ;update max

NOT_MAX:
    CMP DI,127
    JNE COMPARE ;finish if DI reaches 127 (array from 0 to 127)
    PRINT_BYTE BH ;max
    PRINT " "
    PRINT_BYTE BL ;min

END:MOV AX,4C00H ;end
    INT 21H      

MAIN ENDP
CODE_SEG ENDS 
END MAIN 