INCLUDE macros.asm

DATA SEGMENT
    MSGZ DB "Z=$"
    MSGW DB "W=$"
    MSGSUM DB "Z+W=$"
    MSGSUB DB "Z-W=$"
    MSGMINUS DB "Z-W=-$"
    Z DB 0
    W DB 0
	TEN DB DUP(10)				
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
	
	MAIN PROC FAR
			MOV AX,DATA
			MOV DS,AX
			
		START:			
			PRINTSTR MSGZ
			CALL READ_DEC_DIGIT	; read the first digit of Z
			MUL TEN		        ;multiply with 10 the number of the tens		
			LEA DI,Z			
			MOV [DI],AL         ; store the numberoftens*10 of Z			
			CALL READ_DEC_DIGIT	; read the second digit
			ADD [DI],AL			; add the second digit to number_of_tens*10 and we have now the number Z ready and stored
			
			PRINTCH ' '
						
			PRINTSTR MSGW
			CALL READ_DEC_DIGIT ; read the first digit of W	
			MUL TEN             ; multiply with 10 the number of tens
			LEA DI,W			
			MOV [DI],AL         ; store the numberoftens*10 of W
			CALL READ_DEC_DIGIT	; read the second digit of W
			ADD [DI],AL			; add the second digit to number_of_tens*10 and we have now the number W ready and stored
			
			PRINTLN
						
			MOV AL,[DI]			; AL stores W
			LEA DI,Z			; DI has the address of Z
			ADD AL,[DI]			; Z+W
			PRINTSTR MSGSUM
			CALL PRINT_NUM8_HEX	; print the sum
			
			PRINTCH ' '
						
			MOV AL,[DI]		    ; AL has Z
			LEA DI,W			; DI has the address of W
			MOV BL,[DI]         ; BL has W
			
			CMP AL,BL		    ; tsekare an AL<BL
			JB MINUS            ; an AL<BL tote to Z-W tha einai arnitikos
			SUB AL,BL			; an einai thetiki i diafora apla kane afairesi kai typwse
			PRINTSTR MSGSUB     ; xwris - mprosta
			JMP SHOWSUB
		MINUS:                  
			SUB BL,AL			; an i diafora einai arnitikos arithmos kantin thetiko
			MOV AL,BL
			PRINTSTR MSGMINUS   ; kai typwse kai ena - mprosta
		SHOWSUB:
			CALL PRINT_NUM8_HEX	; typwse tin diafora
			PRINTLN
			PRINTLN
			JMP START           ; kai epanelave
	MAIN ENDP
					
	READ_DEC_DIGIT PROC NEAR
		READ:
			READCH        ; macro for read
			CMP AL,48	  ; check if it is decimal digit (48-57)	
			JB READ
			CMP AL,57			
			JA READ
			PRINTCH AL    ; print the digit
			SUB AL,48	  ; sub 48 in order to keep the number in binary form		
			RET
	READ_DEC_DIGIT ENDP
						
	PRINT_NUM8_HEX PROC NEAR
			MOV DL,AL
			AND DL,0F0H		; first hex digit 	
			MOV CL,4
			ROR DL,CL       ; shift the 4 msb's 4 times right
			CMP DL,0		; an to prwto psifio einai 0 (ara ta 4 msb's) agnoise to 	
			JE SKIPZERO
			CALL PRINT_HEX
		SKIPZERO:
			MOV DL,AL
			AND DL,0FH		; second hex digit	
			CALL PRINT_HEX
			RET
	PRINT_NUM8_HEX ENDP
						
	PRINT_HEX PROC NEAR	
			CMP DL,9	; an to digit einai megalytero tou 9 prosthese 55 gia na ftasoume sto 65-70 ASCII CODE pou einai to A-F	
			JG LETTER       ; an einai megalytero pigaine sto letter pou prosthetei 55
			ADD DL,48       ; an to digit einai <=9 tote prosthese 48 gia na ftasoume sto 48-57 (0-9)
			JMP SHOW        ; pigaine sto show pou kanei print to digit
		LETTER:
			ADD DL,55			
		SHOW:
			PRINTCH DL
			RET
	PRINT_HEX ENDP
CODE ENDS
END MAIN
