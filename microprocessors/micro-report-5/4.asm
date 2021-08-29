


DATA SEGMENT
S DB 20 DUP(?)
DATA ENDS



CODE SEGMENT
    ASSUME CS:CODE, DS:DATA

PRINT MACRO CHAR
    PUSH AX
    PUSH DX ;store register values that will be changed
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

MAIN PROC FAR
  
  REPEAT:
    MOV CX,0 ;read at most 20 times
    MOV DI,0
  
  READ:  
    CALL INPUT 
    CMP AL,13
    JE BEGIN
    MOV S[DI],AL ;save input (AL)
    INC DI       ; increase DI to read the next number and store it
    INC CX       ; increase counter of data
    CMP CX,20    ; if we have read 20 data we stop reading
    JB READ    ; loop until finish reading
    
    
    
  BEGIN:  
    MOV DI,0
    MOV DX,CX  ; save counter of data
    NEWLINE
  LETTERS:
    MOV AL,S[DI]
    CMP AL,97
    JB SKIP2
    CMP AL,122
    JA SKIP2
    SUB AL,32 ;convert to UPPERCASE
    PRINT AL  ;print if it's a letter
  SKIP2:
    INC DI
    LOOP LETTERS    
    PRINT "-"
    MOV CX,DX
    MOV DI,0
  
  NUMBERS:
    MOV AL,S[DI]
    CMP AL,48
    JB SKIP
    CMP AL,57
    JA SKIP
    PRINT AL ;print if it's a number
  SKIP:
    INC DI
    LOOP NUMBERS 
    NEWLINE
    JMP REPEAT
MAIN ENDP

INPUT PROC NEAR
  IGNORE:
    MOV AH,8
    INT 21H   ;read from keyboard, result in AL
    CMP AL,61 ;check if it is =
    JE QUIT   ; if it is equal exit
    CMP AL,13 ; if we input enter then return
    JE  ENTER
    CMP AL,48 ;ignore if not a-z(97-122) or 0-9(48-57)
    JB IGNORE
    CMP AL,122
    JA IGNORE
    CMP AL,57
    JBE FINISH
    CMP AL,97
    JB IGNORE
  FINISH:  
    PRINT AL
    RET 
  ENTER: 
    RET
  QUIT:
    MOV AX,4C00H ;end
    INT 21H    
INPUT ENDP

CODE ENDS
END MAIN