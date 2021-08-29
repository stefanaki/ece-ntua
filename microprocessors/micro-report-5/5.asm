INCLUDE macros.asm

DATA SEGMENT
	STARTPROMPT DB "START(Y,N):$"    ;begin message
	ERRORMSG DB "ERROR$"		 ;error message
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA
	
	MAIN PROC FAR
			MOV AX,DATA
			MOV DS,AX
			
			PRINTSTR STARTPROMPT
		START:			                ; read first char 
			READCH
			CMP AL,'N'			; if it is = N
			JE FINISH			;finish
			CMP AL,'Y'			; if it is = Y
			JE CONT				; continute
			JMP START
		CONT:
			PRINTCH AL			; print first char
			PRINTLN
			PRINTLN
		NEWTEMP:
			MOV DX,0
			MOV CX,3			; read 3 digits
		READTEMP:	 	        ;input
			CALL HEX_KEYB		
			CMP AL,'N'		;check if we need to terminate
			JE FINISH
						;put all the digits at DX
			PUSH CX
			DEC CL			
			ROL CL,2		
			MOV AH,0
			ROL AX,CL			
			OR DX,AX			
			POP CX
			LOOP READTEMP
			
			PRINTTAB
			MOV AX,DX
			CMP AX,2047			; V<=2 ?
			JBE BRANCH1
			CMP AX,3071			; V<=3?
			JBE BRANCH2
			PRINTSTR ERRORMSG	;V>3?
			PRINTLN
			JMP NEWTEMP
			
		BRANCH1:		; first branch V<=2, T=800*V div 4095
			MOV BX,800
			MUL BX
			MOV BX,4095
			DIV BX
			JMP SHOWTEMP
		BRANCH2:		;second branch 2<V<=3, T=((3200*V) div 4095)-1200
			MOV BX,3200
			MUL BX
			MOV BX,4095
			DIV BX
			SUB AX,1200
		SHOWTEMP:
			CALL PRINT_DEC16	;akeraio meros (AX)
						;klasmatiko meros = (ypoloipo*10) div 4095
			MOV AX,DX
			MOV BX,10
			MUL BX
			MOV BX,4095
			DIV BX
			
			PRINTCH ','			
			ADD AL,48			;ascii code
			PRINTCH AL			;print klasmatiko meros
			PRINTLN
			JMP NEWTEMP
			
		FINISH:
			PRINTCH AL
			EXIT
	MAIN ENDP
						;input hex digit at AL
	HEX_KEYB PROC NEAR	
		READ:
			READCH
			CMP AL,'N'			;=N ?
			JE RETURN
			CMP AL,48			;<0 ?
			JL READ
			CMP AL,57			;>9 ?
			JG LETTER
			PRINTCH AL
			SUB AL,48			;ASCII code
			JMP RETURN
		LETTER:					;A...F
			CMP AL,'A'			;<A ?
			JL READ
			CMP AL,'F'			;>F ?
			JG READ
			PRINTCH AL
			SUB AL,55			;ASCII code
		RETURN:
			
			RET
	HEX_KEYB ENDP
							;print 16bit decimal number from AX
	PRINT_DEC16 PROC NEAR	
			PUSH DX
			
			MOV BX,10			
			MOV CX,0			;counter of digits
		GETDEC:			                ;get the digits
			MOV DX,0			;number mod 10 (ypoloipo)
			DIV BX				;div with 10
			PUSH DX				
			INC CL
			CMP AX,0			;number div 10 = 0 ? (piliko)
			JNE GETDEC
		PRINTDEC:				;print digits
			POP DX
			ADD DL,48			;ASCII code
			PRINTCH DL
			LOOP PRINTDEC
			
			POP DX
			RET
	PRINT_DEC16 ENDP
CODE ENDS
END MAIN
